//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

MkdirCommand::MkdirCommand(string args):BaseCommand(args) {}

void MkdirCommand::execute(FileSystem &fs) {//TODO

    if(getArgs().empty())return; // no path
    string str=getArgs();
    string nextdir;
    size_t found;
    Directory* temp = &fs.getWorkingDirectory();// Relative path
    Directory* newdir = nullptr;
    bool founddir=false;

    if (str[0]=='/') {//absolute path
        str = str.substr(1);
        temp = &fs.getRootDirectory();
    }

    while (str.size()!=0){
        found = str.find('/');
        if (found != string::npos) {// found the '/' char
            nextdir = str.substr(0, found);
            str = str.substr(found + 1);
        } else {// last dir
            nextdir = str;
            str = "";
        }
        founddir=false;
        vector<BaseFile *> vct = (*temp).getChildren();
        if (!vct.empty())
        for (int i=0; i<vct.size() & founddir==false; i++) {
            if (vct[i]->getName().compare(nextdir) == 0 && !vct[i]->directoryType())return;
            if (vct[i]->getName().compare(nextdir) == 0 && vct[i]->directoryType()) {
                temp = (Directory *) (vct[i]);
                founddir = true;
            }
        }
          if (founddir==false){
              newdir = makenewdir(nextdir,temp);
              temp->addFile(newdir);
              temp = newdir;
          }

    }//end of while
}

string MkdirCommand::toString() {
    return "mkdir";
}

Directory* MkdirCommand::makenewdir(string name, Directory *parent) {
    return new Directory(name,parent);
}