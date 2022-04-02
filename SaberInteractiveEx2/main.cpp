#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "List.h"


int main()
{
    List* TestList = new List();

    int ListLen = 10;

    for (int i = 1; i <= ListLen; i++)
    {
        TestList->PushBack("Line " + std::to_string(i));
    }
    TestList->UpdateRand();
    TestList->Print();

    FILE* FileToSave = fopen("TestList.bin", "wb");
    if (FileToSave != nullptr)
    {
        TestList->Serialize(FileToSave);
        fclose(FileToSave);
    }
    delete TestList;

    FILE* OpenedFile = fopen("TestList.bin", "rb");
    if (OpenedFile != nullptr)
    {
        List* OpenedList = new List();

        OpenedList->Deserialize(OpenedFile);
        OpenedList->Print();

        delete OpenedList;
    }
}