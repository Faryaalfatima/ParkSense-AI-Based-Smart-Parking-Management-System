#include "Queue.h"

int main()
{
    Queue q;

    q.enqueue(Request("ABC-111", 3, 1));
    q.enqueue(Request("XYZ-222", 2, 2));
    q.enqueue(Request("LEA-333", 3, 3));

    cout << "Waiting list:" << endl;
    q.show();

    cout << endl << "Pehli request nikali:" << endl;
    Request r = q.dequeue();
    r.show();

    cout << endl << "Ab waiting list:" << endl;
    q.show();

    q.dequeue();
    q.dequeue();
    cout << endl;
    q.dequeue();   // khali queue ka test

    return 0;
}