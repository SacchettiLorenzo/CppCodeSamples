#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Line.h"


class FileHandler {
public:
	FileHandler(std::string file_path, int mode);
	~FileHandler();
	std::fstream file;

	
private:
	std::string file_path;
	std::vector<std::exception>errors;

};

class CSVManager
{
public:

	CSVManager(std::string file_path);
	std::vector<Line> BulkRead();
	Line ReadLine(int lineNumber);

	bool AddLine(Line newLine);
	bool BulkAdd(std::vector<Line> newLines);

	bool AddLineAfter(int line, Line newLine);

	bool UpdateLine(int line, Line newLine);

	bool DeleteLine(int line);
	bool DeleteLine(Line line);
	bool BulkDelete();

    std::string addEscapeCharacters(std::string s);

private:
	std::string file_path;
	


};

