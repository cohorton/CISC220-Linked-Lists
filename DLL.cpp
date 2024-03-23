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
    if (!first) {
        return NULL;
    }
    Task *taskPop = NULL;
    if (first == last) {
        taskPop = last->task;
        delete last;
        first = last = NULL;
    }
    else {
        DNode *current = last;
        last = last->prev;
        last->next = NULL;
        taskPop = current->task;
        delete current;
    }
    removeTime(taskPop->hr, taskPop->min);
    numTasks--;
    return taskPop;
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
	if (first == NULL || first == last) {
        return;
    }
    DNode *current = first;

    while (current != NULL && current->task->tasknum != tasknum) {
        current = current->next;
    }
    if (current == NULL){
        return;
    }
    if (current == first) {
        first = first->next;
        first->prev = NULL;
        last->next = current;
        current->prev = last;
        current->next = NULL;
        last = current;
    }
    else {
        DNode *prevDnode = current->prev;
        DNode *beforePrevDnode = prevDnode->prev;

        if (beforePrevDnode != NULL) {
            if (prevDnode->task->priority < current->task->priority) {
                current->task->priority = prevDnode->task->priority;
                prevDnode->task->priority = current->task->priority;
            }
            beforePrevDnode->next = current;
            current->prev = beforePrevDnode;
        }
        else {
            first = current;
        }
        current->next = prevDnode;
        prevDnode->prev = current;
        prevDnode->next = current->next;
        if (current->next != NULL) {
            current->next->prev = prevDnode;
        }
        else {
            last = prevDnode;
        }
        current->next = prevDnode;
        prevDnode->prev = current;

    }
}

void DLL::moveDown(int tasknum) {
    if (first == NULL || first == last) {
        return;
    }
    DNode* current = first;

    while (current != NULL && current->task->tasknum != tasknum) {
        current = current->next;
    }
    if (current == NULL){
        return;
    }
    if (current == last) {
        last = last->prev;
        last->next = NULL;
        current->prev = NULL;
        current->next = first;
        first->prev = current;
        first = current;
    }
    else {
        DNode *nextDnode = current->prev;
        DNode *afterNextDnode = nextDnode->prev;

        if (afterNextDnode != NULL) {
            if (nextDnode->task->priority < current->task->priority) {
                current->task->priority = nextDnode->task->priority;
                nextDnode->task->priority = current->task->priority;
                afterNextDnode->prev = current;
            }
            afterNextDnode->prev = current;
            current->next = afterNextDnode;
        }
        else {
            last = current;
        }
        current->next = afterNextDnode;


        current->prev = nextDnode;
        nextDnode->prev = current;
        nextDnode->next = current->next;
        if (current->prev != NULL) {
            current->prev->next = nextDnode;
        }
        else {
            first = nextDnode;
        }
        current->prev = nextDnode;
        nextDnode->next = current;

    }
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
    cout << endl;
}

void DLL::printReverse() {
    DNode *current = last;
    cout << "Total Time Required: "<<tothrs<<":"<<totmin<<endl;
    while (current != NULL){
        current->task->printTask();
        current = current->prev;
    }
    cout << endl;
}
