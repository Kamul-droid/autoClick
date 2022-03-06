#include <string>
#include <iostream>
#include<Windows.h>
#include<tchar.h>
#include<stdio.h>
#include <winuser.h>
#include<limits>
#include<ios>
#include <vector>
#include<map>
#include<conio.h>
#include "Action.hpp"
#include"Task.hpp"
#include<thread>

using namespace std;


bool stopCode = false;
int interaction ( Task newTask);
string inputChoice( Task newTask);

int main(int argc, char const *argv[])
{
    Task newTask("SomeTask");
   
    interaction(newTask);
    
    return 0;
}


int interaction ( Task newTask ){
    bool repeat = true;
    string check,temp;
    int answer = 0;

     while (repeat)
        {
            /* code */
            cout << "####################### WELCOME ####################" << endl;

            cout << " ---------------What do you want to do ?------------" << endl;
            cout << " ****************        Enter      ****************" << endl;
            cout << " -> 1 <-----------To create task--------------------" << endl;
            cout << " -> 2 <-----------Restart the task------------------" << endl;
            cout << " -> 3 <-----------Rename the task-------------------" << endl;
            cout << " -> 4 <-- --------Configure the task  " << endl;
            cout << " -> 5 <---------- To exit the program---------------" << endl;
            cout << "  Press -> Space <- to pause and -> F3 <-to Stop the task" << endl;
            cout << "******************Enter your choice*****************" << endl;
            
            
            temp = inputChoice(newTask);
            answer = stoi(temp);

            string newName;

            switch (answer)
            {
            case 1:
                /* code */
            
                newTask.createTask();
                newTask.miniInterAction();
                
                break;
            case 2:

                newTask.miniInterAction();
                break;

            case 3:
                /*rename the task*/
                
                cout << "Enter the new name for the task "<<newTask.getName()<<endl;
                
                cin.clear();
                cin.ignore(1000,'\n');
                
                getline(cin, newName);
                newTask.setName(newName);
                cout << "----------------------------------------------------"<<endl;
                cout << "The  task new name is------>: "<<newTask.getName()<<endl;
                cout << "--------------                          ------------"<<endl;
                break;

            case 4:
                    /* Add action to the task*/
                    cout << "Select the action you want to execute" << endl;
                    cout << "1 <-- Modify a selected action of the task" << endl;
                    cout << "2 <-- Duplicate a selected action of the task" << endl;
                    cout << "3 <-- Add an action" << endl;
                    cout << "Enter your choice" << endl;
                    temp = inputChoice(newTask);
                    answer = stoi(temp);

                    switch (answer)
                    {
                    case 1:
                        /* code */
                        cout << "Select the action you want to modify " << endl;
                        cout << " " << endl;
                        newTask.display();


                        answer = stoi(inputChoice(newTask))-1;
                        newTask.configAction(answer);
                        
                        break;

                    case 2 :
                        cout << "Select the action you want to duplicate " << endl;
                        cout << " " << endl;
                        newTask.display();

                        answer = stoi(inputChoice(newTask))-1;
                        newTask.duplicateAction(answer);
                        
                        break;

                    case 3:

                        newTask.addAction();
                        newTask.miniInterAction();
                        break;
                    
                    default:
                        break;
                    }

                    break;
            case 5:
                return 0;
                break;
            
            default:
                break;
            }

            if (answer == 5)
            {
                /* code */
                repeat = false;
                
            }
            

        }
   
               
}



string inputChoice( Task newTask){
    string check;
    cin.clear();
    cin >> check;
    bool ctrl = false;
    ctrl = newTask.checkIntegerInput(check);

    while (!ctrl)
    {
        /* code */
        cout << " Wrong choice, Reenter your choice" << endl;
        cin.clear();
        cin >> check;
        ctrl = newTask.checkIntegerInput(check);

    }

    return check;
}

