#ifndef CDNA_NODE_NODE_H
#define CDNA_NODE_NODE_H

#include "../node/abstract-node.h"

using namespace cdna_node;

namespace cdna_node_micro {

    class Node : public AbstractNode {
    public:

        Node(Spec spec);

        ~Node();

        virtual void run();
    };
}

#endif //CDNA_NODE_NODE_H
