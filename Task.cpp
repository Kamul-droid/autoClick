
#include <string>
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include<tchar.h>
#include<stdio.h>
#include <vector>
#include <conio.h>
#include "Task.hpp"
#include "Action.hpp"
#include<thread>
using namespace std;




// volatile bool Task::keep_running = true;

string Task::getName() const
{
    return taskName;
}

void Task::setName(string name)
{
    this->taskName = name;
}

void Task::setStopCode(bool code)
{
    
        this->stopCode = code;
    
}

void Task::setPauseCode(bool code)
{
    this->pauseCode = code;
}


void Task::display(){
    if (cycle.empty())
    {
        std::cout << " Nothing to display " << endl;
    }
    else
    {   
        auto count = 0;
        for (auto &&i : cycle)
        {
            std::cout<< count+1 <<") " ; i.display() ;
            count ++;
        }
        
    }
    
}

void Task::addAction()
{
    string actionName, buttonPress, timeT, waitT;
    double posX =-1, posY=-1;
    int time, wait, response;
    bool again = true;


    while (again)
    {
        /* code */
        std::cout << "Name of the action" << endl;
        std::cout << "----------------" << endl;
        std::cin >> actionName;
        this->setName(actionName);

        std::cout << "---------------------------------------------------------------------" << endl;
        std::cout << "Enter the parameters for the action " << this->getName() << endl;
        std::cout << "---------------------------------------------------------------------" << endl;

        // std::cout << "Which Button click do you want to simulate ex:L or R ?" <<endl;
        // std::cout << "----------------" <<endl;
        // std::cin >> buttonPress;

        bool control = false;

        while (!control)
        {
            std::cout << "Which Button click do you want to simulate ex:L or R ?" << endl;

            std::cout << "-------------------->       <--------------------------" << endl;
            std::cout << "You must enter either L or R " << endl;
            std::cout << "--------------------><------><-------------------------" << endl;
            std::cin >> buttonPress;

            if (buttonPress == "L" || buttonPress == "R")
            {
                control = true;
            }
        }

        int useranswer;

        std::cout << "How do you want to get the mouse position for your task ?" << endl;
        std::cout << "-------------------------------------------------------" << endl;
        std::cout << "--> 1 <-- Enter the position myself  " << endl;
        std::cout << "--> 2 <-- Get them with my mouse cursor   " << endl;
        std::cout << "              Enter your choice " << endl;
        std::cin.clear();
        std::cin >> useranswer;
        switch (useranswer)
        {
        case 1:
            /* code */
            createUserInputPosition();
            break;
        case 2:
            /* code */
            createMouseInputPosition( posX,  posY);
            break;

        default:
            break;
        }


        std::cout << "Enter time for click in ms ?" << endl;
        std::cout << "------------------------------------" << endl;
        std::cin >> timeT;
        control = checkIntegerInput(timeT);

        while (!control)
        {
            /* code */
            std::cout << "Enter the delay before click in ms ?" << endl;
            std::cout << "------------------------------------" << endl;
            std::cin >> timeT;
            control = checkIntegerInput(timeT);
        }
        // convert input to int
        time = stoi(timeT);

        std::cout << "Enter the delay before next click in ms ?" << endl;
        std::cout << "----------------------------------------" << endl;
        std::cin >> waitT;

        control = checkIntegerInput(waitT);

        while (!control)
        {

            std::cout << "Enter the delay before next click in ms ?" << endl;
            std::cout << "----------------------------------------" << endl;
            std::cin >> waitT;
            control = checkIntegerInput(waitT);
        }

        // convert input to int
        wait = stoi(waitT);

        // instanciate the action

        Action item(actionName, posX, posY, time,wait, buttonPress);
       
        cycle.push_back(item);
        // to process loop
        actionLoop.push(item);
        waitBeforeNextAction[item] = wait;

        std::cout << "Do you want to add another action ? " << endl;
        std::cout << "Enter --> 0 <-- for no and --> 1 <-- for yes " << endl;
        std::cin >> response;

        if (response == 0)
        {
            /* code */
            again = false;
        }
        else if (response != 1 && response !=0)
        {
            /* code */
            again = false;
        }
        std::cin.clear();
         
    }

    display();
    
    
}

bool Task::checkIntegerInput(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]) == false)
        {
            return false;
        }

    }
        return true;
}

