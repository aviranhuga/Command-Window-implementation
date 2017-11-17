#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Files.h"


class FileSystem {
private:
	Directory* rootDirectory;
	Directory* workingDirectory;
public:
	FileSystem();
	Directory& getRootDirectory() const; // Return reference to the root directory
	Directory& getWorkingDirectory() const; // Return reference to the working directory
	void setWorkingDirectory(Directory *newWorkingDirectory); // Change the working directory of the file system


	~FileSystem();//Destructor
	FileSystem(const FileSystem& other);//copy constuctor
	FileSystem& operator=(const FileSystem& rhs); // Assinment operator
	FileSystem& operator=(FileSystem&& rhs);//Move Assignment operator
	FileSystem(FileSystem&& rhs);//Move constructor
};


#endif
