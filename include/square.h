#pragma once
#include <iostream>
#include <string>

class Square{
    int size;
    std::string color;
    public:
    Square();
    Square(int size, std::string color);
    int returnSize();
    std::string returnColor();
    void setColor(std::string color);
};