#include "abstract-node.h"

namespace cdna_node {

    AbstractNode::AbstractNode(Spec spec) {
        this->spec_ = spec;
    }

    AbstractNode::~AbstractNode() { }
}