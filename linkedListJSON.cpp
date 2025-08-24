#include <iostream>
#include <time.h>
#include <string>
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
            if (!head){ 
                head = tail = newTask;
                return;
            }
            tail->next = newTask;
            tail = newTask;
        }

        void removeTask(Task* newTask){
            Task* temp = head;
            while(temp->next != newTask){
                temp = temp->next;
            }
            temp->next = newTask->next;
            delete newTask;
        }

        void addTask(Task* newTask){
            float taskWeight = newTask->data.weight;
            if(!head){
                head = tail = newTask;
                return;
            }
            if(taskWeight <= head->data.weight){
                newTask->next = head;
                head = newTask;
                return;
            }
            if(taskWeight >= tail->data.weight){
                push_back(newTask);
                return;
            }
            Task* temp = head;
            while(temp->next != nullptr && temp->next->data.weight < taskWeight){
                temp = temp->next;
            }
            newTask->next = temp->next;
            temp->next = newTask;
            return;
        }

        void display() {
            if (!head) {
                std::cout << "List is empty.\n";
                return;
            }
            Task* temp = head;
            while (temp != nullptr) {
                std::cout << temp->data.name << " -> ";
                temp = temp->next;
            }
            std::cout << "NULL\n";
        }
};

void loadTasksFromJson(const std::string& filename, LinkedList& list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open " << filename << " for reading.\n";
        return; 
    }

    json j;
    file >> j;

    for (auto& item : j) {
        std::string name = item["name"];
        time_t deadlineRaw = item["deadline"];
        int type = item["type"];
        float weight = item["weight"];

        Task* newTask = new Task(name, deadlineRaw, type, weight);
        list.push_back(newTask);
    }
}

void saveTasksToJson(const std::string& filename, Task* head) {
    if (!head) {
        std::cout << "No tasks to save.\n";
        return;
    }

    json j = json::array();
    Task* temp = head;
    while (temp != nullptr) {
        j.push_back({
            {"name", temp->data.name},
            {"deadline", temp->data.deadlineRaw},
            {"type", temp->data.type},
            {"weight", temp->data.weight}
        });
        temp = temp->next;
    }

    std::ofstream file(filename);
    file << j.dump(4);
}


int main() {
    LinkedList list;

    loadTasksFromJson("tasks.json", list);

    

    saveTasksToJson("tasks.json", list.head);

    return 0;
}
