#pragma once
#include <iostream>
#include <string>
#include "Slot.h"
using namespace std;

class HashNode
{
public:
    Reservation data;
    HashNode* next;

    HashNode(string p, int id)
    {
        data = Reservation(p, id);
        next = NULL;
    }
};

class HashTable
{
private:
    HashNode* table[TABLE_SIZE];

    int hashFunction(string plate)
    {
        int sum = 0;
        int n = plate.length();
        for (int i = 0; i < n; i++)
        {
            sum = sum + plate[i];
        }
        return sum % TABLE_SIZE;
    }

public:
    HashTable()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            table[i] = NULL;
        }
    }

    void insert(string plate, int slotID)
    {
        int index = hashFunction(plate);

        HashNode* curr = table[index];
        while (curr != NULL)
        {
            if (curr->data.plate == plate)
            {
                curr->data.slotID = slotID;
                return;
            }
            curr = curr->next;
        }

        HashNode* temp = new HashNode(plate, slotID);
        temp->next = table[index];
        table[index] = temp;
    }

    int search(string plate)
    {
        int index = hashFunction(plate);
        HashNode* curr = table[index];

        while (curr != NULL)
        {
            if (curr->data.plate == plate)
            {
                return curr->data.slotID;
            }
            curr = curr->next;
        }
        return -1;
    }

    bool remove(string plate)
    {
        int index = hashFunction(plate);
        HashNode* curr = table[index];
        HashNode* prev = NULL;

        while (curr != NULL)
        {
            if (curr->data.plate == plate)
            {
                if (prev == NULL)
                    table[index] = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    void display()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << "Index " << i << ": ";
            HashNode* curr = table[i];
            if (curr == NULL)
            {
                cout << "empty";
            }
            while (curr != NULL)
            {
                cout << "[" << curr->data.plate << " -> " << curr->data.slotID << "] ";
                curr = curr->next;
            }
            cout << endl;
        }
    }

    ~HashTable()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            HashNode* curr = table[i];
            while (curr != NULL)
            {
                HashNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }
};