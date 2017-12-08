//Name: Daniel Salazar
//Email: dsalazar10@csueastbay.edu
//
// This is an implementation of a 2-D list
// The LinkedList class is an implementation
// of a BigInt, so this is effectively a
// list of BigInts.
// The free stack used here is not the same
// as the free stack used in LinkedList

#include "ListNode.h"
#include <string>   // string
#ifndef Table_h
#define Table_h
template<typename T>
class Table
{
    // So I don't have to type out all the <T>.
    typedef ListNode<T> ListNode;
private:
    ListNode* head;
    ListNode* tail;
    int _size;
    
    // Memory Management
    // Keeps all the unused ListNodes on a stack
    // for reuse later
    static ListNode* free;
    // Keep track of how many Tables are using
    // the free stack
    static int numTables;
    // Gets a node from the free stack, or if
    // there is aenough memory, it creates a new node
    ListNode* GetNode(void);
    // Returns an unused node to the free stack
    void FreeNode(ListNode* p);
    // Checks if there is enough memory to create
    // a new node
    bool IsFull() const;
public:
    // Default constructor
    Table();
    // Copy constructor
    Table(Table<T>& aTable);
    // Move constructor
    Table(Table<T>&& aTable) noexcept;
    // Destructor
    ~Table() noexcept;
    // Copy assignment
    Table& operator= (Table<T>& aTable);
    // Move Assignment
    Table& operator= (Table<T>&& aTable) noexcept;
    // User input constructor
    Table(std::string num);
    // User input assignment
    Table &operator=(std::string rhs);
    // Get the number of lists
    unsigned long long int size(void) { return _size; }
    // Checks if table is empty
    bool empty(void) { return head == nullptr; }
    // Destroys the table
    void Clear();
    // Gets a pointer to the first BigInt
    ListNode* begin() { return head; }
    // Gets a pointer to the last BigInt
    ListNode* end() { return tail; }
    // Stores a BigInt in the front
    void Push(std::string newEntry);
    // Removes the first BigInt
    bool pop();
    
    // HW Functions
    // Stores a BigInt at the end of the table
    void Append(std::string newEntry);
    // Adds a user defined BigInt to a BigInt
    // specified in by the user
    void Add(std::string newEntry, int index);
    // Removes a BigInt specified by the user
    bool Delete(std::string key);
    // Get a reference to a BigInt
    ListNode &Get(int index);
    // Prints all the BigInts in the Table
    void PrintAll(ListNode* p);
};
#endif /* Table_h */

