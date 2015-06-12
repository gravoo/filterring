//
// Created by gravoo on 5/11/15.
//

#include "FileReader.h"

std::queue<bool> FileReader::readFile(std::string fileName) {
    std::queue<bool> myqueue;
    std::ifstream myfile(fileName, std::ios::binary | std::ios::in);
    if (myfile.is_open()) {
        char c;
        while (myfile.get(c)) {
            saveToQueue(myqueue,c);
        }
        myfile.close();
    }
    else {
        std::cerr << "error file not opened";
    }
    std::cerr<<"DONE\n";
    return myqueue;
}

void FileReader::saveToQueue(std::queue<bool> &myqueue, char c) {
    for (int i = 7; i >= 0; i--) {
        myqueue.emplace((c >> i) & 1);
    }

}
