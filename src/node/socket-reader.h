#ifndef CDNA_NODE_SOCKET_READER_H
#define CDNA_NODE_SOCKET_READER_H

#include <iostream>
#include <functional>

using namespace std;

namespace cdna_node {

    class SocketReader {
    public:
        SocketReader(string host, int port);
        ~SocketReader();

        void on_write(function<string(string content)> handler);

    private:
        string host_;
        int port_;
    };
}

#endif //CDNA_NODE_SOCKET_READER_H
