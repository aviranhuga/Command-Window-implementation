//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

LsCommand::LsCommand(string args):BaseCommand(args) {}



void LsCommand::execute(FileSystem &fs) {
    size_t found;
    found = getArgs().find("-s");
    string path = getArgs();
    bool sortBy = true; // true - name , false - size
    if (found != string::npos) { // found the '-s' char
        path = getArgs().substr(found + 3);
        sortBy = false;
    }
    Directory *temp = &fs.getWorkingDirectory();
    if (!getArgs().empty()) { // no args
        temp = findpath(fs, path);
        if (temp == nullptr) {
            cout << "The system cannot find the path specified" << endl;
            return;
        }
    }//end of no args
    if(sortBy == false)temp->sortBySize();
    else temp->sortByName();

    vector<BaseFile *> vct = (*temp).getChildren();
            for (int i=0; i<vct.size(); i++)
                if(vct[i]->directoryType())
                    cout << "DIR" << "\t" << vct[i]->getName() << "\t" << vct[i]->getSize() << endl;
                else cout << "FILE" << "\t" << vct[i]->getName() << "\t" << vct[i]->getSize() << endl;
}

string LsCommand::toString(){
    return "ls";
}