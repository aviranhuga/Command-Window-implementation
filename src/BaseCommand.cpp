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
                if (path[path.size()-1]=='/') return nullptr;
                path = path.substr(found + 1);
            } else {// last dir
                nextdir = path;
                path = "";
                }

            if(nextdir.compare("..")==0) {
                if (temp->getParent()== nullptr)return nullptr;
                temp = temp->getParent();
            }
            else {
                if ((*temp).getChildren().empty()) return nullptr;// no dir's
                founddir = false;
                vector<BaseFile *> vct = (*temp).getChildren();
                for (unsigned int i = 0; (i < vct.size()) & (founddir == false); i++) {
                    if (vct[i]->getName().compare(nextdir) == 0 && vct[i]->directoryType()) {
                        temp = (Directory *) (vct[i]);
                        founddir = true;
                    }
                }
                if (founddir == false)return nullptr;// didnt found the dir
            }//end of else
        }//end of while
    return temp;
    }

string BaseCommand::fixstring(string str) {
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

bool BaseCommand::Findfile(Directory *dir, string name) {
    vector<BaseFile *> vct = dir->getChildren();
    if (!vct.empty())//not empty
        for (unsigned int i=0; i< vct.size() ; i++) {
            if (vct[i]->getName().compare(name) == 0)//file or dir with the same name
                return true;
        }
    return false;
}

BaseCommand::~BaseCommand(){

}
