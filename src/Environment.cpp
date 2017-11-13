//
// Created by aviran on 12/11/17.
//

#include "../include/Environment.h"


Environment::Environment() {}

void Environment::start() {

    bool exit = true;
    string currentline; // the line that user entered
    string commandString;
    string argsString;
    size_t found;
    while(exit) { // run until user type exit
        cout << fs.getWorkingDirectory().getAbsolutePath() << ">"; // print path
        getline(cin,currentline); // get line from user
        found = currentline.find(" "); // find the first " "
        if(found!=string::npos){// Command with args
            commandString = currentline.substr(0,found);
            argsString = currentline.substr(found+1);
        }else {// Command without args
           commandString = currentline;
           argsString = "";
        }
        BaseCommand* currentcommand = findcommand(commandString,argsString);
        currentcommand->execute(fs);
        addToHistory(currentcommand);
    }
}

FileSystem& Environment::getFileSystem(){
       return fs;
}

void Environment::addToHistory(BaseCommand *command) {
    commandsHistory.push_back(command);
}

const vector<BaseCommand*>& Environment::getHistory() const {
    return commandsHistory;
}

BaseCommand* Environment::findcommand(string command, string args) {
    command=fixargs(command);
    args=fixargs(args);
    BaseCommand* ptr = nullptr;
    if (command.compare("pwd")==0)
         ptr = new PwdCommand(args);
   else  if (command.compare("ls")==0)
        ptr = new LsCommand(args);
   else  if (command.compare("cd")==0)
        ptr = new CdCommand(args);
    else  if (command.compare("mkdir")==0)
        ptr = new MkdirCommand(args);

    else ptr = new ErrorCommand(command + " " + args);
    return ptr;
}

string Environment::fixargs(string str) {
    if (str.size()==0)return str;
    bool finish=false;
    while(finish==false){//delete all the ' ' from the start
        if (str[0]!=' ')finish=true;
        else str=str.substr(1);
    }
    finish=false;
    while(finish==false){//delete all the ' ' from the end
        if (str[str.size()-1]!=' ')finish=true;
        else str=str.substr(0,str.size()-1);
    }
    return str;
}


















