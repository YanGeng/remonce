#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <event.h>
#include <netdb.h>
#include <pthread.h>
#include <unistd.h> 
#include <evhttp.h>
#include <iostream>

#include <cache.h>

using namespace std;

/* An item in the connection queue. */
typedef struct conn_queue_item CQ_ITEM;
struct conn_queue_item {
    int               sfd;
//    enum conn_states  init_state;
    int               event_flags;
    int               read_buffer_size;
//    enum network_transport     transport;
    CQ_ITEM          *next;
};


/* A connection queue. */
typedef struct conn_queue CQ;
struct conn_queue {
    CQ_ITEM *head;
    CQ_ITEM *tail;
    pthread_mutex_t lock;
    pthread_cond_t  cond;
};


typedef struct {
    pthread_t thread_id;        /* unique ID of this thread */
    struct event_base *base;    /* libevent handle this thread uses */
    struct event notify_event;  /* listen event for notify pipe */
    int notify_receive_fd;      /* receiving end of notify pipe */
    int notify_send_fd;         /* sending end of notify pipe */
//    struct thread_stats stats;  /* Stats generated by this thread */
//   struct conn_queue *new_conn_queue; /* queue of new connections to handle */
	cache_t *suffix_cache;      /* suffix cache */
} LIBEVENT_THREAD;

int main () {
	cout << "Test starts:\n";
	return 0;
}