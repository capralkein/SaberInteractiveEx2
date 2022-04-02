#include <iostream>
#include <ctime> 
#include <map>
#include "List.h"

List::List() :
    head(nullptr),
    tail(nullptr),
    count(0)
{
    
}

void List::Serialize(FILE* file)
{
    for (auto CurrentNode = head; CurrentNode != nullptr; CurrentNode = CurrentNode->next)
    {
        fprintf(file,
            "%p %p %s\n",
            reinterpret_cast<int*>(CurrentNode),
            reinterpret_cast<int*>(CurrentNode->rand),
            CurrentNode->data.c_str());
    }
}

void List::Deserialize(FILE* file)
{
    std::map<ListNode*, int*> intMap;
    std::map<int*, ListNode*> ListNodeMap;

    int* FirstPtr;
    int* SecondPtr;

    while (fscanf_s(file, "%p %p ", &FirstPtr, &SecondPtr) != EOF)
    {
        char BuffStr[128];
        int Index = 0;
        
        for (char Buff = fgetc(file); Buff != '\n'; Buff = fgetc(file))
        {
            BuffStr[Index] = Buff;
            Index++;
        }
        BuffStr[Index] = '\0';

        PushBack(BuffStr);
        intMap[tail] = SecondPtr;
        ListNodeMap[FirstPtr] = tail;
    }

    ListNode* CurrentNode = head;
    for (; CurrentNode != nullptr; CurrentNode = CurrentNode->next)
    {
        CurrentNode->rand = ListNodeMap[intMap[CurrentNode]];
    }
}

void List::PushBack(std::string newData)
{
    ListNode* NewNode = new ListNode{ nullptr, nullptr, nullptr, newData };

    if (tail != nullptr)
    {
        tail->next = NewNode;
        NewNode->prev = tail;
    }
    
    tail = NewNode;

    count++;

    if (head == nullptr)
    {
        head = tail;
    }
}

void List::Print()
{
    std::cout << 
        "prev\t\t" << 
        "curr\t\t" << 
        "next\t\t" << 
        "rand\t\t"
        "data" << std::endl;
    for (auto CurrentNode = head; CurrentNode != nullptr; CurrentNode = CurrentNode->next)
    {
        std::cout << 
            CurrentNode->prev << "\t" << 
            CurrentNode << "\t" << 
            CurrentNode->next << "\t" << 
            CurrentNode->rand << "\t" << 
            CurrentNode->data << std::endl;
    }
    std::cout << std::endl;
}

void List::UpdateRand()
{
    if (!head || !tail || count <= 0) return;

    ListNode* CurrentNode = head;
    std::srand(time(NULL));
    
    for (; CurrentNode != nullptr; CurrentNode = CurrentNode->next)
    {
        int RandomDigit = rand() % count;
        ListNode* RandomNode = nullptr;

        if (RandomDigit < count / 2)
        {
            RandomNode = head;
            for (int i = 0; i < RandomDigit; i++)
            {
                RandomNode = RandomNode->next;
            }
        }
        else
        {
            RandomNode = tail;
            for (int i = count; i > RandomDigit; i--)
            {
                RandomNode = RandomNode->prev;
            }
        }

        CurrentNode->rand = RandomNode;
    }
}


