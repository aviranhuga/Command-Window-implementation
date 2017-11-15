//
// Created by aviran on 15/11/17.
//

#include "../include/Commands.h"

HistoryCommand::HistoryCommand(string args, const vector<BaseCommand *> &history)
        :BaseCommand(args),history(history){}

void HistoryCommand::execute(FileSystem &fs) {
        if(!getArgs().empty())return; //Worng args

        if (!history.empty())//not empty
                for (int i=0; i<history.size(); i++) {
                        cout << i << "\t" << history[i]->toString() + " " + history[i]->getArgs() << endl;
                }
}

string HistoryCommand::toString() {
    return "history";
}