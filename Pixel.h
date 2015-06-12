//
// Created by gravoo on 5/11/15.
//

#ifndef LISTA6_PIXEL_H
#define LISTA6_PIXEL_H


#include <bitset>
#include <iostream>

class Pixel {
    std::bitset<8> red;
    std::bitset<8> green;
    std::bitset<8> blue;

public:
    Pixel(const std::bitset<8> red, const std::bitset<8> green, const std::bitset<8> blue) : red(red), green(green),
                                                                                             blue(blue) { }

    Pixel(std::string basic_string){
        std::bitset<8> red(basic_string.substr(0,7));
        this->red=red;
        std::bitset<8> green(basic_string.substr(8,15));
        this->green=green;
        std::bitset<8> blue(basic_string.substr(16,23));
        this->blue=blue;
    }
    std::string getStringColor();
    Pixel(){ };

    std::string getBlue();

    std::string getGreen();

    std::string getRed();

    unsigned long getValBlue();

    unsigned long getValRed();

    unsigned long getValGreen();
};


#endif //LISTA6_PIXEL_H
