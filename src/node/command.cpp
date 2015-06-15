#include "command.h"

namespace cdna_node {

    Command::Command(string name, CommandOptions options) {
        this->name_ = name;
        this->options_ = options;
    }

    Command::~Command() { }

    string Command::name() {
        return this->name_;
    }

    string Command::option(string name) {
        CommandOptions::iterator found = this->options_.find(name);
        if (found == this->options_.end()) {
            return "";
        }
        return found->second;
    }
}