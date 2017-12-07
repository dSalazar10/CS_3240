// Linked List Queue

#include <iostream>
#include <string>
#include <cassert>

#ifndef ListQueue_h
#define ListQueue_h

#ifndef Node_h
#define Node_h

template<typename T>
class Node
{
private:
    T item;
    Node<T>* next;
    
public:
    Node();
    Node(const T& anItem);
    Node(const T& anItem, Node<T>* nextNodePtr);
    void setItem(const T& anItem);
    void setNext(Node<T>* nextNodePtr);
    T &getItem();
    Node<T>* getNext() const;
};

#endif /* Node_h */

template<typename T>
Node<T>::Node() : next(nullptr)
{
}

template<typename T>
Node<T>::Node(const T& anItem) : item(anItem), next(nullptr)
{
}

template<typename T>
Node<T>::Node(const T& anItem, Node<T>* nextNodePtr) :
item(anItem), next(nextNodePtr)
{
}

template<typename T>
void Node<T>::setItem(const T& anItem)
{
    item = anItem;
}

template<typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
    next = nextNodePtr;
}

template<typename T>
T &Node<T>::getItem()
{
    return item;
}

template<typename T>
Node<T>* Node<T>::getNext() const
{
    return next;
}

#ifndef LinkedList_h
#define LinkedList_h

template<typename T>
class LinkedList
{
private:
    Node<T>* headPtr;
    int itemCount;
    Node<T>* getNodeAt(int position) const;
    
public:
    LinkedList();
    LinkedList(const LinkedList<T>& aList);
    virtual ~LinkedList();
    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPosition, const T& newEntry);
    bool remove(int position);
    void clear();
    T &getEntry(int position) throw(std::logic_error);
    void setEntry(int position, const T& newEntry) throw(std::logic_error);
};

#endif /* LinkedList_h */

template<class T>
LinkedList<T>::LinkedList() : headPtr(nullptr), itemCount(0)
{
}

template<class T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    return itemCount == 0;
}

template<class T>
int LinkedList<T>::getLength() const
{
    return itemCount;
}

template<class T>
bool LinkedList<T>::insert(int newPosition, const T& newEntry)
{
    bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
    if (ableToInsert)
    {
        // Create a new node containing the new entry
        Node<T>* newNodePtr = new Node<T>(newEntry);
        
        // Attach new node to chain
        if (newPosition == 1)
        {
            // Insert new node at beginning of chain
            newNodePtr->setNext(headPtr);
            headPtr = newNodePtr;
        }
        else
        {
            // Find node that will be before new node
            Node<T>* prevPtr = getNodeAt(newPosition - 1);
            // Insert new node after node to which prevPtr points
            newNodePtr->setNext(prevPtr->getNext());
            prevPtr->setNext(newNodePtr);
        }
        itemCount++;
    }
    return ableToInsert;
}

template<class T>
bool LinkedList<T>::remove(int position)
{
    bool ableToRemove = (position >= 1) && (position <= itemCount);
    if (ableToRemove)
    {
        Node<T>* curPtr = nullptr;
        if (position == 1)
        {
            // Remove the first node in the chain
            curPtr = headPtr;
            headPtr = headPtr->getNext();
        }
        else
        {
            // Find node that is before the one to delete
            Node<T>* prevPtr = getNodeAt(position - 1);
            // Point to node to delete
            curPtr = prevPtr->getNext();
            // Disconnect indicated node from chain by connecting the
            // prior node with the one after
            prevPtr->setNext(curPtr->getNext());
        }
        // Return node to system
        curPtr->setNext(nullptr);
        delete curPtr;
        curPtr = nullptr;
        
        itemCount--;
    }
    return ableToRemove;
}

template<class T>
void LinkedList<T>::clear()
{
    while (!isEmpty())
        remove(1);
}

template<class T>
T &LinkedList<T>::getEntry(int position) throw(std::logic_error)
{
    // Enforce precondition
    bool ableToGet = (position >= 1) && (position <= itemCount);
    if (ableToGet)
    {
        Node<T>* nodePtr = getNodeAt(position);
        return nodePtr->getItem();
    }
    else
    {
        std::string message = "getEntry() called with an empty list or ";
        message  = message + "invalid position.";
        throw(std::logic_error(message));
    }
}

template<class T>
Node<T>* LinkedList<T>::getNodeAt(int position) const
{
    // Debugging check of precondition
    assert((position >= 1) && (position <= itemCount));
    // Count from the beginning of the chain
    Node<T>* curPtr = headPtr;
    for (int skip = 1; skip < position; skip++) curPtr = curPtr->getNext();
    return curPtr;
}


template<typename T>
class ListQueue
{
private:
    LinkedList<T>* head;
    
public:
    ListQueue();
    ListQueue(const ListQueue& aQueue);
    ~ListQueue();
    // Test whether container is empty
    bool isEmpty() const;
    // Return size
    unsigned long long int size();
    // Access next element
    T &front() throw(std::logic_error);
    // Access last element
    T &back() throw(std::logic_error);
    bool enqueue(const T& newEntry);
    bool dequeue();
    
};

#endif /* ListQueue_h */

template<typename T>
ListQueue<T>::ListQueue()
{
    head = new LinkedList<T>();
}

template<typename T>
ListQueue<T>::ListQueue(const ListQueue& aQueue) : head(aQueue.listPtr)
{
    
}
template<typename T>
ListQueue<T>::~ListQueue()
{
}

template<typename T>
bool ListQueue<T>::isEmpty() const
{
    return head->isEmpty();
}
template<typename T>
unsigned long long int ListQueue<T>::size()
{
    return head->getLength();
}
template<typename T>
T &ListQueue<T>::front() throw(std::logic_error)
{
    if (isEmpty()) throw std::logic_error("peekFront() called with empty queue.");
    else return head->getEntry(1);
        }
template<typename T>
T &ListQueue<T>::back() throw(std::logic_error)
{
    if (isEmpty()) throw std::logic_error("peekFront() called with empty queue.");
    else return head->getEntry(head->getLength());
        }
template<typename T>
bool ListQueue<T>::enqueue(const T& newEntry)
{
    return head->insert(head->getLength() + 1, newEntry);
}

template<typename T>
bool ListQueue<T>::dequeue()
{
    return head->remove(1);
}

using namespace std;

int main()
{
    ListQueue<int> q;
    int choice, item;
    bool done = false;
    while (!done)
    {
        cout << "1.Insert Element into the Queue" << endl;
        cout << "2.Delete Element from the Queue" << endl;
        cout << "3.Size of the Queue" << endl;
        cout << "4.Front Element of the Queue" << endl;
        cout << "5.Last Element of the Queue" << endl;
        cout << "6.Exit" << endl;
        cout << "Enter your Choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                cout << "Enter value to be inserted: ";
                cin >> item;
                q.enqueue(item);
                break;
            case 2:
                item = q.front();
                q.dequeue();
                cout << "Element " << item << " Deleted" << endl;
                break;
            case 3:
                cout << "Size of the Queue: ";
                cout << q.size() << endl;
                break;
            case 4:
                cout<<"Front Element of the Queue: ";
                cout<<q.front()<<endl;
                break;
            case 5:
                cout<<"Back Element of the Queue: ";
                cout<<q.back()<<endl;
                break;
            default:
                done = true;
        }
    }
    return 0;
}
