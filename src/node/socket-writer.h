#ifndef CDNA_NODE_SOCKET_WRITER_H
#define CDNA_NODE_SOCKET_WRITER_H

#include <iostream>

using namespace std;

namespace cdna_node {

    class SocketWriter {
    public:
        SocketWriter(string host, int port);
        ~SocketWriter();

        string write_to(string content);

    protected:
        string host_;
        int port_;
    };
}

#endif //CDNA_NODE_SOCKET_WRITER_H
