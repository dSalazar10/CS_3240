//
//  main.cpp
//  HW3
//
//  Created by DANIEL SALAZAR on 10/10/17.
//  Copyright © 2017 DANIEL SALAZAR. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Array.h"
using namespace std;
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
int main(int argc, const char * argv[]) {
    
    /*************************/
    /*********Storage*********/
    /*************************/

    // File handle (file-in)
    std::ifstream fin;
    // Buffer to hold a full line
    char lineBuffer[MAXLINE];
    // Pointers to the beginning of a card token
    char* ptr;
    // Sorted Array Implementation
    Array arr; // 20 elements
    
    
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
    
    // Read the first 20 cards in the first line of the file
    try {
        // Get the first line
        fin.getline(lineBuffer, MAXLINE - 1);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    // tokenize a card
    ptr = strtok(lineBuffer, ",");
    // put first card into the list
    if(ptr != nullptr)
    {
        arr.PutItem(ptr);
    } else {
        cout << "Failed to process first line." << endl;
        exit(-1);
    }
    // put other cards into the list
    int i = 0;
    while(i++ < 20 && (ptr = strtok(NULL, ", \n\t")) != nullptr)
    {
        // Initialize a string with the token
        if(ptr != nullptr)
        {
            arr.PutItem(ptr);
        } else {
            break;
        }
    }
    // Output all the cards in the list
    arr.PrintAll();
    cout << endl << endl;
    
    // Delete the cards indicated in the second line of the file
    try {
        // Get the second line
        fin.getline(lineBuffer, MAXLINE - 1);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    // Start with the first card
    ptr = strtok(lineBuffer, ",");
    // Delete first card
    if(ptr != nullptr)
    {
        arr.DeleteItem(ptr);
    } else {
        cout << "Failed to process second line." << endl;
        exit(-1);
    }
    // Delete the rest of the cards in line two
    while((ptr = strtok(NULL, ", \n\t")) != nullptr)
    {
        // Initialize a string with the token
        if(ptr != nullptr)
        {
            arr.DeleteItem(ptr);
        } else {
            break;
        }
    }
    // Output all the cards in the list
    arr.PrintAll();
    cout << endl << endl;
    
    // Put the items in the third line in to the list
    try {
        // Get the third line
        fin.getline(lineBuffer, MAXLINE - 1);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    // Start with the first card
    ptr = strtok(lineBuffer, ",");
    // Put into array
    if(ptr != nullptr)
    {
        arr.PutItem(ptr);
    } else {
        cout << "Failed to process first line." << endl;
        exit(-1);
    }
    // Put the rest of the cards from the line into the list
    while((ptr = strtok(NULL, ", \n\t")) != nullptr)
    {
        // Initialize a string with the token
        if(ptr != nullptr)
        {
            arr.PutItem(ptr);
        } else {
            break;
        }
    }
    // Output all the cards in the list
    arr.PrintAll();
    cout << endl << endl;
    
    // Search the current list for the elements in the line
    try {
        // Get the fourth line
        fin.getline(lineBuffer, MAXLINE - 1);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    // Start with the first card
    ptr = strtok(lineBuffer, ",");
    // Search for first card
    if(ptr != nullptr)
    {
        arr.Search(ptr);
    } else {
        cout << "Failed to process third line." << endl;
        exit(-1);
    }
    // Search for the rest of the cards
    while((ptr = strtok(NULL, ", \n\t")) != nullptr)
    {
        if(ptr != nullptr)
        {
            std::cout << ", ";
            arr.Search(ptr);
        } else {
            break;
        }
    }
    cout << endl << endl;
    
    //  Close the file
    try {
        fin.close();
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to close file.\n";
    }

    return 0;
}












