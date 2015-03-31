#include <fstream>
#include <cassert>
#include "json/json.h"


int main()
{
	Json::Value root;
	Json::FastWriter writer;
	Json::Value person;

	person["name"] = "hello world";
	person["age"] = 100;
	root.append(person);

	std::string json_file = writer.write(root);


	std::ofstream ofs;
	ofs.open("test1.json");
	assert(ofs.is_open());
	ofs<<json_file;

	return 0;
}
