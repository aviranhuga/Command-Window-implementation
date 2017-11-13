//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

BaseCommand::BaseCommand(string args):args(args) {}

string BaseCommand::getArgs() {return args;}

Directory* BaseCommand::findpath(FileSystem & fs, string path) {

    if (path.empty())return nullptr;

    string nextdir;
    size_t found;
    Directory* temp = &fs.getWorkingDirectory();// Relative path
    bool founddir=false;

    if (path[0]=='/') {//absolute path
        path = path.substr(1);
        temp = &fs.getRootDirectory();
    }

        while (path.size()!=0){
            found = path.find('/');
            if (found != string::npos) {// found the '/' char
                nextdir = path.substr(0, found);
                path = path.substr(found + 1);
            } else {// last dir
                nextdir = path;
                path = "";
            }
            if ((*temp).getChildren().empty()) return nullptr;// no dir's
                founddir=false;
            vector<BaseFile *> vct = (*temp).getChildren();
            for (int i=0; i<vct.size() & founddir==false; i++) {
                if(vct[i]->getName().compare(nextdir)==0 && vct[i]->directoryType() ) {
                    temp = (Directory*)(vct[i]);
                    founddir = true;
                }
            }
            if (founddir==false)return nullptr;// didnt found the dir
        }//end of while
    return temp;
    }