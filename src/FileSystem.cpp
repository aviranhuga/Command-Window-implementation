//
// Created by aviran on 12/11/17.
//
#include "../include/FileSystem.h"
#include "../include/GlobalVariables.h"
#include "../include/Commands.h"

FileSystem::FileSystem():rootDirectory(new Directory("Root", nullptr)),workingDirectory(nullptr){
    workingDirectory = this->rootDirectory;
}

Directory& FileSystem::getRootDirectory() const {
    return *rootDirectory;
}

Directory& FileSystem::getWorkingDirectory() const {
    return *workingDirectory;
}

void FileSystem::setWorkingDirectory(Directory *newWorkingDirectory) {
    workingDirectory = newWorkingDirectory;
}


//............................
//.......RULE OF 5............
//............................

FileSystem::~FileSystem() { //Destructor
    delete(rootDirectory);
    if (verbose==1 || verbose==3)cout << "~FileSystem()" << endl;
}

//Copy Constructor
FileSystem::FileSystem(const FileSystem &other):rootDirectory(nullptr),workingDirectory(nullptr) {

    //copy the root
    Directory* temp = &other.getRootDirectory();
    rootDirectory = new Directory(*temp);

    temp = rootDirectory;
    string nextdir;
    size_t found;
    bool founddir=false;

    //finding working directory
    string path = other.getWorkingDirectory().getAbsolutePath();
    path = path.substr(1);// get abolute path with out '/' in the start

    while (path.size()!=0){
        found = path.find('/');
        if (found != string::npos) {// found the '/' char
            nextdir = path.substr(0, found);
            path = path.substr(found + 1);
        } else {// last dir
            nextdir = path;
            path = "";
        }
            founddir = false;
            vector<BaseFile *> vct = (*temp).getChildren();
            for (unsigned int i = 0; (i < vct.size()) & (founddir == false); i++) {
                if (vct[i]->getName().compare(nextdir) == 0 && vct[i]->directoryType()) {
                    temp = (Directory *) (vct[i]);
                    founddir = true;
                }
        }//end of else
    }//end of while

    workingDirectory = temp;

    if (verbose==1 || verbose==3)cout << "FileSystem(const FileSystem& other)" << endl;
}

FileSystem& FileSystem::operator=(const FileSystem &rhs) {

    rootDirectory = &rhs.getRootDirectory();
    workingDirectory = &rhs.getWorkingDirectory();

    if (verbose==1 || verbose==3)cout << "FileSystem& operator=(const FileSystem& rhs)" << endl;
    return *this;
}

FileSystem& FileSystem::operator=(FileSystem &&rhs) {

    rootDirectory = &rhs.getRootDirectory();
    workingDirectory = &rhs.getWorkingDirectory();

    if (verbose==1 || verbose==3)cout << "FileSystem& operator=(FileSystem&& rhs)" << endl;
    return *this;
}

FileSystem::FileSystem(FileSystem &&rhs):rootDirectory(&rhs.getRootDirectory()),workingDirectory(&rhs.getWorkingDirectory()) {

    if (verbose==1 || verbose==3)cout << "FileSystem(FileSystem&& rhs)" << endl;
}


