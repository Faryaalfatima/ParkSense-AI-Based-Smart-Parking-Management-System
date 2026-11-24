#pragma once
#include "Slot.h"

// priority wali requests: sabse zyada priority wali request root (index 0) par hoti hai
// Emergency (1) pehle, phir VIP (2), phir Normal (3)
class MinHeap
{
public:
    Request data[MAX_REQUESTS];
    int count;   // heap mein kitni requests hain

    MinHeap()
    {
        count = 0;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    bool isFull()
    {
        return count == MAX_REQUESTS;
    }

    // do requests ki jagah badal do
    void swapRequests(int i, int j)
    {
        Request temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }

    // nayi request add karo (neeche se shuru karke upar le jao)
    void insert(Request r)
    {
        if (isFull())
        {
            cout << "Pending requests full hain" << endl;
            return;
        }

        data[count] = r;
        int i = count;
        count++;

        // jab tak parent se zyada priority hai, upar chadhte jao
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (data[i].isBefore(data[parent]))
            {
                swapRequests(i, parent);
                i = parent;
            }
            else
                break;
        }
    }

    // sabse zyada priority wali request root se nikalo
    Request extractMin()
    {
        Request top;
        if (isEmpty())
        {
            cout << "Pending requests khali hain" << endl;
            return top;   // khali request wapas
        }

        top = data[0];

        // aakhri request ko root par le aao
        data[0] = data[count - 1];
        count--;

        // ab usko neeche le jao jab tak apni sahi jagah na mil jaye
        int i = 0;
        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < count && data[left].isBefore(data[smallest]))
                smallest = left;
            if (right < count && data[right].isBefore(data[smallest]))
                smallest = right;

            if (smallest != i)
            {
                swapRequests(i, smallest);
                i = smallest;
            }
            else
                break;
        }

        return top;
    }

    // root dekho, nikalo nahi
    Request peek()
    {
        Request r;
        if (isEmpty())
            return r;
        return data[0];
    }

    // saari pending requests dikhao
    void show()
    {
        if (isEmpty())
        {
            cout << "Pending requests khali hain" << endl;
            return;
        }
        for (int i = 0; i < count; i++)
            data[i].show();
    }
};
