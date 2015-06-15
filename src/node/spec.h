#ifndef CDNA_REVOLUTION_COMMAND_LINE_H
#define CDNA_REVOLUTION_COMMAND_LINE_H

#include <map>
#include <list>
#include "command.h"

using namespace std;

namespace cdna_node {

    class Spec {
    public:
        Spec();
        ~Spec();

        /**
         * parse configuration file
         */
        void parse_file(string path);

        Command first(string name);

        list<Command> commands();
    private:
        list<Command> commands_;
    };
}

#endif //CDNA_REVOLUTION_COMMAND_LINE_H
