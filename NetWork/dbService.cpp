#include "dbService.h"
#include "iostream"
#include "dynServiceFactory.h"

void DbService::run() {
	std::cout << "run the dbService\n";
}

// Register the class, this is very important
REGISTER_CLASS(DbService);
