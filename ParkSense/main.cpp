#include "Slot.h"
// TEST KELIYE
int main()
{
    Slot s(1, 'A');
    s.show();
    s.markOccupied("LEA-1234");
    s.show();
    s.markFree();
    s.show();

    Request r1("ABC-111", 3, 1);
    Request r2("EMG-999", 1, 2);
    r1.show();
    r2.show();

    if (r2.isBefore(r1))
        cout << "Emergency pehle" << endl;

    Reservation res("LEA-1234", 1);
    res.show();

    return 0;
}