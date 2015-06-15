#ifndef CDNA_REVOLUTION_COMMAND_OPTION_H
#define CDNA_REVOLUTION_COMMAND_OPTION_H

#include <iostream>
#include <map>

using namespace std;

namespace cdna_node {

    typedef pair<string, string> CommandOption;
    typedef map<string, string> CommandOptions;

    class Command {
    public:
        Command(string name, CommandOptions options);
        ~Command();

        string name();
        string option(string name);
    private:
        string name_;
        CommandOptions options_;
    };
}

#endif //CDNA_REVOLUTION_COMMAND_OPTION_H
