#include "httpServer.h"

int main() {
	HttpServer *hp = new HttpServer();
	hp->httpServerStart();
	return 0;
}
