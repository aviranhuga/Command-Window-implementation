//
// Created by aviran on 08/11/17.
//

#include "../include/Files.h"

BaseFile::BaseFile(string name)
        :name(name){
}

string BaseFile::getName() const  {
    return name;
}

void BaseFile::setName(string newName) {
    name = newName;
}
