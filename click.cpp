
#include<Windows.h>
#include <winuser.h>

//**********************************************************************
//
// Sends Win + D to toggle to the desktop
//
//**********************************************************************
void ShowDesktop()
{
    //OutputString(L"Sending 'Win-D'\r\n");
    INPUT inputs[4] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_LWIN;
    
   
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 65;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 65;
    inputs[2].ki.time = 10065;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;


    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_LWIN;
    inputs[3].ki.time = 10065;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    if (uSent != ARRAYSIZE(inputs))
    {
       // OutputString(L"SendInput failed: 0x%x\n", HRESULT_FROM_WIN32(GetLastError()));
    } 
}

int main(){
    ShowDesktop();
    return 0;
}