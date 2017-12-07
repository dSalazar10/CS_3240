// Priority Queue
#include <iostream>
#include <fstream>
typedef int ItemType;
using namespace std;
class FullPQ{};
class EmptyPQ{};

template <class ItemType>
void swap(ItemType& one, ItemType& two);

template<class ItemType>
// Assumes ItemType is either a built-in simple type or a class
// with overloaded relational operators.
struct HeapType
{
    void ReheapDown(int root, int bottom);
    void ReheapUp(int root, int bottom);
    ItemType* elements;   // Array to be allocated dynamically
    int numElements;
};

template <class ItemType>
void Swap(ItemType& one, ItemType& two)
{
    ItemType temp;
    temp = one;
    one = two;
    two = temp;
}
template<class ItemType>
void HeapType<ItemType>::ReheapUp(int root, int bottom)
// Post: Heap property is restored.
{
    int parent;
    
    if (bottom > root)
    {
        parent = (bottom-1) / 2;
        if (elements[parent] < elements[bottom])
        {
            Swap(elements[parent], elements[bottom]);
            ReheapUp(root, parent);
        }
    }
}
template<class ItemType>
void HeapType<ItemType>::ReheapDown(int root, int bottom)
// Post: Heap property is restored.
{
    int maxChild;
    int rightChild;
    int leftChild;
    
    leftChild = root*2+1;
    rightChild = root*2+2;
    if (leftChild <= bottom)
    {
        if (leftChild == bottom)
            maxChild = leftChild;
        else
        {
            if (elements[leftChild] <= elements[rightChild])
                maxChild = rightChild;
            else
                maxChild = leftChild;
        }
        if (elements[root] < elements[maxChild])
        {
            Swap(elements[root], elements[maxChild]);
            ReheapDown(maxChild, bottom);
        }
    }
}


template<class ItemType>
class PQType
{
public:
    PQType(int);          // parameterized class constructor
    ~PQType();            // class destructor
    
    void MakeEmpty();
    // Function: Initializes the queue to an empty state.
    // Post: Queue is empty.
    
    bool IsEmpty() const;
    // Function: Determines whether the queue is empty.
    // Post: Function value = (queue is empty)
    
    bool IsFull() const;
    // Function: Determines whether the queue is full.
    // Post: Function value = (queue is full)
    
    void Enqueue(ItemType newItem);
    // Function: Adds newItem to the rear of the queue.
    // Post: if (the priority queue is full) exception FullPQ is thrown;
    //       else newItem is in the queue.
    
    void Dequeue(ItemType& item);
    // Function: Removes element with highest priority from the queue
    // and returns it in item.
    // Post: If (the priority queue is empty) exception EmptyPQ is thrown;
    //       else highest priority element has been removed from queue.
    //       item is a copy of removed element.
private:
    int length;
    HeapType<ItemType> items;
    int maxItems;
};

template<class ItemType>
PQType<ItemType>::PQType(int max)
{
    maxItems = max;
    items.elements = new ItemType[max];
    length = 0;
}

template<class ItemType>
void PQType<ItemType>::MakeEmpty()
{
    length = 0;
}

template<class ItemType>
PQType<ItemType>::~PQType()
{
    delete [] items.elements;
}
template<class ItemType>
void PQType<ItemType>::Dequeue(ItemType& item)
// Post: element with highest priority has been removed
//       from the queue; a copy is returned in item.
{
    if (length == 0)
        throw EmptyPQ();
    else
    {
        item = items.elements[0];
        items.elements[0] = items.elements[length-1];
        length--;
        items.ReheapDown(0, length-1);
    }
}

template<class ItemType>
void PQType<ItemType>::Enqueue(ItemType newItem)
// Post: newItem is in the queue.
{
    if (length == maxItems)
        throw FullPQ();
    else
    {
        length++;
        items.elements[length-1] = newItem;
        items.ReheapUp(0, length-1);
    }
}
template<class ItemType>
bool PQType<ItemType>::IsFull() const
// Post: Returns true if the queue is full; false, otherwise.
{
    return length == maxItems;
}

template<class ItemType>
bool PQType<ItemType>::IsEmpty() const
// Post: Returns true if the queue is empty; false, otherwise.
{
    return length == 0;
}

int main()
{
    
    ifstream inFile;       // file containing operations
    ofstream outFile;      // file containing output
    string inFileName;     // input file external name
    string outFileName;    // output file external name
    string outputLabel;
    string command;        // operation to be executed
    
    ItemType item;
    PQType<int> queue(5);
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
        try
        {
            if (command == "Enqueue")
            {
                inFile >> item;
                queue.Enqueue(item);
                outFile << item << " is enqueued." << endl;
            }
            else if (command == "Dequeue")
            {
                queue.Dequeue(item);
                outFile<< item  << " is dequeued. " << endl;
            }
            else if (command == "IsEmpty")
                if (queue.IsEmpty())
                    outFile << "Queue is empty." << endl;
                else
                    outFile << "Queue is not empty." << endl;
            
                else if (command == "IsFull")
                    if (queue.IsFull())
                        outFile << "Queue is full." << endl;
                    else outFile << "Queue is not full."  << endl;
                    else if (command == "MakeEmpty")
                        queue.MakeEmpty();
        }
        catch (FullPQ)
        {
            outFile << "FullQueue exception thrown." << endl;
        }
        
        catch (EmptyPQ)
        {
            outFile << "EmtpyQueue exception thrown." << endl;
        }
        numCommands++;
        cout <<  " Command number " << numCommands << " completed."
        << endl;
        inFile >> command;
        
    };
    
    cout << "Testing completed."  << endl;
    inFile.close();
    outFile.close();
    return 0;
}
