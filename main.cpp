#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

/*
 * bin2int inputs a binary 32-bit IP address string and
 * outputs a CIDR formatted address string (ex "219.45.0.255")
 * This function is meant to convert a binary formatted IP address back into
 * a CIDR format for printing to the output.
 */
std::string bin2int(string bin)
{
    string substr;
    string returnstr;
    int i, j, k, l;
    substr.assign(bin, 0, 8);
    i = stoi(substr, nullptr, 2);
    substr.assign(bin, 8, 8);
    j = stoi(substr, nullptr, 2);
    substr.assign(bin, 16, 8);
    k = stoi(substr, nullptr, 2);
    substr.assign(bin, 24, 8);
    l = stoi(substr, nullptr, 2);
    returnstr = to_string(i) + "." + to_string(j) + "." + to_string(k) + "." + to_string(l);
    return returnstr;
}

/* int2bin inputs an integer value and returns an 8-bit binary string
 * this function is a helper function to convertIPtoBinary */
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

/*convertIPtoBinary inputs 4 integer values and
 * outputs a single 32-bit binary string (ex "11110000111100001010010110100000")
 * output is meant to be used for IP address matching in main function. */
std::string convertIPtoBinary(int i, int j, int k, int l)
{
    std::string str1 = int2bin(i);
    std::string str2 = int2bin(j);
    std::string str3 = int2bin(k);
    std::string str4 = int2bin(l);
    std::string address = str1 + str2 + str3 + str4;
    return address;
}

int main(int argc, char * argv[]) {

    // Input two tables
    // First Loop, iterate through IP table
    // Second loop, go through Database table
    // Convert everything to binary
    // cut both down according to the current database entry mask
    // compare:
    // If database entry larger than search ip, print and move to next search term
    // if not, continue on
    // repeat

    if(argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        cout << "Correct usage is: \"./a.out [database file] [IP address file]\"" << endl;
        exit(1);
    }

    ifstream inFile;
    ifstream database;
    database.open(argv[1]);  //open database file
    inFile.open(argv[2]);    //open IP list file
    if (!inFile) {
        cerr << "Unable to open file IPlist.txt" << endl;
        exit(1);   // call system to stop
    }
    if (!database) {
        cerr << "Unable to open file Database" << endl;
        exit(1);   // call system to stop
    }

    int mask[200000];               //array for storing database bit mask lengths
    int AS[200000];                 //array for storing database AS numbers
    static string DBIPBin[200000];         //array for storing database IP addresses in binary string format

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
            //handling invalid IP addresses
            if ((databaseIP[j+1] == '.' && i != 3) || oldj >= databaseIP.size()){
                doParse = 0;    // Do not parse
                break;          // Erroneous .. checker
            }
            ip[i] = stoi(databaseIP.substr(oldj,j - oldj + 1));  // Insert
            oldj = j+1;                                                 // Iterate
            j++;                                                        // Iterate
        }

        //If IP address is invalid, this code does not run
        //and the array index will not increment
        if (doParse) {
            DBIPBin[databaseIndex] = convertIPtoBinary(ip[0], ip[1], ip[2], ip[3]);
            databaseIndex++;
        }

    }
    database.close();

    //================================
    // Input IP search list
    //================================
    string searchIP;
    string searchIPbin;
    int searchIndex = 0;
    while (!inFile.eof()) {                                              //iterate until end of file

        inFile >> searchIP;
        if (searchIP.size() == 0)
        {
            continue;
        }
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

        //Binary Conversion code
        searchIPbin = convertIPtoBinary(ip[0], ip[1], ip[2], ip[3]);

        //=======================
        //Finding and printing a match in the database
        //=======================
        int maxMatchLength = 0;
        int matchIndex = 0;
        for(int dbIndex = 0; dbIndex < 200000; dbIndex++)
        {
            //check if entry can possibly be a longer prefix match
            if(mask[dbIndex] > maxMatchLength)
            {
                //compare substrings as long as the bit mask to see if a match is found
                if(searchIPbin.compare(0, mask[dbIndex], DBIPBin[dbIndex], 0, mask[dbIndex]) == 0)
                {
                    //match is found!
                    maxMatchLength = mask[dbIndex]; //update the maxMatchLength
                    matchIndex = dbIndex; //save the index into matchIndex
                }
            }
        }

        //printing the CIDR formatted IP database address and AS number as well as the searched IP address
        cout << bin2int(DBIPBin[matchIndex]) << "/" << mask[matchIndex] << " " << AS[matchIndex] << " " << searchIP << endl;
        //go to next IP address in file
        searchIndex++;
    }

    inFile.close();
    return 0;
}