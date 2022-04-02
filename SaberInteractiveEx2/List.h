#pragma once
#include <string>


struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // ��������� �� ������������ ������� ������� ������ ���� NULL
    std::string data;
};

class List {
public:
    List();

    void Serialize(FILE* file);  // ���������� � ���� (���� ������ � ������� fopen(path, "wb"))
    void Deserialize(FILE* file);  // �������� �� ����� (���� ������ � ������� fopen(path, "rb"))

    void PushBack(std::string newData);
    void Print();
    void UpdateRand();

private:
    ListNode* head;
    ListNode* tail;
    int count;

};
