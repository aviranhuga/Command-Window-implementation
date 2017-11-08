//
// Created by aviran on 08/11/17.
//

#include "../include/Files.h"
#include <iostream>

int main(int , char **) {

        BaseFile* BaseFile1 = new File("test",1);

        File File1("File1",1);
        File File2("File2",2);
        File File3("File3",3);
        File File11("File11",4);
        File File12("File12",5);
        File File21("File21",6);
        File File22("File22",7);
        File File111("File111",8);
        File File121("File121",9);
        File File1111("File1111",10);
        File File1112("File1112",0);

        Directory DirRoot("root", nullptr);
        Directory Dir1("Dir1" , &DirRoot);
        Directory Dir2("Dir2" , &DirRoot);
        Directory Dir11("Dir11" , &Dir1);
        Directory Dir12("Dir12" , &Dir1);
        Directory Dir111("Dir111" , &Dir11);

        cout << "BaseFile.cpp Tests starts:"<< endl;

        //Test 1 check - BaseFile.getName()
        if(File1.getName().compare("File1")==0)
            cout << "1 test is OK"<<endl;
        else cout << "Fail at test 1"<< endl;

         //Test 2 check - BaseFile.setName()
        File2.setName("File1");
        if(File2.getName().compare("File1")==0)
            cout << "2 test is OK"<<endl;
         else cout << "Fail at test 2"<< endl;
        File2.setName("File2");

        //Test 3 check - BaseFile.getName()
         if(File1.getName().compare(File2.getName())==0)
          cout << "3 test is OK"<<endl;
         else cout << "Fail at test 3"<< endl;


        cout << "File.cpp Tests starts:"<< endl;

        //Test 4 check - BaseFile.getName()
          if(File1.getSize()==1 && File2.getSize()==2)
             cout << "4 test is OK"<<endl;
         else cout << "Fail at test 4"<< endl;


        //Test 5 check - Directory *getParent()
        cout << "Directory.cpp Tests starts:"<< endl;
        if(DirRoot.getParent() == nullptr && Dir111.getParent() == &Dir11)
          cout << "5 test is OK"<<endl;
         else cout << "Fail at test 5"<< endl;

        //Test 6 check - setParent(Directory *newParent)
        Dir12.setParent(&Dir2);
         if(Dir12.getParent() == &Dir2)
             cout << "6 test is OK"<<endl;
         else cout << "Fail at test 6"<< endl;
        Dir12.setParent(&Dir1);

    //Test 7 check - addFile(BaseFile* file)
    DirRoot.addFile(BaseFile1);
    DirRoot.addFile(&File2);
    vector<BaseFile*>::iterator iterator1 = DirRoot.getChildren().begin();
    //string what =  (*(*iterator1))->getName();
    //cout << what << endl;

    //for (; it!=DirRoot.getChildren().end(); it++) {
   //     cout << (*it)->getName() << endl;
   //     cout << "FUCK" << endl;
   // }
        return 0;
}
