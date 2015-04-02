#ifndef __JSONCONVERT_H
#define __JSONCONVERT_H

#include <cppconn/resultset.h>
#include "json/json.h"
#include <vector>
#include <boost/shared_ptr.hpp>

class JsonConvert {
	public:
		JsonConvert();
		JsonConvert(boost::shared_ptr< sql::ResultSet > res, std::vector<std::string> &vec);
		std::string sqlRes2Json() const;
	
	private:
		Json::Value jsonValue;
};

#endif // end of the __JSONCONVERT_H
