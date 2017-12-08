//Name: Daniel Salazar
//Email: dsalazar10@csueastbay.edu
//

#include <iostream>
#include <fstream>
#include <string>
#include "LinkedList.h"
using namespace std;

#define MAXLINE (int)1028



int main(int argc, const char * argv[])
{
    
    /*************************/
    /*********Storage*********/
    /*************************/
    
    // List to hold the data
    LinkedList<char> list;
    
    // File handle (file-in)
    std::ifstream letters, sequence;
    // Buffer to hold a full line
    char lineBuffer[MAXLINE];
    // Used as temp storage of line elements
    std::string num;
    
    
    /*************************/
    /**********Input**********/
    /*************************/
    
    try {
        letters.open("Letters.txt", std::ifstream::in);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to open Letters.txt.\n";
    }
    try {
        sequence.open("Sequence.txt", std::ifstream::in);
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to open Sequence.txt.\n";
    }
    
    /*************************/
    /********Processing*******/
    /*************************/
    
    // Get Letters
    try {
        while(letters.getline(lineBuffer, MAXLINE - 1))
        {
            list.PutItem(lineBuffer[0]);
        }
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    
    try {
        while(sequence.getline(lineBuffer, MAXLINE - 1))
        {
            num.assign(lineBuffer);
            list.PrintWord(num);
            std::cout << endl;
        }
    }
    catch (std::ifstream::failure e) {
        std::cerr << "Failed to process file.\n" << e.what() << "\n" << e.std::exception::what() << "\n";
        exit(-1);
    }
    
    try {
        letters.close();
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to close file.\n";
    }
    try {
        sequence.close();
    } catch (std::ifstream::failure e) {
        std::cerr << "Failed to close file.\n";
    }
    
    
    return 0;
}









