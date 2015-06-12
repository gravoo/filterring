//
// Created by gravoo on 6/7/15.
//

#include "QuantizerEncoder.h"
std::tuple<std::queue<bool>, std::queue<bool>> QuantizerEncoder::highPassEncoder(Image &image,
                                                                                 unsigned int bits){

    std::queue<bool> myQueueY, myQueueZ;

    int i{0};
    for( i=1;i<image.getTableOfPixels().size()/2;i++){
        highPassFilter(image.getTableOfPixels()[(2*i - 1)], image.getTableOfPixels()[2*i], myQueueY, myQueueZ);
    }
    myQueueY= quantizeImage(myQueueY, std::pow(2, bits));
    myQueueZ= quantizeImage(myQueueZ, std::pow(2, bits));


    return make_tuple(myQueueY,myQueueZ);

}
std::queue<bool> QuantizerEncoder::quantizeImage(std::queue<bool> &myInQueue, unsigned int bits) {
    std::queue<bool> result;

    char x_n{0};
    while(!myInQueue.empty()){
        x_n=getNumber(myInQueue);
        x_n=getQantizedValue(x_n,bits);
        fillResultQueue(result,x_n);
    }

    return result;
}

void QuantizerEncoder::initResultQueues(Image &image, std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ) const {

    fillResultQueue(myQueueY,image.getTableOfPixels()[0].getValRed());
    fillResultQueue(myQueueY,image.getTableOfPixels()[0].getValGreen());
    fillResultQueue(myQueueY,image.getTableOfPixels()[0].getValBlue());

    fillResultQueue(myQueueZ,image.getTableOfPixels()[0].getValRed());
    fillResultQueue(myQueueZ,image.getTableOfPixels()[0].getValGreen());
    fillResultQueue(myQueueZ,image.getTableOfPixels()[0].getValBlue());


}

std::tuple<std::queue<bool>, std::queue<bool>> QuantizerEncoder::lowPassEncoder(Image &image,
                                                                                unsigned int bits) {

    std::queue<bool> myQueueY, myQueueZ;

    initResultQueues(image, myQueueY, myQueueZ);

    for(int i=1;i<image.getTableOfPixels().size();i++) {
        lowPassFilter(image.getTableOfPixels()[i - 1], image.getTableOfPixels()[i], myQueueY, myQueueZ);
    }

    myQueueY= diffEncode(myQueueY, image, std::pow(2,bits));
    myQueueZ= diffEncode(myQueueZ, image, std::pow(2,bits));

    return make_tuple(myQueueY,myQueueZ);
}

std::queue<bool> QuantizerEncoder::diffEncode(std::queue<bool> &myInQueue, Image &image, unsigned int bits) {
    std::queue<bool> myOutQueue;
    Quantizer::setHeader(myOutQueue,image);
    int x_n {0},x_n_1{0};
    int d_n{0};
    while(!myInQueue.empty()){

        x_n=getNumber(myInQueue);
        d_n=x_n-x_n_1;
        d_n=getQantizedValue(d_n,bits);
        x_n_1+=d_n;
        fillResultQueue(myOutQueue,x_n_1);
    }

    setFooter(myOutQueue,image);
    return myOutQueue;

}

void QuantizerEncoder::lowPassFilter(Pixel &pixel_0, Pixel &pixel_1, std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ) {

    filterFillQueue(pixel_0.getValRed(), pixel_1.getValRed() , myQueueY,myQueueZ);
    filterFillQueue(pixel_0.getValGreen(), pixel_1.getValGreen(), myQueueY,myQueueZ);
    filterFillQueue(pixel_0.getValBlue(), pixel_1.getValBlue(), myQueueY,myQueueZ);

}

void QuantizerEncoder::filterFillQueue(unsigned long xn0, unsigned long xn1, std::queue<bool> &myQueueY,
                                std::queue<bool> &myQueueZ) {

    char tmp=(xn1+xn0)/2;
    fillResultQueue(myQueueY,(tmp));
    tmp=(xn1-xn0)/2;
    fillResultQueue(myQueueZ,(tmp));

}

void QuantizerEncoder::highPassFilter(Pixel &pixel, Pixel &pixel1, std::queue<bool> &myQueueY,
                                      std::queue<bool> &myQueueZ) {
    lowPassFilter(pixel,pixel1,myQueueY,myQueueZ);

}
