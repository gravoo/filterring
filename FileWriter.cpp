//
// Created by gravoo on 5/11/15.
//

#include "FileWriter.h"

void FileWriter::toFile(std::queue<bool> myQueue, std::string outFileName) {

    std::ofstream myfile(outFileName);
    char tmp;
    if (myfile.is_open()) {
        while(myQueue.size()>7)
        {
            tmp= toChar(myQueue, 7);
            myfile<<tmp;

        }
        tmp= toChar(myQueue, myQueue.size());
        myfile<<tmp;
        myfile.close();
    }
    else {
        std::cerr << "error file not opened";
    }

}

char FileWriter::toChar(std::queue<bool> &myQueue, int size) {
    char a = 0;
    for (int i = 0; i <= size; i++) {
        a = a << 1;
        if (myQueue.front()) {
            a++;
        }
        myQueue.pop();
    }
    return a;
}