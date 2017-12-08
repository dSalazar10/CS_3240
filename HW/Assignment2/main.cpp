//Name: Daniel Salazar
//Email: dsalazar10@csueastbay.edu
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include "Table.h"
using namespace std;

typedef Table<int> List;
#define MAXLINE (int)1028
//  Process:
//  3) Check if number is valid
//  input: data from file in string
//  processing:
//  - check zeroth element for a negative sign or digit
//  - check the string from 1 to (n - 1) for digits
//  output: true if valid, false otherwise
bool is_valid(std::string number)
{
    // loop the whole string checking each element
    // if element is a digit or not
    try {
        // if any character is not a number, return false
        for(int i = 0; i < number.size(); ++i)
            if(!(isdigit(number[i]))) return false;
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    // If all the characters are numbers, return true
    return true;
}

//  Todo: Input Validation
std::ifstream& getFile(std::ifstream& fin)
{
    fin.exceptions (std::ifstream::badbit);
    do {
        // Prompt user for a file name
        std::string filename = "";
        std::cout << "Please input the filename: " <<    std::flush;
        std::cin >> filename;
        try {
            // open file for input
            fin.open(filename, std::ifstream::in);
        }
        catch (std::ifstream::failure e) {
            std::cerr   <<    "Failed to open "   <<    filename   <<    ".\n";
        }
        std::cin.ignore();
    } while (!fin.is_open());
    return fin;
}
int main(int argc, const char * argv[])
{

    /*************************/
    /*********Storage*********/
    /*************************/

    // List to hold the data
    List list;


    // File handle (file-in)
    std::ifstream fin;
    // Buffer to hold a full line
    char lineBuffer[MAXLINE];
    // Pointers to the beginning of a number token
    char* ptr;
    // Used as temp storage of line elements
    std::string num, pos;


    /*************************/
    /**********Input**********/
    /*************************/

    // Prompt user for filename
    // Open file if file exists
    getFile(fin);


    /*************************/
    /********Processing*******/
    /*************************/

    // Process File
    // While able to get a line from the file
    try {
        // Get the first line
        fin.getline(lineBuffer, MAXLINE - 1);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    // Start with the first number
    ptr = strtok(lineBuffer, ",");

    // Initialize a string with the token
    // and append it to the list
    if(ptr != nullptr)
    {
        num.assign(ptr);
        if(is_valid(num))
            list.Append(num);
    } else {
        cout << "Failed to process first line." << endl;
        exit(-1);
    }
    // Parse the rest of the numbers
    while((ptr = strtok(NULL, ", \n\t")) != nullptr)
    {
        // Initialize a string with the token
        if(ptr != nullptr)
        {
            num.assign(ptr);
            if(is_valid(num))
                list.Append(num);
        } else {
            break;
        }
    }
    list.PrintAll(list.begin());
    cout << endl;


    try {
        // Get the second line
        fin.getline(lineBuffer, MAXLINE - 1);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    // Start with the first number
    ptr = strtok(lineBuffer, ",");

    // Initialize a string with the token
    // and append it to the list
    if(ptr != nullptr)
    {
        num.assign(ptr);
        if(is_valid(num))
            list.Delete(num);
    } else {
        cout << "Failed to process second line." << endl;
        exit(-1);
    }
    // Parse the rest of the numbers
    while((ptr = strtok(NULL, ", \n\t")) != nullptr)
    {
        // Initialize a string with the token
        if(ptr != nullptr)
        {
            num.assign(ptr);
            if(is_valid(num))
                list.Delete(num);
        } else {
            break;
        }
    }
    list.PrintAll(list.begin());
    cout << endl;


    try {
        // Get the third line
        fin.getline(lineBuffer, MAXLINE - 1);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }

    // Get value to add
    ptr = strtok(lineBuffer, "@");
    if(ptr != nullptr) num.assign(ptr);
    // Get position
    ptr = strtok(NULL, ",");
    if(ptr != nullptr) pos.assign(ptr);
    // If both values are valid
    if(is_valid(num) && is_valid(pos))
    {
        // Use a string stream to convert
        // a C++ string into an int
        // Puts pos into buffer
        stringstream p(pos);
        // Init position
        int position = 0;
        // Output buffer of p into position
        p >> position;
        list.Add(num, position);
    }

    // Parse the rest of the numbers
    while((ptr = strtok(NULL, "@ \n\t")) != nullptr)
    {
        // Get value to add
        if(ptr != nullptr) num.assign(ptr);
        // Get position
        ptr = strtok(NULL, ",");
        if(ptr != nullptr) pos.assign(ptr);
        // If both values are valid
        if(is_valid(num) && is_valid(pos))
        {
            // Use a string stream to convert
            // a C++ string into an int
            // Puts pos into buffer
            stringstream p(pos);
            // Init position
            int position = 0;
            // Output buffer of p into position
            p >> position;
            list.Add(num, position);
        }
    }
    list.PrintAll(list.begin());
    cout << endl;



    //  Close the file
    try {
        fin.close();
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to close file.\n";
    }


    return 0;
}








