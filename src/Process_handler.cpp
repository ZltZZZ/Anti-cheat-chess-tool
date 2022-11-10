//#define DEBUG_IN_PROCESS_HANDLER

#include "Process_handler.h"
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

    // Wait for initializing of engine (synchronize engine and app) (send a msg and wait answ)
    send_message(pipe_in_w, "h\n");
    wait_for_answ(pipe_out_r);

    return PROCESS_CREATE_OK;
}

void close_stream_handle(HANDLE* stream) {
    if (stream != NULL) CloseHandle(*stream);
}

void wait_for_answ(HANDLE* pipe_out_r) {
    DWORD bites_aval = 0; // Bites availible in pipe's buffer

    // Busy waits msg (block curr thread)
    while (bites_aval <= 0)
    {
        PeekNamedPipe(*pipe_out_r, NULL, NULL, NULL, &bites_aval, NULL);
    }
}

void send_message(HANDLE* pipe_in_w, const char msg[MAX_MSG_SIZE]) {
    DWORD dwWritten;

    WriteFile(*pipe_in_w, msg, strlen(msg), &dwWritten, NULL);
}
