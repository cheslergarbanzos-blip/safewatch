#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

void menu() {
    int c;
    cout << "<<<<<<<<MAIN MENU>>>>>>>>" << endl;
    cout << "[1]" << endl;
    switch (c) {
        case 1:
            cout << "Option 1 selected." << endl;
            break;
        case 2:
            cout << "Option 2 selected." << endl;
            break;
        default:
            cout << "Invalid option." << endl;
    }
}