//
// Created by aviran on 15/11/17.
//

#include "../include/Commands.h"
#include "../include/GlobalVariables.h"

VerboseCommand::VerboseCommand(string args)BaseCommand(args) {}

void VerboseCommand::execute(FileSystem &fs) {
    string args=getArgs();
    args=fixstring(args);
    if(args.compare("1")==0) verbose=1;
    else if(args.compare("1")==0) verbose=1;
    else if(args.compare("2")==0) verbose=2;
    else if(args.compare("3")==0) verbose=3;
    else cout << "Wrong verbose input" << endl;
}

string VerboseCommand::toString() {
    return "verbose";
}
