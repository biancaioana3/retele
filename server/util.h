#ifndef MYFTP_BI_UTIL_H
#define MYFTP_BI_UTIL_H
#include <string>
#include <fstream>
#include <filesystem>
#include "Thread.h"

using namespace std;

static bool check_username(const string& username){
    ifstream fin("../server/blacklist.txt");
    string usr;
    while(!fin.eof()){
        fin >> usr;
        if(usr == username){
            fin.close();
            return false;
        }
    }
    fin.close();
    return true;
}

static bool check_user_pass(const string& user, const string& pass){
    ifstream fin("../server/users.txt");
    string u, p;
    while(!fin.eof()){
        fin >> u >> p;
        if(u == user && p == pass){
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

static int treatLogin(const string& usr, const string& pwd){

    if(!check_username(usr)){
        return 403;
    }

    if(!check_user_pass(usr, pwd)){
        return 401;
    }

    return 200;
}

static int treatCreate(const string& usr, const string& pwd){

    if(!check_username(usr)){
        return 406;
    }

    ifstream fin("../server/users.txt");
    string u, p;
    while(!fin.eof()){
        fin >> u >> p;
        if(u == usr){
            fin.close();
            return 406;
        }
    }

    ofstream fout("../server/users.txt", ios::app);
    fout << usr <<'\n'<< pwd<<'\n';
    std::filesystem::create_directory("../server/workspace/" + usr);

    fout.close();
    return 201;

}

static int treatTree(const string & username, string & response){
    string path = "../server/workspace/" + username;

    for(const auto & entry : std::filesystem::recursive_directory_iterator(path)){
        if(!entry.is_directory()) {
            auto trimmed_entry = entry.path().string().substr(path.length() - username.length());
            response.append(trimmed_entry).append(" ");
        }
    }
    return 200;
}

static int treatDownload(int fd, const string &path) {
    string server_path = "../server/workspace/" + path;
    std::cout << "server_path: " << server_path << '\n';

    if(filesystem::is_directory(server_path))
        return 400;

    send_file(fd, server_path);
    return 200;
}

static int treatUpload(int fd, const string & dest_path, const string & username){

    string server_file_path = "../server/workspace/" + username + '/' + dest_path;
    std::cout << "server_file_path: " << server_file_path << '\n';

    string resp;
    read_message(fd, resp);
    if(resp == "INIT_SEND")
        receive_file(fd, server_file_path);

    return 200;
}

#endif //MYFTP_BI_UTIL_H
