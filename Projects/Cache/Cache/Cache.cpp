#include <iostream>
#include "LFUCache.h"
#include "LRUCache.h"
#include "Server.h"

int main()
{
    std::cout << "Server" << std::endl;
    cache_server_start();

}

