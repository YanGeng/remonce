#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <err.h>

#include <event.h>
#include <evhttp.h>
#include <vector>
#include <unistd.h> // pipe
#include <pthread.h>
#include <iostream>
#include <queue>
#include <string.h>

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

void
generic_handler(struct evhttp_request *req, void *arg)
{
	cout << "The size of the queue is: " << que.size() << endl;
	que.push(req);
	int *fd = (int *)arg;
	cout << "Finish creating thread, start to write the pipe\n";
	printf("write fd = %d\n", *fd);  
	char str[] = "hello everyone!";  
	write( *fd, str, strlen(str) );  
	cout << "The size of the queue is: " << que.size() << endl;
	/*
	struct evbuffer *buf;

	buf = evbuffer_new();
	if (buf == NULL)
		err(1, "failed to create response buffer");
	evbuffer_add_printf(buf, "Requested: %s\n", evhttp_request_uri(req));
	evhttp_send_reply(req, HTTP_OK, "OK", buf);
	*/
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
	struct evhttp *httpd;
	int fd[2];

	event_init();
	httpd = evhttp_start("0.0.0.0",11150);//("127.0.0.9", 8087);

	/* Set a callback for requests to "/". */
	evhttp_set_cb(httpd, "/", root_handler, NULL);

	/* Set a callback for all other requests. */
	evhttp_set_gencb(httpd, generic_handler, &fd[1]);

	if(pipe(fd) < 0)  
	{  
		printf("pipe error!\n");  
	}  
	// create the new pthread
	pthread_t tid = 0;
	pthread_create(&tid, NULL, func, &fd[0]);  


	event_dispatch();

	pthread_join(tid, NULL);
	/* Not reached in this code as it is now. */

	evhttp_free(httpd);

	return 0;
}
