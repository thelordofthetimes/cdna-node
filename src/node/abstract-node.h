#ifndef CDNA_ABSTRACT_NODE_NODE_H
#define CDNA_ABSTRACT_NODE_NODE_H

#include <netinet/in.h>
#include <iostream>
#include "spec.h"

using namespace std;

namespace cdna_node {

    class AbstractNode {
    public:
        AbstractNode(Spec spec);

        ~AbstractNode();

        virtual void run() = 0;

    protected:
        Spec spec_;
    };
}

#endif //CDNA_ABSTRACT_NODE_NODE_H
