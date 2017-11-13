//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

CdCommand::CdCommand(string args):BaseCommand(args){}

void CdCommand::execute(FileSystem &fs) {
    if(getArgs().empty()) {
        return; //empty args - do nothing
    }

    if(getArgs().compare("..")==0){ // go back to parent
        if (fs.getWorkingDirectory().getParent() == nullptr){// we are in the root - stay in cd
            return;
        }
        fs.setWorkingDirectory(fs.getWorkingDirectory().getParent());
    }//end of ..
    else { // not a ".." path
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
    }

string CdCommand::toString() {
    return "cd";
}
