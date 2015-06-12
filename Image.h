//
// Created by gravoo on 5/11/15.
//

#ifndef LISTA6_IMAGE_H
#define LISTA6_IMAGE_H

#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include "Pixel.h"
#include "FileReader.h"

const int sizeOfHeader=18*8;
const int sizeOfFoot=26*8;

class Image {

private:
    std::bitset<sizeOfHeader> header;
    std::bitset<sizeOfFoot> foot;
    unsigned int width;
    unsigned int height;
    unsigned int size;
    std::vector<Pixel> tableOfPixels;
    std::bitset<8> setColor(std::queue<bool> &myqueue);
    FileReader readFile;
    void init(std::queue<bool> &myqueue);
    void setHeader(std::queue<bool> &myqueue);
    void setFoot(std::queue<bool> &myqueue);
    void setTableOfPixels(std::queue<bool> &myqueue);
    double getDouble(const std::map<std::string, int> &counter, double entrophy) const;


public:

    Image() { }
    Image(std::string fileName);
    Image(Image &image);
    Image(std::queue<bool> &myqueue);

    unsigned int getSize() const {
        return size;
    }
    unsigned int getFooterSize() const {
        return sizeOfFoot;
    }
    unsigned int getHeaderSize() const {
        return sizeOfHeader;
    }

    std::string getFoot() const;
    std::string getHeader() const;
    std::vector<Pixel> & getTableOfPixels();
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    std::string operator[](int i);
    double countEntropy();

    void setColors(std::queue<bool> &myqueue, std::bitset<8> &tmpRed, std::bitset<8> &tmpGreen,
                   std::bitset<8> &tmpBlue);

    void uniformQuantizer();
};



#endif //LISTA6_IMAGE_H
