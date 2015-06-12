//
// Created by gravoo on 6/7/15.
//

#include "QuantizerDecoder.h"


std::queue<bool> QuantizerDecoder::lowPassDecoder(std::queue<bool> myQueueY, std::queue<bool> myQueueZ, Image &image) {
    std::queue<bool> result;
    getImageContent(image,myQueueY);
    getImageContent(image,myQueueZ);

    myQueueZ= decodeDifference(myQueueZ, image);
    myQueueY= decodeDifference(myQueueY, image);

    result= decodeLowPassFilter(myQueueY, myQueueZ, image);
    return result;


}
std::queue<bool> QuantizerDecoder::decodeDifference(std::queue<bool> &myInQueue, Image &image) {
    std::queue<bool> result;
    int x_n = 0,x{0};
    for(int i=0;i<image.getTableOfPixels().size()*3;i++){
        x_n=getNumber(myInQueue);
        fillResultQueue(result,x_n);
    }
    return result;
}
std::queue<bool> QuantizerDecoder::decodeLowPassFilter(std::queue<bool> &myQueueY,
                                                       std::queue<bool> &myQueueZ, Image &image) {
    std::queue<bool> result;
    Quantizer::setHeader(result,image);

    while(!myQueueY.empty()){
        fillResultQueue(result, getNumber(myQueueY)+ getNumber(myQueueZ));
    }
    setFooter(result,image);
    return result;
}

std::queue<bool> QuantizerDecoder::hightPassDecoder(std::queue<bool> myQueueY, std::queue<bool> myQueueZ, Image &image) {
    std::queue<bool> result;

    result=decodeHighPassFilter(myQueueY,myQueueZ,image);

    return result;
}

std::queue<bool> QuantizerDecoder::decodeHighPassFilter(std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ,
                                                        Image &image) {
    std::queue<bool> result;
    char y{0},z{0};
    setHeader(result,image);
    while(!myQueueY.empty()){
        y=getNumber(myQueueY);
        z=getNumber(myQueueZ);
        fillResultQueue(result,y+z);
        fillResultQueue(result,y-z);
    }
    setHeader(result,image);

    return result;
}
