//
// Created by gravoo on 5/11/15.
//

#ifndef LISTA6_FILEWRITER_H
#define LISTA6_FILEWRITER_H


#include <queue>
#include <string>
#include <iostream>
#include <initializer_list>
#include <queue>
#include <fstream>


class FileWriter {

    char toChar(std::queue<bool> &myQueue, int size);
public:
    void toFile(std::queue<bool> myQueue, std::string outFileName);

};


#endif //LISTA6_FILEWRITER_H
