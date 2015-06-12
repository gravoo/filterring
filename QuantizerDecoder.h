//
// Created by gravoo on 6/7/15.
//

#ifndef KWANTYZACJA_QUANTIZERDECODER_H
#define KWANTYZACJA_QUANTIZERDECODER_H


#include "Quantizer.h"

class QuantizerDecoder :public Quantizer {


public:
    QuantizerDecoder() { }

    std::queue<bool> lowPassDecoder(std::queue<bool> myQueueY, std::queue<bool> myQueueZ, Image &image);

    std::queue<bool> hightPassDecoder(std::queue<bool> myQueueY, std::queue<bool> myQueueZ, Image &image);

private:


    std::queue<bool> decodeDifference(std::queue<bool> &myInQueue, Image &image);

    std::queue<bool> decodeLowPassFilter(std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ, Image &image);

    std::queue<bool> decodeHighPassFilter(std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ, Image &image);
};


#endif //KWANTYZACJA_QUANTIZERDECODER_H
