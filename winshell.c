#include <minwindef.h>
#include <processenv.h>
#include <windows.h>

inline DWORD write(HANDLE file, LPCVOID buffer, DWORD size) {
    DWORD written;
    WriteFile(file, buffer, size, &written, NULL);
    return written;
}

inline DWORD read(HANDLE file, LPVOID buffer, DWORD size) {
    DWORD read;
    ReadFile(file, buffer, size, &read, NULL);
    return read;
}

int main() {
    HANDLE stdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE stderr = GetStdHandle(STD_ERROR_HANDLE);
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);
    LPSTR cwd = __builtin_alloca(256);
    DWORD cwd_size;
    LPSTR prompt = __builtin_alloca(256);
    #define prompt_length cwd_size // Alias
    while (TRUE) {
        cwd_size = GetCurrentDirectoryA(256, cwd);
        write(stdout, cwd, cwd_size);
        write(stdout, "> ", 2);
        prompt_length = read(stdin, prompt, 256);
        prompt[prompt_length - 2] = 0;
        if (!strncmp(prompt, "cd ", 3)) {
            SetCurrentDirectoryA(prompt + 3);
            continue;
        }
        if (!strncmp(prompt, "exit", 5)) break;
        if (!strncmp(prompt, "out ", 4)) {
            write(stdout, prompt + 4, strlen(prompt + 4));
            write(stdout, "\n", 1);
            continue;
        }
        if (!strncmp(prompt, "lsdir", 6)) {
            system("dir");
            continue;
        }
        if (!strncmp(prompt, "cmd ", 4)) {
            prompt[0] = '/';
            prompt[1] = 'c';
            prompt[2] = ' ';
            CreateProcessA("C:\\Windows\\System32\\cmd.exe", prompt, NULL, NULL, TRUE, 0, NULL, cwd, &si, &pi);
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            continue;
        }
        CreateProcessA(NULL, prompt, NULL, NULL, TRUE, 0, NULL, cwd, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}