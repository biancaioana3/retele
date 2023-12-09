#include "Thread.h"

Thread::Thread(int socket, pthread_t id) {
    this->socket = socket;
    this->id = id;
}

//void Thread::start() {
//    pthread_mutex_init(& this->lock_list, nullptr);
//}

void Thread::add_thread(Thread *thread) {
    pthread_mutex_lock(& lock_list);
    thread_list.push_back(thread);
    pthread_mutex_unlock(&lock_list);
}

void Thread::remove_thread(Thread *thread) {
    pthread_mutex_lock(&lock_list);
    thread_list.remove(thread);
    delete thread;
    pthread_mutex_unlock(&lock_list);

}

