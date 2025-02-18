#pragma once
#include <iostream>
#include <Windows.h>
#include <tchar.h> 
#include <strsafe.h>

#include "Messages.h"
#include "LRUCache.h"
#include "LFUCache.h"
#include "Cache.h"

int cache_server_start();
DWORD WINAPI InstanceThread(LPVOID lpvParam);