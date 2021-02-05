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
    ifstream database;
    inFile.open("C:\\Users\\tuckr\\OneDrive\\Documents\\EEC 173\\Assignment1\\IPlist.txt");
    database.open("C:\\Users\\tuckr\\OneDrive\\Documents\\EEC 173\\Assignment1\\DB_091803.txt");
    if (!inFile) {
        cerr << "Unable to open file IPlist.txt";
        exit(1);   // call system to stop
    }
    if (!database) {
        cerr << "Unable to open file Database";
        exit(1);   // call system to stop
    }


    int mask[200000];
    int AS[200000];


    int databaseIndex = 0;          //used to iterate through database parse
    string databaseIP;  //database ip temp variable
    int ip [4];         //ip temp variables
    while (!database.eof()) {                                              //iterate until end of file
        database >> databaseIP;     // input next ip address
        database >> mask[databaseIndex];
        database >> AS[databaseIndex];
        bool doParse = 1;
        int j = 0;                                                      // Initialize the J
        int oldj = 0;                                                   // Initialize the oldJ
        for (int i = 0; i < 4; i++) {                                   //For loop to get ip address
            while (databaseIP[j] != '.' && j != databaseIP.size()) {        //Find end of byte string
                j++;                                                    //Iterate
            }
            if (databaseIP[j+1] == '.' && i != 3 || oldj >= databaseIP.size()){
                doParse = 0;    // Do not parse
                cout << "exception handled";
                break;          // Erroneous .. checker
            }
            ip[i] = stoi(databaseIP.substr(oldj,j - oldj + 1));             //insert
            oldj = j+1;         // Iterate
            j++;                // Iterate
        }

        if (doParse) {
            cout << databaseIndex << ": " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << ' ' << mask[databaseIndex] << ' ' << AS[databaseIndex] << endl;
        }

        // Insert Binary Conversion code here and move database into array
        databaseIndex++;
    }

    cout << "Finished Database Input" << endl;

    //================================
    // Input IP search list
    //================================
    string searchIP;
    int searchIndex = 0;
    while (!inFile.eof()) {                                              //iterate until end of file
        inFile >> searchIP;
        int j = 0;                                                      // Initialize the J
        int oldj = 0;                                                   // Initialize the oldJ
        for (int i = 0; i < 4; i++) {                                   //For loop to get ip address
            while (searchIP[j] != '.' && j != searchIP.size()) {        //Find end of byte string
                j++;                                                    //Iterate
            }
            ip[i] = stoi(searchIP.substr(oldj,j - oldj + 1));             //insert
            // add if statement
            oldj = j+1;         // iterate
            j++;                // iterate
        }
        cout << "Search Term " << searchIndex + 1 << ": " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << endl;
        searchIndex++;
    }


    inFile.close();
    database.close();
    return 0;
}


/*
  if (temp1 > temp2) {
      cout << "It works" << endl;
  }
  if (temp1 < temp2){
      cout << "It also works" << endl;
  }
  */