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
    int intSIZE = 0;
    for (int i=0; i<str.size() ; i++){
        if (!(48 <= (int)str[i] && (int)str[i] <= 57)){
            cout << "Command not found" << endl;
            return;
        }
        intSIZE=intSIZE + ((int)str[i]-48)*((int)pow(10,(str.size()-1-i)));
    }

    if(intSIZE < history.size()){
        string command = history[intSIZE]->toString();
        string args = history[intSIZE]->getArgs();
        command=fixstring(command);
        args=fixstring(args);
        BaseCommand* ptr = nullptr;
        if (command.compare("pwd")==0)
            ptr = new PwdCommand(args);
        else  if (command.compare("ls")==0)
            ptr = new LsCommand(args);
        else  if (command.compare("cd")==0)
            ptr = new CdCommand(args);
        else  if (command.compare("mkdir")==0)
            ptr = new MkdirCommand(args);
        else  if (command.compare("mkfile")==0)
            ptr = new MkfileCommand(args);
        else  if (command.compare("cp")==0)
            ptr = new CpCommand(args);
        else  if (command.compare("rename")==0)
            ptr = new RenameCommand(args);
        else  if (command.compare("rm")==0)
            ptr = new RmCommand(args);
        else  if (command.compare("mv")==0)
            ptr = new MvCommand(args);
        else  if (command.compare("history")==0)
            ptr = new HistoryCommand(args,history);
        else  if (command.compare("exec")==0)
            ptr = new ExecCommand(args,history);

        else ptr = new ErrorCommand(command + " " + args);
        ptr->execute(fs);
    }else cout << "Command not found" << endl;

    return;
}

string ExecCommand::toString() {
    return "exec";
}