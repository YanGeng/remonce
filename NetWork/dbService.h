#ifndef __DBSERVICE_H
#define __DBSERVICE_H

#include "service.h"

class DbService : public Service {
	public:
		void run();
		~DbService() {};
};

#endif // __DBSERVICE_H
