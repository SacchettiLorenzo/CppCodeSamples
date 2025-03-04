//https://learn.microsoft.com/en-us/windows/win32/ipc/using-pipes
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <any>
#include "..\Cache\Messages.h"
#include <string>
#include <list>
#include <iostream>

bool insert(HANDLE hPipe, services service, LPCVOID* data, int data_length, std::string key, bool keep_alive);
bool remove(HANDLE hPipe, services service, std::string key, bool keep_alive);
std::any get(HANDLE hPipe, services service, std::string key, bool keep_alive);

HANDLE hHeap = GetProcessHeap();

int _tmain(int argc, TCHAR* argv[])
{
	std::cout << "Client" << std::endl;
	Sleep(1000);
	HANDLE hPipe;


	LPCTSTR lpvMessage = TEXT("Get this message bitch.\0");

	TCHAR  chBuf[BUFSIZE];
	BOOL   fSuccess = FALSE;
	DWORD  cbRead, cbWritten, dwMode;
	LPCTSTR lpszPipename = TEXT("\\\\.\\pipe\\main_pipe");

	// Try to open a named pipe; wait for it, if necessary. 

	while (true)
	{
		hPipe = CreateFile(
			lpszPipename,                   // pipe name 
			GENERIC_WRITE | GENERIC_READ,  // write access 
			0,                              // no sharing 
			NULL,                           // default security attributes
			OPEN_EXISTING,                  // opens existing pipe 
			0,                              // default attributes 
			NULL);                          // no template file 

		// Break if the pipe handle is valid. 

		if (hPipe != INVALID_HANDLE_VALUE) {
			break;
		}

		// Exit if an error other than ERROR_PIPE_BUSY occurs. 

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(TEXT("Could not open pipe. GLE=%d\n"), GetLastError());
			//return -1;
		}

		// All pipe instances are busy, so wait for 20 seconds. 

		if (!WaitNamedPipe(lpszPipename, 20000))
		{
			printf("Could not open pipe: 20 second wait timed out.");
			//return -1;
		}
	}

	// The pipe connected; change to message-read mode. 

	dwMode = PIPE_READMODE_MESSAGE | PIPE_READMODE_BYTE | PIPE_WAIT;
	fSuccess = SetNamedPipeHandleState(
		hPipe,    // pipe handle 
		&dwMode,  // new pipe mode 
		NULL,     // don't set maximum bytes 
		NULL);    // don't set maximum time 
	if (!fSuccess)
	{
		_tprintf(TEXT("SetNamedPipeHandleState failed. GLE=%d\n"), GetLastError());
		//return -1;
	}

	DWORD bytesRead = 0, bytesAvailable = 0, bytesLeftThisMessage = 0, bytesWritten = 0;
	HANDLE hHeap = GetProcessHeap();
	LPCTSTR* random_pipe_name = NULL;


	while (true) {
		fSuccess = PeekNamedPipe(
			hPipe,
			NULL,
			0,
			&bytesRead,
			&bytesAvailable,
			&bytesLeftThisMessage
		);

		if (fSuccess == 0) {
			std::cout << "PeekNamedPipe failed: , GLE = " << GetLastError() << std::endl;
		}

		if (bytesAvailable > 0) {
			random_pipe_name = (LPCTSTR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, bytesAvailable);
			fSuccess = ReadFile(
				hPipe,
				random_pipe_name,
				bytesAvailable,
				&bytesRead,
				NULL
			);


			if (fSuccess == 0) {
				std::cout << "ReadFile failed: , GLE = " << GetLastError() << std::endl;
			}
			else {
				break;
			}
		}
	}

	std::wstring pipe_name_base = L"\\\\.\\pipe\\";
	wchar_t* pipe_name_end = reinterpret_cast<wchar_t*>(random_pipe_name);
	std::wcout << pipe_name_end << std::endl;

	std::wstring pipe_name = pipe_name_base + pipe_name_end;

	std::wcout << pipe_name << std::endl;
	CloseHandle(hPipe);

	while (true) {
		hPipe = CreateFile(
			pipe_name.c_str(),                      // pipe name 
			GENERIC_WRITE | GENERIC_READ,  // write access 
			0,                              // no sharing 
			NULL,                           // default security attributes
			OPEN_EXISTING,                  // opens existing pipe 
			0,                              // default attributes 
			NULL);                          // no template file 

		// Break if the pipe handle is valid. 

		if (hPipe != INVALID_HANDLE_VALUE) {
			break;
		}

		// Exit if an error other than ERROR_PIPE_BUSY occurs. 

		if (GetLastError() != ERROR_PIPE_BUSY){
			_tprintf(TEXT("Could not open pipe. GLE=%d\n"), GetLastError());
			//if the named pipe is not opened on the server side yet, error will occur
			//return -1;
		}

		// All pipe instances are busy, so wait for 20 seconds. 

		if (!WaitNamedPipe(lpszPipename, 20000)){
			printf("Could not open pipe: 20 second wait timed out.");
			
			//return -1;
		}
	}

	insert(hPipe, LFU, (LPCVOID*)lpvMessage, lstrlen(lpvMessage) * sizeof(TCHAR), "My_data",true);
	Sleep(1000);
	//remove(hPipe, LFU, "My_data",false);
	std::any res = get(hPipe, LFU, "My_data", false);
	_getch();
	CloseHandle(hPipe);


	return 0;
}

