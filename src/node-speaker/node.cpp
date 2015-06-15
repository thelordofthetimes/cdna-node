#include <unistd.h>
#include <string.h>
#include "node.h"
#include "../node/socket-reader.h"
#include "../node/node-exception.h"

using namespace placeholders;

namespace cdna_node_speaker {

    Node::Node(Spec spec) : AbstractNode(spec) {

    }

    Node::~Node() {

    }

    string Node::signal_handle_(string content) {
        // display income content
        cout<<"IN: "<<content<<endl;

        // speak
        string command = "echo '" + string(content) + "' | festival --tts";
        system(command.c_str());

        return "";
    }

    void Node::run() {
        // instance socket to listen signal
        Command command = this->spec_.first("node-speaker");
        int port = atoi(command.option("--port").c_str());
        SocketReader socket(command.option("--host"), port);

        // display configuration in std output
        cout << "node-speaker: " << command.name() <<
        " --host " << command.option("--host") <<
        " --port " << command.option("--port") <<
        endl;

        // handle signal
        socket.on_write(bind(&Node::signal_handle_, this, _1));
    }
}