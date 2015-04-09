#include "httpServer.h"
#include <sys/socket.h>
#include <pthread.h>
#include <err.h>
#include <netinet/in.h>
#include <event.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <iostream>
#include <evhttp.h>

HttpServer::HttpServer() : nThreads(4)
	,port(11150)
	,backlog(10240) {
}


HttpServer::HttpServer(int nThreads, int port, int backlog) : nThreads(nThreads)
	,port(port)
	,backlog(backlog) {
}


/********************************************************************************
 * func_name: 
 * return: 
 * parameters: 
 * description: 
 * *****************************************************************************/
void* HttpServer::httpServerDispatch(void *arg) {
	event_base_dispatch((struct event_base*)arg);
	return NULL;
}


/********************************************************************************
 * func_name: 
 * return: 
 * parameters: 
 * description: 
 * *****************************************************************************/
int HttpServer::httpBindSocket(int port, int backlog) const {
	int r;
	int nfd;
	nfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (nfd < 0) return -1; 
	int one = 1;
	r = setsockopt(nfd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);

	r = bind(nfd, (struct sockaddr*)&addr, sizeof(addr));
	if (r < 0) return -1; 
	r = listen(nfd, backlog);
	if (r < 0) return -1; 

	int flags;
	if ((flags = fcntl(nfd, F_GETFL, 0)) < 0 
			|| fcntl(nfd, F_SETFL, flags | O_NONBLOCK) < 0)
		return -1; 
	return nfd;
}


/********************************************************************************
 * func_name: 
 * return: 
 * parameters: 
 * description: 
 * *****************************************************************************/
void HttpServer::genericHandle(struct evhttp_request *req, void *arg) {
	std::cout << "thread 2\n";
	struct evbuffer *buf;

	buf = evbuffer_new();
	if (buf == NULL)
		err(1, "failed to create response buffer");
	evbuffer_add_printf(buf, "Requested: %s\n", evhttp_request_uri(req));
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
}


/********************************************************************************
 * func_name: 
 * return: 
 * parameters: 
 * description: 
 * *****************************************************************************/
 int HttpServer::httpServerStart() {
	 int r, i;
	 int nfd = httpBindSocket(port, backlog);
	 if (nfd < 0)  
		 return -1; 
	 pthread_t ths[500]; // max: 500 threads
	 for (i = 0; i < nThreads; i++) {
		 struct event_base *base = event_base_new();
		 if (base == NULL) 
			 return -1; 
		 struct evhttp *httpd = evhttp_new(base);
		 if (httpd == NULL) 
			 return -1; 
		 r = evhttp_accept_socket(httpd, nfd);
		 if (r != 0)  
			 return -1; 

		 evhttp_set_gencb(httpd, genericHandle, NULL);
		 r = pthread_create(&ths[i], NULL, httpServerDispatch, base);
		 if (r != 0)  
			 return -1; 
	 }   

	 for (i = 0; i < nThreads; i++) {
		 pthread_join(ths[i], NULL);
	 }   

	 return 0;
}
