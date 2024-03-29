#if !defined(ACTION_H_INCLUDED)
#define ACTION_H_INCLUDED
#include <string>
using namespace std;




class Action
{
private:
    /* data */
    
    static int instanceCount;
    double posX;
    double posY;
    int timeToWait,time;
    string buttonClick, name;
   
protected:

public:
    
    void leftClick(double x, double y, int time);
    void rightClick(double x, double y, int time);
    void display();
    //Action(const Action &other);
    void setName(string newName);
    const string& getName();
    const string& getButton();
    const double& getPosX();
    const double& getPosY();
    const int& getTime();
    const int& getWaitTime();
    void setTime(int time);
    void setWaitTime(int time);
    static void waitTime(int time);
    void startAction();
    void setPosition(double x , double y);
    void setX(double x);
    void setY(double y);
    void setButton(string button);
    bool operator<(const Action& other) const;
    Action(string name,double screenPosX, double screenPosY, int time, int wait,string click);
    ~Action();
};


#endif // ACTION_H_INCLUDED