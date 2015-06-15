#include <iostream>
#include "node.h"
#include "../node/node-exception.h"

using namespace std;
using namespace cdna_node;
using namespace cdna_node_core;

int main(int argc, char *argv[]) {

    try {
        // load specification
        Spec spec;
        spec.parse_file("cdna-node-core.spec");

        // run a node
        Node node(spec);
        node.run();
    } catch (NodeException e) {
        cout << "ERROR: " << e.what() << endl;
    }

    return 0;
}