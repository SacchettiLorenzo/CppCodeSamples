//https://learn.microsoft.com/en-us/windows/win32/ipc/using-pipes
#include "Server.h"


LRUCache* lru_cache;
LFUCache* lfu_cache;

// LPVOID is a Windows API typdef for void*
// HANDLE pointer to void* for handling object reference
// LPCTSTR null terminater string, automatically chose between unicode or not depending on system support

struct threadParams {
	HANDLE mutex;
	LPCTSTR random_pipe_name;
};

DWORD WINAPI InstanceThread(LPVOID params);
VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD);

//_tmain is a Microsoft extension of main
int cache_server_start()
{
	HANDLE hHeap = GetProcessHeap();
	lru_cache = new LRUCache(DEFAULT_CACHE_SIZE);
	lfu_cache = new LFUCache(DEFAULT_CACHE_SIZE);

	HANDLE ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL             // unnamed mutex
	);

	if (ghMutex == NULL) {
		_tprintf(TEXT("CreateMutex failed, GLE=%d.\n"), GetLastError());
		return -1;
	}

	BOOL fConnected = FALSE;
	DWORD dwthreadId = 0;
	HANDLE hThread = NULL;
	LPCTSTR main_pipe_name = TEXT("\\\\.\\pipe\\main_pipe");

	std::cout << "Awaiting client connection" << std::endl;

	HANDLE h_main_pipe = INVALID_HANDLE_VALUE;

	h_main_pipe = CreateNamedPipe(
		main_pipe_name,                           // pipe name
		PIPE_ACCESS_DUPLEX,                     // read/write access
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_READMODE_BYTE |
		PIPE_WAIT,								// message type pipe mode | message-read mode | blocking mode
		PIPE_UNLIMITED_INSTANCES,               // unlimited (max) number of instances
		BUFSIZE,                                // output buffer size
		BUFSIZE,                                // input buffer size
		0,                                      // client time-out        
		NULL                                    // default security attribute
	);

	if (h_main_pipe == INVALID_HANDLE_VALUE) {
		_tprintf(TEXT("CreateNamedPipe failed, GLE=%d.\n"), GetLastError());
		return -1;
	}

	bool fSuccess = false;
	DWORD bytesRead = 0, bytesAvailable = 0, bytesLeftThisMessage = 0, bytesWritten = 0;

	while (true) {

		//todo: random string generator here
		LPCTSTR random_pipe_name = TEXT("a8shg1la");

		fSuccess = false;
		fSuccess = ConnectNamedPipe(h_main_pipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);


		if (fSuccess == true) {
			//fixme: Client Connected is printed 2 times
			std::cout << "Client Connected" << std::endl;
			fSuccess = PeekNamedPipe(
				h_main_pipe,
				NULL,
				0,
				&bytesRead,
				&bytesAvailable,
				&bytesLeftThisMessage
			);

			if (bytesAvailable == 0) {
				fSuccess = WriteFile(
					h_main_pipe,				// pipe handle 
					random_pipe_name,           // message 
					lstrlen(random_pipe_name) * sizeof(WCHAR),   // message length 
					&bytesWritten,				// bytes written 
					NULL);

				if (fSuccess == 0) {
					_tprintf(TEXT("WriteFile failed: GLE=%d at line: %d\n"), GetLastError(), __LINE__);
				}

				threadParams params{
					ghMutex,
					nullptr
				};
				params.random_pipe_name = (LPCTSTR)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, lstrlen(random_pipe_name) * sizeof(WCHAR));
				params.random_pipe_name = random_pipe_name;

				FlushFileBuffers(h_main_pipe);
				hThread = CreateThread(
					NULL,				// security attribute
					0,					// stack size
					InstanceThread,		// thread proc
					(LPVOID)&params,	// thread parameters
					0,
					&dwthreadId     // reference to the variable that hold thread id
				);


				if (hThread == NULL) {
					_tprintf(TEXT("Failed on thread creation: GLE=%d at line: %d\n"), GetLastError(), __LINE__);
				}
				else {
					CloseHandle(hThread);
				}
			}
		}
	}
	DisconnectNamedPipe(h_main_pipe);
	CloseHandle(h_main_pipe);
	return 0;

}

