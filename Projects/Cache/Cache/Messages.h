#pragma once
#include "Cache.h"
#include <string>

#define BUFSIZE 512

struct Header {
	services service;
	int message_size;
	types type;
	operations operation;
	const char key[128]; //key | new size
};
