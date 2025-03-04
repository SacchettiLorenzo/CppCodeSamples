#pragma once
#include "Cache.h"
#include <string>

#define BUFSIZE 512
#define KEYSIZE 128

struct Message {
	services service;
	int payload_size;
	operations operation;
	const std::string key;
	bool keep_thread_alive;
	void* payload;
};