// Free Stack for memory management
template<typename T>
ListNode<T>* Table<T>::free = nullptr;
// Count of BigInts that share the Free Stack
template<typename T>
int Table<T>::numTables = 0;
// Checks if memory is full
template<typename T>
bool Table<T>::IsFull() const
{
    ListNode* p;
    try{
        p = new ListNode;
        delete p;
        return false;
    }
    // If this fails, it means there is
    // no RAM available.
    catch(std::bad_alloc exception){
        return true;
    }
}
// Get a Listnode from the free stack
template<typename T>
ListNode<T>* Table<T>::GetNode(void)
{
    ListNode* p;
    // Check the Free List for a Node
    if(free != nullptr) {
        // Get a List from the Free List
        p = free;
        free = free->GetNext();
    } else {
        // If there is memory left
        // create a new node, or not
        if(!IsFull()) p = new ListNode;
        else p = nullptr;
    }
    // Empty the Node
    p->SetNext(nullptr);
    p->SetPrev(nullptr);
    return p;
}
// Release a BigInt from the table to the free stack
template<typename T>
void Table<T>::FreeNode(ListNode* p)
{
    // Push the BigInt onto the Free Stack
    p->SetNext(free);
    p->SetPrev(nullptr);
    free = p;
    return;
}
// Initialize everything to an empty state
// add one to number of tables using free stack
template <typename T>
Table<T>::Table() : head(nullptr), tail(nullptr), _size(0)
{
    ++numTables;
}
// Deep copy everything
template <typename T>
Table<T>::Table(Table<T>& aTable) : head(aTable.head), tail(aTable.tail), _size(aTable._size)
{
    assert(this != &aTable);
    Clear();
    ListNode* rhs = aTable.head;
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
Table<T>::Table(Table<T>&& aTable) noexcept  : head(aTable.head), tail(aTable.tail), _size(aTable._size)
{
    aTable.head = nullptr;
    aTable.tail = nullptr;
    aTable._size = 0;
}
// Since the list creates new ListNodes, we
// need to delete them from memory
template <typename T>
Table<T>::~Table() noexcept
{
    // Inchworm down the list
    ListNode* p = head,* q;
    Clear();
    // Now that the list is empty
    // remove it from the count of
    // Lists sharing the Free List
    numTables--;
    // If there are no more lists
    // using the Free List
    if(numTables == 0) {
        p = free;
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
Table<T> &Table<T>::operator= (Table<T>& aTable)
{
    // Destroy this list
    Clear();
    // Start at the end
    ListNode* q = aTable.tail;
    while(q != nullptr)
    {
        // Push a copy into this object's list
        Push(q->GetNode());
        // Move back one node
        q = q->GetPrev();
    }
   return * this;
}
// Shallow copy each object
template <typename T>
Table<T> &Table<T>::operator= (Table<T>&& aTable) noexcept
{
    head = aTable.head;
    tail = aTable.tail;
    _size = aTable._size;
   return * this;
}
// Remove all elements from the list
template<class T>
void Table<T>::Clear()
{
    while(_size > 0) pop();
}
// Insert at end of list
template<class T>
void Table<T>::Append(std::string newEntry)
{
    // Either allocate space or pull form Free List
    ListNode* n = GetNode();
    // Initalize the node to newEntry
    n->Set(newEntry);
    // If the list is empty
    if(head == nullptr) {
        n->SetPrev(nullptr);
        n->SetNext(nullptr);
        head = n;
    } else {
        n->SetPrev(tail);
        n->SetNext(nullptr);
        tail->SetNext(n);
    }
    // Point to last node again
    tail = n;
    // Increment the number of Nodes
    ++_size;
}
// Adds two BigInts together
template<typename T>
void Table<T>::Add(std::string newEntry, int index)
{
    // User defined BigInt
    LinkedList<T> tmp;
    tmp = newEntry;
    // Find The BigInt that was specified by the user
    ListNode* p = head;
    for(int i = 0; p != nullptr && i < index; ++i, p = p->GetNext());
    // Add the user defined BigInt to the BigInt at index
    p->GetList() += tmp;
}
// Remove a BigInt specified by the user
template<typename T>
bool Table<T>::Delete(std::string key)
{
    // User defined BigInt
    LinkedList<T> tmp;
    tmp = key;
    ListNode* p,* q;
    // Find Key
    for(p = head, q = nullptr; p != nullptr && p->GetList() != tmp; q = p, p = p->GetNext());
    // Not found
    if(p == nullptr) return false;
    // First element
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
    // Release ListNode
    FreeNode(p);
    // Decrease number of BigInts
    --_size;
    return true;
}
// Get a reference to a BigInt
template<typename T>
ListNode<T> &Table<T>::Get(int index)
{
    // Up to the user to enter a proper index
    assert((index >= 0) && (index <= _size + 1));
    ListNode* p = head;
    // Go to index
    for(int i = 0; p != nullptr && i < index; p = p->GetNext(), ++i);
    // Return BigInt
    return p;
}
// Prints all of the BigInts in the table
template<typename T>
void Table<T>::PrintAll(ListNode* p)
{
    for(int i = 0; i < _size; ++i, p = p->GetNext())
        std::cout << " " << p->GetList();
    return;
}
// Inserts a Node at the head of this table
template<typename T>
void Table<T>::Push(std::string newEntry)
{
    ListNode* n = GetNode();
    // Initialize the node with user entry
    n->Set(newEntry);
    n->SetPrev(nullptr);
    n->SetNext(head);
    ListNode* h = head;
    // if list isn't empty, init first
    // node's prev to n
    if(h != nullptr) h->SetPrev(n);
    // Reset head to new node
    head = n;
    // If list is empty, set tail
    // to new node
    if(tail == nullptr) tail = n;
    // Increase number of BigInts in table
    ++_size;
}
// Removes the first BigInt in this table
template<typename T>
bool Table<T>::pop()
{
    // Nothiing to do if table is empty
    if (head == nullptr) return false;
    ListNode* p = head;
    head = p->GetNext();
    // If table not empty after move, clear prev
    if(head != nullptr) head->SetPrev(nullptr);
    // Otherwise, clear tail
    else tail = nullptr;
    // Decrease number of BigInts
    --_size;
    // Release BigInt
    FreeNode(p);
    return true;
}













