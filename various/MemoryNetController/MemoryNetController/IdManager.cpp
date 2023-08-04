// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "IdManager.h"

int IdManager::id = 0;

IdManager::IdManager() {
}

 int IdManager::getNextId() {
	id++;
	return id;
}