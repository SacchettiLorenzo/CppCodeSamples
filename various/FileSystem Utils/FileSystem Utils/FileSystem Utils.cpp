#include <iostream>
#include <string>
#include <filesystem>
#include <stdexcept>
#include <vector>

using namespace std;

void rename_all_files();

int main()
{
	rename_all_files();
	int a;
	cin >> a;
}

void rename_all_files() {
	vector<filesystem::path> files_path;
	filesystem::path p = filesystem::current_path();
	for (const auto& entry : filesystem::directory_iterator(p)) {
		cout << entry.path() << endl;
		if(entry.path().extension().generic_string() != ".exe")
		files_path.push_back(entry.path());
	}

	string new_name;
	string starting_value;
	int sv;

	cout << "Insert new name: " << endl;
	cin >> new_name;
	cout << "Insert starting value: " << endl;
	cin >> starting_value;

	try
	{
		for (char c : starting_value) {
			if (isdigit(c) == false) {
				throw exception("Invalid starting value");
			}
		}

		sv = stoi(starting_value);
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}

	
	for (filesystem::path p : files_path) {
		string full_name =  new_name+"_" + to_string(sv) + p.extension().generic_string();
		sv++;

		try
		{
			rename(p, full_name);
		}
		catch (const std::exception& e)
		{
			cout << e.what();
		}
	}

	
	


	
}

