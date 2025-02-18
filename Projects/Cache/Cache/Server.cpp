//https://learn.microsoft.com/en-us/windows/win32/ipc/using-pipes
#include "Server.h"


LRUCache* lru_cache;
LFUCache* lfu_cache;

// LPVOID is a Windows API typdef for void*
// HANDLE pointer to void* for handling object reference
// LPCTSTR null terminater string, automatically chose between unicode or not depending on system support

DWORD WINAPI InstanceThread(LPVOID);
VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);

//_tmain is a Microsoft extension of main
int cache_server_start()
{
    
    lru_cache = new LRUCache(DEFAULT_CACHE_SIZE);
    lfu_cache = new LFUCache(DEFAULT_CACHE_SIZE);

    BOOL fConnected = FALSE;
    DWORD dwthreadId = 0;
    HANDLE hPipe = INVALID_HANDLE_VALUE, hThread = NULL;
    LPCTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe");

    for (;;) {
        _tprintf(TEXT("\n Awaiting client connection on %s\n"), lpszPipename);
        hPipe = CreateNamedPipe(
            lpszPipename,                                           // pipe name
            PIPE_ACCESS_DUPLEX,                                     // read/write access
            PIPE_TYPE_MESSAGE | 
            PIPE_READMODE_MESSAGE |
            PIPE_READMODE_BYTE |
            PIPE_WAIT,        // message type pipe mode | message-read mode | blocking mode
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

        while (true) {
            //wait the client to connect; if succedes the function return a non zero value

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

                /*if (hThread == NULL) {
                    _tprintf(TEXT("Failed on thread creation: %d\n"), GetLastError());
                    return -1;
                }
                else {
                    CloseHandle(hThread);
                }*/
            }
        }
        /*else {
            CloseHandle(hPipe);
        }*/
    }
    return 0;

}


//thread processing function that read and reply to a client
DWORD WINAPI InstanceThread(LPVOID lpvParam) {
    HANDLE hHeap = GetProcessHeap();

    LPCVOID* header = (LPCVOID*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));
    TCHAR* pchReply = (TCHAR*)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

    DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0;
    BOOL fSuccess = FALSE;
    HANDLE hPipe = NULL;

    //more error check
    if (header == NULL) {
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
        if (header != NULL) HeapFree(hHeap, 0, header);
        return (DWORD)-1;
    }

    printf("InstanceThread created, receiving and processing messages.\n");

    //pipe is passed as parameter at thread creation
    hPipe = (HANDLE)lpvParam;

    //read header
    fSuccess = ReadFile(
        hPipe,
        header,
        BUFSIZE * sizeof(TCHAR),
        &cbBytesRead,
        NULL
    );

    if (!fSuccess || cbBytesRead == 0) {
        if (GetLastError() == ERROR_BROKEN_PIPE)
        {
            _tprintf(TEXT("InstanceThread: client disconnected.\n"));
        }
        else
        {
            _tprintf(TEXT("InstanceThread ReadFile (header) failed, GLE=%d.\n"), GetLastError());
        }
    }


    Header h{};
    memcpy(&h, header, sizeof(Header));

    DWORD bytesRead = 0, bytesAvailable = 0, bytesLeftThisMessage = 0;
    TCHAR* message = (TCHAR*)HeapAlloc(hHeap, 0, h.message_size);

    switch (h.operation)
    {
    case INSERT:
        while (bytesAvailable == 0)
        {
            fSuccess = PeekNamedPipe(
                hPipe,
                NULL,
                0,
                &bytesRead,
                &bytesAvailable,
                &bytesLeftThisMessage
            );
        }

        fSuccess = ReadFile(
            hPipe,
            message,
            h.message_size * sizeof(TCHAR),
            &cbBytesRead,
            NULL
        );

        if (!fSuccess || cbBytesRead == 0) {

            if (GetLastError() == ERROR_BROKEN_PIPE)
            {
                _tprintf(TEXT("InstanceThread: client disconnected.\n"));
            }
            else
            {
                _tprintf(TEXT("InstanceThread ReadFile failed, GLE=%d.\n"), GetLastError());
            }
        }


        switch (h.service)
        {
        case LRU:
            lru_cache->insert(h.key, message);
            break;
        case LFU:
            lfu_cache->insert(h.key, message);
        default:
            break;
        }

        break;

    case REMOVE:
        switch (h.service)
        {
        case LRU:
        lru_cache->remove(h.key);
            break;
        case LFU:
            lfu_cache->remove(h.key);
        default:
            break;
        }
        break;

    case RESIZE:
        switch (h.service)
        {
        case LRU:
        lru_cache->resize(h.message_size);

            break;
        case LFU:
            lfu_cache->resize(h.message_size);
        default:
            break;
        }
        break;

    case GET:
        break;

    default:
        _tprintf(TEXT("This operation is not currently defined\n"));
        break;
    }


    
}

