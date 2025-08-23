#include <iostream>
#include <time.h>
#include <fstream>
#include "json.hpp"

class Task{
    public: 
        std::string name;
        time_t deadlineRaw;
        std::string deadline;
        int type;
        float weight;
        Task* next;

        Task(std::string name, time_t deadlineRaw, int type, float weight){
            this->name = name;
            this->deadlineRaw = deadlineRaw;
            this->type = type;
            this->weight = weight;

            this->deadline = ctime(&deadlineRaw);
            this->next = nullptr;
        }
};

class LinkedList{
    public:
        Task* head;
        Task* tail;

        void push_back(Task* newTask){
            if(!head){
                head = tail = newTask;
                return;
            }
            Task* temp = tail;
            temp->next = newTask;
            tail = newTask;
        }
};