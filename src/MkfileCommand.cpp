//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"
#include <cmath>

MkfileCommand::MkfileCommand(string args):BaseCommand(args) {}

void MkfileCommand::execute(FileSystem &fs) {
    string args = getArgs();
    string filesize; // size of the file
    string name; // name of the file
    string path; // the path to the file
    size_t found;
    found = args.find_last_of("/");
    if (found != string::npos) {// found the '/' char - there is a path
        path = args.substr(0, found); //save path
        args = args.substr(found + 1); // delete path from args
    }else path = "";
        found = args.find(" ");
    if (found != string::npos) {//found the " "
        name = args.substr(0, found); //save name
        filesize = args.substr(found); // save size
    }else return;

    filesize=fixstring(filesize);
    name=fixstring(name);

    //get size in int
    int intSIZE = 0;
    for (unsigned int i=0; i<filesize.size() ; i++){
        if (!(48 <= (int)filesize[i] && (int)filesize[i] <= 57)) return;
        intSIZE=intSIZE + ((int)filesize[i]-48)*((int)pow(10,(filesize.size()-1-i)));
    }
    Directory* temp = &fs.getWorkingDirectory();
    if (!path.empty()){ // if there is a path
    temp = findpath(fs,path);
    if (temp==nullptr) {
        cout << "The system cannot find the path specified" << endl;
        return;
     }
    }


    vector<BaseFile *> vct = (*temp).getChildren();
    if (!vct.empty())//not empty
        for (unsigned int i=0; i<vct.size() ; i++) {
            if (vct[i]->getName().compare(name) == 0) {//file or dir with the same name
                cout << "File already exists" << endl;
                return;
            }
        }
        //Check if the name is legit
        for(unsigned int i=0 ; i<name.size() ; i++) {
            if (!((97 <= (int) name[i] && (int) name[i] <= 122) || (65 <= (int) name[i] && (int) name[i] <= 90) || (48 <= (int) name[i] && (int) name[i] <= 57)))
                return;
        }
        BaseFile* newfile = new File(name,intSIZE);
        temp->addFile(newfile);
}

string MkfileCommand::toString() {
    return "mkfile";
}

MkfileCommand::~MkfileCommand() {

}
