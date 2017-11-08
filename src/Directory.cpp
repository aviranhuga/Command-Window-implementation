//
// Created by aviran on 08/11/17.
//

#include "../include/Files.h"

Directory::Directory(string name, Directory *parent):
        BaseFile(name),parent(parent) {}

Directory* Directory::getParent() const {
    return parent;
}

void Directory::setParent(Directory *newParent) {
    parent=newParent;
}

void Directory::addFile(BaseFile *file) {
    children.push_back(file); // add the element to the end
}

void Directory::removeFile(string name) {
    if ( !(children.empty()) ){ // if its not empty
        bool found=false;
        vector<BaseFile*>::iterator it = children.begin();// iterator to first element
        for(; it!=children.end() & found==false ; it++){
            if( ((*it)->getName().compare(name))==0 ){
                children.erase(it);
                found=true;
            }//end of if
        }//end of for
    }//end of empty
}

void Directory::removeFile(BaseFile *file) {
        bool found=false;
        vector<BaseFile*>::iterator it = children.begin();// iterator to first element
        for(; it!=children.end() & found==false ; it++){
            if( (*it) == file ){
                children.erase(it);
                found=true;
            }//end of if
        }//end of for
}

void Directory::sortByName() {}//TODO
void Directory::sortBySize() {}//TODO

vector<BaseFile*> Directory::getChildren() {
    return children;
}

int Directory::getSize() {
    int size(0);
    if (children.empty())
        return size;

    vector<BaseFile*>::iterator it = children.begin();
    for (; it!=children.end() ; it++){
      size = size + (*it)->getSize();
    }
    return size;
}

string Directory::getAbsolutePath() {
    string Path;
    if(parent!= nullptr){
        Path = (*parent).getAbsolutePath() + "/" + this->getName();
    }
    else Path = "/";

    return Path;
    }

