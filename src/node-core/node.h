#ifndef CDNA_NODE_NODE_H
#define CDNA_NODE_NODE_H

#include <iostream>
#include "../node/abstract-node.h"

using namespace std;
using namespace cdna_node;

namespace cdna_node_core {

    class Node : public AbstractNode {
    public:

        Node(Spec spec);

        ~Node();

        virtual void run();

    protected:
        string signal_handle_(string content);

        void broadcast_signal_(string content);

        string process_(string content);
    };
}

#endif //CDNA_NODE_NODE_H
