// Unsorted Array

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

const int MAX_ITEMS = 5;
enum RelationType  {LESS, GREATER, EQUAL};

using namespace std;


class ItemType
{
public:
    ItemType(){ value = 0; }
    RelationType ComparedTo(ItemType) const;
    void Print(std::ostream& out) const { out << value; }
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


class UnsortedType
{
public:
    UnsortedType();
    // Constructor
    
    void MakeEmpty();
    // Function: Returns the list to the empty state.
    // Post:  List is empty.
    
    bool IsFull() const;
    // Function:  Determines whether list is full.
    // Pre:  List has been initialized.
    // Post: Function value = (list is full)
    
    int GetLength() const;
    // Function: Determines the number of elements in list.
    // Pre:  List has been initialized.
    // Post: Function value = number of elements in list
    
    ItemType GetItem(ItemType, bool&);
    // Function: Retrieves list element whose key matches item's key (if
    //           present).
    // Pre:  List has been initialized.
    //       Key member of item is initialized.
    // Post: If there is an element someItem whose key matches
    //       item's key, then found = true and someItem is returned.
    //      otherwise found = false and item is returned.
    //       List is unchanged.
    
    void PutItem(ItemType item);
    // Function: Adds item to list.
    // Pre:  List has been initialized.
    //       List is not full.
    //       item is not in list.
    // Post: item is in list.
    
    void DeleteItem(ItemType item);
    // Function: Deletes the element whose key matches item's key.
    // Pre:  List has been initialized.
    //       Key member of item is initialized.
    //       One and only one element in list has a key matching item's key.
    // Post: No element in list has a key matching item's key.
    
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
    //       item is a copy of element at current position.
    
private:
    int length;
    ItemType info[MAX_ITEMS];
    int currentPos;
};

UnsortedType::UnsortedType()
{
    length = 0;
}
bool UnsortedType::IsFull() const
{
    return (length == MAX_ITEMS);
}
int UnsortedType::GetLength() const
{
    return length;
}

ItemType UnsortedType::GetItem(ItemType item, bool& found)
// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the
//       list and a copy of that element has been returned;
//       otherwise, item is returned.
{
    bool moreToSearch;
    int location = 0;
    found = false;
    
    moreToSearch = (location < length);
    
    while (moreToSearch && !found)
    {
        switch (item.ComparedTo(info[location]))
        {
            case LESS    :
            case GREATER : location++;
                moreToSearch = (location < length);
                break;
            case EQUAL   : found = true;
                item = info[location];
                break;
        }
    }
    return item;
}
void UnsortedType::MakeEmpty()
// Post: list is empty.
{
    length = 0;
}
void UnsortedType::PutItem(ItemType item)
// Post: item is in the list.
{
    info[length] = item;
    length++;
}
void UnsortedType::DeleteItem(ItemType item)
// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
{
    int location = 0;
    
    while (item.ComparedTo(info[location]) != EQUAL)
        location++;
    
    info[location] = info[length - 1];
    length--;
}
void UnsortedType::ResetList()
// Post: currentPos has been initialized.
{
    currentPos = -1;
}

ItemType UnsortedType::GetNextItem()
// Pre:  ResetList was called to initialized iteration.
//       No transformer has been executed since last call.
//       currentPos is defined.
// Post: item is current item.
//       Current position has been updated.
{
    currentPos++;
    return info[currentPos];
}

void PrintList(ofstream& outFile, UnsortedType& list);

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
    UnsortedType list;
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
    cin >> outputLabel;
    
    outFile << outputLabel << endl;
    if(!inFile)
    {
        cout << "File not found." << endl;
        exit(2);
    }
    
    inFile >> command;
    
    numCommands = 0;
    while (command != "Quit")
    {
        cout << command;
        if (command == "PutItem")
        {
            inFile >> number;
            item.Initialize(number);
            list.PutItem(item);
            item.Print(outFile);
            outFile << " is in list." << endl;
        }
        else if (command == "DeleteItem")
        {
            inFile >> number;
            item.Initialize(number);
            list.DeleteItem(item);
            item.Print(outFile);
            outFile << " is deleted." << endl;
        }
        else if (command == "GetItem")
        {
            inFile >> number;
            item.Initialize(number);
            item = list.GetItem(item, found);
            if (found)
                outFile << number << " found in list." << endl;
            else outFile << number  << " not in list."  << endl;
        }
        else if (command == "GetLength")
            outFile << "Length is " << list.GetLength() << endl;
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
    
    cout << "Quit" << endl << "Testing completed."  << endl;
    inFile.close();
    outFile.close();
    return 0;
};


void PrintList(ofstream& dataFile, UnsortedType& list)
// Pre:  list has been initialized.
//       dataFile is open for writing.
// Post: Each component in list has been written to dataFile.
//       dataFile is still open.
{
    int length;
    ItemType item;
    dataFile << "PrintList" << endl;
    list.ResetList();
    length = list.GetLength();
    if (length == 0)
        dataFile << "List is empty.";
    else
        for (int counter = 1; counter <= length; counter++)
        {
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
 Length is 0
 5 is in list.
 7 is in list.
 6 is in list.
 9 is in list.
 PrintList
 5769
 1 is in list.
 PrintList
 57691
 4 not in list.
 5 found in list.
 9 found in list.
 10 not in list.
 List is full.
 5 is deleted.
 List is not full.
 1 is deleted.
 6 is deleted.
 9 is deleted.
 PrintList
 7
 PrintList
 List is empty. */

