#include <iostream>
#include<Windows.h>
#include <winuser.h>
#include <vector>
#include <string>
#include "Action.hpp"
using namespace std;



int Action::instanceCount = 0;

void Action::leftClick(double x, double y, int time){
    
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
    double fx = x*(65535.0f / fScreenWidth);
    double fy = y*(65535.0f / fScreenHeight);

    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = fx;
    Input.mi.dy = fy;
    SendInput(1, &Input, sizeof(INPUT));

    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
    Input.mi.time = time;
    ::SendInput(1,&Input,sizeof(INPUT));


    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
    ::SendInput(1,&Input,sizeof(INPUT));




}

void Action::rightClick(double x, double y, int time){
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
    double fx = x*(65535.0f / fScreenWidth);
    double fy = y*(65535.0f / fScreenHeight);
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = fx;
    Input.mi.dy = fy;
    SendInput(1, &Input, sizeof(INPUT));

    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_RIGHTDOWN;
    Input.mi.time = time;
    ::SendInput(1,&Input,sizeof(INPUT));

    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
    ::SendInput(1,&Input,sizeof(INPUT));

}

void Action::startAction(){
    if (buttonClick=="L"||buttonClick=="l")
    {
        
        leftClick(posX,posY,time);
        display();
    }
    else if (buttonClick=="R"||buttonClick=="r")
    {
        
        rightClick(posX,posY,time);
        display();
    }
    else
    {
        cout << "No button defined" <<endl;
        //printf("hello");
    }
    
}

const string& Action::getName(){
    return this->name;
}
const string& Action::getButton(){
    return this->buttonClick;
}
const double& Action::getPosX(){
    return this->posX;
}
const double& Action::getPosY(){
    return this->posY;
}
const int& Action::getTime(){
    return this->time;
}
const int& Action::getWaitTime(){
    return this->timeToWait;
}


void Action::setName(string name){
    this->name = name;
}

void Action::setTime(int time){

    this->time = time;

}

void Action::setWaitTime(int time){

    this->timeToWait = time;

}

void Action::setPosition(double x , double y){
    this->posX = x;
    this->posY = y;

}

void Action::setX(double x ){
    this->posX = x;

}

void Action::setY(double y ){
    this->posY = y;

}

void Action::display(){
    cout << "\t Action name: "<<name <<endl;
    cout<<"\t Mouse button: "<<buttonClick <<endl;
    cout << "\t Screen position X: "<< posX <<" Y: "<< posY <<endl;
    cout <<"\t Mouse time: " << time << endl;
    cout <<"\t Wait time: " << timeToWait << endl;
    cout <<" "<<endl;
}

// Action::Action(const Action &other){

// }

void Action::setButton(string button){

    this->buttonClick = button;

}

void Action::waitTime(int time){
    Sleep(time);
}

 bool  Action::operator<(const Action& other) const{
    if (other.instanceCount < this->instanceCount)
    {
        return true;
    }
    return false;
    
}



Action::Action(string name,double screenPosX, double screenPosY, int time , int wait,string click): posX(screenPosX),posY(screenPosY),time(time),timeToWait(wait) ,buttonClick(click),name(name)
{
    this->instanceCount++;
   
    
}

Action::~Action()
{
    this->instanceCount--;
}
