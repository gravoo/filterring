//
// Created by gravoo on 5/11/15.
//

#include "Pixel.h"

std::string Pixel::getStringColor() {
    return red.to_string()+green.to_string()+blue.to_string();
}
std::string Pixel::getRed() {
    return red.to_string();
}
std::string Pixel::getGreen() {
    return green.to_string();
}
std::string Pixel::getBlue() {
    return blue.to_string();
}
unsigned long Pixel::getValBlue(){
    return blue.to_ulong();
}
unsigned long Pixel::getValRed(){
    return red.to_ulong();
}
unsigned long Pixel::getValGreen(){
    return green.to_ulong();
}
