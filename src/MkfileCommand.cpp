//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

MkfileCommand::MkfileCommand(string args):BaseCommand(args) {}

void MkfileCommand::execute(FileSystem &fs) {//TODO

}

string MkfileCommand::toString() {
    return "mkfile";
}