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
        for(; it != children.end() & found == false ; it++){
            if( (*it) == file ){
                children.erase(it);
                found=true;
            }//end of if
        }//end of for
}

void Directory::sortByName() {

    if(children.size()<=1)return;
    BaseFile** p = nullptr;
    BaseFile* temp = nullptr;
    bool swapp = true;
    while(swapp){
        swapp = false;
        p = children.data();
        for (size_t i = 0; i < children.size()-1 ; i++) {
            if (BiggerString( (**p).getName(),(**(p+1)).getName()) ){
                temp = (*(p+1));
                (*(p+1))= (*p);
                (*p)=temp;

                swapp = true;
            }
            p++;
        }
    }

}

bool Directory::BiggerString(string a, string b) {
    unsigned long asize=a.size();
    unsigned long bsize=b.size();
    int i=0;
    while(true){
        if(i == asize)
            return false; //a dont have another char, so b is bigger
        if(i == bsize)
            return true; //b dont have another char, so a is bigger
        if((int)a[i]>(int)b[i])
            return true;
        if((int)a[i]<(int)b[i])
            return false;
        i++;
    }
}

void Directory::sortBySize() {

    if(children.size()<=1)return;
    BaseFile** p = nullptr;
    BaseFile* temp = nullptr;
    bool swapp = true;
    while(swapp){
        swapp = false;
        p = children.data();
        for (size_t i = 0; i < children.size()-1 ; i++) {

            if ( ( (**p).getSize()>(**(p+1)).getSize() )
                || (((**p).getSize()==(**(p+1)).getSize())
                   && ( BiggerString( (**p).getName(),(**(p+1)).getName()) )))
                    {
                temp = (*(p+1));
                (*(p+1))= (*p);
                (*p)=temp;

                swapp = true;
            }
            p++;
        }
    }

}

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
    if(parent!= nullptr && this->parent->parent== nullptr) //if its parent is the root
        Path = (*parent).getAbsolutePath() + this->getName();
    else if(parent!= nullptr){
        Path = (*parent).getAbsolutePath() + "/" + this->getName();
    }
    else Path = "/";

    return Path;
    }

Directory::~Directory() {
    if (!children.empty()) {
        BaseFile* pd;
        for (vector<BaseFile *>::iterator it = children.begin(); it != children.end(); ++it) {
            pd = *it;
            delete pd;
            cout << (*it)->getName() << endl;
        }
    }
    cout << "Directiry Destractor:" << endl;
}


bool Directory::directoryType() {
    return true;
}