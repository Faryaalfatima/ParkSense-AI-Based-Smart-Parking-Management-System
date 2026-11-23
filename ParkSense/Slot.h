#pragma once
#include <iostream>
#include <string>
using namespace std;

const int MAX_SLOTS = 50;
const int MAX_REQUESTS = 50;
const int TABLE_SIZE = 10;

// parking ka ek slot
class Slot
{
public:
    int slotID;
    char zone;
    bool isFree;
    string plate;

    Slot()
    {
        slotID = 0;
        zone = 'A';
        isFree = true;
        plate = "";
    }

    Slot(int id, char z)
    {
        slotID = id;
        zone = z;
        isFree = true;
        plate = "";
    }

    // slot bhar do aur gaari ka number likh do
    void markOccupied(string p)
    {
        isFree = false;
        plate = p;
    }

    // slot khali kar do
    void markFree()
    {
        isFree = true;
        plate = "";
    }

    void show()
    {
        cout << "Slot " << slotID << " | Zone " << zone << " | ";
        if (isFree)
            cout << "Free" << endl;
        else
            cout << "Occupied by " << plate << endl;
    }
};

// gaari ki parking request
class Request
{
public:
    string plate;
    int priority;    // 1 = Emergency, 2 = VIP, 3 = Normal
    int requestNo;   // pehle aane wali request ka number chhota

    Request()
    {
        plate = "";
        priority = 3;
        requestNo = 0;
    }

    Request(string p, int pr, int no)
    {
        plate = p;
        priority = pr;
        requestNo = no;
    }

    // true agar ye request other se pehle honi chahiye
    bool isBefore(Request other)
    {
        if (priority != other.priority)
            return priority < other.priority;
        return requestNo < other.requestNo;
    }

    void show()
    {
        cout << "Plate " << plate << " | ";
        if (priority == 1)
        {
            cout << "Emergency";
        }
        else if (priority == 2)
        {
            cout << "VIP";
        }
        else
        {
            cout << "Normal";
        }
        cout << " | Request No " << requestNo << endl;
        
    }
};

// plate se slot ka record (hash table mein save hoga)
class Reservation
{
public:
    string plate;
    int slotID;

    Reservation()
    {
        plate = "";
        slotID = -1;   // -1 matlab koi slot nahi
    }

    Reservation(string p, int id)
    {
        plate = p;
        slotID = id;
    }

    void show()
    {
        cout << "Plate " << plate << " -> Slot " << slotID << endl;
    }
};

