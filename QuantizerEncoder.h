//
// Created by gravoo on 6/7/15.
//

#ifndef KWANTYZACJA_QUANTIZERENCODER_H
#define KWANTYZACJA_QUANTIZERENCODER_H


#include "Quantizer.h"

class QuantizerEncoder : public Quantizer {

public:
    QuantizerEncoder() { }

    std::tuple<std::queue<bool>, std::queue<bool>> lowPassEncoder(Image &image, unsigned int bits);

    std::tuple<std::queue<bool>, std::queue<bool>> highPassEncoder(Image &image, unsigned int bits);
private:

    std::queue<bool> diffEncode(std::queue<bool> &myInQueue, Image &image, unsigned int bits);

    void lowPassFilter(Pixel &pixel_0, Pixel &pixel_1, std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ);

    void filterFillQueue(unsigned long xn0, unsigned long xn1, std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ);

    void initResultQueues(Image &image, std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ) const;

    void highPassFilter(Pixel &pixel, Pixel &pixel1, std::queue<bool> &myQueueY, std::queue<bool> &myQueueZ);

    std::queue<bool> quantizeImage(std::queue<bool> &myInQueue, unsigned int bits);
};


#endif //KWANTYZACJA_QUANTIZERENCODER_H
