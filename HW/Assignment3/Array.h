//
//  Array.h
//  HW3
//
//  Created by DANIEL SALAZAR on 10/10/17.
//  Copyright © 2017 DANIEL SALAZAR. All rights reserved.
//
// This data structure is used to hold cards. They are represented
// as integers from 0-51. The order of the suits are, from lowest
// to highest, Clubs, Diamonds, Hearts, and Spades.
// The order of values is 2,3,4,5,6,7,8,9,10,J,Q,K,A.
// C = 0-12
// D = 13-25
// H = 26-38
// S = 39-51
#include <cassert>
#include <sstream>

#define MAX (int)20

#ifndef Array_h
#define Array_h

class Array
{
private:
    int *_a;
    int _n;
    
    // Shift everything to the left
    void ShiftR(int i);
    // Shift everything to the right
    void ShiftF(int i);
    // Change from char to int
    int convert(char *c);
    // Change from int to char
    char* revert(int c);
    // Direct access to the integer
    int GetItem(int i) { assert(_n >= 0); return _a[i]; }
    // Check if given card is in Array
    bool inArray(int card);
public:
    // Default constructor
    Array(int size = MAX);
    // Copy constructor
    Array(const Array &m);
    // Move constructor
    Array(Array &&m);
    // Destructor
    ~Array();
    // Number of elements
    int size(void) const { return _n; }
    // Checks if 0 elements
    bool empty(void) const { return _n == 0; }
    // Direct access to element
    char* operator[](int i) { return revert(GetItem(i)); }
    // Copy assignment
    Array &operator=(Array &rhs);
    // Move constructor
    Array &operator=(Array &&rhs);
    // Set a card in array
    void PutItem(char *item);
    // Remove a card from the array
    void DeleteItem(char* item);
    // Display all the card
    void PrintAll();
    void Search(char* item);
};
#endif /* Array_h */

