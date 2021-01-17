/**
 * @file main.cpp
 * @author
 *  Alejandra Guadalupe Olivas Altamirano  A01741389
 *  Carolina Gómez Manzano                 A01632229 
 *  Josue Salvador Cano Martinez           A00829022 
 * @brief Comprehensive activity on the use of hash codes (Competition Evidence)
 * @version 0.1
 * @date 2020-11-28
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * @brief the main function
 * 
 * @return nothing
 */
int main() {

    string file = "bitacora.txt"; 
    unordered_map<string, vector<string>> myData;

    ifstream in(file.c_str());
    string str, ip, port, dateHour, theIp; 
    myData[ip] = vector<string>();

    // Read the file and extract from each record the attributes necessary for the summary
    // Time Complexity: O(n)
    while (getline(in, str)) {
        dateHour = str.substr(0, 15);
        str = str.substr(16);
        ip = str.substr(0, str.find(":"));
        port = str.substr(str.find(":") + 1, 4);

        // Add the records to the hash table
        dateHour = dateHour + "   " + port;
        myData[ip].push_back(dateHour);
    }
    in.close();
    
    // Input data 
    cout << "Write the IP to display the summary: ";
    cin >> theIp;

    // Print the query result
    // Time Complexity: O(1)
    int theSize = myData[theIp].size();
    cout << "Number of accesses: " << theSize << endl; 
    cout << "Ip" << "                " << "Port" << endl; 
    for (const auto &x : myData[theIp]) 
        cout << x << endl; 

    return 0; 
}