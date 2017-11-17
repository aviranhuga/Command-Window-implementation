//
// Created by aviran on 14/11/17.
//

#include "../include/Commands.h"

CpCommand::CpCommand(string args):BaseCommand(args) {}

void CpCommand::execute(FileSystem &fs) {
    if(getArgs().empty()){
        cout << "No such file or directory" << endl;
        return;
    }

    string args = getArgs();
    string source; // source path
    string destination; // destination path
    string filename;
    size_t found;
    Directory *tempsrc = nullptr;
    Directory *tempDIR = nullptr;
    File *tempFILE = nullptr;

    found = args.find(" ");
    if (found != string::npos) {// found the " " char - there is a path
        source = args.substr(0, found); //save path
        destination = args.substr(found + 1); //save destination
        source = this->fixstring(source);
        destination = this->fixstring(destination);
    }else {
        cout << "No such file or directory" << endl;
        return;
    }

    Directory* tempdest = findpath(fs,destination);
    if (tempdest== nullptr){
        cout << "No such file or directory" << endl;
        return;
    }

    if (source[source.size()-1]=='/'){
        cout << "No such file or directory" << endl;
        return;
    }
    found = source.find_last_of("/");//if there a path
    if (found != string::npos) {// found the '/' char
        args = source.substr(0, found); //save source
        filename = source.substr(found + 1); // save file name
        source = args;
        if (source.compare("")==0)source = "/"; //source is the root
        tempsrc = findpath(fs,source);
        if (tempsrc== nullptr){
            cout << "No such file or directory" << endl;
            return;
        }
    }else {
        tempsrc = &fs.getWorkingDirectory();
        filename = source;
    }

    if (Findfile(tempdest,filename))return;

    bool foundfile=false;
    vector<BaseFile *> vct = (*tempsrc).getChildren();
    if (!vct.empty())//not empty
        for (int i=0; i<vct.size() && foundfile==false ; i++) {
            if (vct[i]->getName().compare(filename) == 0) {//found the file
                foundfile=true;
                if(vct[i]->directoryType()){//he's a directory
                    tempDIR = new Directory(*(Directory *)vct[i]);
                    tempDIR->setParent(tempdest);
                    (*tempdest).addFile(tempDIR);
                }else{//hes a file
                    tempFILE = new File(*(File *)vct[i]);
                    (*tempdest).addFile(tempFILE);
                }
            }//end of found file
        }//end of for loop

     if(foundfile==false){//didnt found the file
         cout << "No such file or directory" << endl;
         return;
     }

}

string CpCommand::toString() {
    return "cp";
}