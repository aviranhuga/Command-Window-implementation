//
// Created by aviran on 12/11/17.
//

#include "../include/Commands.h"

LsCommand::LsCommand(string args):BaseCommand(args) {}



void LsCommand::execute(FileSystem &fs) {
    size_t found;
    found = getArgs().find("-s");
    string path = getArgs();
    //WHICH SORT TO USE
    bool sortBy = true; // true - name , false - size
    if (found != string::npos) { // found the '-s' char
        if (path.compare("-s")==0)path=""; //only -s
        else if(path.size()>=3) path = getArgs().substr(found + 3);
        sortBy = false;
    }
    //DELETE SPACES
    if (!path.empty()){
    bool finish=false;
    while(finish==false) {//delete all the ' ' from the start
        if (path[0] !=' ')finish = true;
        else path = path.substr(1);
        }
    }//end of delete spaces
    Directory *temp = &fs.getWorkingDirectory();
    if (!path.empty()) { // with path
        temp = findpath(fs, path);
        if (temp == nullptr) {
            cout << "The system cannot find the path specified" << endl;
            return;
        }
    }//end of with path
    //sort
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