//
//  main.cpp
//  test
//
//  Created by DANIEL SALAZAR on 9/21/17.
//  Copyright © 2017 DANIEL SALAZAR. All rights reserved.
//
// Calculate time for popular sorting algorithms on a 1000 element array

#include <iostream> // cout, cin, flush, endl
#include <string>   // string
#include <cstring>  // strtok
#include <fstream>  // ifstream
#include <iomanip>  // showpoint, fixed
#include "Data.h"
#define MAXLINE     (int)1028


// Input:
//  1) Get Filename from user
//  input: file stream reference
//  processing:
//  - set prompt to stdout
//  - get user input from stdin
//  - return results of input
//  output: a filename
//
//  Todo: Input Validation
std::ifstream& getFile(std::ifstream& fin)
{
    fin.exceptions (std::ifstream::badbit);
    do {
        // Prompt user for a file name
        std::string filename = "";
        std::cout << "Please input the filename: " << std::flush;
        std::cin >> filename;
        try {
            // open file for input
            fin.open(filename, std::ifstream::in);
        }
        catch (std::ifstream::failure e) {
            std::cerr << "Failed to open " << filename << ".\n";
        }
        std::cin.ignore();
    } while (!fin.is_open());
    return fin;
}
//  Output:
//  1) Print average of first column
//  input: calculated average value
//  processing:
//  - set results to output
//  output: nothing
//
//  Todo: Precision
void printAverage(Data<int> *average)
{
    try {
        std::cout << "The average value of all numbers in the first column: ";
        std::cout << average << std::endl;
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to print average.\n";
    }
    
}

//  Output:
//  2) Print max of second column
//  input: determined max value
//  processing:
//  - set results to output
//  output: nothing
void printMax(Data<int> max)
{
    try {
        std::cout << "The largest value of all numbers in the second column: " << max << std::endl;
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to print max value.\n";
    }
}

//  Output:
//  3) Print total number of rows
//  input: determined total value
//  processing:
//  - set results to output
//  output: nothing
//
//  Todo: nothing
void printTotal(Data<int> total)
{
    try {
        std::cout << "The total number of rows in the file is: " << total << std::endl;
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to print total rows.\n";
    }
}

//  Output:
//  4) Print List of invalid numbers
//  input: list
//  processing:
//  - foreach element in list
//      + set element to output
//  output: nothing
void printList(Data<char> list[], unsigned long long int count)
{
    try {
        std::cout << "The invalid numbers are: " << std::flush;
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to print.\n";
    }
    foreach(i, 0, count)
    {
        try {
            try {
                std::cout << list[i];
            } catch (std::range_error r) {
                std::cerr << "Index out of range.\n";
            }
            if(i < count - 1) std::cout << ", "  << std::flush;
            else std::cout << std::endl;
        } catch (std::ifstream::failure e) {
            std::cerr << "Failed to print list of invalid numbers.\n";
        }
    }
}

//  Process:
//  3) Check if number is valid
//  input: data from file in string
//  processing:
//  - check zeroth element for a negative sign or digit
//  - check the string from 1 to (n - 1) for digits
//  output: true if valid, false otherwise
bool is_valid(std::string number)
{
    // convert first element to character
    try {
        char zero(number[0]);
        // check if - or 0 to 9
        if(!(zero == '-' || isdigit(zero))) return false;
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    
    // loop the whole string checking each element
    // if element is a digit or not
    try {
        foreach(i, 1, number.size()) if(!(isdigit(number[i]))) return false;
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    // if element 0 is a - or a digit and the rest of the string are digits
    // then it is a valid number, return true.
    return true;
}


int main(int argc, const char * argv[])
{
    /*************************/
    /*********Storage*********/
    /*************************/
    
    // Sum of first column
    Data<int> sum("0");
    // Count of numbers added to sum
    Data<int> sumCount("0");
    // Max of second column
    Data<int> max("0");
    // Total rows in file
    Data<int> total("0");
    // Used to check if both col elements are valid
    // to make sure not to count a row of two
    // invalid numbers
    bool n1 = false, n2 = false;
    // List of invalid numbers (will get updated in Process)
    Data<char> *list;
    try {
        list = new Data<char>[MAXLINE];
    } catch (std::bad_alloc&) {
        std::cerr << "Unable to allocate memory.\n";
    }
    
    // list iterator
    unsigned long long int it = 0;
    // File handle (file-in)
    std::ifstream fin;
    // Buffer to hold a full line
    char lineBuffer[MAXLINE];
    // Pointers to the beginning of a number token
    char* ptr;
    // Used as temp storage of line elements
    std::string num1, num2;
    
    
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
        while(fin.getline(lineBuffer, MAXLINE - 1))
        {//seems to count blank lines as valid
            // Todo: account for blank lines
            // Get number 1
            ptr = strtok(lineBuffer, ",");
            // Initialize a string with the token
            if(ptr != nullptr) num1.assign(ptr);
            // test if token is an invalid number
            if(!is_valid(num1))
            {
                // number 1 is invalid
                n1 = false;
                // if it is invalid, turn it into data
                Data<char> invalid1(num1.c_str(), num1.length());
                // store in invalid list
                try {
                    list[it++] = invalid1;
                } catch (std::range_error r) {
                    std::cerr << "Index out of range.\n";
                }
                
            }
            else
            {
                // number 1 is valid
                n1 = true;
                // If it is a valid number
                Data<int> number1(num1);
                // Keep a running total of first column
                sum += number1;
                // Keep a running count of the first column
                ++sumCount;
            }
            
            // Get number 2
            ptr = strtok(NULL, "\n");
            // Initialize a string with the token
            if(ptr != nullptr) num2.assign(ptr);
            // test if token is an invalid number
            if(!is_valid(num2))
            {
                // number 2 is invalid
                n2 = false;
                // if it is invalid, turn it into data
                Data<char> invalid2(num2.c_str(), num2.length());
                // store in invalid list
                try {
                    list[it++] = invalid2;
                } catch (std::range_error r) {
                    std::cerr << "Index out of range.\n";
                }
            }
            else
            {
                // number 2 is valid
                n2 = true;
                // If it is a valid number
                Data<int> number2(num2);
                // Keep track of the maximum number in second column
                if(max < number2) max = number2;
            }
            // if number 1 or number 2 are valid numbers
            // then add one to total rows counter
            if(n1 == true || n2 == true) ++total;
        }
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    //  Close the file
    try {
        fin.close();
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to close file.\n";
    }
    
    
    // Calculate the average of the first column
    Data<int> *average = sum / sumCount;
    
    /*************************/
    /*********Output**********/
    /*************************/
    
    // Print Average of first column
    printAverage(average);
    // Print Max of second column
    printMax(max);
    // Print Total number of rows
    printTotal(total);
    // Print list of invalid numbers
    printList(list, it);
    
    return 0;
}





