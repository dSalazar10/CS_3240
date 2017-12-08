//
//  Data.h
//  test
//
//  Created by DANIEL SALAZAR on 9/27/17.
//  Copyright © 2017 DANIEL SALAZAR. All rights reserved.
//
// This class is used to represent either an arbitrarily long
// number, or an array of characters to represnt an illegal number
// It has the capability of arithmetic, however the multiplication
// and division algorithms are poorly construction and basic.
// Essentially, they are both based on repeated addition or subtraction.
// Ideally you would use better algorithms, but speed isn't much of a
// concern here. It can print out the Data, compare two Data, and has
// some macros as well.

#include <iostream>
#include <string>
#include <stdexcept>

//  Shorten a for loop
//  i is the iterator name
//  a is the start condition
//  b is the end condition
//  progress is made by incrementation
#define foreach(i,a,b)  for(auto i = (a); i < (b); ++i)
// Default Data size is 11 (0-10)
#define DEFAULT         (int)4
// Sign Values
#define NEGATIVE        false
#define POSITIVE        true
// Macro Functions
#define is_negative(a)  ((a) - '-' == 0)
#define min(a,b)        (((a) < (b))?(a):(b))

#ifndef Data_h
#define Data_h

template<typename T>
class Data {
private:
    // Whole numbers _a >= 0
    // Array of elements of a template type
    // Intended for int. Extended to char.
    T *_a;
    // Length of whole
    int _n;
    // Sign
    bool _s;
    // Prints the array object
    friend std::ostream& operator<< (std::ostream& os, Data<T> &n)
    {
        // if the number's sign is negative
        // print a negative sign to show so
        try {
            if(n._s == NEGATIVE) os << "-";
        } catch (std::ifstream::failure e) {
            std::cerr << "Failed to print.\n";
        }
        // prints the whole part of the Data number
        try {
            foreach(i, 0, n._n) os << n[i];
        } catch (std::range_error r) {
            std::cerr << "Index out of range.\n";
        }
        return os;
    }
    // This needs to be changed along with the division algorithm
    // I created an exception to this library because of the need
    // for a fractional part in the average of column one. An Ideal
    // change would be to convert this whole library from a BigInt
    // to a BigDouble. I an any case, this function will print two
    // Data Numbers, the first representing a whole number, and the
    // second representing it fractional part.
    friend std::ostream& operator<< (std::ostream& os, Data<T> *n)
    {
        int i = n[1]._n - 1, j = i - 4;
        
        // Prints whole part followed by a '.'
        try {
            os << n[0] << ".";
            // Prints the fractional part
            for(; i > j; --i) os << ((i >= 0) ? (n[1]._a[i]) : (0));
        } catch (std::ifstream::failure e) {
            std::cerr << "Failed to print.\n";
        }
        return os;
    }
    // Observer
    int compare(Data<T> &rhs);
    // Mutator
    void changeSign(bool sign);
    // Mutator
    void normalize(std::string &s);
    // Observer
    std::string convert(Data<T> &rhs);
public:
    // Default Constructor
	Data<T>(void);
    // Constructor
    Data<T>(int num[], int len);
    // Copy Constructor
    Data<T>(std::string num);
    // Copy Constructor
    Data<T>(const char letters[], int len);
    // Copy constructor
    Data<T>(const Data<T> &n);
    // Move Constructor
    Data<T>(Data<T> &&n);
    // Destructor
    ~Data<T>(void);
    // Accessor
    T &operator [](int pos);
    // Observer
    int getSize(void) const;
    
    // Number only Functions
    // Accessor
    T &operator [](Data<T> pos);
    // Observer
    bool getSign(void) const;
    // Observer
    bool operator <(Data<T> &rhs);
    // Observer
    bool operator >(Data<T> &rhs) { return rhs < *this; }
    // Observer
    bool operator <=(Data<T> &rhs) { return !(*this > rhs); }
    // Observer
	bool operator >=(Data<T> &rhs) { return !(*this < rhs); }
    // Observer
    bool operator ==(Data<T> &rhs);
    // Observer
    bool operator <(int rhs);
    // Observer
    bool operator >(int rhs) { return rhs < *this; }
    // Observer
    bool operator <=(int rhs) { return !(*this > rhs); }
    // Observer
    bool operator >=(int rhs) { return !(*this < rhs); }
    // Observer
    Data<T> &operator +(Data<T> &rhs);
    // Observer
    Data<T> &operator -(Data<T> &rhs);
    // Observer
    Data<T> &operator *(Data<T> &rhs);
    // Observer
    Data<T> *operator /(Data<T> &rhs);
    // Mutator
    Data<T> &operator +=(Data<T> &rhs);
    // Mutator
    Data<T> &operator -=(Data<T> &rhs);
    // Mutator
    Data<T> &operator *=(Data<T> &rhs);
    // Mutator
    Data<T> &operator =(Data<T> &rhs);
    // Mutator
    Data<T> &operator =(Data<T> &&rhs);
    // Mutator
    Data<T> &operator ++(void);
    // Mutator
    Data<T> &operator --(void);
    
};
#endif /* Data_h */
// These are used mainly in comparisons
Data<int> zero("0");
Data<int> one("1");
Data<int> base("10");

