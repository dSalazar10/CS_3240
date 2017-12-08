//Name: Daniel Salazar
//Email: dsalazar10@csueastbay.edu
//
// This is a BigInt Implementation using a
// Linked List as its container. There are
// some added features in this class, so it
// isn't a pure Linked List class. This is
// intended to be initialized using a string
// and the values of each node are to be an
// integer value.

#include "Node.h"
#include <cassert>  // assert
#include <string>   // string

#ifndef LinkedList_h
#define LinkedList_h

template<typename T>
class LinkedList
{
    // So I don't have to type out all the <T>.
    typedef Node<T> Node;
    
private:
    // List Variables
    Node* head;
    Node* tail;
    unsigned long long int _size;
    
    // Memory Management
    // Keeps all the unused Nodes on a stack
    // for reuse later
    static Node* free;
    // Keep track of how many lists exist.
    // Used to determine when to destroy the
    // free stack
    static int numLists;
    // Gets a node form the free stack or
    // creates a new node if memory is available
    Node* GetNode(void);
    // Puts a node on the free stack
    void FreeNode(Node* p);
    // Check if there is available memory
    bool IsFull() const;
    // Outputs BigInt
    friend std::ostream& operator<<(std::ostream& os, LinkedList<T> &aList)
    {
        if(aList.begin() == nullptr) return os;
        for(Node* p = aList.begin(); p != nullptr; p = p->GetNext())
            std::cout << p->GetNode();
        return os;
    }
public:
    // Default constructor
    LinkedList();
    // Copy constructor
    LinkedList (LinkedList<T>& aList);
    // Move constructor
    LinkedList (LinkedList<T>&& aList) noexcept;
    // Destructor
    ~LinkedList() noexcept;
    // Copy assignment
    LinkedList& operator=(LinkedList<T>& aList);
    // Move Assignment
    LinkedList& operator=(LinkedList<T>&& aList) noexcept;
    // User input constructor
    LinkedList(std::string num);
    // User input assignment
    LinkedList &operator=(std::string rhs);
    // Returns _size
    unsigned long long int size(void) { return _size; }
    // Check if list is empty
    bool empty(void) { return head == nullptr; }
    // Get first element's item
    T &Front() { return head->GetNode(); }
    // Get last element's item
    T &Back()  { return tail->GetNode(); }
    // Empties the list of all nodes
    void Clear();
    // Get a pointer to the first node
    Node* begin() { return head; }
    // Get a pointer to the last node
    Node* end() { return tail; }
    // Comparators
    int cmp(LinkedList<T> &aList);
    bool operator==(LinkedList<T>& rhs){ return cmp(rhs) == 0; }
    bool operator!=(LinkedList<T>& rhs){ return cmp(rhs) != 0; }
    bool operator< (LinkedList<T>& rhs){ return cmp(rhs) < 0; }
    bool operator> (LinkedList<T>& rhs){ return cmp(rhs) > 0; }
    bool operator<=(LinkedList<T>& rhs){ return cmp(rhs) <= 0; }
    bool operator>=(LinkedList<T>& rhs){ return cmp(rhs) >= 0; }
    // Stores newEntry in a node at the end
    void Append(T newEntry);
    // Removes a node that contains a
    // value that is specified by key
    bool Delete(T &key);
    // Stores newEntry in a node at the begining
    void Push(T newEntry);
    // Removes the first node
    bool pop();
    // Get a reference to a node's item
    // at an index specified by index
    T &Get(int index);
    // Add two BigInt together
    LinkedList &operator+(LinkedList &rhs);
    // Add two BigInt together and assign it
    // to the first BigInt
    LinkedList &operator+=(LinkedList &rhs);
};
#endif /* LinkedList_h */

