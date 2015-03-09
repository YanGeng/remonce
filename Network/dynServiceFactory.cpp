#include "dynServiceFactory.h"

std::map<std::string, CREATE_SERVICE> DynServiceFactory::mapCls_;

void *DynServiceFactory::createService(const std::string &name) {
	std::map<std::string, CREATE_SERVICE>::const_iterator it;
	it = mapCls_.find(name);
	if (it == mapCls_.end()) {
		return 0;
	} else {
		return it->second();
	}
}

void DynServiceFactory::registerService(const std::string &name, CREATE_SERVICE func) {
	mapCls_[name] = func;
}

Register::Register(const std::string &name, CREATE_SERVICE func) {
	DynServiceFactory::registerService(name, func);
}