// Observer
// input: an object to be compared
// process: compares lhs and rhs objects
// output: -1 if lhs < rh, 0 if equal, and 1 if greater
template<typename T>
int Data<T>::compare(Data<T> &rhs)
{
    // This is intended for use in the class
    // to compare two numbers, ignoring the sign
    int i = 0, j = 0, cmp = 0;
    
    // Compare sizes:
    // if lhs.size < rhs.size, return -1
    if (_n < rhs._n) return -1;
    // if lhs.size > rhs.size, return -1
    if (_n > rhs._n) return 1;
    // At this point, the sizes are equal
    while (i < _n && cmp == 0)
    {
        // if the lhs[i] > rhs[i], cmp = 1
        try {
            if(_a[i] > rhs._a[j]) cmp = 1;
            // if the lhs[i] < rhs[i], cmp = -1
            else if(_a[i] < rhs._a[j]) cmp = -1;
            // otherwise they are equal, cmp = 0
            else cmp = 0;
        } catch (std::range_error r) {
            std::cerr << "Index out of range.\n";
        }
        // move to next element for both lhs and rhs
        ++i;
        ++j;
    }
    return cmp;
}
// Mutator
// input: sign to change this object to
// process: changes private variable
// output: none
template<typename T>
void Data<T>::changeSign(bool sign)
{
    // Allows the programmer to modify the sign
    // this is intended to be used in the
    // addition and subtraction algorithms
    // where they refer to each other in the
    // case that the signs of the operands are
    // opposite
    _s = sign;
}
// Mutator
// input: a string representing a Data number's value
// process: removes the leading zeros
// output: none
template<typename T>
void Data<T>::normalize(std::string &s)
 {
     int i = 0;
     
     // If only 1 element, exit
     if(s.size() == 1) return;
     // Loop through looking for the first non-zero
     try {
         while(i < s.size() - 1 && s[i] == '0') ++i;
     } catch (std::range_error r) {
         std::cerr << "Index out of range.\n";
     }
     // Erase all of the elements that are 0s
     s = s.erase(0, min(i, s.size() - 1));
 }
