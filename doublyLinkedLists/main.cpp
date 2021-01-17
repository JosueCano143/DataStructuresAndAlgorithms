/*
*   Alejandra 07/10/2020
*
*
*
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

/**
 * @brief Fills ip address with zeros in order to have 3 digits blocks
 * 
 * @param ipAddress 
 */
void createNewIp(string &ipAddress) {
    string ip, ipEnd, currentblock, newIpAddress;
    int indexIp, index;

    indexIp = ipAddress.find(":");
    ipEnd = ipAddress.substr(indexIp+1,4); // ipEnd = last block
    ip = ipAddress.substr(0, indexIp);     // ip = first part

    // Create a new ip (first 12 digits)
    for (int i = 0;i < 4; i++) {

        index = ip.find("."); 
        currentblock = ip.substr(0,index);  // Get the new block

        if (currentblock.length() < 3) {
            currentblock.insert(0,3-currentblock.length(),'0');
        }

        newIpAddress.append(currentblock);
        if(i < 3)
            newIpAddress.append(".");

        // Set the beginning of the next block
        ip = ip.substr(index+1);
    }
    
    // Append the last block to the new ip
    newIpAddress.append(":");
    newIpAddress.append(ipEnd);

    ipAddress = newIpAddress;
}

/**
 * @brief Changes line format from month_day_hour...ip..
 *        to ip_month_day_hour...
 * 
 * @param line 
 */
void createNewLine(string &line) {
    string ip = "";
    int index = 0, indexIp = 0, c = 0;

    ip = line.substr(16);
    
    // Count ip length
    while(ip[c] != ' ') {
        c++;
    }    
    ip = ip.substr(0,c);
    line.erase(16,c+1);
    createNewIp(ip);

    // Insert new ip at the beginning of the line
    line.insert(0," ");
    line.insert(0,ip);
}

/**
 * @brief Read the file, changes its format and appends each line to a linked list
 *        Complexity O(n)
 * 
 * @param archivo 
 * @param file 
 */
void readFile(string archivo, list<string>& file) {

    ifstream in(archivo.c_str());
    string str;

    while (getline(in, str)) {
        createNewLine(str);
        file.push_back(str);
    }

    in.close();
}
/**
 * @brief Changes line format from ip_month_day_hour...
 *        to month_day_hour...ip...
 * 
 * @param line 
 */
void revertLine(string &line) {
    string oldIp = "";
    int index, k = 0;

    index = line.find(" "); // Find the index where ip ends
    oldIp = line.substr(0,index);   // Get ip address from line

    // delete zeros
    for(int i = 0; i <= oldIp.length(); i++) {
        if (oldIp[k] == '0') {
            if (oldIp[k-1] == '0' || oldIp[k-1] == '.' || k == 0) {
                oldIp.erase(k,1);
            } else {
                k++;
            }
        } else {
            k++;
        }
    }

    line.erase(0,index+1);  // Delete ip address from line
    index = 16; 
    line.insert(index," "); 
    line.insert(index,oldIp); // Insert ip address at index 16
    
}

int main() {

    list<string> file;  // linked list
    list<string>::iterator low, up, it,i;
    ofstream sortedFile;
    string first = "", last = "", low_s="", up_s="";

    sortedFile.open("sortedFile.txt", std::ofstream::out | std::ofstream::trunc);
    sortedFile.close(); 

    readFile("bitacora.txt", file);     

    file.sort(); // Complexity (nlogn)

    cout << "Hi " << endl;
    
    // Request first and last ip 
    cout << '\n' << "First ip address: " << endl;
    cin >> first;
    cout << '\n' << "Last ip address: " << endl;
    cin >> last;

    cout << '\n' <<  "Search results: " << '\n' << "_____________________" << endl;

    // New format
    createNewIp(first);
    createNewIp(last);
 
    // Iterators 
    it = file.begin();
    low = lower_bound(file.begin(), file.end(), first); // O(n) since random access is not supported in std::list
    up = upper_bound(low,file.end(), last); // O(n) since random access is not supported in std::list
    // Strings 
    low_s = *low;
    up_s = *up;

    // Complexity O(n)
    sortedFile.open("sortedFile.txt", std::ios_base::app);
    for(it; it != file.end(); it++) {

        // Each line is reverted         
        if (*it >= low_s && *it <= up_s ) { // If a line is on the search range it'll be printed
            revertLine(*it);
            cout << *it << endl;

        } else {
            revertLine(*it);
        }        
        sortedFile << *it << endl; // Append each line to the file
    } 

    sortedFile.close();
  
}

