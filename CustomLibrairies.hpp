#if !defined(CUSTOMLIBRAIRIES_H_INCLUDED)
#define CUSTOMLIBRAIRIES_H_INCLUDED
int interaction ( Task newTask);
string inputChoice( );
void isEmptyContainer(vector<Task> &saveTaskContainer,Task &newTask);
void saveTask(Task toSave);
void saveTaskToFile(vector<Task> toSave);
void loadTaskFromFile(string filename, vector<Task> &taskContainer);
void loadTask(vector<Task> &saveTaskContainer);
Task createTask();
int findTaskPositionInContainer(vector<Task> Container, Task task);
void updateNameList(vector<Task>saveTaskContainer,vector <string> &nameList);
bool uniqueNameConstraint(vector<string> nameList, string name);

#endif // CUSTOMLIBRAIRIES_H_INCLUDED
