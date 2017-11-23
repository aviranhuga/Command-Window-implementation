//
// Created by aviran on 15/11/17.
//

#include "../include/Commands.h"

RenameCommand::RenameCommand(string args):BaseCommand(args) {
}

void RenameCommand::execute(FileSystem &fs) {

    if(getArgs().empty()){
        cout << "No such file or directory" << endl;
        return;
    }

    string args = getArgs();
    string source; // source path
    string newname; // new name
    string oldname; // old name
    size_t found;
    Directory *tempsrc = nullptr;

    found = args.find(" ");
    if (found != string::npos) {// found the " " char
        source = args.substr(0, found); //save path to file/dir
        newname = args.substr(found + 1); //save new name
        source = this->fixstring(source);
        newname = this->fixstring(newname);
    }else return;


    found = source.find_last_of("/");//if there a path
    if (found != string::npos) {// found the '/' char
        args = source.substr(0, found); //save source
        oldname = source.substr(found + 1); // save old file name
        source = args;
        if (source.compare("")==0)source = "/"; //source is the root
        tempsrc = findpath(fs,source);
        if (tempsrc== nullptr){
            cout << "No such file or directory" << endl;
            return;
        }
    }else { // file in the working directory
        tempsrc = &fs.getWorkingDirectory();
        oldname = source;
    }

    bool foundfile=false;
    vector<BaseFile *> vct = (*tempsrc).getChildren();
    if (!vct.empty())//not empty
        for (unsigned int i=0; i<vct.size() && foundfile==false ; i++) {
            if (vct[i]->getName().compare(oldname) == 0) {//found the file
                if (vct[i]->directoryType()) {
                    if (((Directory *)vct[i])->getAbsolutePath().compare(fs.getWorkingDirectory().getAbsolutePath()) ==0) {//trying to change the working directory
                        cout << "Can't rename the working directory" << endl;
                        return;
                    }
                }
                if (Findfile(tempsrc,newname))return;
                foundfile=true;
                //check if the name is legit
                for(unsigned int i=0 ; i<newname.size() ; i++) {
                    if (!((97 <= (int) newname[i] && (int) newname[i] <= 122) || (65 <= (int) newname[i] && (int) newname[i] <= 90) || (48 <= (int) newname[i] && (int) newname[i] <= 57)))
                        return;
                }
                vct[i]->setName(newname);
            }//end of found file
        }//end of for loop

    if(foundfile==false){//didnt found the file
        cout << "No such file or directory" << endl;
        return;
    }


}

string RenameCommand::toString() {
    return "rename";
}

RenameCommand::~RenameCommand() {

}
