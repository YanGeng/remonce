#include "xmlConf.h"
#include <iostream>
#include <map>

int main() {
	XmlConf *test = new XmlConf();

	test->readXmlConf("./test.xml");

	std::map<std::string, std::string> mapTest = test->getXmlConf();
}
