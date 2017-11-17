//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

PwdCommand::PwdCommand(string args):BaseCommand(args){}

void PwdCommand::execute(FileSystem &fs) {
   cout << fs.getWorkingDirectory().getAbsolutePath() << endl;
}

string PwdCommand::toString() {
    return "pwd";
}

PwdCommand::~PwdCommand() {

}
