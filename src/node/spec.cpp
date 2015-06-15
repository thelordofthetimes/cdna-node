#include "spec.h"
#include <fstream>
#include <sstream>
#include <string.h>

namespace cdna_node {

    Spec::Spec() { }
    Spec::~Spec() { }

    void Spec::parse_file(string path) {
        ifstream config_file;
        config_file.open(path, ios_base::in);
        string line;
        while (getline(config_file, line)) {
            if (line.empty()) {
                continue;
            }

            stringstream iis(line);
            string token;
            list<string> tokens;
            while (getline(iis, token, ' ')) {
                tokens.push_back(token);
            }
            string name = tokens.front();
            tokens.pop_front();
            CommandOptions command_options;
            string option, value;
            while (!tokens.empty()) {
                option = tokens.front();
                tokens.pop_front();
                value = tokens.front();
                tokens.pop_front();
                command_options.insert(CommandOption(option, value));
            }
            Command command(name, command_options);
            this->commands_.push_back(command);
        }
    }

    Command Spec::first(string name) {
        list<Command>::iterator command;
        for (command = this->commands_.begin(); command != this->commands_.end(); command++) {
            if (command->name() == name) {
                break;
            }
        }
        return *command;
    }

    list<Command> Spec::commands() {
        return this->commands_;
    }
}