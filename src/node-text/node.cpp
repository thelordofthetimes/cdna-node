#include "node.h"
#include "../node/socket-writer.h"
#include "../node/node-exception.h"

namespace cdna_node_text {

    Node::Node(Spec spec) : AbstractNode(spec) {

    }

    Node::~Node() {

    }

    void Node::run() {
        // instance socket
        Command command = this->spec_.first("node-core");
        int port = atoi(command.option("--port").c_str());
        SocketWriter socket(command.option("--host"), port);

        // display configuration in std output
        cout << "node-text: " << command.name() <<
        " --host " << command.option("--host") <<
        " --port " << command.option("--port") <<
        endl;

        // get command and send to node-core
        string signal;
        while (true) {
            try {
                // get signal from command line
                cout << "node-text: ";
                signal.clear();
                getline(cin, signal);
                if (signal.empty()) {
                    continue;
                }
                if (signal == "exit") {
                    break;
                }

                // use socket to send signal
                string response = socket.write_to(signal);
                cout << "node-core: " << response << endl;
            } catch (NodeException e) {
                cout<<"ERROR: "<<e.what()<<endl;
            }
        }
    }
}