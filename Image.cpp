//
// Created by gravoo on 5/11/15.
//

#include <iostream>
#include "Image.h"

Image::Image(std::string fileName) {
    std::queue<bool> myqueue=readFile.readFile(fileName);
    init(myqueue);
}


Image::Image(Image &image) {
    header=image.header;
    foot=image.foot;
    width=image.width;
    height=image.height;
}

Image::Image(std::queue<bool> &myqueue) {
    init(myqueue);
}

std::string Image::getFoot() const {
    return foot.to_string();
}

std::string Image::getHeader() const {
    return header.to_string();
}

void Image::setHeader(std::queue<bool> &myqueue) {

    for(int i=sizeOfHeader-1;i>=0;i--){
        header[i]=myqueue.front();
        myqueue.pop();
    }
    std::bitset<16> tmp (header.to_string().substr(13*8,8)+header.to_string().substr(12*8,8));
    std::bitset<16> tmp2 (header.to_string().substr(15*8,8)+header.to_string().substr(14*8,8));
    width=tmp.to_ulong();
    height=tmp2.to_ulong();
}

void Image::setFoot(std::queue<bool> &myqueue) {
    for(int i=sizeOfFoot-1;i>=0;i--) {
        foot[i] = myqueue.front();
        myqueue.pop();

    }

}
std::vector<Pixel> & Image::getTableOfPixels() {
    return tableOfPixels;
}

void Image::setTableOfPixels(std::queue<bool>& myqueue) {
    std::bitset<8> tmpRed;
    std::bitset<8> tmpGreen;
    std::bitset<8> tmpBlue;
    tableOfPixels.reserve(width*height);
    while(myqueue.size()>sizeOfFoot){

         setColors(myqueue, tmpRed, tmpGreen, tmpBlue);

    }
    size=tableOfPixels.size();
}

void Image::setColors(std::queue<bool> &myqueue, std::bitset<8> &tmpRed, std::bitset<8> &tmpGreen,
                      std::bitset<8> &tmpBlue) {
    tmpRed=setColor(myqueue);
    tmpGreen=setColor(myqueue);
    tmpBlue=setColor(myqueue);
    tableOfPixels.push_back(Pixel(tmpRed,tmpGreen,tmpBlue));
}

std::bitset<8> Image::setColor(std::queue<bool> &myqueue){
    std::bitset<8> tmp;
    for(int i{7};i>=0;i--) {
        tmp[i] = myqueue.front();
        myqueue.pop();
    }
    return tmp;
}

unsigned int Image::getHeight() const {
    return height;
}

unsigned int Image::getWidth() const {
    return width;
}
std::string Image::operator[](int i){
    if(i<0||i>=size) return "000000000000000000000000";
    return tableOfPixels[i].getStringColor();
}
double Image::countEntropy(){

    std::map<std::string,int> counter;
    std::map<std::string,int> counterR;
    std::map<std::string,int> counterG;
    std::map<std::string,int> counterB;

    for(auto &x:tableOfPixels){
        counter[x.getStringColor()]=+1;
        counterR[x.getRed()]=+1;
        counterG[x.getGreen()]=+1;
        counterB[x.getBlue()]=+1;
    }
    double  entrophy{0};
    entrophy = getDouble(counter, entrophy);

    std::cerr<<getDouble(counterR, 0)*-1.0<<"   ";
    std::cerr<<getDouble(counterG, 0)*-1.0<<"   ";
    std::cerr<<getDouble(counterB, 0)*-1.0<<"   ";

    return entrophy*-1.0;
}


double Image::getDouble(const std::map<std::string, int> &counter, double entrophy) const {
    for(auto x:counter) {
            entrophy += (double) x.second / (double) counter.size() * log2((double) x.second / (double) counter.size());
    }
    return entrophy;
}

void Image::init(std::queue<bool> &myqueue) {
    setHeader(myqueue);
    setTableOfPixels(myqueue);
    setFoot(myqueue);

}