// MARK: - Memory Management
// Stack of Nodes for memory management
template<typename T>
Node<T> * LinkedList<T>::free = nullptr;
// Count of Lists that share the Free Stack
template<typename T>
int LinkedList<T>::numLists = 0;
// Checks if there exists memory for allocations
template<typename T>
bool LinkedList<T>::IsFull() const
{
    Node* p;
    try{
        p = new Node;
        delete p;
        return false;
    }
    // If this fails, it means there is
    // no RAM available.
    catch(std::bad_alloc exception){
        return true;
    }
}
// Get a node from free stack
template<typename T>
Node<T>* LinkedList<T>::GetNode(void)
{
    Node* p;
    // If the free stack has a node
    if(free != nullptr) {
        // Pop from the Free Stack
        p = free;
        free = free->GetNext();
    } else {
        // If there is memory left
        // create a new node, or not
        if(!IsFull()) p = new Node;
        else p = nullptr;
    }
    // Empty the Node
    p->SetNext(nullptr);
    p->SetPrev(nullptr);
    return p;
}
// Release a node from the list to the free stack
template<typename T>
void LinkedList<T>::FreeNode(Node* p)
{
    // Push the Node onto the Free Stack
    p->SetNext(free);
    p->SetPrev(nullptr);
    free = p;
    return;
}
// Initialize everything to an empty state
// add one to number of lists using free stack
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), _size(0)
{
    ++numLists;
}
// Deep copy everything
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>& aList) : head(aList.head), tail(aList.tail), _size(aList._size)
{
    assert(this != &aList);
    Clear();
    Node* rhs = aList.head;
    while (rhs != nullptr)
    {
        Append(rhs->GetNode());
        ++_size;
        rhs = rhs->GetNext();
    }
}
// Move everything from aNode to this object
// and empty aNode
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& aList) noexcept  : head(aList.head), tail(aList.tail), _size(aList._size)
{
    aList.head = nullptr;
    aList.tail = nullptr;
    aList._size = 0;
}
// Since the list creates new nodes, we
// need to delete them from memory
template <typename T>
LinkedList<T>::~LinkedList() noexcept
{
    // Destroy the current list
    Clear();
    // Now that the list is empty
    // remove it from the count of
    // Lists sharing the Free List
    numLists--;
    // If there are no more lists
    // using the Free Stack
    if(numLists == 0) {
        Node* p = free, *q;
        // Delete all the Nodes in
        // the Free List
        while(p != nullptr) {
            q = p;
            p = p->GetNext();
            delete q;
        }
    }
}
// Deep copy aList to this list object
template <typename T>
LinkedList<T> &LinkedList<T>::operator= (LinkedList<T>& aList)
{
    // Destroy this list
    Clear();
    // Start at the end
    Node* q = aList.tail;
    while(q != nullptr)
    {
        // Push a copy into this object's list
        Push(q->GetNode());
        // Move back one node
        q = q->GetPrev();
    }
   return *this;
}
// Shallow copy each object
template <typename T>
LinkedList<T> &LinkedList<T>::operator= (LinkedList<T>&& aList) noexcept
{
    head = aList.head;
    tail = aList.tail;
    _size = aList._size;
   return * this;
}
// Construct a list using a string
// just call the operator= to save some lines
template<typename T>
LinkedList<T>::LinkedList(std::string num)
{
    *this = num;
    ++numLists;
}
// Overwrite this list with a string
template<typename T>
LinkedList<T> &LinkedList<T>::operator=(std::string rhs)
// This assumes that the string has been validated beforehand
{
    // Destroy this list
    Clear();
    try {
        // Get each digit in rhs
        for(int i = 0; i < rhs.length(); ++i)
        {
            // convert the string to an int
            int digit = rhs[i] - '0';
            // Store the digit at the end of this list
            Append(digit);
        }
        // This will fail if i goes out of bounds.
    } catch (std::range_error r) {
        std::cerr << "Index out of range.\n";
    }
   return *this;
}
// Remove all elements from the list
template<class T>
void LinkedList<T>::Clear()
{
    while(_size > 0) pop();
}
// Compares two lists
template<typename T>
int LinkedList<T>::cmp(LinkedList<T> &rhs)
// Numbers are organized in left to right order
{
    // If lhs is shorter than rhs, it is less
    if (_size < rhs.size())
        return -1;
    // If lhs is longer than rhs, it is greater
    if(_size > rhs.size())
        return 1;
    // The sizes are equal
    Node* i = head, *j = rhs.begin();
    int cmp = 0;
    // We don't need to check j for nullptr because
    // they are the same length
    while (i != nullptr && cmp == 0)
    {
        // if i[i] > j[i], return 1
        if(i->GetNode() > j->GetNode()) cmp = 1;
        // if i[i] < j[i], return -1
        else if(i->GetNode() < j->GetNode()) cmp = -1;
        // keep searching
        i = i->GetNext();
        j = j->GetNext();
    }
    return cmp;
}
// Insert a node at end of this list
template<class T>
void LinkedList<T>::Append(T newEntry)
{
    // Either allocate space or pull form Free Stack
    Node* n = GetNode();
    n->Set(newEntry);
    // If the list is empty
    if(head == nullptr) {
        // Store it at the front
        n->SetPrev(nullptr);
        n->SetNext(nullptr);
        head = n;
    // Otherwise, store it at the end
    } else {
        n->SetPrev(tail);
        n->SetNext(nullptr);
        tail->SetNext(n);
    }
    // Reset the tail pointer
    tail = n;
    // Increment the number of Nodes
    ++_size;
}

