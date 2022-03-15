#if !defined(TASK_H_INCLUDED)
#define TASK_H_INCLUDED

#include <string>
#include"Action.hpp"
#include <iostream>
#include<windows.h>
#include <winuser.h>
#include <vector>
#include <map>
#include <queue>
#include<fstream>





using namespace std;

class Task 
{
    private:
        /* data */

        vector <Action> cycle;
        vector <int> waitTime;
        map <Action,int> waitBeforeNextAction;
        queue <Action> actionLoop;
        string taskName;
        bool stopCode = false;
        bool pauseCode = false;
        vector <Task> taskList;
    

    public:
        void setName(string name);
        string getName() const;
        void setCycle(vector<Action> cycl);
        void setActionLoop(vector<Action> cycle);
        vector<Action> getCycle() const;
        void display() ;
        void setStopCode(bool code);
        void setPauseCode(bool code);
        static bool checkIntegerInput(string str);
        void createUserInputPosition(double &posX, double &posY);
        void createMouseInputPosition(double &posX, double &posY);
        void createTask();
        void repeatNTask();
        void addAction();
        void miniInterAction();
        void duplicateAction(int pos);
        void configAction(int place);
        string inputChoice();
        void insertAction(int select, int answer);
        void repeatTask();
        void start();
        void interruptCode();
        int mouseEvent(int key);
        void getMousePos(double &posx, double &posy);
       
        
        Task(string name);
        Task();
        ~Task();
};



    


#endif
 // TASK_H_INCLUDED

