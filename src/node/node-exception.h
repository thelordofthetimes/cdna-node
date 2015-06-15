#include <iostream>
#include <exception>

#ifndef CDNA_NODE_NODE_EXCEPTION_H
#define CDNA_NODE_NODE_EXCEPTION_H

using namespace std;

namespace cdna_node {

    class NodeException : public exception {
    public:
        virtual const char *what() const throw();

        NodeException(string message);

    protected:
        string message_;
    };
}

#endif //CDNA_NODE_NODE_EXCEPTION_H
