#pragma once
#include <iostream>
#include "Slot.h"
#include "BST.h"
using namespace std;

const int GRAPH_SIZE = MAX_SLOTS + 1;
const int INF = 999999;

class Graph
{
private:
    int matrix[GRAPH_SIZE][GRAPH_SIZE];
    bool exists[GRAPH_SIZE];

public:
    int lastDistance;

    Graph()
    {
        for (int i = 0; i < GRAPH_SIZE; i++)
        {
            exists[i] = false;
            for (int j = 0; j < GRAPH_SIZE; j++)
            {
                matrix[i][j] = 0;
            }
        }
        lastDistance = -1;
    }

    void addNode(int slotID)
    {
        if (slotID < 0 || slotID >= GRAPH_SIZE)
        {
            cout << "Invalid node" << endl;
            return;
        }
        exists[slotID] = true;
    }

    void addEdge(int a, int b, int distance)
    {
        if (a < 0 || a >= GRAPH_SIZE || b < 0 || b >= GRAPH_SIZE)
        {
            cout << "Invalid node" << endl;
            return;
        }
        if (!exists[a] || !exists[b])
        {
            cout << "Add both nodes first" << endl;
            return;
        }
        if (distance <= 0)
        {
            cout << "Distance must be positive" << endl;
            return;
        }
        matrix[a][b] = distance;
        matrix[b][a] = distance;
    }

    void displayGraph()
    {
        for (int i = 0; i < GRAPH_SIZE; i++)
        {
            if (exists[i])
            {
                cout << "Node " << i << " : ";
                for (int j = 0; j < GRAPH_SIZE; j++)
                {
                    if (matrix[i][j] > 0)
                    {
                        cout << j << "(" << matrix[i][j] << ") ";
                    }
                }
                cout << endl;
            }
        }
    }

    int suggestNearestFreeSlot(int startSlotID, BST& tree)
    {
        lastDistance = -1;

        if (startSlotID < 0 || startSlotID >= GRAPH_SIZE || !exists[startSlotID])
        {
            return -1;
        }

        int dist[GRAPH_SIZE];
        bool visited[GRAPH_SIZE];
        for (int i = 0; i < GRAPH_SIZE; i++)
        {
            dist[i] = INF;
            visited[i] = false;
        }
        dist[startSlotID] = 0;

        for (int count = 0; count < GRAPH_SIZE; count++)
        {
            int u = -1;
            for (int i = 0; i < GRAPH_SIZE; i++)
            {
                if (exists[i] && !visited[i] && dist[i] < INF)
                {
                    if (u == -1 || dist[i] < dist[u])
                    {
                        u = i;
                    }
                }
            }

            if (u == -1)
            {
                break;
            }
            visited[u] = true;

            Slot* s = tree.search(u);
            if (s != NULL && s->isFree)
            {
                lastDistance = dist[u];
                return u;
            }

            for (int v = 0; v < GRAPH_SIZE; v++)
            {
                if (matrix[u][v] > 0 && !visited[v] && dist[u] + matrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + matrix[u][v];
                }
            }
        }
        return -1;
    }
};