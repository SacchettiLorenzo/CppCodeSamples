#include "CSVmanager.h"


FileHandler::FileHandler(std::string file_path, int mode)
{
	this->file_path = file_path;
	try {
		file.open(file_path, mode);
	}
	catch (const std::exception& e) {
		errors.push_back(e);
	}

}

FileHandler::~FileHandler()
{
	try {
		file.close();
	}
	catch(const std::exception& e){
		errors.push_back(e);
	}
}

CSVManager::CSVManager(std::string file_path)
{
	this->file_path = file_path;
}

std::vector<Line> CSVManager::BulkRead()
{
	std::vector<Line> lines;

	FileHandler fileHandler(file_path,1);
	

	std::string line;
	std::string word;
	int count = 0;
	
	while (std::getline(fileHandler.file, line)) {
		
		if (line == "") {
			continue;
		}

		Line newline;
		std::stringstream ss(line);

		while (std::getline(ss,word,';')) {
			switch (count)
			{
			case 0:
				newline.english = word;
				count++;
				break;
			case 1:
				newline.italian = word;
				count++;
				break;
			case 2:
				newline.count = stoi(word);
				count = 0;
				break;
			default:
				break;
			}
		}

		lines.push_back(newline);
	}

	return lines;
}

Line CSVManager::ReadLine(int lineNumber)
{
	FileHandler fileHandler(file_path,1);

	std::string line;
	std::string word;
	int count = 0;
	int counter = 0;
	bool avoidFirstLine = true;
		Line newline;
	while (std::getline(fileHandler.file, line)) {
		line = line;
		if (counter != lineNumber)
		{
			counter++;
			continue;
		}

		if (avoidFirstLine == true) {
			avoidFirstLine = false;
			continue;
		}
		std::stringstream ss(line);

		while (std::getline(ss, word, ';')) {
			switch (count)
			{
			case 0:
				newline.english = word;
				count++;
				break;
			case 1:
				newline.italian = word;
				count++;
				break;
			case 2:
				newline.count = stoi(word);
				count = 0;
				break;
			default:
				break;
			}
			
		}
		break;
	}
	
	return newline;


	
}

bool CSVManager::AddLine(Line newLine)
{
	FileHandler fileHandler(file_path, 8);
	
	std::string newline = "";
	newline = newLine.english + ";" + newLine.italian + ";" + std::to_string(newLine.count) + "\n";

	fileHandler.file << newline;

	return true;
}

bool CSVManager::BulkAdd(std::vector<Line> newLines)
{
	FileHandler fileHandler(file_path, 8);//append;

	for (Line& i : newLines)
	{
		std::string newline = "";
		newline = i.english + ";" + i.italian + ";" + std::to_string(i.count) + "\n";

		fileHandler.file << newline;
	}

	return false;
}

bool CSVManager::AddLineAfter(int line, Line newLine)
{
	//like DeleteLine but instead of .erase use .insert
	std::vector<Line> lines;

	lines = this->BulkRead();

	lines.insert(lines.begin() + line, newLine);

	this->BulkDelete();
	this->BulkAdd(lines);

	return true;
	return false;
}

bool CSVManager::UpdateLine(int line, Line newLine)
{
	std::vector<Line> lines;

	lines = this->BulkRead();

	lines.erase(lines.begin() + line);
	lines.insert(lines.begin() + line, newLine);

	this->BulkDelete();
	this->BulkAdd(lines);

	return true;
	return false;
}

bool CSVManager::DeleteLine(int line)
{
	std::vector<Line> lines;
	
	lines = this->BulkRead();

	lines.erase(lines.begin() + line);

	this->BulkDelete();
	this->BulkAdd(lines);

	return true;
}

bool CSVManager::DeleteLine(Line line)
{
	std::vector<Line> lines = this->BulkRead();
	std::vector<Line>::iterator it;
	
	for (it = lines.begin(); it != lines.end(); it++)
	{
		if (*it == line) {
			lines.erase(it);
			break;
		}
	}

	this->BulkDelete();
	this->BulkAdd(lines);
	return true;
}

bool CSVManager::BulkDelete()
{
	FileHandler fileHandler(file_path, 2|16);//output//truncate;
	fileHandler.file << L"";
	return true;
}

std::string CSVManager::addEscapeCharacters(std::string input)
{
    std::string result;
    for (char c : input) {
        if (c == '"' || c == '\\'  || c == '\'') {
            // Add a backslash before the special character
            result += '\\';
        }
        result += c;
    }

    return result;
}



