

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::wifstream file("C:\\Users\\Lorenzo\\Downloads\\worldcities.csv");

    std::wofstream out("C:\\Users\\Lorenzo\\Documents\\testing_platform Database\\2 - City.sql", std::ios_base::app);

    wchar_t separation = L';';

    std::wstring DBName = L"City";

    std::vector<std::wstring> columns;
    columns.emplace_back(L"name");
    columns.emplace_back(L"state_id");
    columns.emplace_back(L"lat");
    columns.emplace_back(L"lng");

    std::vector<std::wstring> comlumnsTypes;
    comlumnsTypes.emplace_back(L"text");
    comlumnsTypes.emplace_back(L"integer");
    comlumnsTypes.emplace_back(L"real");
    comlumnsTypes.emplace_back(L"real");

    if (columns.size() != comlumnsTypes.size()) {
        std::cerr << "something went wrong" << std::endl;
    }

    std::vector<std::wstring> values;

    std::wstring text;

    bool firstLine = false;

    while (getline(file, text)) {
        //if (!firstLine) {
        //    text = text.substr(3, text.size()); //get rid of byte order mark
        //    firstLine = true;
        //}
        int i = 0;
        int last = 0;
        for (int i = 0; i < text.size(); i++) {
            if (text.at(i) == separation || text.at(i) == '\n') {
                values.emplace_back(text.substr(last, i - last));
                last = i + 1;
            }

            if (i == text.size() - 1) {
                values.emplace_back(text.substr(last, i - last + 1));
                last = i + 1;
            }
        }
    }
   /* for (std::wstring s : values) {
        std::wcout << s << std::endl;
    }*/

    std::wstring insert = L"";

    

    int cursor = 0;
    while (cursor < values.size())
    {
        insert.append(L"INSERT INTO \"");
        insert.append(DBName);
        insert.append(L"\"(");

        for (int i = 0; i < columns.size(); i++) {
            insert.append(columns.at(i));
            if (i != columns.size() - 1) {
                insert.append(L",");
            }
        }
        insert.append(L") VALUES (\n");

        for (int i = 0; i < columns.size(); i++) {
            
            if (comlumnsTypes.at(i) == L"text") {
                insert.append(L"'");
            }

            if (values.at(cursor).find_first_of(L"'", 0) != std::string::npos) {
                size_t pos = values.at(cursor).find_first_of(L"'", 0);
                std::wstring temp = values.at(cursor).substr(0, pos);
                temp.append(L"'");
                temp.append(values.at(cursor).substr(pos));
                values.at(cursor) = temp;
            }

            if (i == 1) {
                insert.append(L"( SELECT id FROM \"State\" WHERE short2 = '");
                insert.append(values.at(cursor));
                insert.append(L"')");
            }
            else {
                if (comlumnsTypes.at(i) == L"real") {
                    int tmp = values.at(cursor).find_first_of(L",");
                    if (tmp != -1) {

                    values.at(cursor).replace(tmp, 1, L".");
                    }
                }
                
                insert.append(values.at(cursor));

                
            }

            if (comlumnsTypes.at(i) == L"text") {
                insert.append(L"'::");
            }
            else {
                insert.append(L"::");
            }
            insert.append(comlumnsTypes.at(i));
            if (i != columns.size() - 1) {
                insert.append(L",\n");
            }
            cursor++;
        }
        insert.append(L"\n)");
        

        if (insert.size() >= 1000) {
            out << insert;
            insert.erase();
        }
    insert.append(L";\n");
    }

    out << insert;







}

