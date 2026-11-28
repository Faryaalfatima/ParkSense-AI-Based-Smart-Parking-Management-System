#pragma once
#include "Slot.h"

// BST: saare slots slotID ke hisaab se tarteeb mein
// Rule: chhota ID left mein, bada ID right mein
// -1 ka matlab "koi nahi"
class BST
{
public:
    Slot data[MAX_SLOTS];     // slots yahan save hote hain
    int left[MAX_SLOTS];      // left child array mein kahan hai
    int right[MAX_SLOTS];     // right child array mein kahan hai
    bool used[MAX_SLOTS];     // ye jagah bhari hai ya khali
    int root;                 // sabse upar wala slot kahan hai (-1 = tree khali)

    BST()
    {
        root = -1;
        for (int i = 0; i < MAX_SLOTS; i++)
        {
            left[i] = -1;
            right[i] = -1;
            used[i] = false;
        }
    }

    // array mein pehli khali jagah dhoondo
    int findEmptyPlace()
    {
        for (int i = 0; i < MAX_SLOTS; i++)
        {
            if (used[i] == false)
            {
                return i;
            }
        }
        return -1;   // array full hai
    }

    // naya slot add karo
    void insert(Slot s)
    {
        // pehle check karo ye ID pehle se to nahi hai
        if (search(s.slotID) != -1)
        {
            cout << "This slot ID already exists" << endl;
            return;
        }

        int place = findEmptyPlace();
        if (place == -1)
        {
            cout << "Slots are full" << endl;
            return;
        }

        // naya slot array mein rakho
        data[place] = s;
        left[place] = -1;
        right[place] = -1;
        used[place] = true;

        // agar tree khali hai to ye root ban jayega
        if (root == -1)
        {
            root = place;
            return;
        }

        // warna root se neeche jao aur apni jagah dhoondo
        int current = root;
        while (true)
        {
            if (s.slotID < data[current].slotID)
            {
                // left jao
                if (left[current] == -1)
                {
                    left[current] = place;   // jagah mil gayi
                    return;
                }
                current = left[current];
            }
            else
            {
                // right jao
                if (right[current] == -1)
                {
                    right[current] = place;  // jagah mil gayi
                    return;
                }
                current = right[current];
            }
        }
    }

    // slot dhoondo, array ki jagah (index) wapas karo, na mile to -1
    int search(int id)
    {
        int current = root;
        while (current != -1)
        {
            if (id == data[current].slotID)
            {
                return current;  // mil gaya
            }
            else if (id < data[current].slotID)
            {
                current = left[current];       // chhota hai, left jao
            }
            else
            {
                current = right[current];      // bada hai, right jao

            }
        }
        return -1;   // nahi mila
    }

    // slot hatao (neeche wala deleteNode kaam karta hai)
    void deleteSlot(int id)
    {
        if (search(id) == -1)
        {
            cout << "Slot not found" << endl;
            return;
        }
        root = deleteNode(root, id);
        cout << "Slot " << id << " deleted" << endl;
    }

    // node ko delete karo aur batao ke ab is jagah par kaun hai
    int deleteNode(int node, int id)
    {
        if (node == -1)
        {
            return -1;
        }
        if (id < data[node].slotID)
        {
            left[node] = deleteNode(left[node], id);     // left mein dhoondo
        }
        else if (id > data[node].slotID)
        {
            right[node] = deleteNode(right[node], id);   // right mein dhoondo
        }
        else
        {
            // ye wohi node hai jo hatana hai

            // Case 1: koi bacha nahi (leaf)
            if (left[node] == -1 && right[node] == -1)
            {
                used[node] = false;
                return -1;
            }

            // Case 2: sirf right bacha hai
            if (left[node] == -1)
            {
                int child = right[node];
                used[node] = false;
                return child;
            }

            // Case 2: sirf left bacha hai
            if (right[node] == -1)
            {
                int child = left[node];
                used[node] = false;
                return child;
            }

            // Case 3: dono bache hain

            // right side ka sabse chhota slot dhoondo
            int smallest = right[node];
            while (left[smallest] != -1)
                smallest = left[smallest];

            // uska data is node mein copy kar do
            data[node] = data[smallest];

            // ab right side se wo chhota slot hata do
            right[node] = deleteNode(right[node], data[smallest].slotID);
        }
        return node;
    }

    // saare slots sorted dikhao (left, phir khud, phir right)
    void inorder(int node)
    {
        if (node == -1)
        {
            return;
        }
        inorder(left[node]);
        data[node].show();
        inorder(right[node]);
    }

    void show()
    {
        if (root == -1)
        {
            cout << "No slots available" << endl;
            return;
        }
        inorder(root);
    }

    // sabse chhote ID wala khali slot dhoondo (index wapas, na mile to -1)
    int findFree(int node)
    {
        if (node == -1)
        {
            return -1;
        }
        int result = findFree(left[node]);   // pehle left dekho
        if (result != -1)
        {
            return result;
        }
        if (data[node].isFree)               // phir khud
        {
            return node;
        }
        return findFree(right[node]);        // phir right
    }

    int findFreeSlot()
    {
        return findFree(root);
    }

    // slot ko bhar do
    void markOccupied(int id, string plate)
    {
        int index = search(id);
        if (index != -1)
            data[index].markOccupied(plate);
    }

    // slot ko khali kar do
    void markFree(int id)
    {
        int index = search(id);
        if (index != -1)
            data[index].markFree();
    }
};