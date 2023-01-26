#include "UCI_API.h"

error_process create_process(std::wstring path, HANDLE* pipe_in_w, HANDLE* pipe_out_r) {
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    SECURITY_ATTRIBUTES saAttr;
    HANDLE pipe_in_r = NULL;               // Used by engine to recieve msg from app
    HANDLE pipe_out_w = NULL;              // Used by engine to send msg to app
    HANDLE ghJob = CreateJobObject(NULL, NULL); // GLOBAL

    if (ghJob != NULL)
    {
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };

        // Configure all child processes associated with the job to terminate when the
        jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
        if (0 == SetInformationJobObject(ghJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli)))
        {
            return PROCESS_CREATE_FAIL;
        }
    }
    else return PROCESS_CREATE_FAIL;

    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    ZeroMemory(&saAttr, sizeof(SECURITY_ATTRIBUTES));
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create 2 pipes
    if (!CreatePipe(&pipe_in_r, pipe_in_w, &saAttr, 0))
        return PROCESS_CREATE_FAIL;

    if (!CreatePipe(pipe_out_r, &pipe_out_w, &saAttr, 0))
        return PROCESS_CREATE_FAIL;

    // Fill standart options for console invisible application
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.wShowWindow = SW_HIDE;            // Hide console window
    si.dwFlags |= STARTF_USESTDHANDLES;  // Use pipes instead of default std_in/out
    si.hStdInput = pipe_in_r;
    si.hStdOutput = pipe_out_w;
    si.hStdError = pipe_out_w;

    // Start the child process. 
    if (!CreateProcess(
        path.c_str(),           // Module name
        NULL,           // No Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        TRUE,           // Set handle inheritance to TRUE
        CREATE_NO_WINDOW,// Creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)            // Pointer to PROCESS_INFORMATION structure
        )
    {
        return PROCESS_CREATE_FAIL;
    }

    if (ghJob)
    {
        if (0 == AssignProcessToJobObject(ghJob, pi.hProcess))
        {
            return PROCESS_CREATE_FAIL;
        }
    }

    // Close useless handle of process
    //CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Close useless handles of pipes sides of child process
    close_stream_handle(&pipe_in_r);
    close_stream_handle(&pipe_out_w);

    return PROCESS_CREATE_OK;
}

void close_stream_handle(HANDLE* stream) {
    if (stream != NULL) CloseHandle(*stream);
}

error_process wait_for_answ(HANDLE* pipe_out_r) {
    DWORD bites_aval = 0;     // Bites availible in pipe's buffer
    time_t time_start, time_curr;   // Avoid infinite loop by setting a waiting timer

    time_start = clock();
    time_curr = clock();

    // Busy waits msg (block curr thread)
    while (bites_aval <= 0 && (time_curr - time_start) / 1000.0 < WAITING_TIME)
    {
        PeekNamedPipe(*pipe_out_r, NULL, NULL, NULL, &bites_aval, NULL);
        time_curr = clock();
    }

    if ((time_curr - time_start) / 1000.0 >= WAITING_TIME) return PROCESS_TIMEOUT;
    else return PROCESS_OK;
}

error_process wait_for_answ(HANDLE* pipe_out_r, int w_time_ms) {
    DWORD bites_aval = 0;     // Bites availible in pipe's buffer
    time_t time_start, time_curr;   // Avoid infinite loop by setting a waiting timer

    time_start = clock();
    time_curr = clock();

    // Busy waits msg (block curr thread)
    while (bites_aval <= 0 && (time_curr - time_start) / 1000.0 < w_time_ms)
    {
        PeekNamedPipe(*pipe_out_r, NULL, NULL, NULL, &bites_aval, NULL);
        time_curr = clock();
    }

    if ((time_curr - time_start) / 1000.0 >= w_time_ms) return PROCESS_TIMEOUT;
    else return PROCESS_OK;
}

void send_message(HANDLE* pipe_in_w, const char msg[MAX_MSG_SIZE]) {
    DWORD dwWritten;

    WriteFile(*pipe_in_w, msg, strlen(msg), &dwWritten, NULL);
}

void recieve_message(HANDLE* pipe_out_r, char* buff) {
    DWORD dwRead;

    ReadFile(*pipe_out_r, buff, MAX_MSG_SIZE - 1, &dwRead, NULL);
}

void recieve_char(HANDLE* pipe_out_r, char* c_buff) {
    DWORD dwRead;

    ReadFile(*pipe_out_r, c_buff, 1, &dwRead, NULL);
}

error_process check_pipe(HANDLE* pipe_out_r) {
    DWORD bites_aval = 0; // Bites availible in pipe's buffer

    PeekNamedPipe(*pipe_out_r, NULL, NULL, NULL, &bites_aval, NULL);

    if (bites_aval > 0) {
        return PROCESS_PIPE_MSG_AVAILABLE;
    }
    else {
        return PROCESS_PIPE_NO_MSG;
    }
}