DWORD WINAPI InstanceThread(LPVOID tparams) {
	HANDLE hHeap = GetProcessHeap();

	std::wstring pipe_name_base = L"\\\\.\\pipe\\";

	threadParams* params = (threadParams*)tparams;

	std::wstring pipe_name = pipe_name_base + params->random_pipe_name;
	//_tprintf(TEXT("%s\n"),pipe_name.c_str());

	HANDLE th_pipe = INVALID_HANDLE_VALUE;

	bool keep_thread_alive = true;
	bool operation_result = false;

	std::pair < size_t, std::any >GET_result;

	th_pipe = CreateNamedPipe(
		pipe_name.c_str(),						// pipe name
		PIPE_ACCESS_DUPLEX,                     // read/write access
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_READMODE_BYTE |
		PIPE_WAIT,								// message type pipe mode | message-read mode | blocking mode
		PIPE_UNLIMITED_INSTANCES,               // unlimited (max) number of instances
		BUFSIZE,                                // output buffer size
		BUFSIZE,                                // input buffer size
		0,                                      // client time-out        
		NULL                                    // default security attribute
	);

	if (th_pipe == INVALID_HANDLE_VALUE) {
		_tprintf(TEXT("CreateNamedPipe failed, GLE=%d at line: %d\n"), GetLastError(), __LINE__);
		return -1;
	}
	else {
		_tprintf(TEXT("Thread and pipe created\n"));
	}

	DWORD cbWritten = 0;
	bool fSuccess = false;
	fSuccess = ConnectNamedPipe(th_pipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

	DWORD bytesRead = 0, bytesAvailable = 0, bytesLeftThisMessage = 0, bytesWritten = 0;

	if (fSuccess == true) {
		_tprintf(TEXT("Client connected on thread\n"));

		while (keep_thread_alive) {

			while (true) {
				fSuccess = PeekNamedPipe(
					th_pipe,
					NULL,
					0,
					&bytesRead,
					&bytesAvailable,
					&bytesLeftThisMessage
				);

				if (fSuccess == 0) {
					_tprintf(TEXT("PeekNamedPipe failed, GLE=%d at line: %d\n"), GetLastError(), __LINE__);
				}
				if (bytesAvailable > 0) break;
			}

			if (bytesAvailable > 0) {
				LPCVOID* data = (LPCVOID*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, bytesAvailable);
				fSuccess = ReadFile(
					th_pipe,
					data,
					bytesAvailable,
					&bytesRead,
					NULL
				);

				if (!fSuccess || bytesRead == 0) {
					if (GetLastError() == ERROR_BROKEN_PIPE) {
						_tprintf(TEXT("InstanceThread: client disconnected, GLE=%d at line: %d \n"), GetLastError(), __LINE__);
					}
					else {
						_tprintf(TEXT("InstanceThread ReadFile (header) failed, GLE=%d at line: %d \n"), GetLastError(), __LINE__);
					}
				}

				Message* message = (Message*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, bytesAvailable);

				if (!message) {
					_tprintf(TEXT("HeapAlloc failed, GLE=%d at line: %d \n"), GetLastError(), __LINE__);
					return false;
				}

				if (data != NULL) {
					memcpy(message, data, bytesAvailable);
				}
				else {
					return 0;
				}

				keep_thread_alive = message->keep_thread_alive;

				DWORD dwWaitResult = WaitForSingleObject(
					params->mutex,    // handle to mutex
					INFINITE);  // no time-out interval

				switch (dwWaitResult)
				{
				case WAIT_OBJECT_0:
					try {
						switch (message->operation)
						{
						case INSERT:
							switch (message->service)
							{
							case LRU:
								operation_result = lru_cache->insert(message->key, message->payload, bytesAvailable);
								_tprintf(TEXT("insert\n"));
								break;
							case LFU:
								operation_result = lfu_cache->insert(message->key, message->payload, bytesAvailable);
								_tprintf(TEXT("insert\n"));
								break;
							}
							break;
						case UPDATE:
							switch (message->service)
							{
							case LRU:
								operation_result = lru_cache->update(message->key, message->payload, bytesAvailable);
								_tprintf(TEXT("update\n"));
								break;
							case LFU:
								operation_result = lfu_cache->update(message->key, message->payload, bytesAvailable);
								_tprintf(TEXT("update\n"));
								break;
							}
							break;
						case GET:
							switch (message->service)
							{
							case LRU:
								GET_result = lru_cache->get(message->key);
								_tprintf(TEXT("get\n"));
								break;
							case LFU:
								GET_result = lfu_cache->get(message->key);
								_tprintf(TEXT("get\n"));
								break;
							}

							fSuccess = PeekNamedPipe(
								th_pipe,
								NULL,
								0,
								&bytesRead,
								&bytesAvailable,
								&bytesLeftThisMessage
							);

							if (bytesAvailable == 0) {
								fSuccess = WriteFile(
									th_pipe,                  // pipe handle 
									&(GET_result.second),                 // message 
									GET_result.first,              // message length 
									&cbWritten,             // bytes written 
									NULL);                  // not overlapped 

								if (!fSuccess)
								{
									_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
									return false;
								}
							}

							break;
						case REMOVE:
							switch (message->service)
							{
							case LRU:
								operation_result = lru_cache->remove(message->key);
								_tprintf(TEXT("remove\n"));
								break;
							case LFU:
								operation_result = lfu_cache->remove(message->key);
								_tprintf(TEXT("remove\n"));
								break;
							}
							break;
						case RESIZE:
							switch (message->service) {
							case LRU:
								operation_result = lru_cache->resize(message->payload_size);
								_tprintf(TEXT("resize\n"));
								break;
							case LFU:
								operation_result = lfu_cache->resize(message->payload_size);
								_tprintf(TEXT("resize\n"));
								break;
							}
							break;
						}
					}
					catch (...) {
						_tprintf(TEXT("Exception caught at line: %d\n"), __LINE__);
					}



					if (!ReleaseMutex(params->mutex)) {
						_tprintf(TEXT("lock release failed, GLE = % d at line : % d\n"), GetLastError(), __LINE__);
						return false;
					}

					break;
				case WAIT_ABANDONED:
					return false;
				}
			}
		}
	}

	return 1;
}

//to string 
/*wchar_t* pString =  reinterpret_cast<wchar_t*>(message);
pString[header.message_size / sizeof(wchar_t)] = L'\0';
std::wcout << pString << std::endl;*/
//-------------------------------------


