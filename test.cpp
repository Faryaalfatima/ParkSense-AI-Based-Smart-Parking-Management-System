#include <iostream>
#include "Slot.h"
using namespace std;

class BST
{
public:
    Slot slots[MAX_SLOTS + 1];

    BST()
    {
        for (int i = 1; i <= MAX_SLOTS; i++)
        {
            slots[i] = Slot(i, 'A');
        }
    }

    Slot* search(int id)
    {
        if (id < 1 || id > MAX_SLOTS)
            return NULL;
        return &slots[id];
    }
};

#include "Graph.h"

int main()
{
    BST tree;
    Graph g;
    for (int i = 0; i <= 4; i++)
    {
        g.addNode(i);
    }
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 4);
    g.addEdge(2, 3, 3);
    g.addEdge(3, 4, 5);
    g.displayGraph();

    tree.slots[2].markOccupied("AB1");
    cout << g.suggestNearestFreeSlot(0, tree) << " dist " << g.lastDistance << endl;

    tree.slots[3].markOccupied("BA1");
    cout << g.suggestNearestFreeSlot(0, tree) << " dist " << g.lastDistance << endl;

    tree.slots[1].markOccupied("LHR5");
    cout << g.suggestNearestFreeSlot(0, tree) << " dist " << g.lastDistance << endl;

    tree.slots[4].markOccupied("XY9");
    cout << g.suggestNearestFreeSlot(0, tree) << " dist " << g.lastDistance << endl;
    return 0;
}