//#define DEBUG_IN_PROCESS_HANDLER

#include "Process_handler.h"
#include <ctime>
#ifdef DEBUG_IN_PROCESS_HANDLER
#include <stdio.h>
#endif // DEBUG_IN_PROCESS_HANDLER

error_process create_process(LPCWSTR path, HANDLE* pipe_in_w, HANDLE* pipe_out_r) {
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    SECURITY_ATTRIBUTES saAttr;
    HANDLE pipe_in_r = NULL;               // Used by engine to recieve msg from app
    HANDLE pipe_out_w = NULL;              // Used by engine to send msg to app

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
        path,           // Module name
        NULL,           // No Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        TRUE,           // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi)            // Pointer to PROCESS_INFORMATION structure
        )
    {
        return PROCESS_CREATE_FAIL;
    }

    // Close useless handle of process
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Close useless handles of pipes sides of child process
    close_stream_handle(&pipe_in_r);
    close_stream_handle(&pipe_out_w);

    return PROCESS_CREATE_OK;
}

void close_stream_handle(HANDLE* stream) {
    if (stream != NULL) CloseHandle(*stream);
}

void wait_for_answ(HANDLE* pipe_out_r) {
    DWORD bites_aval = 0;     // Bites availible in pipe's buffer
    time_t time_start, time_curr;   // Avoid infinite loop by setting a waiting timer

    time(&time_start);
    time(&time_curr);

    // Busy waits msg (block curr thread)
    while (bites_aval <= 0 && difftime(time_curr, time_start) < WAITING_TIME)
    {
        PeekNamedPipe(*pipe_out_r, NULL, NULL, NULL, &bites_aval, NULL);
        time(&time_curr);
    }
}

void send_message(HANDLE* pipe_in_w, const char msg[MAX_MSG_SIZE]) {
    DWORD dwWritten;

    WriteFile(*pipe_in_w, msg, strlen(msg), &dwWritten, NULL);
}

void recieve_message(HANDLE* pipe_out_r, char* buff) {
    DWORD dwRead;

    ReadFile(*pipe_out_r, buff, MAX_MSG_SIZE, &dwRead, NULL);
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