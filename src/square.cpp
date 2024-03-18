#include <square.h>

Square::Square(){
    size = rand()%100;
    color = "red";
}
Square::Square(int size, std::string color){
        this->color = color;
        this->size = size;
    }
int Square::returnSize()
{
    return size;
}
std::string Square::returnColor()
{
    return color;
}
void Square::setColor(std::string color)
{
    this->color = color;
}