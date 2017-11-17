//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

CdCommand::CdCommand(string args):BaseCommand(args){}

void CdCommand::execute(FileSystem &fs) {
    if(getArgs().empty()) {
        return; //empty args - do nothing
    }

        Directory* temp = findpath(fs,getArgs());
        if (temp==nullptr){
            cout << "The system cannot find the path specified" << endl;
            return;
        }
        else {
            fs.setWorkingDirectory(temp);
            return;
        }
    }

string CdCommand::toString() {
    return "cd";
}

CdCommand::~CdCommand() {

}
