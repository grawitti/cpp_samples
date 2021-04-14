#ifndef SERVER_ARM
#define SERVER_ARM

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>

#include "protocol.hh"

using std::string;
using std::ifstream;
using std::ios;
using std::cerr;
using std::cout;
using std::endl;

class Server : QObject
Q_OBJECT


{
public:
    Server(uint p, string f_name);
    Server(QObect *pobj);
    ~Server();
    int start();
    int stop();

private:
    uint _port;
    uint _file_size;
    int _tcp_sock;
    string _file_to_send;
    sockaddr_in _addr;

    int accepting_connection();
    int recive();
    int request_conf(int conn_sock);
    int send_confirm(int conn_sock);
    int send_file(int conn_sock);
};

#endif // SERVER_ARM