// Recursively shift elements to the left
// Used in Delete
void Array::ShiftR(int i)
{
    // Start i
    if(i + 1 <= MAX)
    {
        // copy
        _a[i] = _a[i + 1];
        // goto next element
        ShiftR(i + 1);
    }
    return;
}
// Recursively shift elements to the right
// Used in PutItem
void Array::ShiftF(int i)
{
    // start at i
    if(i + 1 <= MAX)
    {
        // effectively moves to end first
        ShiftF(i + 1);
        // copy
        _a[i + 1] = _a[i];
    }
    return;
}
// Change from char (C2 - SA) to int (0 - 51)
int Array::convert(char *c)
{
    int s = 0, v = 0;
    // convert suit to int
    // Suit becomes superscript
    switch(c[0])
    {
        case 'C': s = 0;
            break;
        case 'D': s = 1;
            break;
        case 'H': s = 2;
            break;
        default: s = 3;
            break;
    }
    // get next element in card
    char *ca = c+1;
    // Convert letter values
    switch(*ca)
    {   // CJ == 9 + (13 * 0) == 9
        case 'J': return 9 + (13 * s);
        // DQ == 10 + (13 * 1) == 23
        case 'Q': return 10 + (13 * s);
        // HK == 11 + (13 * 2) == 37
        case 'K': return 11 + (13 * s);
        // SA == 12 + (13 * 3) == 51
        case 'A': return 12 + (13 * s);
    }
    // convert value into an int
    // used for values 2-10
    // Store in buffer
    std::stringstream val(ca);
    // Output into x
    val >> v;
    // If buffer isn't empty
    // return fail flag -1
    // otherwise return v - 2
    // the - 2 is used because
    // C2 needs to equal 0, shift to
    // the left by 2
    v = (!val) ? (-1) : (v - 2);
    // H10 == 8 + (13 * 2) == 34
    return v + (13 * s);
}
// Change from int (0 - 51) to char (C2 - SA)
char* Array::revert(int c)
{
    char *results;
    // Reduce complexity
    char suits[] = "CDHS";
    char values[] = "23456789";
    const int J = 9, Q = 10, K = 11, A = 12;
    
    // Revert suit and value if ten card
    // otherwise revert suit
    switch(c)
    {
        // If value is 10, we need 3 elements
        // C10
        case 8: results = new char[3];
            results[0] = suits[c / 13];
            results[1] = '1';
            results[2] = '0';
            return results;
        // D10
        case 21: results = new char[3];
            results[0] = suits[c / 13];
            results[1] = '1';
            results[2] = '0';
            return results;
        // H10
        case 34: results = new char[3];
            results[0] = suits[c / 13];
            results[1] = '1';
            results[2] = '0';
            return results;
        // S10
        case 47: results = new char[3];
            results[0] = suits[c / 13];
            results[1] = '1';
            results[2] = '0';
            return results;
        // otherwise we only need 2
        // [2-9]&[J-A]
        default: results = new char[2];
            results[0] = suits[c / 13];
            // mod out the suits
            c %= 13;
            break;
    }
    // Revert the value
    switch(c % 14)
    {
        // Either revert the face cards
        case J: results[1] = 'J';
            break;
        case Q: results[1] = 'Q';
            break;
        case K: results[1] = 'K';
            break;
        case A: results[1] = 'A';
            break;
        // or revert everything else
        default: results[1] = values[c % 8];
            break;
    }
    return results;
}
// Check if a card is in the array
bool Array::inArray(int card)
{
    // nothing to search
    if(empty()) return false;
    // Binary search array
    // lower starts at 0
    // upper starts at _n
    // middle is _n / 2
    int l = 0, u = _n, m = u / 2;
    // while card not found and
    // lower less than upper
    while(GetItem(m) != card && l <= u)
    {
        // if array item is greater
        if(GetItem(m) > card)
            // reset upper to middle - 1
            u = m - 1;
        // otherwise item is less
        else
            // reset lower to middle + 1
            l = m + 1;
        // reset middle to (lower + upper) / 2
        m = (l + u) / 2;
    }
    // If card found, return true
    // otherwise return false
    return (l <= u) ? (true) : (false);
}
// Construct a dynamic array
// Default size is 20
Array::Array(int size)
{
    int i;
    // No values less than 1 allowed
    // If you give me that, you get
    // a max size array
    if(size <= 0) size = MAX;
    // Create a new int array
    _a = new int[size];
    // zero elements in a new array
    _n = 0;
    // Clear all the spots with zero
    for(i = 0; i < size; i++) _a[i] = 0;
}
// Copy constructor
Array::Array(const Array &m)
{
    // Create an array the size of m
    _a = new int[m._n];
    // copy size
    _n = m._n;
    // copy elements
    for(int i = 0; i <m._n; i++) _a[i] = m._a[i];
}
// Move constructor
Array::Array(Array &&m)
{
    // Move m to this array
    _a = m._a;
    // nullify m
    m._a = nullptr;
}
// Destructor
Array::~Array()
{
    // free array's memory
    delete[] _a;
}
// Copy assignment operate
Array &Array::operator=(Array &rhs)
{
    int i;
    // ignore self assignment
    if(&rhs == this) return *this;
    // If sizes difer
    if(rhs._n != _n)
    {
        // destroy this array
        delete[] _a;
        // create a new array with the size of rhs
        _a = new int[rhs._n];
        // update number of elements
        _n = rhs._n;
    }
    // copy elements overs
    for(i = 0; i < rhs._n; i++) _a[i] = rhs._a[i];
    return *this;
}
// Move assignment
Array &Array::operator =(Array &&rhs)
{
    // Ignore self assignment
    if(&rhs == this) return *this;
    // destroy this array
    delete[] _a;
    // Move rhs over
    _a = rhs._a;
    _n = rhs._n;
    // nullify rhs
    rhs._a = nullptr;
    return *this;
}
// Insert a card into the array in sorted order
void Array::PutItem(char *item)
{
    // change from char to int
    int card = convert(item);
    // Ignore duplicates
    if(inArray(card)) return;
    // if empty, push card
    if(empty())
    {
        _a[0] = card;
    } else {
        // find spot
        int i = 0;
        while(i < _n && _a[i] < card) ++i;
        
        // Array is full
        if(i >= MAX)
        {
            // Resize the array
            //Resize(i);
        } else if(i <= _n) {
            // make room
            ShiftF(i);
        }
        // put item
        _a[i] = card;
    }
    // increase number of elements
    ++_n;
}
// Remove a card from the array
void Array::DeleteItem(char* item)
{
    
    int i = 0, j = convert(item);
    // find spot
    while(i <= _n && GetItem(i) != j) ++i;
    // overwrite the spot with rest of array
    ShiftR(i);
    // decrease number of elements
    --_n;
}
// Display all cards in array
void Array::PrintAll()
{
    for (int i = 0; i < _n; ++i) {
        std::cout << revert(GetItem(i));
        if(i < _n - 1) std::cout << ", ";
    }
}
// Check if card is in list
void Array::Search(char* item)
{
    // convert to int, check if in array,
    // if in array, print "H4 YES"
    if(inArray(convert(item))) std::cout << item << " YES";
    // otherwise print "H4 NO"
    else std::cout << item << " NO";
}









