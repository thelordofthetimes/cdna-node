#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include "socket-reader.h"
#include "node-exception.h"

namespace cdna_node {

    SocketReader::SocketReader(string host, int port) {
        this->host_ = host;
        this->port_ = port;
    }

    SocketReader::~SocketReader() { }

    void SocketReader::on_write(function<string(string content)> handler) {
        // declare variables
        int socket_fd, new_socket_fd;
        socklen_t client;
        struct sockaddr_in server_address, client_address;

        // create new socket
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            throw NodeException(strerror(errno));
        }

        // bind socket to port
        bzero((char *) &server_address, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(this->port_);
        int bind_result = bind(socket_fd,
                               (struct sockaddr *) &server_address,
                               sizeof(server_address));
        if (bind_result < 0) {
            throw NodeException(strerror(errno));
        }

        // start listen signal to socket
        listen(socket_fd, 5);
        client = sizeof(client_address);

        // handle signal to socket
        // todo how to break this loop and close socket
        while (true) {
            try {
                // accept signal
                new_socket_fd = accept(socket_fd,
                                       (struct sockaddr *) &client_address,
                                       &client);
                if (new_socket_fd < 0) {
                    throw  NodeException(strerror(errno));
                }

                // read request content
                char request_content[256];
                bzero(request_content, 255);
                if (read(new_socket_fd, request_content, 255) < 0) {
                    throw NodeException(strerror(errno));
                }

                // call handler, get result
                string handler_result = handler(request_content);

                // write to request socket
                ssize_t write_result = write(new_socket_fd, handler_result.c_str(), handler_result.length());
                if (write_result < 0) {
                    throw NodeException(strerror(errno));
                }

                // close new socket
                close(new_socket_fd);
            } catch  (NodeException e) {
                cout<<"ERROR: "<<e.what()<<endl;
            }
        }
    }
}
