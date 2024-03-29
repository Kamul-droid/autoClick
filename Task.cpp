
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
#include<ctime>
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


void Task::display() {
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
        
        std::cout << "Name of the action" << endl;
        std::cout << "----------------" << endl;
        std::cin >> actionName;
        
        std::cout << "---------------------------------------------------------------------" << endl;
        std::cout << "Enter the parameters for the action " << this->getName() << endl;
        std::cout << "---------------------------------------------------------------------" << endl;


        bool control = false;

        while (!control)
        {
            std::cout << "Which Button click do you want to simulate ex: Left (L) or Right (R) ?" << endl;

            std::cout << "        -------------------->       <--------------------------" << endl;
            std::cout << "       You must enter either L or R " << endl;
            std::cout << "        --------------------><------><-------------------------" << endl;
            std::cin >> buttonPress;

            if (buttonPress == "L" || buttonPress == "l" || buttonPress == "R" || buttonPress == "r" )
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
           /*                                     */
            createUserInputPosition(posX, posY);
            break;
        case 2:
           /*                                     */
            cout <<"Move your mouse cursor to the position then Enter 1 "<<endl;
            std::cin.clear();
            std::cin >> useranswer;
            if (useranswer == 1)
            {
               /* get position with mouse cursor   */
               createMouseInputPosition( posX,  posY);
            }
            
         
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
           /* validate user input  */
            std::cout << "Enter time for click in ms  ?" << endl;
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
           /* terminate the loop  */
            again = false;
        }
        else if (response != 1 && response !=0)
        {
           /*                                     */
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

void Task::createUserInputPosition(double &posX, double &posY){
   
        
   
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
               /*                                     */
                string dummy;
                getline(std::cin, dummy);
                if (dummy.find_first_not_of(" ") != string::npos)
                {
                   /*                                     */
                    control = false;
                }
            }
            if (!control)
            {
               /*                                     */
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
               /*                                     */
                string dummy;
                getline(std::cin, dummy);
                if (dummy.find_first_not_of(" ") != string::npos)
                {
                   /*                                     */
                    control = false;
                }
            }
            if (!control)
            {
               /*                                     */
                std::cout << " Invalid double" << endl;
            }

        } while (!control);

        
    

}

void Task::getMousePos(double &posX, double &posY){
     POINT p;
        GetCursorPos(&p);
        posX = p.x;
        posY = p.y;
}

void Task::createMouseInputPosition(double &posX, double &posY){
   
    
    bool hasPos = false;
    while (!hasPos)
    {
       /*                                     */
        std::cout << "This is the Cursor position on the screen " << endl;

        getMousePos(posX,posY);

        if (posX != -1)
        {
            hasPos = true;
        }
        std::cout << " The action position are : " << endl;
        std::cout << " -------------> Screen X : " <<posX <<endl;
        std::cout << "--------------> Screen Y : " <<posY << endl;
        
    }     
    
}

int Task::mouseEvent(int key){
     return (GetKeyState(key) & 0x8000 != 0);
}
                 
