#include <iostream>
#include<fstream>
#include<iomanip>
#include "hashTableType.h"
using namespace std;
int main()
{
    hashTableType <int> test(101);
    string ID;
    int data;
    ifstream f;
    f.open("data.txt");
    while (!f.eof())
    {
        f >> ID >> data;
        cout << setw(9) << ID << "\t" << setw(5) << data << endl;
        if (!test.insert(ID, data))
            cout << "key " << ID << " is already in the table. Duplicated key cannot be inserted" << endl;
    }
    f.close();

    

    
    return 0;
}
