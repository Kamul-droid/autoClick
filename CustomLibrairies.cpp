#include"CustomLibrairies.hpp"
#include"Task.hpp"
#include"Action.hpp"
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
#include <fstream>
#include <sstream>

using namespace std;


int interaction ( Task newTask ){
    bool repeat = true;
    string check,temp;
    int answer = 0;
    int i;

     while (repeat)
        {
            /* code */
            cout << "####################### WELCOME ####################" << endl;

            cout << " ---------------What do you want to do ?------------" << endl;
            cout << " ****************        Enter      ****************" << endl;
            cout << " -> 1 <---------- load---------------" << endl;
            cout << " -> 2 <-----------To create task--------------------" << endl;
            cout << " -> 3 <-----------Start the task------------------" << endl;
            cout << " -> 4 <-----------Rename the task-------------------" << endl;
            cout << " -> 5 <-- --------Configure the task  " << endl;
            cout << " -> 6 <---------- To exit the program---------------" << endl;
            cout << "  Press -> Space <- to pause and -> F3 <-to Stop the task" << endl;
            cout << "******************Enter your choice*****************" << endl;
            
            
            temp = inputChoice();
            answer = stoi(temp);

            string newName;

            switch (answer)
            {

            case 1:
                loadTaskFromFile("database.txt",saveTaskContainer);
                //update nameList to ensure unique task name
                updateNameList(saveTaskContainer,nameList);
                isEmptyContainer(saveTaskContainer,newTask);

                break;

            case 2:
                /* code */
            
                newTask = createTask();
                
                
                break;
            case 3:

                newTask.miniInterAction();
                break;

            case 4:
                /*rename the task*/
                
                cout << "Enter the new name for the task "<<newTask.getName()<<endl;
                
                cin.clear();
                cin.ignore(1000,'\n');
                
                getline(cin, newName);
                i = findTaskPositionInContainer(saveTaskContainer, newTask);
                cout <<" index :" << i <<endl;
                newTask.setName(newName);
                saveTaskContainer[i] = newTask;

                cout << "----------------------------------------------------"<<endl;
                cout << "The  task new name is------>: "<<newTask.getName()<<endl;
                cout << "--------------                          ------------"<<endl;
                break;

            case 5:
                    /* Add action to the task*/
                    cout << "Select the action you want to execute" << endl;
                    cout << "1 <-- Modify a selected action of the task" << endl;
                    cout << "2 <-- Duplicate a selected action of the task" << endl;
                    cout << "3 <-- Add an action" << endl;
                    cout << "Enter your choice" << endl;
                    temp = inputChoice();
                    answer = stoi(temp);

                    switch (answer)
                    {
                    case 1:
                        /* code */
                        cout << "Select the action you want to modify " << endl;
                        cout << " " << endl;
                        newTask.display();
                        answer = stoi(inputChoice())-1;
                        newTask.configAction(answer);

                        break;

                    case 2 :
                        cout << "Select the action you want to duplicate " << endl;
                        cout << " " << endl;
                        newTask.display();

                        answer = stoi(inputChoice())-1;
                        newTask.duplicateAction(answer);
                        
                        break;

                    case 3:

                        newTask.addAction();
                        newTask.miniInterAction();
                        break;
                    
                    default:
                        break;
                    }
                    saveTaskContainer[findTaskPositionInContainer(saveTaskContainer, newTask)] = newTask;

                    break;
            case 6:
                saveTaskToFile(saveTaskContainer);
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


string inputChoice( ){
    string check;
    cin.clear();
    cin >> check;
    bool ctrl = false;
    ctrl = Task::checkIntegerInput(check);

    while (!ctrl)
    {
        /* code */
        cout << " Wrong choice, Reenter your choice" << endl;
        cin.clear();
        cin >> check;
        ctrl = Task::checkIntegerInput(check);

    }

    return check;
}

void saveTaskToFile(vector<Task> toSave){
    // create output file
    string fileName("database.txt");
    ofstream file_out;
    string cmd;

    //open the file in append mode
    file_out.open(fileName, ios::trunc|ios::in);
    vector<Action> miniTask;
    for (auto &&i : toSave)
    {   
        miniTask.clear();
        cmd.clear();
        cmd += i.getName()+",";

        miniTask = i.getCycle();
            for (auto &&j : miniTask)
            {
                 cmd +=j.getName()+","+j.getButton() +"," + to_string( j.getPosX()) +",";
                 cmd +=to_string(j.getPosY()) +",";
                 cmd += to_string(j.getTime()) +",";
                 cmd +=to_string(j.getWaitTime())+",";
            }
            
        
        cmd = cmd.substr(0,cmd.size()-1);
        file_out << cmd <<endl;
    }
}

void saveTask(Task toSave){
    saveTaskContainer.push_back(toSave);
    cout << " "<<endl;
    cout << "                    Task saved "<<endl;
    cout << " "<<endl;

    

    

}

void loadTask(vector<Task> &saveTaskContainer){
    vector <Task>::iterator i;
    vector <Task> ouTput;
    int count = 0;

    for ( i = saveTaskContainer.begin() ; i < saveTaskContainer.end(); i++){
        cout<< count+1 <<" ) Task: " << i->getName() <<endl;
        cout <<" "<<endl;
        vector<Action> miniTask;
        miniTask = i->getCycle();
            for (auto &&j : miniTask)
            {
                 j.display();
            }
        count++;
            
        

    }

    
}

void loadTaskFromFile(string filename, vector<Task> &taskContainer){
    string line, info;
    int count;
    vector<string> row;
    vector<vector<string>> container;
    vector<Action> cycle;
    //Input file
    
    fstream file(filename,ios::in);

    if (file.is_open())
    {
        /* code */
        while (getline(file,line))
        {   
            row.clear();
            /* code */
            
            stringstream str(line);
            //cout << " line  "<<line;
            while (getline(str,info,','))
          
               //cout << " data "<<info;
               row.push_back(info);
                
            container.push_back(row);
            

        }
        
    }
    else
    {
        cout << "Could not open the file" <<endl;
    }
    
    // transform data in container into task
   

    for (int i = 0; i < container.size(); i++)
    {
        string name, button;
        double posX ;
        double posY ;
        int  time ;
        int  wait ;
        Task task("S");
       
        cycle.clear();
        
        for (int j = 1; j < container[i].size(); j++)
        {
            task.setName(container[i][0]);
            //cout << "task name "<<task.getName() << endl;

            name = container[i][j];
            //cout << "name "<<name << endl;
            button = container[i][j+1];
            //cout << "button "<<button << endl;
            posX = stod(container[i][j+2]);
            //cout << posX << endl;
            posY = stod(container[i][j+3]);
            //cout << posY << endl;
            time = stoi(container[i][j+4]);
           // cout << time << endl;
            wait = stoi(container[i][j+5]);
            //cout << wait << endl;
            Action action(name,posX,posY,time,wait,button);
            //action.display() ;
            cycle.push_back(action);
            j+=5;

        }
        task.setCycle(cycle);
        taskContainer.push_back(task);
        
    }
    



}
void isEmptyContainer(vector<Task> &saveTaskContainer, Task &newTask){
    int answer;
    string temp;
    if (saveTaskContainer.empty())
    {
        cout << "Nothing to display " << endl;
        Sleep(5000);
    }
    else
    {
        loadTask(saveTaskContainer);
        cout << "Choose the task you want to execute by enter his number on the list "<<endl;
        temp = inputChoice();
        answer = stoi(temp)-1;
        newTask = saveTaskContainer[answer];
    }
    
}

Task createTask(){
    string taskname;
    cout << "##########################"<< endl;
    cout << "Enter the name of the task"<< endl;
    cout << "##########################"<< endl;
    cin.clear();
    cin >> taskname;
    bool check = uniqueNameConstraint(nameList, taskname) ;
    while (check)
    {
        cout << "Name already exist, enter another one " <<endl;
        cin.clear();
        cin >> taskname;
        check = uniqueNameConstraint(nameList, taskname) ;
    }
    
    Task taskToExecute(taskname);
    //record to nameList to ensure unique name later
    nameList.push_back(taskname);
    // Start creating action for the task
    taskToExecute.createTask();
    saveTask(taskToExecute);
    taskToExecute.miniInterAction();

    return taskToExecute;
}

int findTaskPositionInContainer(vector<Task> Container, Task task){
    vector<Task> ::iterator i;
    int count = -1 ;
    for (auto &&t : Container)
    {
        count ++;
        if (t.getName().compare( task.getName())==0)
        {
            break;
        }
        
        
    } 

    return count;
    
}

void updateNameList(vector<Task>saveTaskContainer,vector <string> &nameList){
    for (auto &&i : saveTaskContainer)
    {
        nameList.push_back(i.getName());
    }
    
}


bool uniqueNameConstraint(vector<string> nameList, string name){
    bool inside = false;
    for (auto &&i : nameList)
    {
        if (i.compare(name)==0)
        {
            return true;
        }
        
    }

    return inside;
    

}

