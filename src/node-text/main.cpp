#include <iostream>
#include "node.h"

using namespace std;
using namespace cdna_node_text;

int main(int argc, char *argv[]) {

    // load specification
    Spec spec;
    spec.parse_file("cdna-node-text.spec");

    // run a node
    Node node(spec);
    node.run();

    return 0;
}