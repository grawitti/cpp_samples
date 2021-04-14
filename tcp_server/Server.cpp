#include "Server.h"

Server::Server(uint p, string f_name) : _port(p), _file_to_send(f_name)
{
    _tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    in_addr ip_addr = {0};
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = INADDR_ANY;
}

Server::Server(QObject *pobj)
{
    Q_UNUSED(pobj);
}

Server::~Server()
{
    stop();
}

int Server::start()
{
    if (bind(_tcp_sock, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
    {
        perror("Bind error");
        return -1;
    }

    if (listen(_tcp_sock, 0) < 0)
    {
        perror("Listen error");
        return -1;
    }

    int rc = 0;
    while (rc == 0)
    {
        rc = recive();
    }

    return 0;
}

int Server::stop()
{
    // shutdown(_tcp_sock, SHUT_RDWR);
    if (close(_tcp_sock) < 0)
    {
        perror("Close");
        return -1;
    }
    return 0;
}

int Server::accepting_connection()
{
    in_addr peer_ip_addr = {0};
    sockaddr_in peer_addr = {0};
    socklen_t addrlen = sizeof(sockaddr_in);

#ifdef DEBUG
    cout << "accepting\n";
#endif

    int conn_sock;
    if ((conn_sock = accept(_tcp_sock, (struct sockaddr *)&peer_addr, &addrlen)) < 0)
    {
        perror("Accept error");
        return -1;
    }

#ifdef DEBUG
    cout << "accept success\n";
#endif

    return conn_sock;
}

int Server::recive()
{
    int conn_sock = accepting_connection();
    if (conn_sock < 0)
    {
        return -1;
    }

    int rc = 0;
    while (rc == 0)
    {
        request req;
        memset(&req, 0, sizeof(req));

        if (recv(conn_sock, &req, sizeof(request), 0) < 0)
        {
            perror("Recive error");
            rc = -1;
        }

        switch (req.type)
        {
        case CONFIRM:
        {
            if (send_confirm(conn_sock) < 0)
            {
                rc = -1;
            }
            break;
        }

        case GREET:
        {
            request_greeting *req_greet = (request_greeting *)&req;
            printf("Terminal ID: %u\n", req_greet->terminal_id);

            if (send_confirm(conn_sock) < 0)
                rc = -1;
            break;
        }

        case GET_BULLETIN:
        {
            if (send_file(conn_sock) < 0)
                rc = -1;
            break;
        }

        case SEND_RESULT:
        {
            send_result *send_res = (send_result *)&req;
            printf("Candidate ID: %u\n", send_res->candidate_id);

            if (send_confirm(conn_sock) < 0)
                rc = -1;
            break;
        }

        case SEND_CANCELED:
        {
            cout << "Canceled, terminal if now free\n";

            if (send_confirm(conn_sock) < 0)
                rc = -1;
            break;
        }

        default:
            cerr << "Unexpected type: " << req.type << endl;
            rc = -1;
        }
    }

    return 0;
}

int Server::send_confirm(int conn_sock)
{
    request_confirm req_confirm;
    if (send(conn_sock, &req_confirm, sizeof(request_confirm), 0) < 0)
    {
        perror("Send confirm");
        return -1;
    }

#ifdef DEBUG
    cerr << "Send confirm success\n";
#endif

    return 0;
}

int Server::request_conf(int conn_sock)
{
    request_confirm req_conf;
    memset(&req_conf._data, 0, sizeof(req_conf._data));

    if (recv(conn_sock, &req_conf, sizeof(request_confirm), 0) < 0)
    {
        perror("Request confirm");
        return -1;
    }

    if (req_conf.type != CONFIRM)
    {
        printf("Error confirming\n");
        return -1;
    }

    return 0;
}

int Server::send_file(int conn_sock)
{
    send_bulletin send_bltn;
    memset(&send_bltn.file_size, 0, sizeof(send_bltn.file_size));

    struct stat fi;
    stat(_file_to_send.c_str(), &fi);
    printf("file %s size: %d\n", _file_to_send.c_str(), fi.st_size);

    //Sending file size
    send_bltn.file_size = htonl(fi.st_size);
    send(conn_sock, &send_bltn, sizeof(send_bltn), 0);
    cout << "send length!" << endl;

    // send file in cycle
    ifstream file;
    file.open(_file_to_send, ios::in | ios::binary);
    char *buff = new char[FILE_BUFF_SIZE];
    size_t num;
    int rest_size = fi.st_size;
    int size;

    while (rest_size > 0)
    {
        size = (rest_size < FILE_BUFF_SIZE) ? rest_size : FILE_BUFF_SIZE;
        file.read(buff, size);

        if ((num = send(conn_sock, buff, size, 0)) < 0)
        {
            cerr << "sending err" << endl;
        }

        rest_size -= FILE_BUFF_SIZE;

#ifdef DEBUG
        cout << "send: " << num << " bytes" << endl;
        if (rest_size > 0)
            { cout << "left to send: " << rest_size << endl; }
#endif
    }

#ifdef DEBUG
    cout << "Bulletin send, wait confirm" << endl;
#endif

    if (request_conf(conn_sock) < 0)
    {
        cerr << "Bulletin send failed! !Confirm\n";
        return -1;
    }

#ifdef DEBUG
    cout << "Confirm for send bulettin success\n";
#endif

    return 0;
}
