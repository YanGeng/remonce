#include "xmlConf.h"
#include <iostream>
#include <map>

int main() {
	XmlConf *test = new XmlConf();

	test->readXmlConf("/Users/tony/SandBox/remonce/Xml/web.xml");

	std::map<std::string, std::string> mapTest = test->getXmlConf();

	std::map<std::string, std::string>::iterator it;
	for (it = mapTest.begin(); it!=mapTest.end();++it) {
		std::cout << "Key:" << it->first << " value:" << it->second << std::endl;
	}

	return 0;
}
