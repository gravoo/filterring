//
// Created by gravoo on 5/30/15.
//

#include "Quantizer.h"

void Quantizer::setHeader(std::queue<bool> &imageOut,Image &image) {
    std::string head=image.getHeader();
    fillWitStinrg(imageOut,head);
}

void Quantizer::fillResultQueue(std::queue<bool> &imageOut, char result) const {
    for (char  i = 7; i >=0; i--) {
       imageOut.emplace(result>>i&1);
    }
}

void Quantizer::setFooter(std::queue<bool> &imageOut, Image &image) {

    std::string foot=image.getFoot();
    fillWitStinrg(imageOut,foot);

}

void Quantizer::fillWitStinrg(std::queue<bool> &imageOut, std::string basic_string) {

    for(auto &x:basic_string){
        if(x=='1')
            imageOut.emplace(1);
        else
            imageOut.emplace(0);
    }

}

void Quantizer::calcErrors(Image &image, std::queue<bool> quantizedPic) {

    std::vector<int> tableRed;
    tableRed.reserve(image.getTableOfPixels().size());
    std::vector<int> tableGreen;
    tableGreen.reserve(image.getTableOfPixels().size());
    std::vector<int> tableBlue;
    tableBlue.reserve(image.getTableOfPixels().size());

    getImageContent(image, quantizedPic);

    dividePicture(image, quantizedPic, tableRed, tableGreen, tableBlue);

    double mseR{0},mseG{0},mseB{0};

    std::tie(mseR,mseG,mseB)=
            countError(tableRed, tableGreen, tableBlue,image);

    print("MSE: ", mseR, mseG, mseB);

    double snrR{0}, snrG{0}, snrB{0};
    std::tie(snrR, snrG, snrB)=
            countSNR(image,mseR,mseG,mseB);

    print("SNR: ", snrR, snrG, snrB);
}

void Quantizer::getImageContent(const Image &image, std::queue<bool> &quantizedPic) const {
    for( int ij=0;ij<image.getHeader().size();++ij)
        quantizedPic.pop();
}

void Quantizer::dividePicture(const Image &image, std::queue<bool> &quantizedPic, std::vector<int> &probR,
                              std::vector<int> &probG, std::vector<int> &probB) const {
    int val{0};
    while(quantizedPic.size()>image.getFooterSize()) {

        val = getNumberUnsigned(quantizedPic);
        probR.push_back(val);
        val = getNumberUnsigned(quantizedPic);
        probG.push_back(val);
        val = getNumberUnsigned(quantizedPic);
        probB.push_back(val);
    }
}

void Quantizer::print(std::string info, double valR, double valG, double valB) const {
    std::cerr<<info<< valR <<" "<< valG <<" "<< valB << std::endl;
}

std::tuple<double,double,double> Quantizer::countError(std::vector<int> &tabR,
                                                       std::vector<int> &tabG, std::vector<int>  &tabB, Image &img) {

    double errorR{0},errorG{0},errorB{0};
    int i=0,N=img.getTableOfPixels().size();
    for(int i=1;i<N;i++){
        errorR+=contSquare(img.getTableOfPixels()[i].getValRed(), tabR[i]);
        errorG+=contSquare(img.getTableOfPixels()[i].getValGreen(), tabG[i]);
        errorB+=contSquare(img.getTableOfPixels()[i].getValBlue(), tabB[i]);
    }
    errorR=divideError(N, errorR);
    errorG=divideError(N, errorG);
    errorB=divideError(N, errorB);

    return std::make_tuple(errorR,errorG,errorB);

}

double Quantizer::divideError(unsigned int size, double errorR) const {
    return errorR/ size;
}

double Quantizer::contSquare(int a, int b){
    return (a-b)*(a-b);
}
char Quantizer::getQantizedValue(long colorVal, int bitVal) {
    char result = getNumberItem(colorVal, bitVal);
    return result;
}
char Quantizer::getNumberItem(int colorVal, int bitVal) const {

    char interval=std::ceil(128/(double )bitVal);
    auto i = getIntervalNumber(colorVal, interval);
    char tmp{0};

    if(colorVal>=0)
    {
        tmp=((i)*interval+(i-1)*interval)/2.0;
    }
    else
        tmp=((i)*interval+(i+1)*interval)/2.0;

    return tmp;
}

char Quantizer::getIntervalNumber(int colorVal, char interval) const {
    int i{0};
    char j{0};
    if(colorVal<0){
        while(i*interval>= colorVal){
            --i;
            --j;
        }
    }
    else{
        while(i*interval<= colorVal){
            ++i;
            ++j;
        }
    }
    return j;
}



unsigned int Quantizer::getNumberUnsigned(std::queue<bool> &quantizedPic) const {
    int val{0};
    for(int i=0;i<=7;i++){
        val=val<<1;
        if(quantizedPic.front()){
            val++;
        }
        quantizedPic.pop();
    }
    return val;
}
int Quantizer::getNumber(std::queue<bool> &quantizedPic) const {
    int val{0};
    for(int i=0;i<=7;i++){
        val=val<<1;
        if(quantizedPic.front()){
            val++;
        }
        quantizedPic.pop();
    }
    return val;
}
std::tuple<double,double,double> Quantizer::countSNR(Image &image, double errorR, double errorG, double errorB){
    double SNRR{0},SNRG{0},SNRB{0};
    unsigned long N = image.getTableOfPixels().size();
    for(int i=1;i< N;i++){
        SNRR+=image.getTableOfPixels()[i].getValRed()*image.getTableOfPixels()[i].getValRed();
        SNRG+=image.getTableOfPixels()[i].getValGreen()*image.getTableOfPixels()[i].getValGreen();
        SNRB+=image.getTableOfPixels()[i].getValBlue()*image.getTableOfPixels()[i].getValBlue();
    }
    SNRR=divideError(N,SNRR);
    SNRG=divideError(N,SNRG);
    SNRB=divideError(N,SNRB);
    return std::make_tuple(SNRR/errorR,SNRG/errorG,SNRB/errorB);
}




