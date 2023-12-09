#ifndef MYFTP_BI_FUNCTIONS_H
#define MYFTP_BI_FUNCTIONS_H

#include <cstring>
#include <unistd.h>
#include <string>
#include <fstream>
#include <fcntl.h>

using namespace std;

static void read_message(int fd, string &m) {
    m.reserve(256);
    int l;
    read(fd, &l, 4);
    string tmp(l, '\0');
    read(fd, &tmp[0], l);
    m = tmp;
}

static void write_message(int fd, const string &m) {
    int l = m.size();
    write(fd, &l, 4);
    write(fd, m.c_str(), l);
}

static void send_file(int fd, const string &path) {
    write_message(fd, "INIT_SEND");
    fopen(path.c_str(), "r");
    string line;
    fstream file;
    file.open(path.c_str(), ios::in);
    while (getline(file, line)) {
        write_message(fd, line.append("\n"));
    }
    file.close();
}

#include <sys/stat.h>
#include <iostream>


static void receive_file(int fd, const string &path) {

    filesystem::create_directories(path.substr(0, path.find_last_of("\\/")));
    string resp;
    FILE *dest_file = fopen(path.c_str(), "w");
    if (dest_file == NULL) {
        cout << "Error at open file\n";
        exit(1);
    }

    while (0 != ::strcmp(resp.c_str(), "FIN_SEND")) {
        read_message(fd, resp);

        if (strcmp(resp.c_str(), "FIN_SEND") == 0)
            break;
        fputs(resp.c_str(), dest_file);
    }

    fclose(dest_file);
}

#endif //MYFTP_BI_FUNCTIONS_H
