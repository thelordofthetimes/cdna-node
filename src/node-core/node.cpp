#include <unistd.h>
#include <thread>
#include "node.h"
#include "../node/socket-reader.h"
#include "../node/socket-writer.h"
#include "../node/node-exception.h"

using namespace placeholders;

namespace cdna_node_core {

    Node::Node(Spec spec) : AbstractNode(spec) {

    }

    Node::~Node() {

    }

    string Node::signal_handle_(string content) {
        string result;
        try {
            // display income content
            time_t timer;
            time(&timer);
            struct tm *time_info = localtime(&timer);
            cout << "IN " << asctime(time_info) << " " << content << endl;

            // process signal
            result = this->process_(content);

            // direct result to all input type node
            thread broadcast_thread(bind(&Node::broadcast_signal_, this, _1), result);
            broadcast_thread.detach();
        } catch (NodeException e) {
            result = "error";
            cout << "ERROR SIGNAL HANDLE: " << e.what() << endl;
        }

        // return signal to request socket
        return result;
    }

    void Node::run() {
        // instance socket to listen signal
        Command command = this->spec_.first("node-core");
        int port = atoi(command.option("--port").c_str());
        SocketReader socket(command.option("--host"), port);

        // display configuration in std output
        cout << "node-core: " << command.name() <<
        " --host " << command.option("--host") <<
        " --port " << command.option("--port") <<
        endl;

        // handle signal
        socket.on_write(bind(&Node::signal_handle_, this, _1));
    }

    void Node::broadcast_signal_(string content) {
        try {
            list<Command> commands = this->spec_.commands();
            list<Command>::iterator command;
            string command_type;
            for (command = commands.begin(); command != commands.end(); command++) {
                command_type = command->option("--type");
                if (command_type == "input") {
                    int out_port = atoi(command->option("--port").c_str());
                    SocketWriter out_socket(command->option("--host"), out_port);
                    out_socket.write_to(content);
                }
            }
        } catch (NodeException e) {
            cout<<"ERROR: "<<e.what()<<endl;
        }
    }

    string Node::process_(string content) {
        string response = "what";
        if (content == "what your name") {
            response = "my name is CDNA";
        } else if (content == "hello") {
            response = "hi, thank";
        } else if (content == "-kill") {
            exit(EXIT_SUCCESS);
        } else if (content == "open webstorm") {
            response = "webstorm is openning";
            thread child_thread([] {
                system("~/jetbrains/webstorm/bin/webstorm.sh");
            });
            child_thread.detach();
        } else if (content == "close webstorm") {
            response = "webstorm is closed";
            thread child_thread([] {
                system("pkill webstorm");
            });
            child_thread.detach();
        }
        return response;
    }
}