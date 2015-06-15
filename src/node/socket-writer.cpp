#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "socket-writer.h"
#include "node-exception.h"

namespace cdna_node {

    SocketWriter::SocketWriter(string host, int port) {
        this->host_ = host;
        this->port_ = port;
    }

    SocketWriter::~SocketWriter() { }

    string SocketWriter::write_to(string content) {
        // declare variables
        int socket_fd;
        struct sockaddr_in server_address;
        struct hostent *server;

        // create socket
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            throw NodeException(strerror(errno));
        }

        // connect to socket
        server = gethostbyname(this->host_.c_str());
        if (server == NULL) {
            throw NodeException(strerror(errno));
        }
        bzero((char *) &server_address, sizeof(server_address));
        server_address.sin_family = AF_INET;
        bcopy((char *) server->h_addr,
              (char *) &server_address.sin_addr.s_addr,
              server->h_length);
        server_address.sin_port = htons(this->port_);
        if (connect(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
            throw NodeException(strerror(errno));
        }

        // write to socket
        if (write(socket_fd, content.c_str(), content.length()) < 0) {
            throw NodeException(strerror(errno));
        }

        // read from socket
        char buffer[256];
        bzero(buffer, 256);
        if (read(socket_fd, buffer, 255) < 0) {
            throw NodeException(strerror(errno));
        }

        // close socket
        close(socket_fd);

        // return response from socket
        return string(buffer);
    }
}