void Task::createTask()
{   
    string answer, actionName, check, timeT, waitT;
    bool ctrl,control,ctrlL = false, ctrlP=false;
    int response,count =0, countp=0;
    double posX =-1, posY = -1;
    string button;
    int timeP, wait;
    time_t current_time, start_time, wtime;
    vector<string> mouseClick;
    vector<time_t> period;
    vector<int> mousepress;
    vector<double> Xpos;
    vector<double> Ypos;
   
    cout << "How do want do configure the action ?"<<endl;
    cout << "1) Enter the data myself "<<endl;
    cout << "2) Get the position and mouse button automatically"<<endl;
    cout << "   Enter your choice"<<endl;

    cin.clear();
    cin >> check;
    ctrl = checkIntegerInput(answer);
     while (!ctrl)
    {
       /*                                     */
        std::cout << "Wrong input, Enter a correct response " << endl;
        std::cin.clear();
        std::cin >> check;
        ctrl = checkIntegerInput(check);
    }
    response = stoi(check);

    switch (response)
    {
        case 1:
            cycle.clear(); 
            addAction();
            break;
        case 2:
            ctrl = false;
            Sleep(2000);
            cout << "start" <<endl;
            control = false;
            int pressTime;
            while (!ctrl)
            {
               
                /* start of the input*/
                while (1)
                {
                   /*                                     */
                    if( GetKeyState(VK_LBUTTON) & 0x8000){
                       
                    if (!control)
                    {
                       control = true;
                       button = "L";
                       time(&current_time);

                    }
                    //process invoke count in nanoseconde
                        count ++;
                    
                    } 

                    if ((GetKeyState(VK_LBUTTON) & 0x8000) == 0)
                    {
                        // conversion of button press in milliseconde
                        pressTime = count/1000000;
                    
                        break;
                    }
                    
                }
                 //Right button input
                while (1)
                {
                   /*                                     */
                    if( GetKeyState(VK_RBUTTON) & 0x8000){
                       
                    if (!control)
                    {
                       control = true;
                       button = "R";
                       time(&current_time);


                    }
                    //process invoke time count in nanoseconde
                        count ++;
                    
                    } 

                    if ((GetKeyState(VK_RBUTTON) & 0x8000) == 0)
                    {
                        // conversion of button press in milliseconde
                        pressTime = count/1000000;
                
                        break;
                    }
                    
                }
                 
                
                Sleep(150);
                            
                
                if (control && button =="L")
                {
                       /*                                     */
                    ctrlL = true;
                    button = " ";

                }

                if ( control && button =="R")
                {
                       /*                                     */
                    ctrlP = true;
                    button = " ";

                }
              

                
                if (ctrlL)
                {
                   /*                                     */
                    control = false;
                    count = 0;
                    cout << "Click on the mouse or Press Echap to stop the input"<<endl;

                    getMousePos(posX,posY);
                    Xpos.push_back(posX);
                    Ypos.push_back(posY);
                    period.push_back(current_time);
                    mousepress.push_back(pressTime);
                    mouseClick.push_back("L");
                    printf("%s\n","Click gauche");
                    ctrlL = false;
                   
                }
                        

                if (ctrlP)
                {
                    cout << "Click on the mouse or Press Echap to stop the input"<<endl;

                   /*                                     */
                    control = false;
                    count = 0;

                    getMousePos(posX,posY);
                    Xpos.push_back(posX);
                    Ypos.push_back(posY);
                    mouseClick.push_back("R");
                    period.push_back(current_time);
                    mousepress.push_back(pressTime);


                    printf("%s\n","Click Droit");
                    ctrlP = false;
                    
                }
              
                
                
                if (GetKeyState(VK_ESCAPE) & 0x8000)
                {
                   /*                                     */
                    ctrl = true;
                }
              
            
            }
            if (ctrl)
            {
           /*                                     */
            cycle.clear();
            queue <Action> emp;
            actionLoop.swap(emp);
          
                for (int i = 0; i < mouseClick.size(); i++)
                {
                   /*                                     */
                    button = mouseClick[i];
                    
                    posX = Xpos[i];
                    posY = Ypos[i];
                    timeP = mousepress[i];
                    if (i+1 < mouseClick.size())
                    {
                    wait = static_cast <int > (period[i+1]-period[i]);
                       /*                                     */
                    wait *=1000;
                    }else{wait =0;}
                    actionName = "auto"+to_string( i);

                    Action item(actionName, posX, posY, timeP,wait, button);
                    cycle.push_back(item);
                    // to process loop
                    actionLoop.push(item);
                    waitBeforeNextAction[item] = wait;
                }
                


        
            }
        
        
        
        break;
    
    default:
        break;
    }

    
}

