#ifndef __DYNSERVICEFACTORY_H
#define __DYNSERVICEFACTORY_H

#include <string>
#include <map>

typedef void *(CREATE_SERVICE)();

class DynServiceFactory {
	public:
		static void *createService(const std::string &name);
		static void registerService(const std::string &name, CREATE_SERVICE func);

	private:
		static std::map<std::string, CREATE_SERVICE> mapCls_;
};


class Register {
	public:
		Register(const std::string &name, CREATE_SERVICE func);
};


# define REGISTER_CLASS(className) \
class className##Register { \
public: \
	static void *newInstance() { \
		return new className; \
	} \
private: \
	static Register reg_; \
}; \
Register className##Register::reg_(#className, className##Register::newInstance)

#endif // __DYNSERVICEFACTORY_H
