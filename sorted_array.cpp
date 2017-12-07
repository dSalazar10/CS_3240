// Sorted Array

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

using namespace std;

#ifndef SORTED
#define SORTED

const int MAX_ITEMS = 5;
enum RelationType  {LESS, GREATER, EQUAL};

class ItemType
{
public:
    ItemType(){ value = 0; }
    RelationType ComparedTo(ItemType) const;
    void Print(std::ostream& out) const{ out << value; }
    void Initialize(int number){ value = number; }
private:
    int value;
};

RelationType ItemType::ComparedTo(ItemType otherItem) const
{
    if (value < otherItem.value)
        return LESS;
    else if (value > otherItem.value)
        return GREATER;
    else return EQUAL;
}


class SortedType
{
public:
    SortedType();
    
    void MakeEmtpy();
    // Function: Returns list to the empty state
    // Post:  List is empty.
    
    bool IsFull() const;
    // Function:  Determines whether list is full.
    // Pre:  List has been initialized.
    // Post: Function value = (list is full)
    
    int GetLength() const;
    // Function: Determines the number of elements in list.
    // Pre:  List has been initialized.
    // Post: Function value = number of elements in list
    
    ItemType GetItem(ItemType item, bool& found);
    // Function: Retrieves list element whose key matches item's key (if
    //           present).
    // Pre:  List has been initialized.
    //       Key member of item is initialized.
    // Post: If there is an element someItem whose key matches
    //       item's key, then found = true and item is returned;
    //       someItem; otherwise found = false and item is returned.
    //       List is unchanged.
    
    void PutItem(ItemType item);
    // Function: Adds item to list.
    // Pre:  List has been initialized.
    //       List is not full.
    //       item is not in list.
    //       List is sorted.
    // Post: item is in list.
    //       List is sorted
    
    void DeleteItem(ItemType item);
    // Function: Deletes the element whose key matches item's key.
    // Pre:  List has been initialized.
    //       Key member of item is initialized.
    //       One and only one element in list has a key matching item's key.
    // Post: No element in list has a key matching item's key.
    //       List is sorted.
    
    void ResetList();
    // Function: Initializes current position for an iteration through the list.
    // Pre:  List has been initialized.
    // Post: Current position is prior to list.
    
    ItemType GetNextItem();
    // Function: Gets the next element in list.
    // Pre:  List has been initialized and has not been changed since last call.
    //       Current position is defined.
    //       Element at current position is not last in list.
    //
    // Post: Current position is updated to next position.
    //       Returns a copy of element at current position.
    
    void MakeEmpty();
    // Function: Make the list empty
    // Pre:  List has been initialized.
    // Post: The list is empty
    
private:
    int length;
    ItemType info[MAX_ITEMS];
    int currentPos;
};
#endif

SortedType::SortedType()
{
    length = 0;
}

void SortedType::MakeEmpty()
{
    length = 0;
}


bool SortedType::IsFull() const
{
    return (length == MAX_ITEMS);
}

int SortedType::GetLength() const
{
    return length;
}

ItemType SortedType::GetItem(ItemType item, bool& found)
{
    int midPoint;
    int first = 0;
    int last = length - 1;
    
    bool moreToSearch = first <= last;
    found = false;
    while (moreToSearch && !found)
    {
        midPoint = ( first + last) / 2;
        switch (item.ComparedTo(info[midPoint]))
        {
            case LESS    : last = midPoint - 1;
                moreToSearch = first <= last;
                break;
            case GREATER : first = midPoint + 1;
                moreToSearch = first <= last;
                break;
            case EQUAL   : found = true;
                item = info[midPoint];
                break;
        }
    }
    return item;
}

void SortedType::DeleteItem(ItemType item)
{
    int location = 0;
    
    while (item.ComparedTo(info[location]) != EQUAL)
        location++;
    for (int index = location + 1; index < length; index++)
        info[index - 1] = info[index];
    length--;
}

void SortedType::PutItem(ItemType item)
{
    bool moreToSearch;
    int location = 0;
    
    moreToSearch = (location < length);
    while (moreToSearch)
    {
        switch (item.ComparedTo(info[location]))
        {
            case LESS    : moreToSearch = false;
                break;
            case GREATER : location++;
                moreToSearch = (location < length);
                break;
        }
    }
    for (int index = length; index > location; index--)
        info[index] = info[index - 1];
    info[location] = item;
    length++;
}