// Observer
// input: a object that refers to the denominator
// process: converts a fraction into a decimal
// output: a string that represents the Data number's value
template<typename T>
std::string Data<T>::convert(Data<T> &rhs)
{
    std::string remainder = "";
    bool done = false;
    int maxDecimalPlaces = 0;
    unsigned long long int multiple;
    Data<T> d = *this;
    d = (d.compare(one) == 0) ? (base + d - one) : (base * d);
    
    // Loops through max 4 times
    while(!done && maxDecimalPlaces < 4)
    {
        // New starting value each iteration
        multiple = 0;
        // Repeatedly subtract the denominator from the remainder
        while(d >= rhs)
        {
            d -= rhs;
            // Keep track of how many times divisible
            ++multiple;
        }
        // Insert the value at the front of the string because
        // we need to be able to display the results in
        // reverse order
        remainder.insert(remainder.begin(), (char)(multiple + '0'));
        // if there is no remainder left, we are done
        if(!(d > zero)) done = true;
        else
        {
            // otherwise continue
            d = (d.compare(one) == 0) ? (base + d - one) : (base * d);
        }
        ++maxDecimalPlaces;
    }
    return remainder;
}
// Default size is an 4 digit number (9,999)
// Default Constructor
// input: none
// process: create an empty array of size 11
// output: N/A
template<typename T>
Data<T>::Data(void)
{
    // Assign a new array of default size to object
    try {
        _a = new T[DEFAULT];
    } catch (std::bad_alloc&) {
        std::cerr << "Unable to allocate memory.\n";
    }
    // Initialize the size of the object
    _n = DEFAULT;
    // Initialize sign to positive
    _s = POSITIVE;
    // Zero initialize the array
    try {
        foreach(i, 0, DEFAULT) _a[i] = 0;
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
}
// Constructor
// input: number from col0 or col1
// process: copy numbers from string to array
// output: N/A
template<typename T>
Data<T>::Data(int num[], int len)
{
    int start = 0;
    try {
        while(start < len - 1 && num[start] == 0) ++start;
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    len -= start;
    // Create a new Data, the size of num
    try {
        _a = new T[len];
    } catch (std::bad_alloc&) {
        std::cerr << "Unable to allocate memory.\n";
    }
    // Initialize the size of the object to
    // the length of the number
    _n = len;
    // Since this is not a number, not need for a neg sign
    _s = POSITIVE;
    // Copy the numbers over to the object array
    try {
        foreach(i, start, len) _a[i - start] = num[i];
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
}
// Constructor
// input: number from col0 or col1
// process: copy numbers from string to array
// output: N/A
template<typename T>
Data<T>::Data(std::string num)
{
    // length of number
    int length;
    // Test if number is negative or positive
    try {
        _s = (is_negative(num[0])) ? (NEGATIVE) : (POSITIVE);
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    // If it is negative, ignore the neg sign
    try {
        if(_s == NEGATIVE) num = num.substr(1, num.length());
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    // Set length for use in creating a new Data
    length = num.length();
    // Create a new Data, the size of num
    try {
        _a = new T[length];
    } catch (std::bad_alloc&) {
        std::cerr << "Unable to allocate memory.\n";
    }
    // Initialize the size of the object to
    // the length of the number
    _n = length;
    // Copy the numbers over to the object array
    try {
        foreach(i, 0, length) _a[i] = num[i] - '0';
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
}
// Constructor
// input: an array that represents an illegal number
// process: copy numbers from array to Data
// output: N/A
template<typename T>
Data<T>::Data(const char letters[], int len)
{
    // Create a new Data, the size of num
    try {
        _a = new T[len];
    } catch (std::bad_alloc&) {
        std::cerr << "Unable to allocate memory.\n";
    }
    // Initialize the size of the object to
    // the length of the number
    _n = len;
    // Since this is not a number, not need for a neg sign
    _s = POSITIVE;
    // Copy the numbers over to the object array
    try {
        foreach(i, 0, len) _a[i] = letters[i];
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
}
// Copy Constructor
// input: another number object
// process: copy numbers across objects
// output: N/A
template<typename T>
Data<T>::Data(const Data<T> &n)
{
    // Assign a new array with the size of
    //  the other object to this object
    try {
        _a = new T[n._n];
    } catch (std::bad_alloc&) {
        std::cerr << "Unable to allocate memory.\n";
    }
    // Initialize the size of this object to
    // the legnth of the other object
    _n = n._n;
    // copies pointer of sign from m to this object
    _s = n._s;
    // Deep copy the other array to this array
    try {
        foreach(i, 0, n._n) _a[i] = n._a[i];
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
}
// Move Constructor
// input: another number object
// process: move pointers from other object to this object
// output: N/A
template<typename T>
Data<T>::Data(Data<T> &&n)
{
    // Move array
    _a = n._a;
    // move length
    _n = n._n;
    // move sign
    _s = n._s;
    n._a = nullptr;
}
// Destructor
// input: none
// process: deallocate memory
// output: N/A
template<typename T>
Data<T>::~Data(void)
{
    delete[] _a;
}
// Accessor
// input: Requested position
// process: get value at position pos using [] indexing operator
// output: a reference to the requested position
template<typename T>
T &Data<T>::operator [](int pos)
{
    //
    // Todo: Assert position is between 0 and _n
    //
    if(pos >= _n) exit(-1);
    return _a[pos];
}
// Accessor
// input: Requested position
// process: get value at position pos using [] indexing operator
// output: a reference to the requested position
template<typename T>
T &Data<T>::operator [](Data<T> pos)
{
    //
    // Todo: Assert position is between 0 and _n
    //
    if(pos >= _n) exit(-1);
    T *temp = _a;
    unsigned long long int power = 1;
    for(auto i = pos._n - 1; i >= 0; --i)
    {
        try {
            temp += pos[i] * power;
        } catch (std::range_error r) {
            std::cerr << "Index out of range.\n";
        }
        power *= 10;
    }
    return *temp;
}
// Observer
// input: none
// process: get size of object's array
// output: size of object's array
template<typename T>
int Data<T>::getSize(void) const
{
    return _n;
}
// Observer
// input: none
// process: get sign of object's array
// output: sign of object's array
template<typename T>
bool Data<T>::getSign(void) const
{
    return _s;
}
// Observer
// input: reference to an object
// process: checks if this object is less than rhs object
// output: true if less than, otherwise false
template<typename T>
bool Data<T>::operator <(Data<T> &rhs)
{
    // Used to distinguish between equal and less than
    bool lt = false;
    try {
        // if this object has less digits it is less than
        if(_n < rhs._n || (_s == NEGATIVE && rhs._s == POSITIVE)) return true;
        // if this object has more digits it isn't less than
        else if(_n > rhs._n || (_s == POSITIVE && rhs._s == NEGATIVE)) return false;
        // At this point it lhs <= rhs
        else foreach(i, 0, _n) lt = (_a[i] >= rhs[i]) ? (false) : (true);
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    // if the whole array is equivalent return false, otherwise return true
    return lt;
}
// Observer
// input: reference to an object
// process: checks if this object is equal to rhs object
// output: true if equal, otherwise false
template<typename T>
bool Data<T>::operator ==(Data<T> &rhs)
{
    return (compare(rhs) == 0 && _s == rhs._s);
}
// Observer
// input: value
// process: checks if this object is less than value
// output: true if less than, otherwise false
template<typename T>
bool Data<T>::operator <(int rhs)
{
    // Used to distinguish between equal and less than
    // _n can't be longer than 2147483647
    if(_n > 9) return false;
    int lt = 0;
    try {
        foreach(i, 0, _n)
        {
            lt *= 10;
            lt += _a[i];
        }
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    return lt < rhs;
}
// Observer
// input: reference to an object
// process: sums two Datas
// output: reference to new Data containing results
template<typename T>
Data<T> &Data<T>::operator +(Data<T> &rhs)
{
    // A + (-B) == A - B
    // (-A) + B == B - A
    if((_s == POSITIVE && rhs._s == NEGATIVE) || (_s == NEGATIVE && rhs._s == POSITIVE))
    {
        // Prevent it from going beyond zero
        // Compare the two values, ignoring their sign
        int cmp = this->compare(rhs);
        // If A >= B
        if(cmp == 1 || cmp == 0)
        {
            // Create a temp B variable and
            // make it the same sign as A
            Data<T> newRhs = rhs;
            newRhs.changeSign(_s);
            // Perform normal subtraction
            return (*this - newRhs);
        }
        else
        {
            // A < B
            // Create a temp A variable and
            // make it the same sign as B
            Data<T> newRhs = *this;
            newRhs.changeSign(rhs._s);
            // Swap the order and perform
            // normal subtraction
            return (rhs - newRhs);
        }
    }
    else
    {
        // Strings are used as initializers for Data
        std::string s = "";
        // i = length of lhs - 1, j = length of rhs - 1
        // result holds the summation of two digits
        // carry holds the integer remainder of two additions
        // digit holds the resulting digit that is to be inserted into new Data
        // left holds lhs's digit
        // right holds the rhs's digit
        int i = _n - 1, j = rhs._n - 1, result = 0, carry = 0, digit = 0, left = 0, right = 0;
        // Loop while there are digits or a carry to add
        while (i >= 0 || j >= 0 || carry)
        {
            // left = lhs[i] or 0 if no more digits
            try {
                left = (i >= 0) ? (_a[i]) : (0);
            } catch (std::range_error r) {
                std::cerr << "Index out of range.\n";
            }
            // right = rhs[j] or 0 if no more digits
            try {
                right = (j >= 0) ? (rhs[j]) : (0);
            } catch (std::range_error r) {
                std::cerr << "Index out of range.\n";
            }
            // summation of digits and carry
            result = left + right + carry;
            // digit cannot be bigger than 9
            digit = result % 10;
            // get remainder
            carry = result / 10;
            // since we are working in reverse
            // digit has to gi in the front of the string
            s.insert(s.begin(), (char)(digit + '0'));
            // move left one place
            --i;
            --j;
        }
        // If there are any leading zeros, ignore them
        normalize(s);
        // if the result is negative, insert at front
        // this will initialize the new Data as a negative
        if(_s == NEGATIVE && rhs._s == NEGATIVE) s.insert(s.begin(), '-');
        // Create the new Data using the string
        Data<T> *sum = new Data<T>(s);
        // Return the results
        return *sum;
    }
}
// Observer
// input: reference to an object
// process: get the difference of two Datas
// output: reference to new Data containing results
template<typename T>
Data<T> &Data<T>::operator -(Data<T> &rhs)
{
    // A - (-B) == A + B
    // (-A) - B == B + A
    if((_s == POSITIVE && rhs._s == NEGATIVE) || (_s == NEGATIVE && rhs._s == POSITIVE))
    {
        // Create a temp B variable and
        // make it the same sign as A
        Data<T> newRhs = rhs;
        newRhs.changeSign(_s);
        // Perform normal addition
        return (*this + newRhs);
    }
    else
    {
        // If A < B, reorder so result isn't below zero
        if(this->compare(rhs) == -1) return (rhs - *this);
        std::string d = "";
        // i = length of lhs - 1, j = length of rhs - 1
        // result holds the summation of two digits
        // borrow holds the value removed from the next digit
        // left holds lhs's digit
        // right holds the rhs's digit
        int i = _n - 1, j = rhs._n - 1, result = 0, borrow = 0, left = 0, right = 0;
        while (i >= 0 || j >= 0 || borrow)
        {
             // left = lhs[i] or 0 if no more digits
            try {
                left = (i >= 0) ? (_a[i]) : (0);
            } catch (std::range_error r) {
                std::cerr << "Index out of range.\n";
            }
            // right = rhs[j] or 0 if no more digits
            try {
                right = (j >= 0) ? (rhs[j]) : (0);
            } catch (std::range_error r) {
                std::cerr << "Index out of range.\n";
            }
            // difference of digits and carry
            result = left - right - borrow;
            // results cannot be less than zero
            if(result < 0)
            {
                // It is less than zero, bring it back up
                result += 10;
                // Borrow from next digit
                borrow = 1;
            }
            else borrow = 0;
            // since we are working in reverse
            // digit has to gi in the front of the string
            d.insert(d.begin(), (char)(result + '0'));
            // move left one place
            --i;
            --j;
        }
        // If there are any leading zeros, ignore them
        normalize(d);
        // if the result is negative, insert at front
        // this will initialize the new Data as a negative
        if(_s == NEGATIVE && rhs._s == NEGATIVE) d.insert(d.begin(), '-');
        // if the result is negative, insert a '-' at front
        // this will initialize the new Data as a negative
        //if(neg) d.insert(d.begin(), '-');
        Data<T> *difference = new Data<T>(d);
        return *difference;
    }
}
// Observer
// input: reference to an object
// process: get the product of two Datas
// output: reference to new Data containing results
template<typename T>
Data<T> &Data<T>::operator *(Data<T> &rhs)
{ // https://en.wikipedia.org/wiki/Multiplication_algorithm
    
    // This is a bad version of multiplication
    // it performs a repeated addition
    // Should be improved.
    // Considering that performace was least
    // important, i did not implement the better
    // algorithms.
    Data<T> *product;
    // if 0 * M or N * 0, return zero
    if(*this == zero || rhs == zero)
    {
        try {
            product = new Data<T>("0");
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
    }
    // if 1 * M or N * 1, return 1
    else if(*this == one || rhs == one)
    {
        try {
            product = new Data<T>("1");
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
    }
    else
    {// Replace with a better algorithm
        
        // at this point, N * M
        try {
            product = new Data<T>("0");
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
        // This algorithm is based on counters
        Data<T> i("0");
        // Product starts at 0
        // repeatedly add N
        while(i < rhs)
        {
            *product += *this;
            ++i;
        }
    }
    return *product;
}
// Observer
// input: reference to an object
// process: get the quotient of two Datas
// output: reference to new Data containing results
//
// Todo: Better Algorithms
template<typename T>
Data<T> *Data<T>::operator /(Data<T> &rhs)
{ // https://en.wikipedia.org/wiki/Division_algorithm
    
    // This is a bad version of division
    // it performs a repeated subtraction
    // it also return both the quotient
    // and the remainder. Should be improved.
    // Considering that performace was least
    // important, i did not implement the better
    // algorithms.
    //
    // Todo: Assert division by zero
    //
    if(rhs == zero) exit(-1);
    // Holds quotient and remainder
    Data<T> *quotient;
    try {
        quotient = new Data<T>[2];
    } catch (std::bad_alloc&) {
        std::cerr << "Unable to allocate memory.\n";
    }
    // quotient
    Data<T> *q;
    // remainder
    Data<T> *r;
    // if 0 / N, return 0
    if(*this == zero)
    {
        try {
            q = new Data<T>("0");
            r  = new Data<T>("0");
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
        quotient[0] = *q;
        quotient[1] = *r;
    }
    // if N / 1, return N
    else if(rhs == one)
    {
        try {
            q = new Data<T>(_a, _n);
            r  = new Data<T>("0");
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
        quotient[0] = *q;
        quotient[1] = *r;
    }
    // if N / N, return 1
    else if (*this == rhs)
    {
        try {
            q = new Data<T>("1");
            r  = new Data<T>("0");
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
        quotient[0] = *q;
        quotient[1] = *r;
    }
    else
    {// Replace with a better algorithm
        
        // at this point, N / D
        // This algorithm is based on counters
        try {
            q = new Data<T>("0");
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
        // remainder starts at N
        Data<T> rem(_a, _n);
        // repeatedly subtract D
        // until remainder is >= D
        while(rem >= rhs)
        {
            rem -= rhs;
            ++(*q);
        }
        // If a remainder exists, convert from a fraction to decimal
        // otherwise, remainder is zero
        try {
            r = new Data<T>((rem > zero) ? (rem.convert(rhs)) : ("0"));
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
        // Set the array based tuple
        quotient[0] = *q;
        quotient[1] = *r;
    }
    return quotient;
}
// Mutator
// input: reference to an object
// process: Takes the sum of lhs and rhs and stores into lhs
// output: reference to this object
template<typename T>
Data<T> &Data<T>::operator +=(Data<T> &rhs)
{
    *this = *this + rhs;
    return *this;
}
// Mutator
// input: reference to an object
// process: Takes the sum of lhs and rhs and stores into lhs
// output: reference to this object
template<typename T>
Data<T> &Data<T>::operator -=(Data<T> &rhs)
{
    *this = *this - rhs;
    return *this;
}
// Mutator
// input: reference to an object
// process: Takes the product of lhs and rhs and stores into lhs
// output: reference to this object
template<typename T>
Data<T> &Data<T>::operator *=(Data<T> &rhs)
{
    *this = *this * rhs;
    return *this;
}
// Mutator
// input: reference to an object
// process: deep copy rhs to this object
// output: reference to this object
template<typename T>
Data<T> &Data<T>::operator =(Data<T> &rhs)
{
    // Test for self assignment
    if(&rhs == this) return *this;
    // If the two sizes are not the same
    // start over with a new array, the size of rhs
    if(rhs._n != _n)
    {
        // delete this object's array
        delete[] _a;
        // assign new array, the size of rhs to this object
        try {
            _a = new T[rhs._n];
        } catch (std::bad_alloc&) {
            std::cerr << "Unable to allocate memory.\n";
        }
        
        // update this object's size
        _n = rhs._n;
        // update this object's sign
        _n = rhs._n;
    }
    // Deep copy all elements of  rhs into this object
    try {
        foreach(i, 0, rhs._n) _a[i] = rhs._a[i];
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
    return *this;
}

// Mutator
// input: reference to an object
// process: move pointers of rhs to this object
// output: reference to this object
template<typename T>
Data<T> &Data<T>::operator =(Data<T> &&rhs)
{
    // Test for self assignment
    if(&rhs == this) return *this;
    // delete this object's array
    delete[] _a;
    // move pointer of rhs array to this objects array
    _a = rhs._a;
    // move pointer of rhs size to this objects size
    _n = rhs._n;
    // move pointer of rhs length to this objects length
    _s = rhs._s;
    rhs._a = nullptr;
    return *this;
}
// Mutator
// input: none
// process: increment this object
// output: reference to this object
template<typename T>
Data<T> &Data<T>::operator ++()
{
    Data<T> o("1");
    *this += o;
    return *this;
}
// Mutator
// input: none
// process: decrement this object
// output: reference to this object
template<typename T>
Data<T> &Data<T>::operator --()
{
    Data<T> o("1");
    *this -= o;
    return *this;
}









