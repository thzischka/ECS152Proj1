#include <iostream>
#include <fstream>
#include <string>
using namespace std;

std::string int2bin(int i)
{
    std::string buffer = "";
    buffer += to_string(i / 128);
    i = i % 128;
    buffer += to_string(i / 64);
    i = i % 64;
    buffer += to_string(i / 32);
    i = i % 32;
    buffer += to_string(i / 16);
    i = i % 16;
    buffer += to_string(i / 8);
    i = i % 8;
    buffer += to_string(i / 4);
    i = i % 4;
    buffer += to_string(i / 2);
    i = i % 2;
    buffer += to_string(i);
    return buffer;
}

std::string convertIPtoBinary(int i, int j, int k, int l)
{
    std::string str1 = int2bin(i);
    std::string str2 = int2bin(j);
    std::string str3 = int2bin(k);
    std::string str4 = int2bin(l);
    std::string address = str1 + str2 + str3 + str4;
    return address;
}

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
    inFile.open("IPlist.txt");
    database.open("DB_091803.txt");
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
    std::string DBIP[200000];

    //==============================
    // Database input parsing
    //==============================
    int databaseIndex = 0;          //used to iterate through database parse
    string databaseIP;              //database ip temp variable
    int ip [4];                     //ip temp variables
    while (!database.eof()) {       //iterate until end of file
        database >> databaseIP;     // input next ip address
        database >> mask[databaseIndex];
        database >> AS[databaseIndex];
        bool doParse = 1;
        int j = 0;                                                      // Initialize the J
        int oldj = 0;                                                   // Initialize the oldJ
        for (int i = 0; i < 4; i++) {                                   //For loop to get ip address
            while (databaseIP[j] != '.' && j != databaseIP.size()) {    //Find end of byte string
                j++;                                                    //Iterate
            }
            if ((databaseIP[j+1] == '.' && i != 3) || oldj >= databaseIP.size()){
                doParse = 0;    // Do not parse
                cout << "exception handled" << endl;
                break;          // Erroneous .. checker
            }
            ip[i] = stoi(databaseIP.substr(oldj,j - oldj + 1));  // Insert
            oldj = j+1;                                                 // Iterate
            j++;                                                        // Iterate
        }

        if (doParse) {
            DBIP[databaseIndex] = convertIPtoBinary(ip[0], ip[1], ip[2], ip[3]);
            //cout << databaseIndex << ": " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << ' ' << mask[databaseIndex] << ' ' << AS[databaseIndex] << endl;
            databaseIndex++;
        }

    }

    cout << "Finished Database Input" << endl;
    database.close();
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
            ip[i] = stoi(searchIP.substr(oldj,j - oldj + 1));    //insert
            oldj = j+1;                                                 // iterate
            j++;                                                        // iterate
        }

        // Insert Binary Conversion code
        //I should reuse the variable searchIP, right?
        searchIP = convertIPtoBinary(ip[0], ip[1], ip[2], ip[3]);
        cout << "Current IP Search Term: " << searchIP << endl;

        //putting the matching code here.


        //cout << "Search Term " << searchIndex + 1 << ": " << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3] << endl;
        searchIndex++;
    }


    inFile.close();
    return 0;
}