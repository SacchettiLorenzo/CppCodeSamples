#pragma once

#define DEFAULT_CACHE_SIZE 10

enum services {LFU,LRU};

enum types {_MESSAGE,_BYTE};

enum operations {INSERT,GET,REMOVE,UPDATE,RESIZE};
