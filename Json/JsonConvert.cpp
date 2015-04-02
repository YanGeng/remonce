#include "JsonConvert.h"
#include <string>
#include "macro.h"

// Construct and deconstruct
JsonConvert::JsonConvert() {
}


JsonConvert::JsonConvert(boost::shared_ptr< sql::ResultSet > res, std::vector<std::string> &vec) {
	int columns = vec.size();
	Json::Value jVal;

#ifdef _DEBUG 
	CURRENT_FILE_LINE;
#endif

	// Add all the keys in vec and their values into the jsonValue
	while (res->next()) {
		for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it) {
			jVal[*it] = std::string(res->getString(*it));
		}
		jsonValue.append(jVal);
	}
}

/*
JsonConvert::~JsonConvert() {
}
*/


/********************************************************************************
 * func_name:	sqlRes2Json 
 * return:		string
 * parameters:	void
 * description: This func will return the json string of the json file
 *******************************************************************************/
std::string JsonConvert::sqlRes2Json() const {
#ifdef _DEBUG 
	CURRENT_FILE_LINE;
#endif
	Json::FastWriter writer;
	std::string jsonString = writer.write(jsonValue);
	return jsonString;
}