void clean_pipe_out(HANDLE* pipe_out_r) {
    char useless_buff[MAX_MSG_SIZE] = { '\0' };

    while (check_pipe(pipe_out_r) != PROCESS_PIPE_NO_MSG)
    {
        recieve_message(pipe_out_r, useless_buff);
    }
}

engine_error UCI_Engine::load()
{
	// Creates an engine process (run engine.exe).
	if (create_process(this->path_to_engine, &this->pipe_in_w, &this->pipe_out_r) == PROCESS_CREATE_OK) {
        this->setup();
		this->state = WORKING;
		return ENGINE_OK;
	}
	else {
		return ENGINE_LOAD_FAIL;
	}
}

void UCI_Engine::close()
{
	this->send_command(_quit);
	close_stream_handle(&this->pipe_in_w);
	close_stream_handle(&this->pipe_out_r);
	this->pipe_in_w = NULL;
	this->pipe_out_r = NULL;
	this->state = NOT_LOADED;
}

engine_error UCI_Engine::wait_answ()
{
	if (wait_for_answ(&this->pipe_out_r) == PROCESS_OK) return ENGINE_OK;
	else return ENGINE_TIMEOUT;
}

engine_error UCI_Engine::wait_answ(int wait_time_ms) {
	if (wait_for_answ(&this->pipe_out_r, wait_time_ms) == PROCESS_OK) return ENGINE_OK;
	else return ENGINE_TIMEOUT;
}

bool UCI_Engine::check_answ()
{
	if (check_pipe(&this->pipe_out_r) != PROCESS_PIPE_NO_MSG) return true;
	else return false;
}

std::string UCI_Engine::get_answ_string()
{
	char answer[MAX_MSG_SIZE] = { 0 };
	recieve_message(&this->pipe_out_r, answer);

	return std::string(answer);
}

char UCI_Engine::get_answ_char()
{
	char answer = '\0';
	recieve_char(&this->pipe_out_r, &answer);

	return answer;
}

engine_state UCI_Engine::get_state()
{
	return this->state;
}

engine_error UCI_Engine::setup()
{
    this->send_command(_uci);
    if (this->wait_answ() == ENGINE_TIMEOUT) {
        return ENGINE_TIMEOUT;
    }

    this->send_command(_ucinewgame);

    this->send_command(_setoption, _name, "MultiPV", _value, this->multipv);
    this->send_command(_setoption, _name, "Threads", _value, this->cpu);
    this->send_command(_setoption, _name, "Hash", _value, this->hash);

    clean_pipe_out(&this->pipe_out_r);
    return ENGINE_OK;
}

void UCI_Engine::set_options(int cpu, int multipv, int hash, int movetime)
{
    this->cpu = cpu;
    this->multipv = multipv;
    this->hash = hash;
    this->movetime = movetime;
}

void UCI_Engine::start_analyse()
{
    this->send_command(_go, _movetime, this->movetime);
}

void UCI_Engine::set_position(std::string fen)
{
    this->send_command(_position, _fen, fen);
}

void UCI_Engine::parse_analisys_output(engine_line* line)
{
    char word[MAX_WORD2_SIZE] = { '\0' };
    int word_indx = 0, // Index of word string
        line_indx = 0; // Index of line
    char c_buff;
    bool is_word = false,  // Word flag
        is_line = false,  // If word == multipv, than flag true
        is_move = false;  // If word == pv, than flag true

    // Clean old info from engine, before reciving new info 
    clean_pipe_out(&this->pipe_out_r);

    // Continue get data until receive "bestmove" word from engine
    while (memcmp(word, "bestmove", 9) != 0)
    {
        wait_for_answ(&this->pipe_out_r);
        recieve_char(&this->pipe_out_r, &c_buff);

        if (c_buff == ' ' || c_buff == '\n') { // null-characters zero word string
            if (is_word) {
                if (is_line) {
                    line_indx = atoi(word); // Remember index of line
                    is_line = false;
                }
                else if (is_move) { // Remember move from remembered line
                    memcpy(line[line_indx - 1].move, word, sizeof(char) * MAX_MOVE_SIZE);
                    is_move = false;
                }

                is_word = false;
                word_indx = 0;
                memset(word, '\0', sizeof(char) * MAX_WORD2_SIZE);
            }
        }
        else
        {
            if (is_word == false) is_word = true;

            // Gather word
            word[word_indx++] = c_buff;

            if (memcmp(word, "multipv", 8) == 0) {
                is_line = true;
                is_word = false; // This is a little crutch to avoid logical error.
                word_indx = 0;
                memset(word, '\0', sizeof(char) * MAX_WORD2_SIZE);
            }
            else if (memcmp(word, "pv", 3) == 0) {
                is_move = true;
                is_word = false; // The same as upper.
                word_indx = 0;
                memset(word, '\0', sizeof(char) * MAX_WORD2_SIZE);
            }
        }
    }
}
