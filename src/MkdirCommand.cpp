//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

MkdirCommand::MkdirCommand(string args):BaseCommand(args) {}

void MkdirCommand::execute(FileSystem &fs) {

    if(getArgs().empty())return; // no path
    string str=getArgs();
    string nextdir;
    size_t found;
    Directory* temp = &fs.getWorkingDirectory();// Relative path
    Directory* newdir = nullptr;
    bool founddir=false;

    if (findpath(fs,str)!=nullptr){
        cout << "The directory already exists"<< endl;
        return;
    }
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
        for (unsigned int i=0; (i<vct.size()) & (founddir==false); i++) {
            if (vct[i]->getName().compare(nextdir) == 0 && !vct[i]->directoryType()){
                cout << "The directory already exists"<< endl;
                return;
            }
            if (vct[i]->getName().compare(nextdir) == 0 && vct[i]->directoryType()) {
                temp = (Directory *) (vct[i]);
                founddir = true;
            }
        }
          if (founddir==false){
              //Check if the name is legit
              for(unsigned int i=0 ; i<nextdir.size() ; i++) {
                  if (!((97 <= (int) nextdir[i] && (int) nextdir[i] <= 122) || (65 <= (int) nextdir[i] && (int) nextdir[i] <= 90) || (48 <= (int) nextdir[i] && (int) nextdir[i] <= 57)))
                      return;
              }
              newdir = new Directory(nextdir,temp);
              temp->addFile(newdir);
              temp = newdir;
          }

    }//end of while
}

string MkdirCommand::toString() {
    return "mkdir";
}

MkdirCommand::~MkdirCommand() {

}
