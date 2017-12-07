// Sorted Linked List
// Book code is broken...
// They clearly tried to use unsorted list in their sorted list implementation
// WTF?! ...and my professor expects me to memorize this hot garbage...
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

using namespace std;

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


struct NodeType;

class SortedType
{
public:
    SortedType();     // Class constructor
    ~SortedType();    // Class destructor
    
    bool IsFull() const;
    int  GetLength() const;
    void MakeEmpty();
    ItemType GetItem(ItemType& item, bool& found);
    void PutItem(ItemType item);
    void DeleteItem(ItemType item);
    void ResetList();
    ItemType GetNextItem();
    
private:
    NodeType* listData;
    int length;
    NodeType* currentPos;
};

struct NodeType
{
    ItemType info;
    NodeType* next;
};

SortedType::SortedType()  // Class constructor
{
    length = 0;
    listData = NULL;
}

bool SortedType::IsFull() const
{
    NodeType* location;
    try
    {
        location = new NodeType;
        delete location;
        return false;
    }
    catch(std::bad_alloc exception)
    {
        return true;
    }
}

int SortedType::GetLength() const
{
    return length;
}

void SortedType::MakeEmpty()
{
    NodeType* tempPtr;
    
    while (listData != NULL)
    {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    length = 0;
}

ItemType SortedType::GetItem(ItemType& item, bool& found)
{
    bool moreToSearch;
    NodeType* location;
    
    location = listData;
    found = false;
    moreToSearch = (location != NULL);
    
    while (moreToSearch && !found)
    {
        switch(item.ComparedTo(location->info))
        {
            case GREATER: location = location->next;
                moreToSearch = (location != NULL);
                break;
            case EQUAL:   found = true;
                item = location->info;
                break;
            case LESS:    moreToSearch = false;
                break;
        }
    }
    return item;
}

void SortedType::PutItem(ItemType item)
{
    NodeType* newNode;      // pointer to node being inserted
    NodeType* predLoc;      // trailing pointer
    NodeType* location;     // traveling pointer
    bool moreToSearch;
    
    location = listData;
    predLoc = NULL;
    moreToSearch = (location != NULL);
    
    // Find insertion point.
    while (moreToSearch)
    {
        switch(item.ComparedTo(location->info))
        {
            case GREATER: predLoc = location;
                location = location->next;
                moreToSearch = (location != NULL);
                break;
            case LESS:    moreToSearch = false;
                break;
        }
        
    }
    
    // Prepare node for insertion
    newNode = new NodeType;
    newNode->info = item;
    // Insert node into list.
    if (predLoc == NULL)         // Insert as first
    {
        newNode->next = listData;
        listData = newNode;
    }
    else
    {
        newNode->next = location;
        predLoc->next = newNode;
    }
    length++;
}
void SortedType::DeleteItem(ItemType item)
{
    NodeType* location = listData;
    NodeType* tempLocation;
    
    // Locate node to be deleted.
    if (item.ComparedTo(listData->info) == EQUAL)
    {
        tempLocation = location;
        listData = listData->next;    // Delete first node.
    }
    else
    {
        while (item.ComparedTo((location->next)->info) != EQUAL)
            location = location->next;
        
        // Delete node at location->next
        tempLocation = location->next;
        location->next = (location->next)->next;
    }
    delete tempLocation;
    length--;
}

void SortedType::ResetList()
{
    currentPos = NULL;
}

ItemType SortedType::GetNextItem()
{
    ItemType item;
    if (currentPos == NULL)
        currentPos = listData;
    item = currentPos->info;
    currentPos = currentPos->next;
    return item;
    
}

SortedType::~SortedType()
{
    NodeType* tempPtr;
    
    while (listData != NULL)
    {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
}

void PrintList(ofstream& outFile, UnsortedType list);

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
    cin  >> outputLabel;
    outFile << outputLabel << endl;
    
    inFile >> command;
    
    numCommands = 0;
    while (command != "Quit")
    {
        if (command == "InsertItem")
        {
            inFile >> number;
            item.Initialize(number);
            list.InsertItem(item);
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
            outFile << "Length is " << list.GetLength() << endl;
        else if (command == "IsFull")
            if (list.IsFull())
                outFile << "List is full." << endl;
            else outFile << "List is not full."  << endl;
            else if (command == "MakeEmpty")
                list.MakeEmpty();
            else if (command == "PrintList")
                PrintList(outFile, list);
            else cout << "Command not recognized." << endl;
        numCommands++;
        cout <<  " Command number " << numCommands << " completed."
        << endl;
        inFile >> command;   cout << command;
    };
    
    cout << "Testing completed."  << endl;
    inFile.close();
    outFile.close();
    return 0;
}


void PrintList(ofstream& dataFile, UnsortedType list)
// Pre:  list has been initialized.
//       dataFile is open for writing.
// Post: Each component in list has been written to dataFile.
//       dataFile is still open.
{
    int length;
    ItemType item;
    
    list.ResetList();
    length = list.LengthIs();
    for (int counter = 1; counter <= length; counter++)
    {
        ItemType item;
        item = list.GetNextItem();
        item.Print(dataFile);
    }
    dataFile << endl;
}
