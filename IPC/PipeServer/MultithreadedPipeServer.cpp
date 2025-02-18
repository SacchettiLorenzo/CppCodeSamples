//https://learn.microsoft.com/en-us/windows/win32/ipc/using-pipes
#include <iostream>
#include <Windows.h>
#include <tchar.h> //gengeric text macros 
#include <strsafe.h>

#define BUFSIZE 512

//LPVOID is a Windows API typdef for void*
DWORD WINAPI InstanceThread(LPVOID);
VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);

//_tmain is a Microsoft extension of main
int _tmain()
{
    BOOL fConnected = FALSE;
    DWORD dwthreadId = 0;
    HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;
    LPCTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");

    for (;;) {
        _tprintf(TEXT("\n Awaiting client connection on %s\n"),lpszPipename);
        hPipe = CreateNamedPipe(
            lpszPipename,                                           // pipe name
            PIPE_ACCESS_DUPLEX,                                     // read/write access
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  // message type pipe mode | message-read mode | blocking mode
            PIPE_UNLIMITED_INSTANCES,                               // unlimited (max) number of instances
            BUFSIZE,                                                // output buffer size
            BUFSIZE,                                                // input buffer size
            0,                                                      // client time-out        
            NULL                                                    // default security attribute
        );

        if (hPipe == INVALID_HANDLE_VALUE) {
            _tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
            return -1;
        }

        //wait the client to connect; if succedes the functionr eturn a non zero value

        fConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

        if (fConnected) {
            printf("Client connected \n");

            // Crete thread
            hThread = CreateThread(
                NULL,           // security attribute
                0,              // stack size
                InstanceThread, // thread proc
                (LPVOID)hPipe,  // thread parameter
                0,
                &dwthreadId     // reference to the variable that hold thread id
            );

            if (hThread == NULL) {
                _tprintf(TEXT("Failed on thread creation: %d\n"), GetLastError());
                return -1;
            }
            else {
                CloseHandle(hThread);
            }
        }
        else {
            CloseHandle(hPipe);
        }
    }
    return 0;

}


//thread processing function that read and reply to a client
DWORD WINAPI InstanceThread(LPVOID lpvParam) {
    HANDLE hHeap = GetProcessHeap();
    TCHAR* pchRequest = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));
    TCHAR* pchReply = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

    DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0;
    BOOL fSuccess = FALSE;
    HANDLE hPipe = NULL;

    //more error check
    if (pchRequest == NULL) {
        printf("\nERROR - Pipe Server Failure:\n");
        printf("   InstanceThread got an unexpected NULL heap allocation.\n");
        printf("   InstanceThread exitting.\n");
        if (pchReply != NULL) HeapFree(hHeap, 0, pchReply);
        return (DWORD)-1;
    }

    if (pchReply == NULL)
    {
        printf("\nERROR - Pipe Server Failure:\n");
        printf("   InstanceThread got an unexpected NULL heap allocation.\n");
        printf("   InstanceThread exitting.\n");
        if (pchRequest != NULL) HeapFree(hHeap, 0, pchRequest);
        return (DWORD)-1;
    }

    printf("InstanceThread created, receiving and processing messages.\n");

    //pipe is passed as parameter at thread creation
    hPipe = (HANDLE)lpvParam;

    while (true) {
        fSuccess = ReadFile(
            hPipe,
            pchRequest,                 // buffer to receive data
            BUFSIZE * sizeof(TCHAR),    // size of the buffer
            &cbBytesRead,               // number of bytes read
            NULL                        // not overlapper I/O
        );

        //unable to read file or no byte read
        if (!fSuccess || cbBytesRead == 0) {

            if (GetLastError() == ERROR_BROKEN_PIPE)
            {
                _tprintf(TEXT("InstanceThread: client disconnected.\n"));
            }
            else
            {
                _tprintf(TEXT("InstanceThread ReadFile failed, GLE=%d.\n"), GetLastError());
            }
            break;
        }

        //process incoming message
        GetAnswerToRequest(pchRequest, pchReply, &cbReplyBytes);

        fSuccess = WriteFile(
            hPipe,
            pchReply,           // buffer to write from
            cbReplyBytes,       // number of bytes to write
            &cbWritten,         // number of bytes written
            NULL                // not overlapper I/O
            );

        if (!fSuccess || cbReplyBytes != cbWritten)
        {
            _tprintf(TEXT("InstanceThread WriteFile failed, GLE=%d.\n"), GetLastError());
            break;
        }

        //after writing the buffer flush to allow the client to read the contents
        FlushFileBuffers(hPipe);

        DisconnectNamedPipe(hPipe);
        CloseHandle(hPipe);

        HeapFree(hHeap, 0, pchRequest);
        HeapFree(hHeap, 0, pchReply);

        printf("InstanceThread exiting.\n");
        return 1;
    }

    
}

//print the client message and populate reply buffer. This is the function that should prepare the reply to the client request
VOID GetAnswerToRequest(LPTSTR pchRequest, LPTSTR pchReply, LPDWORD pchBytes) {
    _tprintf(TEXT("Client Request String:\"%s\"\n"), pchRequest);

    if (FAILED(StringCchCopy(pchReply, BUFSIZE, TEXT("default asnwer for server")))) {
        *pchBytes = 0;
        pchReply[0] = 0;
        printf("StringCchCopy failed, no outgoing message.\n");
        return;
    }

    *pchBytes = (lstrlen(pchReply) + 1) * sizeof(TCHAR);
}

