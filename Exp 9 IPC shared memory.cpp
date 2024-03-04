#include <stdio.h>
#include <windows.h>

#define BUF_SIZE 256
#define SHM_NAME "Local\\MySharedMemory"

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // use paging file
        NULL,                    // default security
        PAGE_READWRITE,          // read/write access
        0,                       // maximum object size (high-order DWORD)
        BUF_SIZE,                // maximum object size (low-order DWORD)
        SHM_NAME                 // name of mapping object
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        BUF_SIZE);

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());

        CloseHandle(hMapFile);

        return 1;
    }

    printf("Enter a message to share: ");
    fgets((char*)pBuf, BUF_SIZE, stdin);

    printf("Shared memory message: %s\n", pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

