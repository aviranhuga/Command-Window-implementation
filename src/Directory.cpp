//
// Created by aviran on 08/11/17.
//

#include "../include/Files.h"
#include "../include/GlobalVariables.h"

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
                delete *it;
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

bool Directory::directoryType() {
    return true;
}

//............................
//.......RULE OF 5............
//............................

Directory::~Directory() { //Destructor
    BaseFile *pd = nullptr;
    vector<BaseFile *> vct = getChildren();
    if (!vct.empty())//not empty
        for (int i = 0; i < vct.size(); i++) {
                pd = vct[i];
                delete pd;
            }
    if (verbose==1 || verbose==3)cout << "~Directory()" << endl;
}

//Copy Constructor
Directory::Directory(const Directory &other):BaseFile(other.getName()) {

    this->setParent(other.getParent());//same parent

    Directory *tempDIR = nullptr;
    File *tempFILE = nullptr;

    vector<BaseFile *> vct = other.children;
    if (!vct.empty())//not empty
        for (int i = 0; i < vct.size(); i++) {
            if(vct[i]->directoryType()){//he's a directory
                tempDIR = new Directory(*(Directory *)vct[i]);
                this->addFile(tempDIR);
            }else{//hes a file
                tempFILE = new File(vct[i]->getName(),vct[i]->getSize());
                this->addFile(tempFILE);
            }
         }//end of for
    if (verbose==1 || verbose==3)cout << "Directory(const Directory& other)" << endl;
}

Directory& Directory::operator=(const Directory &rhs) {

    this->setName(rhs.getName());
    this->setParent(rhs.getParent());

    //delete from his parent
    bool found=false;
    if(this->getParent() != nullptr) {
        vector<BaseFile *>::iterator it = this->getParent()->children.begin();// iterator to first element
        for (; it != children.end() & found == false; it++) {
            if ((*it) == this) {
                children.erase(it);
                found = true;
            }
        }
    }
    //set new children
    this->children = rhs.children;

    if (verbose==1 || verbose==3)cout << "Directory& operator=(const Directory& rhs)" << endl;
}

Directory& Directory::operator=(Directory &&rhs) {

    this->setName(rhs.getName());
    this->setParent(rhs.getParent());

    //delete from his parent
    bool found=false;
    if(this->getParent() != nullptr) {
        vector<BaseFile *>::iterator it = this->getParent()->children.begin();// iterator to first element
        for (; it != children.end() & found == false; it++) {
            if ((*it) == this) {
                children.erase(it);
                found = true;
            }
        }
    }
    //set new children
    this->children = rhs.children;

    if (verbose==1 || verbose==3)cout << "Directory& operator=(Directory&& rhs)" << endl;
}

Directory::Directory(Directory &&rhs):BaseFile(rhs.getName()) {

    this->setParent(rhs.getParent());//same parent
    this->children=rhs.getChildren();
    if (verbose==1 || verbose==3)cout << "Directory(Directory&& rhs)" << endl;
}


