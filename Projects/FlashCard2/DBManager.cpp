#include "DBManager.h"
#include <iostream>

DBManager::DBManager()
{

}

DBManager::DBManager( const char* host, const char* user, const char* password, const char* DB){
    
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, host, user, password, DB, 0, NULL, 0))
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
            mysql_error(&conn));
    }
    else {
        fprintf(stderr, "Successfully connected to Database.\n");
    }
}

DBManager::~DBManager()
{
    mysql_close(&conn);
}

void DBManager::SetTable(std::string table)
{
    this->table = table;
}

MYSQL_RES* DBManager::ExecuteQuery(std::string query)
{
    int status = mysql_query(&conn, query.c_str());
    if (status != 0) {
        std::cout << "unable to execute query" << std::endl;
    }

    return mysql_store_result(&conn);

}

void DBManager::PrintResult(MYSQL_RES* res_set)
{
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
        for (int i = 0; i < mysql_num_fields(res_set); i++)
        {
            printf("%s \t", row[i] != NULL ? row[i] : "NULL");
        }
        printf("\n");
    }
}

std::vector<Line> DBManager::BulkRead()
{
    std::vector<Line> lines;

    std::string query = "SELECT * FROM " + table;

    MYSQL_RES* res_set = ExecuteQuery(query);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
        Line line;
        
        line.id = atoi(row[0]);
        line.english = std::string(&row[1][0], &row[1][strlen(row[1])]);
        line.italian = std::string(&row[2][0], &row[2][strlen(row[2])]);
        line.count = atoi(row[3]);

        
        lines.push_back(line);
    }

    return lines;
}

Line DBManager::ReadRecord( int lineNumber)
{
    std::string query = "SELECT * FROM " + table + " WHERE id = " + std::to_string(lineNumber);
    MYSQL_RES* res_set = ExecuteQuery(query);
    MYSQL_ROW row;
    
    row = mysql_fetch_row(res_set);
        Line line;
    if (row != NULL) {

        line.id = atoi(row[0]);
        line.english = std::string(&row[1][0], &row[1][strlen(row[1])]);
        line.italian = std::string(&row[2][0], &row[2][strlen(row[2])]);
        line.count = atoi(row[3]);
    }

    return line;
}

bool DBManager::AddRecord(Line newLine)
{
    //INSERT INTO `testdb`.`words` (`english`, `italian`, `count`) VALUES ('ciabats', 'ciabatte', '0');

    std::string query = "SELECT `AUTO_INCREMENT` FROM  INFORMATION_SCHEMA.TABLES where TABLE_NAME = '" + table + "';";//SELECT LAST_INSERT_ID()
    MYSQL_RES* res_set = ExecuteQuery(query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res_set);

    int lastID = 0;
    if(row!=NULL)
    {
        lastID = atoi(row[0]);
    }
    

    query = "INSERT INTO " + table + "(english, italian, count) VALUES " + "('" + newLine.english + "','" + newLine.italian + "','" + std::to_string(newLine.count) + "');";
    ExecuteQuery(query);

    if (mysql_errno(&conn) != 0)return false;
    if ((int)&conn.insert_id > lastID)return true;
    else return false;

}

bool DBManager::BulkAdd(std::vector<Line> newLines)
{
    std::string query = "SELECT `AUTO_INCREMENT` FROM  INFORMATION_SCHEMA.TABLES where TABLE_NAME = '" + table + "';";//SELECT LAST_INSERT_ID()
    MYSQL_RES* res_set = ExecuteQuery(query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res_set);

    int lastID = 0;
    if (row != NULL)
    {
        lastID = atoi(row[0]);
    }

    query = "INSERT INTO " + table + "(english, italian, count) VALUES";

    for (Line l : newLines) {
        query += "('" + l.english + "','" + l.italian + "','" + std::to_string(l.count) + "'),";
    }

    query.pop_back();
    ExecuteQuery(query);

    if (mysql_errno(&conn) != 0)return false;
    if ((int)&conn.insert_id > lastID)return true;
    else return false;
    
}

bool DBManager::UpdateRecord(int id, Line newLine)
{
    std::string query = "UPDATE " + table + " SET english = '" + addEscapeCharacters(newLine.english) + "', italian = '" + addEscapeCharacters(newLine.italian) + "', count = " + std::to_string(newLine.count) + " WHERE id = " + std::to_string(id);
    MYSQL_RES* res_set = ExecuteQuery(query);

    if (mysql_errno(&conn) == 0)return true;
    else return false;

}

bool DBManager::DeleteRecord(int id)
{
    std::string query = "DELETE FROM " + table + " WHERE id = " + std::to_string(id);
    MYSQL_RES* res_set = ExecuteQuery(query);

    if (mysql_errno(&conn) == 0)return true;
    else return false;
}

bool DBManager::DeleteRecord(Line line)
{ 
    std::string query = "DELETE FROM " + table + " WHERE english = '" + line.english + "' AND italian = '" + line.italian + "' LIMIT 1";
    MYSQL_RES* res_set = ExecuteQuery(query);

    if (mysql_errno(&conn) == 0)return true;
    else return false;

    
}

bool DBManager::BulkDelete()
{
    std::string query = "TRUNCATE " + table;
    MYSQL_RES* res_set = ExecuteQuery(query);

    if(mysql_errno(&conn) == 0)return true;
    else return false;
}

std::string DBManager::addEscapeCharacters(std::string input)
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

