#ifndef __HTTPSERVER_H
#define __HTTPSERVER_H

#include <evhttp.h>

class HttpServer {
	public:
		HttpServer();
		HttpServer(int nThreads, int port, int backlog);

		int httpBindSocket(int port, int backlog) const;
		static void genericHandle(struct evhttp_request *req, void *arg);
		int httpServerStart() const;
		static void* httpServerDispatch(void *arg);

	private:
		int nThreads;
		int port;
		int backlog;
};

#endif // end of __HTTPSERVER_H
