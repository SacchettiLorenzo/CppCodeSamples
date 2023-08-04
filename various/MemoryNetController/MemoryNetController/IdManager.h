#pragma once
class IdManager
{
public:
	IdManager();
	static int getNextId();
private:
	static int id;
};

