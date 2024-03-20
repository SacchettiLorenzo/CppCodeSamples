#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdlib.h>     /* srand, rand */
#include <time.h>  

struct Person {
    std::wstring name;
    std::wstring middlename;
    std::wstring lastname;
    std::wstring email;
    std::wstring birthday;
    bool sex;
    int residence;
    int domicile;
};

int main()
{
    int names_numer = 6782;
    int surnames_numer = 151671;
    int address_number = 2136;

    int insert_number = 3000;

    std::wifstream names("C:\\Users\\Lorenzo\\Documents\\testing_platform Database\\raw\\names.csv");
    std::wifstream surnames("C:\\Users\\Lorenzo\\Documents\\testing_platform Database\\raw\\surnames.csv");

    std::wofstream out("C:\\Users\\Lorenzo\\Documents\\testing_platform Database\\data\\4 - Person.sql", std::ios_base::app);

    wchar_t separation = L';';


    std::vector<Person> people;

    srand(time(NULL));
    int step = 0;
    std::wstring text;
    while (step < insert_number) {
        text.erase();
        int random_line = rand() % names_numer + 1;

        Person person;

        for (size_t i = 0; i < random_line - 1; ++i)
        {
            names.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        getline(names, text);

        names.seekg(0);

        int last = 0;
        int counter = 0;
        for (int i = 0; i < text.size(); i++) {
            if (text.at(i) == separation || text.at(i) == '\n') {
                if (counter == 0) {
                    
                    person.name = text.substr(last, i - last);
                    last = i + 1;
                    counter++;
                }

                if (counter == 1) {
                    if (text.substr(last, i - last) == L"boy") {
                        person.sex = 1;
                    }
                    else {
                        person.sex = 0;
                    }
                    last = i + 1;
                }
            }
        }

        random_line = rand() % surnames_numer + 1;
        for (size_t i = 0; i < random_line - 1; ++i)
        {
            surnames.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        getline(surnames, text);
        surnames.seekg(0);

        person.middlename = text;


        random_line = rand() % surnames_numer + 1;
        for (size_t i = 0; i < random_line - 1; ++i)
        {
            surnames.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        getline(surnames, text);
        surnames.seekg(0);
       
        person.lastname = text;

        person.email = person.name;
        person.email.append(person.lastname);
        person.email.append(L"@gmail.com");

        person.residence = rand() % address_number + 1;
        person.domicile = rand() % address_number + 1;

        int month = rand() % 11 + 1;

        int day;
        if (month == 2) {
            day = rand() % 27 + 1;
        }
        else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            day = rand() % 30 + 1;
        }
        else {
            day = rand() % 29 + 1;
        }

        int year = 1900 + rand() % 69 + 20;

        person.birthday = std::to_wstring(year).append(L"-").append(std::to_wstring(month)).append(L"-").append(std::to_wstring(day));


        std::wstring insert = L"INSERT INTO \"Person\" (first_name, middle_name, last_name, email, birthday, sex, residence_address_id, domicile_address_id) VALUES (";
        insert.append(L"'").append(person.name).append(L"'::text,");
        insert.append(L"'").append(person.middlename).append(L"'::text,");
        insert.append(L"'").append(person.lastname).append(L"'::text,");
        insert.append(L"'").append(person.email).append(L"'::text,");
        insert.append(L"'").append(person.birthday).append(L"'::date,");
        insert.append(L"").append(std::to_wstring(person.sex)).append(L"::boolean,");
        insert.append(L"").append(std::to_wstring(person.residence)).append(L"::int,");

        if (rand() % 2 + 1 == 2) {
        insert.append(L"").append(std::to_wstring(person.domicile)).append(L"::int");
        }
        else {
            insert.append(L"").append(std::to_wstring(person.residence)).append(L"::int");
        }

       
        insert.append(L");\n");

        out << insert;
        
        step++;
    }




}