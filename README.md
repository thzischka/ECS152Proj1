# ECS152Proj1
EEC 173A Project 1
By: Ann Ryan and Tucker Zischka

About the Project:
This project is a single script written in C++.
You will need a C++ compiler to compile and run the project.
This is built into many computers, including the UC Davis CS lab ones.

Compile our main.cpp file using the terminal command:
  g++ -o ip2as main.cpp
Feel free to use additional flags such as -Wall or -Werror.
Or skip using this command altogther by using a built-in C++ compilier in an IDE.
Or compile our code however pleases you best.

Run our project using the terminal command:
  ./ip2as DBfilename.txt IPlist.txt
Of course, replace the database and IP search list filenames with what you have.

How our project works:
We check if the number of arguments are correct and if the files can be open and read.
We parse through the Database file and store its values into three separate arrays, one for IP address, one for bit mask length, and one for AS number. As we parse, we do not store invalid IP addresses and their corresponding AS values.
After this, we parse through the IP list file. As we go through each IP address, we find corresponding IP address in the database array using longest prefix matching and print the matching IP address and the matching AS number from the database to the output terminal. Our longest prefix matching is done by comparing the first part of both IP binary strings, up to the specified bit length. After finding the first match, the program only searches and compares strings for IP addresses with longer bit lengths, so that any following match would have a longer prefix. 
Once this is performed on all IP addresses in the search file, the file is closed. 
