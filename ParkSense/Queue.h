#pragma once
#include "Slot.h"

// waiting list: pehle aane wali request pehle nikalti hai
class Queue
{
public:
    Request data[MAX_REQUESTS];
    int front;   // yahan se request nikalti hai
    int rear;    // yahan aakhri request add hui
    int count;   // queue mein kitni requests hain

    Queue()
    {
        front = 0;
        rear = -1;
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

    // request peeche se add karo
    void enqueue(Request r)
    {
        if (isFull())
        {
            cout << "Waiting list full hai" << endl;
            return;
        }
        rear = (rear + 1) % MAX_REQUESTS;
        data[rear] = r;
        count++;
    }

    // aage se request nikalo aur wapas do
    Request dequeue()
    {
        Request r;
        if (isEmpty())
        {
            cout << "Waiting list khali hai" << endl;
            return r;   // khali request wapas
        }
        r = data[front];
        front = (front + 1) % MAX_REQUESTS;
        count--;
        return r;
    }

    // waiting list dikhao
    void show()
    {
        if (isEmpty())
        {
            cout << "Waiting list khali hai" << endl;
            return;
        }
        for (int i = 0; i < count; i++)
        {
            int index = (front + i) % MAX_REQUESTS;
            data[index].show();
        }
    }
};
