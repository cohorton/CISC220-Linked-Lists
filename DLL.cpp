
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
using namespace std;


DLL::DLL(){
    first = last = NULL;
}

DLL::DLL(string taskname, int priority, int hours, int mins){
	DNode *temp = new DNode(taskname, priority, hours, mins);
    first = last = temp;
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

void DLL::push(string taskname, int priority, int hours, int mins) {
    if (!first){
        first = new DNode(taskname, priority, hours, mins);
        last = first;
    }
    else if(priority == 3){
        last->next = new DNode(taskname, priority, hours, mins);
        last->next->prev = last;
        last = last->next;
    }
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
    return taskPop;
}


int DLL::remove(int num) {
	DNode *current = first;
    while(current != NULL){
        if (current->task->tasknum == num){
            if (current == first && first == last){
                first = NULL;
                last = NULL;
            }
            else {
                first = first->next;
                first->prev = NULL;
            }
        }
        else if(current == last) {
            last = last->prev;
            last->next = NULL;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        tothrs -= current->task->hr;
        totmin -= current->task->min;
        if (totmin < 0){
            tothrs--;
            totmin+=60;
        }
        delete current->task;
        delete current;
        numTasks--;
        return num;
    }
    current = current->next;

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
    DNode* current = first;

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
        DNode *prevCurrent = current->prev;
        DNode *beforePrevCurrent = prevCurrent->prev;

        if (beforePrevCurrent != NULL) {
            if (prevCurrent->task->priority < current->task->priority) {
                current->task->priority = prevCurrent->task->priority;
                prevCurrent->task->priority = current->task->priority;
            }
            beforePrevCurrent -> next = current;
        }
        current->next = prevCurrent;
        prevCurrent->prev = current;
        prevCurrent->next = current->next;
        if (current->next != NULL) {
            current->next->prev = prevCurrent;
        }
        else {
            last = prevCurrent;
        }
        current->next = prevCurrent;
        prevCurrent->prev = current;

    }
}

void DLL::moveDown(int tasknum) {
	
}

void DLL::changePriority(int tasknum, int newPriority) {
	
}

void DLL::listDuration(int *pHours, int *pMins,int priority) {
	
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
	
}

void DLL::printReverse() {

}