bool insert(HANDLE hPipe, services service, LPCVOID* data, int data_length, std::string key, bool keep_alive) {

	DWORD cbWritten = 0;
	BOOL   fSuccess = FALSE;
	DWORD bytesRead = 0, bytesAvailable = 0, bytesLeftThisMessage = 0;

	Message message{
		service,
		data_length,
		INSERT,
		key,
		keep_alive,
		nullptr
	};

	//mess here in message memory allocation
	message.payload = (void*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, data_length);
	memcpy(message.payload, data, data_length);

	int message_length = sizeof(Message) - sizeof(void*) + data_length;

	fSuccess = PeekNamedPipe(
		hPipe,
		NULL,
		0,
		&bytesRead,
		&bytesAvailable,
		&bytesLeftThisMessage
	);

	if (bytesAvailable == 0) {
		fSuccess = WriteFile(
			hPipe,                  // pipe handle 
			&message,                 // message 
			message_length,              // message length 
			&cbWritten,             // bytes written 
			NULL);                  // not overlapped 

		if (!fSuccess)
		{
			_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
			return false;
		}

	}

	return true;

}

bool remove(HANDLE hPipe, services service, std::string key, bool keep_alive) {

	DWORD cbWritten = 0;
	BOOL   fSuccess = FALSE;
	DWORD bytesRead = 0, bytesAvailable = 0, bytesLeftThisMessage = 0;

	Message message{
		service,
		0,
		REMOVE,
		key,
		keep_alive,
		nullptr
	};

	int message_length = sizeof(Message) - sizeof(void*);

	fSuccess = PeekNamedPipe(
		hPipe,
		NULL,
		0,
		&bytesRead,
		&bytesAvailable,
		&bytesLeftThisMessage
	);

	if (bytesAvailable == 0) {
		fSuccess = WriteFile(
			hPipe,                  // pipe handle 
			&message,                 // message 
			message_length,              // message length 
			&cbWritten,             // bytes written 
			NULL);                  // not overlapped 

		if (!fSuccess)
		{
			_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
			return false;
		}

	}

	return true;
}

bool resize() {
	return true;
}

std::any get(HANDLE hPipe, services service, std::string key, bool keep_alive) {

	DWORD cbWritten = 0;
	BOOL   fSuccess = FALSE;
	DWORD bytesRead = 0, bytesAvailable = 0, bytesLeftThisMessage = 0;

	Message message{
		service,
		0,
		GET,
		key,
		keep_alive,
		nullptr
	};

	int message_length = sizeof(Message) - sizeof(void*);

	fSuccess = PeekNamedPipe(
		hPipe,
		NULL,
		0,
		&bytesRead,
		&bytesAvailable,
		&bytesLeftThisMessage
	);

	if (bytesAvailable == 0) {
		fSuccess = WriteFile(
			hPipe,                  // pipe handle 
			&message,                 // message 
			message_length,              // message length 
			&cbWritten,             // bytes written 
			NULL);                  // not overlapped 

		if (!fSuccess)
		{
			_tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
			return false;
		}
	}

	while (true) {
		fSuccess = PeekNamedPipe(
			hPipe,
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
			hPipe,
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
		else {
			return data;
		}
	}

}