//
// Created by aviran on 15/11/17.
//

#include "../include/Commands.h"
#include <cmath>

ExecCommand::ExecCommand(string args, const vector<BaseCommand *> &history)
        :BaseCommand(args),history(history) {}

void ExecCommand::execute(FileSystem &fs) {
    if(getArgs().empty())return; //Worng args
    string str=getArgs();
    str=fixstring(str);

    //get size in int
    unsigned int intSIZE = 0;
    for (unsigned int i=0; i<str.size() ; i++){
        if (!((48 <= (int)str[i]) && ((int)str[i] <= 57))){
            cout << "Command not found" << endl;
            return;
        }
        intSIZE=intSIZE + ((int)str[i]-48)*((int)pow(10,(str.size()-1-i)));
    }

    if(intSIZE < history.size()) {
        string command = history[intSIZE]->toString();
        string args = history[intSIZE]->getArgs();
        command = fixstring(command);
        args = fixstring(args);

        if (command.compare("pwd") == 0) {
            PwdCommand ptr(args);
            ptr.execute(fs);
        } else if (command.compare("ls") == 0) {
            LsCommand ptr(args);
            ptr.execute(fs);
        } else if (command.compare("cd") == 0) {
            CdCommand ptr(args);
            ptr.execute(fs);
        } else if (command.compare("mkdir") == 0) {
            MkdirCommand ptr(args);
            ptr.execute(fs);
        } else if (command.compare("mkfile") == 0){
            MkfileCommand ptr(args);
            ptr.execute(fs);
        }
        else if (command.compare("cp") == 0) {
            CpCommand ptr(args);
            ptr.execute(fs);
        }
        else if (command.compare("rename") == 0) {
            RenameCommand ptr(args);
            ptr.execute(fs);
        }
        else if (command.compare("rm") == 0) {
            RmCommand ptr(args);
            ptr.execute(fs);
        }
        else if (command.compare("mv") == 0) {
            MvCommand ptr(args);
            ptr.execute(fs);
        }
        else if (command.compare("history") == 0) {
            HistoryCommand ptr(args, history);
            ptr.execute(fs);
        }
        else if (command.compare("exec") == 0) {
            ExecCommand ptr(args, history);
            ptr.execute(fs);
        }
        else if (command.compare("verbose") == 0) {
            VerboseCommand ptr(args);
            ptr.execute(fs);
        }else {
            ErrorCommand ptr(command + " " + args);
            ptr.execute(fs);
        }

    }else cout << "Command not found" << endl;

    return;
}

string ExecCommand::toString() {
    return "exec";
}

ExecCommand::~ExecCommand() {

}