// Remove an element specified by the user
template<typename T>
bool LinkedList<T>::Delete(T &key)
{
    Node* p, *q;
    // Find Key
    for(p = head, q = nullptr; p != nullptr && p->GetNode() != key; q = p, p = p->GetNext());
    // If not found
    if(p == nullptr) return false;
    // Found at the first element
    else if(q == nullptr)
    {
        // Pop node
        head = head->GetNext();
        head->SetPrev(nullptr);
    }
    
    else
    {
        // Move next over one
        q->SetNext(p->GetNext());
        // Found at the end
        if(p->GetNext() == nullptr) tail = q;
        // Found in middle
        else p->GetNext()->SetPrev(q);
    }
    // Release node
    FreeNode(p);
    // Decrease number of nodes
    --_size;
    return true;
}
// Get a reference to a node's item
template<typename T>
T &LinkedList<T>::Get(int index)
{
    // Up to the user to enter a proper index
    assert((index >= 0) && (index <= _size + 1));
    Node* p = head;
    // Go to index
    for(int i = 0; p != nullptr && i < index; p = p->GetNext(), ++i);
    // Return node's item
    return p->GetNode();
}
// MARK: - BigInt Functions

// Inserts a Node at the head of this list
template<typename T>
void LinkedList<T>::Push(T newEntry)
{
    Node* n = GetNode();
    // Initialize the node with user entry
    n->Set(newEntry);
    n->SetPrev(nullptr);
    n->SetNext(head);
    // if list isn't empty, init first
    // node's prev to n
    if(head != nullptr) head->SetPrev(n);
    // Reset head to new node
    head = n;
    // If list is empty, set tail
    // to new node
    if(tail == nullptr) tail = n;
    // Increase number of nodes in list
    ++_size;
}
// Removes the first Node in thisList
template<typename T>
bool LinkedList<T>::pop()
{
    // Nothiing to do if list is empty
    if (head == nullptr) return false;
    Node* p = head;
    head = p->GetNext();
    // If list not empty after move, clear prev
    if(head != nullptr) head->SetPrev(nullptr);
    // Otherwise, clear tail
    else tail = nullptr;
    // Decrease number of nodes
    --_size;
    // Release node
    FreeNode(p);
    return true;
}

// Adds two BigInt
template<typename T>
LinkedList<T> &LinkedList<T>::operator+(LinkedList &rhs)
// Up to the user to delete the sum list
{
    LinkedList *sum = new LinkedList;
    // Since the numbers are store in left to right order
    // we need to traverse in reverse
    Node* ls = end(), *rs = rhs.end();
    // Temp storage
    T left, right, total, digit, carry = 0;
    // While there is lhs[i], rhs[j], or carry
    while (ls || rs || carry)
    {
        // left gets lhs[i] if available, otherwise it gets 0
        left = (ls == nullptr) ? (0) : (ls->GetNode());
        // right gets rhs[j] if available, otherwise it gets 0
        right = (rs == nullptr) ? (0) : (rs->GetNode());
        // sum of lhs[i], rhs[j], and carry
        total = left + right + carry;
        // We only want one digit
        digit = total % 10;
        // If sum > 9, pick of tens place
        carry = total / 10;
        // Store digit in the front of sum
        sum->Push(digit);
        // Go to next digit
        if (ls != nullptr) ls = ls->GetPrev();
        if (rs != nullptr) rs = rs->GetPrev();
    }
   return *sum;
}
// Assigns the sum of lhs and rhs to lhs
template<typename T>
LinkedList<T> &LinkedList<T>::operator+=(LinkedList & rhs)
{
   *this = *this + rhs;
   return *this;
}


