//
// Created by aviran on 13/11/17.
//

#include "../include/Commands.h"

ErrorCommand::ErrorCommand(string args):BaseCommand(args) {}

void ErrorCommand::execute(FileSystem &fs) {
    cout << getArgs() << ":Unknown command" << endl;
}

string ErrorCommand::toString() {
    return "error";
}