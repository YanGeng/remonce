#include <stdio.h>  // printf  
#include <stdlib.h> // exit  
#include <unistd.h> // pipe  
#include <string.h> // strlen  
#include <pthread.h> // pthread_create  
#include <iostream>

using namespace std;  

void *func(void * fd)  
{ 
	//sleep(5);
//	printf("write fd = %d\n", *(int*)fd);  
//	char str[] = "hello everyone!";  
//	write( *(int*)fd, str, strlen(str) );  
	char readbuf[1024];  
	cout << "start read buf\n";
	while (true) {
	read( *(int*)fd, readbuf, sizeof(readbuf) );  
	cout << "end read buf\n";
	printf("read buf = %s\n", readbuf);  
	}
}  

int main()  
{  
	int fd[2];  
	char readbuf[1024];  

	if(pipe(fd) < 0)  
	{  
		printf("pipe error!\n");  
	}  

	// create a new thread  
	pthread_t tid = 0;  
	pthread_create(&tid, NULL, func, &fd[0]);  
	//pthread_join(tid, NULL);  

	sleep(3);  
	cout << "Finish creating thread, start to write the pipe\n";
	printf("write fd = %d\n", *(int*)fd);  
	char str[] = "hello everyone!";  
	write( fd[1], str, strlen(str) );  

	sleep(3);  

	char str2[] = "The 2th parse the value!\n";  
	write( fd[1], str2, strlen(str2) );  
	// read buf from child thread  
//	read( fd[0], readbuf, sizeof(readbuf) );  
//	printf("read buf = %s\n", readbuf);  
	pthread_join(tid, NULL);  

	return 0;  
}  