void Task::start()
{
    if (!cycle.empty())
    {
       /*                                     */
        for (auto &&i : cycle)
        {
            i.startAction();
            i.display();
           
            Action::waitTime(i.getWaitTime());
      

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
    std::cout << "    -------------------------------------------" << endl;
    std::cout << "    --> 1 <-- Preview the task" << endl;
    std::cout << "    --> 2 <-- Run until stop " << endl;
    std::cout << "    --> 3 <-- Run a certain amount of time" << endl;
    std::cout << "    --> 4 <-- Add new action to the task to run " << endl;
    
    
    std::cout << "     Enter your choice " << endl;
    std::cin.clear();
    

    std::cin >> check;
    ctrl = checkIntegerInput(check);
    while (!ctrl)
    {
       /*                                     */
        std::cout << "Wrong input, Enter a correct response " << endl;
        std::cin.clear();
        std::cin >> check;
        ctrl = checkIntegerInput(check);
    }

    useranswer = stoi(check);
    
    switch (useranswer)
    {
    case 1:
       /*                                     */
        setStopCode(false);
        setPauseCode(false);
        start();
        break;
    case 2:
       /*                                     */
       
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

    while (!stopCode)
    {

       // create a cycle
        auto item = actionLoop.front();
        actionLoop.push(item); 
        actionLoop.pop();
        // Call the event
        item.startAction();
        Action::waitTime(item.getWaitTime());
        
        interruptCode();

        
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
       /*                                     */
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
        Action::waitTime(item.getWaitTime());
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
       /*                                     */
       
        cycle.push_back(selected);
        std::cout << "               "<<endl;
        std::cout << "             Insertion succeeded "<<endl;
        std::cout << "              "<<endl;
        display();
        Sleep(10000);
        
        break;
    case 2:
       /*                                     */
        
        std::cout <<" "<<endl;
        std::cout << "Enter the position of insertion" << endl;
        answer = stoi(inputChoice());

        while (answer > cycle.size())
        {
           /*                                     */
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
       /*                                     */
        if (count==answer)
        {
           /*                                     */
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
       /*                                     */
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
           /*                                     */
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
           /*                                     */
            std::cout << " Wrong choice, Reenter your choice" << endl;
            std::cin.clear();
            std::cin >> check;
            ctr = checkIntegerInput(check);

        }
        answer = stoi(check);

        switch (answer)
        {
        case 1:
           /*                                     */
            std::cout << "Enter the new name" <<endl;
            std::cin.clear();
            std::cin >> name;
            old.setName(name);
            break;
        case 2:
           /*                                     */
            std::cout << "Enter the new button -> R or L <- " <<endl;
            std::cin.clear();
            std::cin >> button;
            old.setButton(button);
            break;
        case 3:
           /*                                     */
            std::cout << "Enter mouse time in ms <- " <<endl;
            std::cin.clear();
            std::cin >> answer;
            old.setTime(answer);
            break;
        case 4:
           /*                                     */
            std::cout << "Enter wait time in ms <- " <<endl;
            std::cin.clear();
            std::cin >> answer;
            old.setWaitTime(answer);
            waitBeforeNextAction[old] = answer;
            break;
        case 5:
           /*                                     */
            std::cout << "Enter the new X position <- " <<endl;
            std::cin.clear();
            std::cin >> x;
            old.setX(x);
            break;
        case 6:
           /*                                     */
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
           /*                                     */
            std::cout <<"Press a Key and Enter to resume"<<endl;
            std::cin.clear();
            std::cin.get();
            pauseCode = false;
        }
        
        

}

std::vector<Action> Task::getCycle() const{
    return this->cycle;
}

void Task::setCycle(vector<Action> cycl){
    this->cycle.swap(cycl);  

}

void Task::setActionLoop(vector<Action> cycle){
    queue<Action> empt;
    this->actionLoop.swap(empt);
    for (auto &&i : cycle)
    {
        this->actionLoop.push(i);
    }
    
}


Task::Task(string name) : taskName(name)
{
}

Task::~Task()
{
}
