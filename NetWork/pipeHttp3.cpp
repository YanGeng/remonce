#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <event.h>
#include <evhttp.h>
#include <vector>
#include <unistd.h> // pipe
#include <pthread.h>
#include <iostream>
#include <queue>
#include <string.h>

#include <event2/http.h>

using namespace std;

std::queue<struct evhttp_request*> que;

void
root_handler(struct evhttp_request *req, void *arg)
{
	struct evbuffer *buf;

	buf = evbuffer_new();
	if (buf == NULL)
		err(1, "failed to create response buffer");
	evbuffer_add_printf(buf, "Hello World!\n");
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
}


int httpserver_bindsocket(int port, int backlog) {
	int r;
	int nfd;
	nfd = socket(AF_INET, SOCK_STREAM, 0);
	if (nfd < 0) return -1;
	int one = 1;
	r = setsockopt(nfd, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));//ÉèÖÃ¶Ë¿Ú¸´ÓÃ

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

void
generic_handler2(struct evhttp_request *req, void *arg)
{
	//cout << "The size of the queue is: " << que.size() << endl;
	/*  
		que.push(req);
		int *fd = (int *)arg;
		cout << "Finish creating thread, start to write the pipe\n";
		printf("write fd = %d\n", *fd);  
		char str[] = "hello everyone!";  
		write( *fd, str, strlen(str) );  
		cout << "The size of the queue is: " << que.size() << endl;
	 */

	cout << "thread 2\n";
	struct evbuffer *buf;

	buf = evbuffer_new();
	if (buf == NULL)
		err(1, "failed to create response buffer");
	evbuffer_add_printf(buf, "Requested: %s\n", evhttp_request_uri(req));
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
}


void
generic_handler(struct evhttp_request *req, void *arg)
{
	//cout << "The size of the queue is: " << que.size() << endl;
	/*
	que.push(req);
	int *fd = (int *)arg;
	cout << "Finish creating thread, start to write the pipe\n";
	printf("write fd = %d\n", *fd);  
	char str[] = "hello everyone!";  
	write( *fd, str, strlen(str) );  
	cout << "The size of the queue is: " << que.size() << endl;
	*/
	
	cout << "thread 1\n";
	sleep(5);
	struct evbuffer *buf;

	buf = evbuffer_new();
	if (buf == NULL)
		err(1, "failed to create response buffer");
	evbuffer_add_printf(buf, "Requested: %s\n", evhttp_request_uri(req));
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
}

void* httpserver_Dispatch(void *arg) {
	event_base_dispatch((struct event_base*)arg);
	return NULL;
}

int httpserver_start(int port,const int nthreads, int backlog) {
	int r, i;
	int nfd = httpserver_bindsocket(port, backlog);
	if (nfd < 0)  
		return -1; 
	pthread_t ths[500];//´¦ÀíÏß³Ì
	for (i = 0; i < nthreads; i++) {
		struct event_base *base = event_base_new();
		if (base == NULL) 
			return -1; 
		struct evhttp *httpd = evhttp_new(base);
		if (httpd == NULL) 
			return -1; 
		r = evhttp_accept_socket(httpd, nfd);
		if (r != 0)  
			return -1; 
		if (i % 2 == 0) {
			evhttp_set_gencb(httpd, generic_handler2, NULL);
		} else {
			evhttp_set_gencb(httpd, generic_handler, NULL);
		}
		r = pthread_create(&ths[i], NULL, httpserver_Dispatch, base);
		if (r != 0)  
			return -1; 
	}   
	for (i = 0; i < nthreads; i++) {
		pthread_join(ths[i], NULL);
	}   
	return 0;
}

void *func(void * fd)  
{ 
	//sleep(5);
	//  printf("write fd = %d\n", *(int*)fd);  
	//  char str[] = "hello everyone!";  
	//  write( *(int*)fd, str, strlen(str) );  
	while (true) {
	char readbuf[1024];  
	cout << "start read buf\n";
	read( *(int*)fd, readbuf, sizeof(readbuf) );  
	cout << "end read buf\n";
	printf("read buf = %s\n", readbuf);  


	cout << "s The size of the queue is: " << que.size() << endl;
	struct evbuffer *buf;
	struct evhttp_request *req = que.front();
	que.pop();
	cout << "s The size of the queue is: " << que.size() << endl;

	buf = evbuffer_new();
	if (buf == NULL)
		err(1, "failed to create response buffer");
	evbuffer_add_printf(buf, "Requested: %s\n", evhttp_request_uri(req));
	cout << "s Send the reply to chrome\n";
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
	cout << "finish send the reply\n";
	}
}  

int
main(int argc, char **argv)
{
	/*
	struct evhttp *httpd;
	int fd[2];

	event_init();
	httpd = evhttp_start("0.0.0.0",11150);//("127.0.0.9", 8087);
*/
	/* Set a callback for requests to "/". */
//	evhttp_set_cb(httpd, "/", root_handler, NULL);

	/* Set a callback for all other requests. */
/*	evhttp_set_gencb(httpd, generic_handler, &fd[1]);

	if(pipe(fd) < 0)  
	{  
		printf("pipe error!\n");  
	}  
	// create the new pthread
	pthread_t tid = 0;
	pthread_create(&tid, NULL, func, &fd[0]);  


	event_dispatch();

	pthread_join(tid, NULL);
	*/
	/* Not reached in this code as it is now. */

//	evhttp_free(httpd);
	httpserver_start(11150, 2, 10240);

	return 0;
}
