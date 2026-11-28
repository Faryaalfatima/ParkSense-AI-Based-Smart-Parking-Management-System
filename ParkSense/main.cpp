#include "BST.h"
#include "MinHeap.h"
#include "Queue.h"

BST tree;           // saare slots
MinHeap heap;       // pending requests (priority ke hisaab se)
Queue waitingList;  // jinhein slot nahi mila
int requestCounter = 1;   // har nayi request ka number

void showMenu()
{
    cout << endl;
    cout << "===== ParkSense =====" << endl;
    cout << "1. Add Slot" << endl;
    cout << "2. Show All Slots" << endl;
    cout << "3. Delete Slot" << endl;
    cout << "4. Add Parking Request" << endl;
    cout << "5. Process Next Request" << endl;
    cout << "6. Show Pending Requests" << endl;
    cout << "7. Show Waiting List" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
}

// naya slot add karo
void addSlot()
{
    int id;
    char zone;
    cout << "Slot ID: ";
    cin >> id;
    cout << "Zone (A/B/C): ";
    cin >> zone;
    tree.insert(Slot(id, zone));
}

// saare slots dikhao
void showSlots()
{
    tree.show();
}

// slot hatao (bhara hua slot nahi hatega)
void deleteSlot()
{
    int id;
    cout << "Slot ID: ";
    cin >> id;

    int index = tree.search(id);
    if (index != -1 && tree.data[index].isFree == false)
    {
        cout << "A car is parked in this slot, it cannot be deleted" << endl;
        return;
    }
    tree.deleteSlot(id);
}

// nayi request lo aur heap mein daalo
void addRequest()
{
    string plate;
    int type;
    cout << "Plate number: ";
    cin >> plate;
    cout << "Type (1 = Emergency, 2 = VIP, 3 = Normal): ";
    cin >> type;

    if (type < 1 || type > 3)
    {
        cout << "Invalid type" << endl;
        return;
    }
    if (heap.isFull())
    {
        cout << "Requests are full" << endl;
        return;
    }

    heap.insert(Request(plate, type, requestCounter));
    requestCounter++;
    cout << "Request added" << endl;
}

// sabse zaroori request ko slot do, slot na mile to waiting list mein
void processNextRequest()
{
    if (heap.isEmpty())
    {
        cout << "No pending requests" << endl;
        return;
    }

    Request r = heap.extractMin();
    int index = tree.findFreeSlot();

    if (index == -1)
    {
        // koi slot khali nahi
        waitingList.enqueue(r);
        cout << r.plate << " did not get a slot, added to the waiting list" << endl;
    }
    else
    {
        tree.data[index].markOccupied(r.plate);
        cout << r.plate << " got Slot " << tree.data[index].slotID << endl;

        // Rameen: yahan hash table mein save karna hai (plate -> slotID)
    }
}

// pending requests dikhao
void showPending()
{
    heap.show();
}

// waiting list dikhao
void showWaiting()
{
    waitingList.show();
}

int main()
{
    int choice;
    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: addSlot(); break;
        case 2: showSlots(); break;
        case 3: deleteSlot(); break;
        case 4: addRequest(); break;
        case 5: processNextRequest(); break;
        case 6: showPending(); break;
        case 7: showWaiting(); break;
        case 0: cout << "Bye" << endl; break;
            // Rameen: yahan apne options add karna (search, cancel, checkout, nearby)
        default: cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}