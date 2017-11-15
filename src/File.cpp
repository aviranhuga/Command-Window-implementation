//
// Created by aviran on 08/11/17.
//

#include "../include/Files.h"

File::File(string name, int size):BaseFile(name), size(size){
}

int File::getSize() {
    return size;
}

//File::~File()=default;
File::~File(){
    cout << "file destractor" << endl;
}

bool File::directoryType() {
    return false;
}

File::File(const File &other):BaseFile(other.getName()){
    size = other.size;
    cout << "file copy constructor" << endl;
}

