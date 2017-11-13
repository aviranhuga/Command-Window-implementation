//
// Created by aviran on 12/11/17.
//
#include "../include/FileSystem.h"

FileSystem::FileSystem() {
    Directory* Root = new Directory("Root", nullptr);
    rootDirectory = Root;
    workingDirectory = Root;
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