void SortedType::ResetList()
// Post: currentPos has been initialized.
{
    currentPos = -1;
}

ItemType SortedType::GetNextItem()
// Post: item is current item.
//       Current position has been updated.
{
    currentPos++;
    return info[currentPos];
}


void PrintList(ofstream& outFile, SortedType list);

int main()
{
    
    ifstream inFile;       // file containing operations
    ofstream outFile;      // file containing output
    string inFileName;     // input file external name
    string outFileName;    // output file external name
    string outputLabel;
    string command;        // operation to be executed
    
    int number;
    ItemType item;
    SortedType list;
    bool found;
    int numCommands;
    
    
    // Prompt for file names, read file names, and prepare files
    cout << "Enter name of input command file; press return." << endl;
    cin  >> inFileName;
    inFile.open(inFileName.c_str());
    
    cout << "Enter name of output file; press return." << endl;
    cin  >> outFileName;
    outFile.open(outFileName.c_str());
    
    cout << "Enter name of test run; press return." << endl;
    cin  >> outputLabel;
    outFile << outputLabel << endl;
    
    inFile >> command;
    
    numCommands = 0;
    while (command != "Quit")
    {
        outFile << command;
        if (command == "PutItem")
        {
            inFile >> number;
            item.Initialize(number);
            list.PutItem(item);
            item.Print(outFile);
            outFile << " is inserted" << endl;
        }
        else if (command == "DeleteItem")
        {
            inFile >> number;
            item.Initialize(number);
            list.DeleteItem(item);
            item.Print(outFile);
            outFile << " is deleted" << endl;
        }
        else if (command == "GetItem")
        {
            inFile >> number;
            item.Initialize(number);
            list.GetItem(item, found);
            if (found)
                outFile << number << " found in list." << endl;
            else outFile << number  << " not in list."  << endl;
        }
        else if (command == "GetLength")
            outFile << " Length is " << list.GetLength() << endl;
        else if (command == "IsFull")
            if (list.IsFull())
                outFile << "List is full." << endl;
            else outFile << "List is not full."  << endl;
            else if (command == "MakeEmpty")
                list.MakeEmpty();
            else if (command == "PrintList")
                PrintList(outFile, list);
            else cout << " Command not recognized." << endl;
        numCommands++;
        cout <<  " Command number " << numCommands << " completed."
        << endl;
        inFile >> command;
    };
    
    cout << "Quit"  << endl << "Testing completed."  << endl;
    inFile.close();
    outFile.close();
    return 0;
}


void PrintList(ofstream& dataFile, SortedType list)
// Pre:  list has been initialized.
//       dataFile is open for writing.
// Post: Each component in list has been written to dataFile.
//       dataFile is still open.
{
    int length;
    ItemType item;
    
    list.ResetList();
    length = list.GetLength();
    for (int counter = 1; counter <= length; counter++)
    {
        ItemType item;
        item = list.GetNextItem();
        item.Print(dataFile);
    }
    dataFile << endl;
}

/* Data in:
 GetLength
 PutItem 5
 PutItem 7
 PutItem 6
 PutItem 9
 PrintList
 PutItem 1
 PrintList
 GetItem 4
 GetItem 5
 GetItem 9
 GetItem 10
 IsFull
 DeleteItem 5
 IsFull
 DeleteItem 1
 DeleteItem 6
 DeleteItem 9
 PrintList
 MakeEmpty
 PrintList
 Error
 Quit */

/* Data out:
 first.txt
 GetLength Length is 0
 PutItem5 is inserted
 PutItem7 is inserted
 PutItem6 is inserted
 PutItem9 is inserted
 PrintList5679
 PutItem1 is inserted
 PrintList15679
 GetItem4 not in list.
 GetItem5 found in list.
 GetItem9 found in list.
 GetItem10 not in list.
 IsFullList is full.
 DeleteItem5 is deleted
 IsFullList is not full.
 DeleteItem1 is deleted
 DeleteItem6 is deleted
 DeleteItem9 is deleted
 PrintList7
 MakeEmptyPrintList
 Error */