void Task::createUserInputPosition(){
   
        double posX,posY;
   
        bool control = false;
        do
        {
            control = true;
            std::cout << "Enter the X Position  ?" << endl;
            std::cout << "----------------" << endl;
            std::cin >> posX;

            if (!std::cin)
            {
                control = false;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            else
            {
                /* code */
                string dummy;
                getline(std::cin, dummy);
                if (dummy.find_first_not_of(" ") != string::npos)
                {
                    /* code */
                    control = false;
                }
            }
            if (!control)
            {
                /* code */
                std::cout << " Invalid double" << endl;
            }

        } while (!control);

        do
        {
            control = true;
            std::cout << "Enter the Y Position  ?" << endl;
            std::cout << "----------------" << endl;
            std::cin >> posY;

            if (!std::cin)
            {
                control = false;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            }
            else
            {
                /* code */
                string dummy;
                getline(std::cin, dummy);
                if (dummy.find_first_not_of(" ") != string::npos)
                {
                    /* code */
                    control = false;
                }
            }
            if (!control)
            {
                /* code */
                std::cout << " Invalid double" << endl;
            }

        } while (!control);

        
    

}

void Task::createMouseInputPosition(double &posX, double &posY){
   
    // double posX, posY;
       
    // posX = posY=-1;
    bool hasPos = false;
    while (!hasPos)
    {
        /* code */
        std::cout << "This is the Cursor position on the screen " << endl;
        POINT p;
        GetCursorPos(&p);
        posX = p.x;
        posY = p.y;

        if (posX != -1)
        {
            hasPos = true;
        }
        std::cout << " The action position are : " << endl;
        std::cout << " -------------> Screen X : " <<posX <<endl;
        std::cout << "--------------> Screen Y : " <<posY << endl;
        
    }     
    
}

void Task::createTask()
{   
    cycle.clear();
    addAction();
    
}

void Task::start()
{
    if (!cycle.empty())
    {
        /* code */
        for (auto &&i : cycle)
        {
            i.startAction();
            Action::waitTime(waitBeforeNextAction[i]);
      

            if (stopCode)
            {
                std::cout << "                     Stop by user " << endl;
                break;
            }
            interruptCode();
        }
        
        std::cout << " *****************************************************************"<<endl;
        std::cout << "                           Thanks for using me   " << endl;
        std::cout << " *****************************************************************"<<endl;
        std::cout << " "<<endl;
    } else
    {
        std::cout << " ##################################################################" << endl;
        std::cout << "                         You have no task to run " << endl;
        std::cout << " ################################################################## " << endl;
        
        
    }

    
}

void Task::miniInterAction(){

    int useranswer{0};
    string check;
    bool ctrl = false;

    std::cout << "" << endl;
    std::cout << "#################### WELCOME BACK ################## ?" << endl;
    std::cout << "  What do you want to do with your created task ?" << endl;
    std::cout << "    -----------------------------------" << endl;
    std::cout << "    --------> 1 <-- Run one time task" << endl;
    std::cout << "    --------> 2 <-- Run until stop " << endl;
    std::cout << "    -----> 3 <-- Run a certain amount of time" << endl;
    std::cout << "    --> 4 <-- Add new action to the task to run " << endl;
    
    std::cout << "     Enter your choice " << endl;
    std::cin.clear();
    

    std::cin >> check;
    ctrl = checkIntegerInput(check);
    while (!ctrl)
    {
        /* code */
        std::cout << "Wrong input, Enter a correct response " << endl;
        std::cin.clear();
        std::cin >> check;
        ctrl = checkIntegerInput(check);
    }

    useranswer = stoi(check);
    
    switch (useranswer)
    {
    case 1:
        /* code */
        setStopCode(false);
        setPauseCode(false);
        start();
        break;
    case 2:
        /* code */
       
        setStopCode(false);
        setPauseCode(false);
        repeatTask ();
       
        break;
    case 3:
        /* repeat the task n time*/
        setStopCode(false);
        setPauseCode(false);
        repeatNTask();
        break;
    case 4:
        /* Add action to the task*/
        addAction();
        miniInterAction();
        
        break;
     
    default:
        break;
    }

}



void Task::repeatTask()
{

    /* default loop */
    bool again = true;
    int count = 200;

    while (!stopCode)
    {

       // create a cycle
        auto item = actionLoop.front();
        actionLoop.push(item); 
        actionLoop.pop();
        // Call the event
        item.startAction();
        Action::waitTime(waitBeforeNextAction[item]);
        
        interruptCode();
    
        // count--;
        // if (count == 0)
        // {
        //     /* end of the loop*/
        //     again = false;
        // }

        
    }
}


void Task::repeatNTask()
{
    int n{0};
    string ctrl;
    bool control = true;

    std::cout << " Enter the number of time to repeat this task " << endl;
    std::cin >> ctrl;

    control = checkIntegerInput(ctrl);

    while (!control)
    {
        /* code */
        std::cout << "Enter a valid integer ?" << endl;
        std::cout << "-----------------------" << endl;
        std::cin >> ctrl;
        control = checkIntegerInput(ctrl);
    }
    // convert input to int
    n = stoi(ctrl);

    while (n > 0 && !stopCode)
    {
        /* repeat the action until n equal zero or user stop */
        n--;
        auto item = actionLoop.front();
        actionLoop.push(item);
        actionLoop.pop();
        // Call the event
        item.startAction();
        Action::waitTime(waitBeforeNextAction[item]);
        interruptCode();
    }
}


void Task::duplicateAction(int pos){

   
    int answer;
    auto selected = cycle[pos];
    auto count = 0;

    std::cout << "Do you want to add the action at the end or at a particular position" << endl;
   
    std::cout << " 1 ) At the end " <<endl;
    std::cout << " 2 ) At a particular position" <<endl;
   
    std::cout << " Enter your choice " <<endl;

    
    answer = stoi(inputChoice());

    switch (answer)
    {
    case 1:
        /* code */
       
        cycle.push_back(selected);
        std::cout << "               "<<endl;
        std::cout << "             Insertion succeeded "<<endl;
        std::cout << "              "<<endl;
        display();
        Sleep(10000);
        
        break;
    case 2:
        /* code */
        
        std::cout <<" "<<endl;
        std::cout << "Enter the position of insertion" << endl;
        answer = stoi(inputChoice());

        while (answer > cycle.size())
        {
            /* code */
            std::cout <<" "<<endl;
            std::cout << "Out of range position" << endl;
            answer = stoi(inputChoice());
        }
        
        insertAction(pos,answer-1);
        std::cout << "               "<<endl;
        std::cout << "             Insertion succeeded "<<endl;
        std::cout << "              "<<endl;
        display();
        Sleep(10000);
        break;
    
    default:
        break;
    }

    
}

void Task:: insertAction(int select, int answer){
    Action selected = cycle[select];
    vector <Action> cstart,cend;
    vector <Action> ::iterator i;
    auto count = 0;

    for ( i = cycle.begin(); i < cycle.end(); i++)
    {
        /* code */
        if (count==answer)
        {
            /* code */
            cycle.insert(i,selected);
            count =0;
            break;
        }
        count++;
        

    }
    
}

string Task::inputChoice(){
    string check;
    std::cin.clear();
    std::cin >> check;
    bool ctrl = false;
    ctrl = checkIntegerInput(check);

    while (!ctrl)
    {
        /* code */
        std::cout << " Wrong choice, Reenter your choice" << endl;
        std::cin.clear();
        std::cin >> check;
        ctrl = checkIntegerInput(check);

    }

    return check;
}

void Task::configAction(int pos){

    //We get the action and update the value.

    Action old = cycle[pos];
    bool ok = false;
    bool ctr = false;
    int answer;
    string name, button , response;
    double x, y;
    bool again = false;

    while (!again)
    {
            /* code */
        std::cout << "what do you want to change" << endl;
        std::cout << " 1 ) Name" <<endl;
        std::cout << " 2 ) Button" <<endl;
        std::cout << " 3 ) Mouse time " <<endl;
        std::cout << " 4 ) Wait time " <<endl;
        std::cout << " 5 ) X position " <<endl;
        std::cout << " 6 ) Y position " <<endl;
        std::cout << " Enter your choice " <<endl;

        string check;
        std::cin.clear();
        std::cin >> check;
        ctr = checkIntegerInput(check);

        while (!ctr)
        {
            /* code */
            std::cout << " Wrong choice, Reenter your choice" << endl;
            std::cin.clear();
            std::cin >> check;
            ctr = checkIntegerInput(check);

        }
        answer = stoi(check);

        switch (answer)
        {
        case 1:
            /* code */
            std::cout << "Enter the new name" <<endl;
            std::cin.clear();
            std::cin >> name;
            old.setName(name);
            break;
        case 2:
            /* code */
            std::cout << "Enter the new button -> R or L <- " <<endl;
            std::cin.clear();
            std::cin >> button;
            old.setButton(button);
            break;
        case 3:
            /* code */
            std::cout << "Enter mouse time in ms <- " <<endl;
            std::cin.clear();
            std::cin >> answer;
            old.setTime(answer);
            break;
        case 4:
            /* code */
            std::cout << "Enter wait time in ms <- " <<endl;
            std::cin.clear();
            std::cin >> answer;
            old.setWaitTime(answer);
            waitBeforeNextAction[old] = answer;
            break;
        case 5:
            /* code */
            std::cout << "Enter the new X position <- " <<endl;
            std::cin.clear();
            std::cin >> x;
            old.setX(x);
            break;
        case 6:
            /* code */
            std::cout << "Enter the new Y position <- " <<endl;
            std::cin.clear();
            std::cin >> y;
            old.setY(y);
            break;
        
        default:
            break;
        }

        cycle[pos] = old;

    
    
        std::cout << " " << endl;
        std::cout << "              The update action " << endl;
        cycle[pos].display();


        /* repeat panel  */

        std::cout << " Would you change another parameter ? Y/N" <<endl;
        std::cout << "Enter your choice"<<endl;
        std::cin.clear();
        std::cin >> response;
        if (response == "N")
        {
            again = true;
        } else if (response =="Y")
        {
            continue;
        } else
        {
            break;

        }
        
        
        
        
    }
    
    
    
   
}

void Task::interruptCode(){
        
        // Press F3 to Stop
        if (GetAsyncKeyState(VK_F3))
        {
            setStopCode(true);
        }

        // Press space to pause
        
        if (GetAsyncKeyState(VK_SPACE))
        { 
        
            //User pressed space
            setPauseCode(true);

        }

        

        if (pauseCode)
        {
            /* code */
            std::cout <<"Press a Key and Enter to resume"<<endl;
            std::cin.clear();
            std::cin.get();
            pauseCode = false;
        }
        
        

}

Task::Task(string name) : taskName(name)
{
}

Task::~Task()
{
}
