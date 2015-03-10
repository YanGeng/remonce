#include "dbService.h"
#include "iostream"

void dbService::run() {
	std::cout << "run the dbService\n";
}

// Register the class, this is very important
REGISTER_CLASS(dbService);
