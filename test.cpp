#include <iostream>
#include "HashTable.h"
using namespace std;

int main()
{
    HashTable h;
    h.insert("AB1", 5);
    h.insert("LHR5", 7);
    h.insert("BA1", 9);
    h.display();
    cout << h.search("AB1") << endl;   // 5
    cout << h.search("XYZ") << endl;   // -1
    h.remove("BA1");
    h.display();
    return 0;
}