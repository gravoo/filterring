#include <iostream>

#include "gtest/gtest.h"
#include "Image.h"
#include "FileReader.h"
#include "Quantizer.h"
#include "FileWriter.h"
#include "QuantizerEncoder.h"
#include "QuantizerDecoder.h"

TEST(sample_test_case, sample_test) {

    EXPECT_EQ(2 + 2, 4);

    FileReader reader;
	std::string fileIn{"/media/gravoo/Studia/1Semestr_VI/KIKD/kwantyzacja/labor8/mg.tga"}
    Image pictureTest{fileIn};



    std::queue<bool> myResutYdiff, myResutZdiff;
    std::queue<bool> myResutYquant, myResutZquant;
    QuantizerEncoder encoder{};
    QuantizerDecoder decoder{};
    std::tie(myResutYdiff, myResutZdiff)=
            encoder.lowPassEncoder(pictureTest, 2);

    std::tie(myResutYquant, myResutZquant)=
            encoder.highPassEncoder(pictureTest, 3);

    std::queue<bool> myResultYandZdiff = decoder.lowPassDecoder(myResutYdiff, myResutZdiff, pictureTest);
    std::queue<bool> myResultYandZquant = decoder.hightPassDecoder(myResutYquant, myResutZquant, pictureTest);

    std::cerr<<std::endl;

//    quantizer.calcErrors(pictureTest, myResult);
//    quantizer.calcErrors(pictureTest, myResutYdiff);
//    quantizer.calcErrors(pictureTest, myResultYandZdiff);
//    quantizer.calcErrors(pictureTest,myResultYandZdiff);

    FileWriter writer;

    writer.toFile(myResutYdiff,"/media/gravoo/Studia/1Semestr_VI/KIKD/kwantyzacja/labor8/lowPasY.tga");
    writer.toFile(myResutZdiff,"/media/gravoo/Studia/1Semestr_VI/KIKD/kwantyzacja/labor8/lowPasZ.tga");
    writer.toFile(myResultYandZdiff,"/media/gravoo/Studia/1Semestr_VI/KIKD/kwantyzacja/labor8/resultDiff.tga");
    writer.toFile(myResultYandZquant,"/media/gravoo/Studia/1Semestr_VI/KIKD/kwantyzacja/labor8/resultQuant.tga");




}
