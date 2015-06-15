#include "node-exception.h"

namespace cdna_node {

    NodeException::NodeException(string message) {
        this->message_ = message;
    }

    const char *NodeException::what() const throw() {
        return this->message_.c_str();
    }
}