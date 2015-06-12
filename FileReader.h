//
// Created by gravoo on 5/11/15.
//
#include <string>
#include <iostream>
#include <initializer_list>
#include <queue>
#include <fstream>

#ifndef LISTA6_FILEREADER_H
#define LISTA6_FILEREADER_H


class FileReader {

    void saveToQueue(std::queue<bool> &myqueue, char c);
public:
    std::queue<bool> readFile(std::string fileName);
};


#endif //LISTA6_FILEREADER_H
