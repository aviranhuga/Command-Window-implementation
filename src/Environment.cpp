//
// Created by aviran on 12/11/17.
//

#include "../include/Environment.h"
#include "../include/GlobalVariables.h"


Environment::Environment():commandsHistory(),fs(){}


void Environment::start() {

    bool exit = true;
    string currentline; // the line that user entered
    string commandString;
    string argsString;
    size_t found;
    while(exit) { // run until user type exit
        cout << fs.getWorkingDirectory().getAbsolutePath() << ">"; // print path
        getline(cin,currentline); // get line from user
        if(currentline.compare("exit")==0)return;
        if (verbose==2 || verbose==3) cout << currentline << endl; // verbose
        currentline=DeleteSpaces(currentline); // delete the spaces
        found = currentline.find(" "); // find the first " "
        if(found!=string::npos){// Command with args
            commandString = currentline.substr(0,found);
            argsString = currentline.substr(found+1);
        }else {// Command without args
           commandString = currentline;
           argsString = "";
        }
        BaseCommand* currentcommand = findcommand(commandString,argsString);
        currentcommand->execute(getFileSystem());
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
    command=DeleteSpaces(command);
    args=DeleteSpaces(args);
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
       ptr = new HistoryCommand(args,this->getHistory());
   else  if (command.compare("exec")==0)
       ptr = new ExecCommand(args,this->getHistory());
   else  if (command.compare("verbose")==0)
       ptr = new VerboseCommand(args);


    else ptr = new ErrorCommand(command + " " +args);
    return ptr;
}

string Environment::DeleteSpaces(string str) {
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

//............................
//.......RULE OF 5............
//............................

Environment::~Environment() { //Destructor
    BaseCommand *pd = nullptr;
    vector<BaseCommand *> vct = getHistory();
    if (!vct.empty())//not empty
        for (unsigned int i = 0; i < vct.size(); i++) {
            pd = vct[i];
            delete pd;
        }
    if (verbose==1 || verbose==3)cout << "~Environment()" << endl;
}

//Copy Constructor
Environment::Environment(const Environment &other):commandsHistory(other.getHistory()),fs(other.fs) {
    if (verbose==1 || verbose==3)cout << "Environment(const Environment& other)" << endl;
}

Environment& Environment::operator=(const Environment &rhs) {

    this->fs=rhs.fs;
    this->commandsHistory = rhs.getHistory();
    if (verbose==1 || verbose==3)cout << "Environment& operator=(const Environment& rhs)" << endl;
    return *this;
}

Environment& Environment::operator=(Environment &&rhs) {

    this->fs=rhs.fs;
    this->commandsHistory = rhs.getHistory();
    if (verbose==1 || verbose==3)cout << "Environment& operator=(Environment&& rhs)" << endl;
    return *this;
}

Environment::Environment(Environment &&rhs):commandsHistory(rhs.getHistory()),fs(rhs.fs){

    if (verbose==1 || verbose==3)cout << "Environment(Environment&& rhs)" << endl;

}

