#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdlib.h>     /* srand, rand */
#include <time.h>  

struct Address {
    std::wstring type;
    std::wstring street_name;
    std::wstring street_number;
    int city_id;
    int zip;
};

int main()
{
    int city_numer = 44691;
    int max_zip = 20000;
    int streets_numer = 11610;

    int insert_number = 1568;

    std::wifstream street("C:\\Users\\Lorenzo\\Documents\\testing_platform Database\\raw\\Street_Names.csv");

    std::wofstream out("C:\\Users\\Lorenzo\\Documents\\testing_platform Database\\data\\3 - Address.sql", std::ios_base::app);

    wchar_t separation = L';';


        srand(time(NULL));
    int step = 0;
        std::wstring text;
    while (step < insert_number) {
        int random_line = rand() % streets_numer + 1;

        Address address;

        for (size_t i = 0; i < random_line-1; ++i)
        {
            street.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        getline(street, text);

        street.seekg(0);

        int last = 0;
        int counter = 0;
        for (int i = 0; i < text.size(); i++) {
            if (text.at(i) == separation || text.at(i) == '\n') {
                if (counter == 0) {
                    address.street_name = text.substr(last, i - last);
                    last = i + 1;
                    counter++;
                }

                if (counter == 1) {
                    address.type = text.substr(last, i - last);
                    last = i + 1;
                }
            }
        }

        address.city_id = rand() % city_numer + 1;

        address.street_number = std::to_wstring(rand() % 300);

        address.zip = rand() % max_zip + 1;

        step++;

        std::wstring insert = L"INSERT INTO \"Address\" (type, street_name, street_number, city_id, zip) VALUES (";
        insert.append(L"'").append(address.type).append(L"'::text,");
        insert.append(L"'").append(address.street_name).append(L"'::text,");
        insert.append(L"'").append(address.street_number).append(L"'::text,");
        insert.append(std::to_wstring(address.city_id)).append(L"::int,");
        insert.append(std::to_wstring(address.zip)).append(L"::int");
        insert.append(L");\n");

        out << insert;
        text.erase();
    }


    

}

