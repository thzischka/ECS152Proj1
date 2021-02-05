#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    // Input two tables
    // First Loop, iterate through IP table
    // Second loop, go through Database table
    // Convert everything to binary
    // cut both down according to the current database entry mask
    // compare:
    // If database entry larger than search ip, print and move to next search term
    // if not, continue on
    // repeat

    ifstream inFile;
    ifstream Database;
    inFile.open("C:\\Users\\tuckr\\OneDrive\\Documents\\EEC 173\\Assignment1\\IPlist.txt");
    Database.open("C:\\Users\\tuckr\\OneDrive\\Documents\\EEC 173\\Assignment1\\DB_091803.txt");
    if (!inFile) {
        cerr << "Unable to open file IPlist.txt";
        exit(1);   // call system to stop
    }
    if (!Database) {
        cerr << "Unable to open file Database";
        exit(1);   // call system to stop
    }


    string searchIP;
    inFile >> searchIP;
    
    int ip [4];
    while (!inFile.eof()) {     //iterate until end of file
        inFile >> searchIP;
        int j = 0;              // Initialize the J
        int oldj = 0;           // Initialize the oldJ
        for (int i = 0; i < 4; i++) {          //For loop to get ip address
            while (searchIP[j] != '.' && searchIP[j] != '\n') {        //Find end of byte string
                j++;                           //Iterate
            }
            ip[i] = stoi(searchIP.substr(oldj,j));        //insert
            oldj = j+1;         // iterate
            j++;                // iterate
        }
        cout << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << endl;
    }
            cout << "done" << endl;
    /*
    if (temp1 > temp2) {
        cout << "It works" << endl;
    }
    if (temp1 < temp2){
        cout << "It also works" << endl;
    }
    */



    inFile.close();
    return 0;
}
