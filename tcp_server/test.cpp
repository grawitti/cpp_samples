#include "Server.h"

int main(int argc, char **argv)
{
    uint port;
    string file_to_send;
    if (argc == 3)
    {
        port = (uint)atoi(argv[1]);
        file_to_send = argv[2];
    }
    else
    {
        cerr << "Parameters: port path_to_file" << endl;
        return 1;
    }

    Server test_server(port, file_to_send);

    test_server.start();
    test_server.stop();

    return 0;
}