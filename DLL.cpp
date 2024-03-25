//Chase Horton
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>


using namespace std;


DLL::DLL(){
    first = last = NULL;
}

DLL::DLL(string taskname, int priority, int hours, int mins){
    first = new DNode(taskname, priority, hours, mins);
    last = first;
    numTasks = 1;
    tothrs = hours;
    totmin = mins;
}

DLL::~DLL(){
    DNode *current = first;
    while (current != NULL){
        DNode *temp = current;
        current = current -> next;
        delete temp;
    }
    first = last = NULL;
    numTasks = 0;
    tothrs = 0;
}

void DLL::push(string taskname, int priority, int hours, int mins){

    DNode *newNode = new DNode(taskname, priority, hours, mins);
    if (!first) {
        first = newNode;
        last = first;
    }
    else {
        if (priority == 3) {
            last->next = newNode;
            last->next->prev = last;
            last = last->next;
        }
        else {
            DNode *current = last;
            while (current != NULL && current->task->priority > priority) {
                current = current->prev;
            }

            if (current == NULL) {
                first->prev = newNode;
                first->prev->next = first;
                first = first->prev;
            }
            else {
                newNode->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = newNode;
                }
                else {
                    last = newNode;
                }
                current->next = newNode;
                newNode->prev = current;
            }
        }
    }
    numTasks++;
    tothrs += hours;
    totmin += mins;
}

Task *DLL::pop() {
    if (first == NULL) {
        return NULL;
    }
    DNode *current = first;
    while (current->next != NULL) {
        current = current->next;
    }
    Task* lastTask = current->task;
    removeTime(lastTask->hr, lastTask->min);
    if (first == last) {
        delete last;
        first = last = NULL;
    }
    else {
        last = last->prev;
        last->next = NULL;
    }
    return lastTask;
}


int DLL::remove(int num) {
    DNode *current = first;
    while (current != NULL && current->task->tasknum != num){
        current = current->next;
    }
    if (current == NULL){
        return -1;
    }
    if (current == first) {
        first = current->next;
        if (first != NULL) {
            first->prev = NULL;
        }
        else {
            last = NULL;
        }
    }
    else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
        else {
            last = current->prev;
        }
    }
    removeTime(current->task->hr, current->task->min);
    delete current;
    return num;
}

void DLL::addTime(int hours, int mins) {
    int minTotal = tothrs * 60 + totmin;
    int minTask = hours * 60 + mins;
    minTotal += minTask;
    tothrs = minTotal / 60;
    totmin = minTotal % 60;

}

void DLL::removeTime(int hours, int mins) {
    tothrs -= hours;
    totmin -= mins;
    tothrs += totmin / 60;
    totmin %= 60;
}

void DLL::moveUp(int tasknum) {
    if (first == NULL) {
        cout << "List is empty, cannot move task." << endl;
        return;
    }
    DNode* current = first;
    while (current != NULL && current->task->tasknum != tasknum) {
        current = current->next;
    }
    if (current == NULL) {
        cout << "Task with number " << tasknum << " not found." << endl;
        return;
    }
    if (current == first || first->next == NULL) {
        first = current->next;
        first->prev = NULL;
        current->prev = last;
        current->next = NULL;
    }
    Task* tempTask = current->task;
    current->task = current->prev->task;
    current->prev->task = tempTask;

    int tempPriority = current->task->priority;
    current->task->priority = current->prev->task->priority;
    current->prev->task->priority = tempPriority;
}
void DLL::moveDown(int tasknum) {
    if (first == NULL) {
        cout << "List is empty, cannot move task." << endl;
        return;
    }
    DNode *current = first;
    while (current != NULL && current->task->tasknum != tasknum) {
        current = current->next;
    }
    if (current == NULL) {
        cout << "Task with number " << tasknum << " not found." << endl;
        return;
    }
    if (current == last || first->next == NULL) {
    last = current->prev;
    last->next = NULL;
    current->next = first;
    current->prev = NULL;
    }
    Task* tempTask = current->task;
    current->task = current->next->task;
    current->next->task = tempTask;

    int tempPriority = current->task->priority;
    current->task->priority = current->next->task->priority;
    current->next->task->priority = tempPriority;
}

void DLL::changePriority(int tasknum, int newPriority) {
    DNode *current = first;
    while (current != NULL && current->task->tasknum != tasknum){
        current = current->next;
    }
    if (current != NULL){
        current->task->priority = newPriority;
    }
}

void DLL::listDuration(int *pHours, int *pMins,int priority) {
    int hrsTotal = 0;
    int minsTotal = 0;
    DNode *current = first;
    while (current != NULL){
        if (current->task->priority == priority) {
            hrsTotal += current->task->hr;
            minsTotal += current->task->min;
        }
        current = current->next;
    }
    hrsTotal += minsTotal / 60;
    minsTotal %= 60;

    *pHours = hrsTotal;
    *pMins = minsTotal;
}

void DLL::printList() {
    DNode *current = first;
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    while (current != NULL) {
        current->task->printTask();
        current = current->next;
    }
    while(totmin > 60){
        tothrs++;
        totmin -= 60;
    }
    cout << endl;
}

void DLL::printList(int priority) {
    DNode *current = first;
    cout << "Total Time Required: "<<tothrs<<":"<<totmin<<endl;
    while (current != NULL){
        if (current->task->priority == priority) {
            current->task->printTask();
        }
        current = current->next;

    }
    while(totmin > 60){
        tothrs++;
        totmin -= 60;
    }
    cout << endl;
}

void DLL::printReverse() {
    DNode *current = last;
    cout << "Total Time Required: "<<tothrs<<":"<<totmin<<endl;
    while (current != NULL){
        current->task->printTask();
        current = current->prev;
    }
    while(totmin > 60){
        tothrs++;
        totmin -= 60;
    }
    cout << endl;
}
