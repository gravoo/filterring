//
// Created by gravoo on 5/30/15.
//

#ifndef KWANTYZACJA_QUANTIZER_H
#define KWANTYZACJA_QUANTIZER_H


#include "Image.h"

class Quantizer {

public:
    void calcErrors(Image &image, std::queue<bool> quantizedPic);

protected:

    Quantizer() {};

    unsigned int getNumberUnsigned(std::queue<bool> &quantizedPic) const;

    void setFooter(std::queue<bool> &imageOut, Image &image);

    char getQantizedValue(long colorVal, int bitVal);

    void fillResultQueue(std::queue<bool> &imageOut, char result) const;

    void fillWitStinrg(std::queue<bool> &imageOut, std::string basic_string);

    void print(std::string info, double valR, double valG, double valB) const;

    void getImageContent(const Image &image, std::queue<bool> &quantizedPic) const;

    int getNumber(std::queue<bool> &quantizedPic) const;

    void setHeader(std::queue<bool> &imageOut, Image &image);


private:
    std::tuple<double,double,double> countSNR(Image &image, double errorR, double errorG, double errorB);

    std::tuple<double,double,double> countError(std::vector<int> &tabR, std::vector<int> &tabG, std::vector<int> &tabB, Image &img);

    double contSquare(int a, int b);

    void dividePicture(const Image &image, std::queue<bool> &quantizedPic, std::vector<int> &probR, std::vector<int> &probG,
                       std::vector<int> &probB) const;

    double divideError(unsigned int size, double errorR) const;

    char getNumberItem(int colorVal, int bitVal) const;

    char getIntervalNumber(int colorVal, char interval) const;
};


#endif //KWANTYZACJA_QUANTIZER_H
