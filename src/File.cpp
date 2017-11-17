//
// Created by aviran on 08/11/17.
//

#include "../include/Files.h"

File::File(string name, int size):BaseFile(name), size(size){
}

int File::getSize() {
    return size;
}

File::~File()=default;

bool File::directoryType() {
    return false;
}
