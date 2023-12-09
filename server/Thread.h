#ifndef MYFTP_BI_THREAD_H
#define MYFTP_BI_THREAD_H

#include <pthread.h>
#include <list>
#include "../common/functions.h"
class Thread {
public:
    int socket;
    pthread_t id;

    Thread(int socket, pthread_t id);

//    static void start();
    static void add_thread(Thread * thread);
    static void remove_thread(Thread * thread);
};


static std::list<Thread *> thread_list;
static pthread_mutex_t lock_list;

static void run(Thread & a);

static void * launch(void *a){
    run(*((Thread *)a));
    close(((Thread*)a)->socket);
    Thread::remove_thread((Thread *) a);
    return nullptr;
}

static void create_thread(Thread * t){
    pthread_create(&t->id, nullptr, launch, t);
    Thread::add_thread(t);
}

#include <iostream>
#include "util.h"

static void run(Thread & a){

    string m;
    while(true){
        read_message(a.socket, m);

        if(m == "REQ_CREATE"){
            string usr, pwd;
            read_message(a.socket, usr);
            read_message(a.socket, pwd);

            switch(treatCreate(usr, pwd)){
                case 406: write_message(a.socket, "RESP_406"); continue;
                case 201: write_message(a.socket, "RESP_201"); continue;
                default: write_message(a.socket, "RESP_500"); continue;
            }
        }

        else if(m == "REQ_LOGIN"){
            string usr, pwd;
            read_message(a.socket, usr);
            read_message(a.socket, pwd);

            switch(treatLogin(usr, pwd)){
                case 403: write_message(a.socket, "RESP_403"); continue;
                case 401: write_message(a.socket, "RESP_401"); continue;
                case 200: write_message(a.socket, "RESP_200"); continue;
                default: write_message(a.socket, "RESP_500"); continue;
            }
        }

        else if (m == "REQ_TREE"){
            string username, response;
            read_message(a.socket, username);

            if(200 == treatTree(username, response)){
                write_message(a.socket, "RESP_PATHS");
                write_message(a.socket, response);
                continue;
            }

            else {
                write_message(a.socket, "RESP_500");
                continue;
            }
        }

        else if (m == "REQ_DOWNLOAD"){
            string path;
            read_message(a.socket, path);
            if(200 == treatDownload(a.socket, path)){
                write_message(a.socket, "FIN_SEND");
            }
            continue;
        }

        else if (m == "REQ_UPLOAD"){
            string dest_path;
            string username;
            read_message(a.socket, username);
            read_message(a.socket, dest_path);
            if(200 == treatUpload(a.socket, dest_path, username)){
                write_message(a.socket, "FIN_GET");
            }
        }

        else return;
    }

}

#endif //MYFTP_BI_THREAD_H