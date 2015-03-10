#ifndef __SERVICE_H
#define __SERVICE_H

class Service {
public:
	virtual void run() = 0;
	virtual ~Service() {};
};

#endif	// __SERVICE_H
