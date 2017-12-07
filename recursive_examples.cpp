// Random recursive functions

#include <fstream>
#include <iostream>
enum RelationType  {LESS, GREATER, EQUAL};

class ItemType
{
public:
    ItemType() { value = 0; }
    RelationType ComparedTo(ItemType otherItem) const
    {
        if (value < otherItem.value)
            return LESS;
        else if (value > otherItem.value)
            return GREATER;
        else return EQUAL;
    }
    void Print(std::ostream& out) const { out << value; }
    void Initialize(int number) { value = number; }
private:
    int value;
};

template<class ItemType>
bool BinarySearch (ItemType info[], ItemType item,
                   int fromLocation, int toLocation)
{
    if (fromLocation > toLocation) // Base case 1
        return false;
    else
    {
        int midPoint;
        midPoint = (fromLocation + toLocation) / 2;
        if (item < info[midPoint])
            return BinarySearch(info, item, fromLocation, midPoint-1);
        else if (item == info[midPoint])
            return true;
        else
            return BinarySearch(info, item, midPoint + 1, toLocation);
    }
}

template<class ItemType>
struct NodeType{
    ItemType info;
    NodeType *next;
};
template<class ItemType>
void Delete(NodeType<ItemType>*& listPtr, ItemType item)
{
    if (item == listPtr->info)
    {
        NodeType<ItemType>* tempPtr = listPtr;
        listPtr = listPtr->next;
        delete tempPtr;
    }
    else
        Delete(listPtr->next, item);
}

int Factorial(int number)
{
    if (number == 0) // line 1
        return 1;    // line 2
    else
        return number * Factorial(number-1); // line 3
}

template<class ItemType>
void Insert(NodeType<ItemType>*& listPtr, ItemType item)
{
    if (listPtr == NULL || item < listPtr->info)
    {
        // Save current pointer.
        NodeType<ItemType>* tempPtr = listPtr;
        // Get a new node.
        listPtr = new NodeType<ItemType>;
        listPtr->info = item;
        listPtr->next = tempPtr;
    }
    else Insert(listPtr->next, item);
}


template <class ItemType>
void RevPrint(NodeType<ItemType>* listPtr)
{
    if (listPtr != NULL)
    {
        RevPrint(listPtr->next);
        std::cout << listPtr->info << std::endl;
    }
}
bool ValueInList(ListType list, int value, int startIndex) {
    if (list.info[startIndex] == value)
        return true; // Base case 1
    else if (startIndex == list.length-1)
        return false; // Base case 2
    else
        return ValueInList(list, value, startIndex+1);
}
