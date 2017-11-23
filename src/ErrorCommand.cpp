//
// Created by aviran on 13/11/17.
//

#include "../include/Commands.h"

ErrorCommand::ErrorCommand(string args):BaseCommand(args) {}

void ErrorCommand::execute(FileSystem &fs) {
    string str = this->getArgs();
    size_t found;
    found = str.find(" "); // find the first " "
    if (found != string::npos) {// Command with args
        str = str.substr(0,found);
    }
    cout << str << ": Unknown command" << endl;
}

string ErrorCommand::toString() {
    return "error";
}

ErrorCommand::~ErrorCommand() {

}
