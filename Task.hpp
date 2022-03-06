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
  

public:
    void setName(string name);
    string getName() const;
    void display();
    void setStopCode(bool code);
    void setPauseCode(bool code);
    bool checkIntegerInput(string str);
    void createUserInputPosition();
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
    
    Task(string name);
    ~Task();
};



#endif // TASK_H_INCLUDED


