//
// Created by aviran on 15/11/17.
//

#include "../include/Commands.h"

RmCommand::RmCommand(string args):BaseCommand(args) {}

void RmCommand::execute(FileSystem &fs) {

    if(getArgs().empty()){
        cout << "No such file or directory" << endl;
        return;
    }
    string args = getArgs();
    string path; // the path to the file
    string filename; // file name
    size_t found;
    Directory *tempsrc = nullptr;

    if (args.compare("/")==0){
        cout << "Can't remove directory" << endl;
        return;
    }
    tempsrc = &fs.getWorkingDirectory();
    while (tempsrc->getParent()!= nullptr){
        if (args.compare(tempsrc->getAbsolutePath())==0) {
            cout << "Can't remove directory" << endl;
            return;
        }
        tempsrc=tempsrc->getParent();
    }//end of while


    found = args.find_last_of("/");//if there a path
    if (found != string::npos) {// found the '/' char

        if ((int)args[args.size()-1]=='/') {//no file name
            cout << "No such file or directory" << endl;
            return;}

        path = args.substr(0, found); //save path
        filename = args.substr(found + 1); // save filename
        if (path.compare("")==0)path="/";
        path=fixstring(path);
        filename=fixstring(filename);
        tempsrc = findpath(fs,path);
        }//end of '/' char
    else { // file in the working directory
        tempsrc = &fs.getWorkingDirectory();
        filename = args;
    }
    bool foundfile=false;
    vector<BaseFile *> vct = (*tempsrc).getChildren();
    if (!vct.empty())//not empty
        for (int i=0; i<vct.size() && foundfile==false ; i++) {
            if (vct[i]->getName().compare(filename) == 0) {//found the file
                foundfile=true;
                tempsrc->removeFile(vct[i]);
            }//end of found file
        }//end of for loop

    if(foundfile==false){//didnt found the file
        cout << "No such file or directory" << endl;
        return;
    }

}

string RmCommand::toString() {
    return "rm";
}