#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Thread.h"


int main(int argc, char ** argv) {
    int s = socket(AF_INET,SOCK_STREAM,0);

    int toggle = 1;
    setsockopt (s,SOL_SOCKET,SO_REUSEADDR,& toggle,sizeof ( toggle ));

    struct sockaddr_in server;

    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(63500);
    server.sin_family = AF_INET;

    if(-1 == ::bind (s,(struct sockaddr*)& server,sizeof(server))){
        cout << "[ERROR] Bind error";
    }

    if(-1 == listen (s,10)){
        cout << "[ERROR] Listen error";
    }

    struct sockaddr_in client;
    socklen_t len = sizeof (struct sockaddr_in);

    while(true) {
        int c = accept(s, (struct sockaddr *) &client, &len);
        Thread * thread = new Thread(c, 0);
        create_thread(thread);
    }
    close(s);
    return 0;
}

