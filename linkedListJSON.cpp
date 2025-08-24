#include <iostream>
#include <time.h>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

struct content{
        std::string name;
        time_t deadlineRaw;
        std::string deadline;
        int type;
        float weight;
};

class Task{
    public:
        struct content data;        
        Task* next;

        Task(std::string name, time_t deadlineRaw, int type, float weight){
            this->data.name = name;
            this->data.deadlineRaw = deadlineRaw;
            this->data.type = type;
            this->data.weight = weight;

            this->data.deadline = ctime(&deadlineRaw);
            this->next = nullptr;
        }
};

class LinkedList{
    public:
        Task* head = nullptr;
        Task* tail = nullptr;

        void push_back(Task* newTask){
            if(!head){
                head = tail = newTask;
                return;
            }
            Task* temp = tail;
            temp->next = newTask;
            tail = newTask;
        }
        void taskSwitch(Task* task1, Task* task2){
            content temp;
            temp = task1->data;
            task1->data = task2->data;
            task2->data = temp;
        }
        void display(){
            Task* temp = head;
            while(temp != nullptr){
                std::cout << temp->data.name << " -> ";
                temp = temp->next;
            }
        }
};