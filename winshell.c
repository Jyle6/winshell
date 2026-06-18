#include <minwindef.h>
#include <processenv.h>
#include <windows.h>

DWORD write(HANDLE file, LPCVOID buffer, DWORD size) {
    DWORD written;
    WriteFile(file, buffer, size, &written, NULL);
    return written;
}

DWORD read(HANDLE file, LPVOID buffer, DWORD size) {
    DWORD read;
    ReadFile(file, buffer, size, &read, NULL);
    return read;
}

int main() {
    HANDLE stdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE stderr = GetStdHandle(STD_ERROR_HANDLE);
    LPSTR cwd = __builtin_alloca(256);
    DWORD cwd_size;
    while (TRUE) {
        cwd_size = GetCurrentDirectoryA(256, cwd);
        write(stdout, cwd, cwd_size);
        write(stdout, "> ", 2);
    }
}