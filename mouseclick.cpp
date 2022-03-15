#include<windows.h>
#include <winuser.h>
#include <iostream>
#include <vector>
// #include"vcpkg/packages/sfml_x86-windows/include/SFML/Config.hpp"
// #include"vcpkg/packages/sfml_x86-windows/include/SFML/System.hpp"
// #include"vcpkg/packages/sfml_x86-windows/include/SFML/Window.hpp"
// #include"vcpkg/packages/sfml_x86-windows/include/SFML/Graphics.hpp"
// #include"vcpkg/packages/sfml_x86-windows/include/SFML/Main.hpp"
#include <string.h>
using namespace std;

void leftClick(double x, double y){
    
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
    ::SendInput(1,&Input,sizeof(INPUT));


    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
    ::SendInput(1,&Input,sizeof(INPUT));

}


void rightClick(double x, double y){
    

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
    ::SendInput(1,&Input,sizeof(INPUT));

    ::ZeroMemory(&Input,sizeof(INPUT));
    Input.type      = INPUT_MOUSE;
    Input.mi.dwFlags  = MOUSEEVENTF_RIGHTUP;
    ::SendInput(1,&Input,sizeof(INPUT));

}

POINT getMousePos(){

    POINT position;
    position.x = LOWORD(WM_LBUTTONDOWN);
    position.y = HIWORD(WM_LBUTTONDOWN);

    return position;
}



int main(int argc, char const *argv[])
{
    leftClick(200,200);
    rightClick(200,200);
    Sleep(500);
    leftClick(350,275);
    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //             switch (event.type) {
    //                 case sf::Event::MouseButtonPressed:
    //             cout << "Button " << event.mouseButton.button << " @ "
    //                         << sf::Mouse::getPosition(window).x << ", "
    //                         << sf::Mouse::getPosition(window).y << "\n";
    //             break;
    //         }
    //     }
    // }

    // bool again = true;
    // string againt ;
   
    // while (again )
    // {
    //     Sleep(1000);
    //     /* code */
    //     POINT pos = getMousePos();
    //     cout << pos.x << " " <<pos.y << endl;

    //     cin >> againt;
    //     if (againt =="non")
    //     {
    //         /* code */
    //         again = false;
    //     }
        
    // }
    
   
    return 0;
}
