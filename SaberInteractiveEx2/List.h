#pragma once
#include <string>


struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // указатель на произвольный элемент данного списка либо NULL
    std::string data;
};

class List {
public:
    List();

    void Serialize(FILE* file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize(FILE* file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

    void PushBack(std::string newData);
    void Print();
    void UpdateRand();

private:
    ListNode* head;
    ListNode* tail;
    int count;

};
