#pragma once
#include <mysql.h> 
#include <string>
#include <vector>
#include "Line.h"

class DBManager
{

public:
    DBManager();
    DBManager(const char* host, const char* user, const char* password, const char* DB);

    ~DBManager();

	void SetTable(std::string table);

	MYSQL_RES* ExecuteQuery(std::string query);

    void PrintResult(MYSQL_RES* res_set);

	std::vector<Line> BulkRead();
	Line ReadRecord(int lineNumber);

	bool AddRecord(Line newLine);
	bool BulkAdd(std::vector<Line> newLines);

	bool UpdateRecord(int id, Line newLine);

	bool DeleteRecord(int id);
	bool DeleteRecord(Line line);
	bool BulkDelete();

    std::string addEscapeCharacters(std::string s);

private:
    MYSQL conn;
	std::string table;

};

