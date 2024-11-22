#include "input.h"


void Input::SetUp(bool up)
{
    this->up = up;
}
void Input::SetLeft(bool left){
    this->left = left;
}
void Input::SetRight(bool right){
    this->right = right;
}
void Input::SetDown(bool down){
    this->down = down;
}

bool Input::GetUp(){
    return up;
}
bool Input::GetLeft(){
    return left;
}
bool Input::GetRight(){
    return right;
}
bool Input::GetDown(){
    return down;
}