
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TaskManager.hpp"
using namespace std;


int main() {
        DLL taskList;

        cout << "Adding tasks:" << endl;
        taskList.push("Task 1", 1, 1, 30);
        taskList.printList();
        taskList.push("Task 2", 2, 2, 15);
        taskList.printList();

        cout << "Removing tasks:" << endl;
        taskList.remove(707);
        taskList.printList();
        taskList.remove(449);
        taskList.printList();

        taskList.push("Task 3", 1, 3, 45);
        taskList.push("Task 4", 3, 1, 0);
        taskList.push("Task 5", 2, 2, 30);
        taskList.printList();

        cout << "Moving tasks up:" << endl;
        taskList.moveUp(858);
        taskList.moveUp(707);
        taskList.moveUp(230);
        taskList.printList();

        cout << "Moving tasks down:" << endl;
        taskList.moveDown(573);
        taskList.moveDown(230);
        taskList.moveDown(858);
        taskList.printList();

        int hours = 0, mins = 0;
        taskList.listDuration(&hours, &mins, 2);
        cout << "Total duration for priority 2: " << hours << " hours and " << mins << " minutes" << endl;

        cout << "Tasks with priority 2:" << endl;
        taskList.printList(2);

        cout << "Changing priority of task 4:" << endl;
        taskList.changePriority(858, 2);
        taskList.printList();

        cout << "List in reverse:" << endl;
        taskList.printReverse();

        return 0;
    }


