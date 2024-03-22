
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
    Task* temp = new Task(taskname,priority,hours,mins);
	if (!first) {
        first = new DNode();
        first->task = temp;
        last = first;
    }
    else if (priority == 3) {
        last->next = new DNode();
        last->prev->next = last;
        last = last->next;
        last->task = temp;
    }
    else {
        DNode *current = last;
        while (current && current->task->priority != priority && current->prev != NULL) {
            current = current->prev;
        }

        if (current->task->priority == priority) {
            DNode *prio = new DNode();
            prio->task = temp;
            prio->next = current->next;
            if (current->next != NULL){
                current->next->prev = prio;
            }
            current->next = prio;
            prio->prev = current;
            if (current == last){
                last = prio;
            }
            else {
                last->next = new DNode();
                last->next->prev = last;
                last = last->next;
                last->task = temp;
            }
        }
    }
    numTasks++;
    tothrs += hours;
    totmin += mins;
}

Task *DLL::pop() {

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

	
}

void DLL::removeTime(int hours, int mins) {
	
}

void DLL::moveUp(int tasknum) {
	
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
