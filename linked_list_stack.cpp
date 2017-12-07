// Linked List Stack, my version

#include <cassert>
#include <iostream>

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



#ifndef LinkedStack_h
#define LinkedStack_h


template<class T>
class LinkedStack
{
private:
    Node<T>* topPtr;
    unsigned long long int _size;
    
public:
    LinkedStack();
    LinkedStack(const LinkedStack<T>& aStack);
    virtual ~LinkedStack();
    // Test whether container is empty
    bool isEmpty() const;
    // Return size
    unsigned long long int size();
    // Access next element
    T &top();
    bool push(const T& newItem);
    bool pop();
    
};
#endif /* LinkedStack_h */

template<class T>
LinkedStack<T>::LinkedStack() : topPtr(nullptr)
{
}
template<class T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& aStack)
{
    // Point to nodes in original chain
    Node<T>* origChainPtr = aStack->topPtr;
    if (origChainPtr == nullptr) topPtr = nullptr;
    else
    {
        // Copy first node
        topPtr = new Node<T>();
        topPtr->setItem(origChainPtr->getItem());
        // Point to last node in new chain
        Node<T>* newChainPtr = topPtr;
        // Copy remaining nodes
        while (origChainPtr != nullptr)
        {
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
            // Get next item from original chain
            T nextItem = origChainPtr->getItem();
            // Create a new node containing the next item
            Node<T>* newNodePtr = new Node<T>(nextItem);
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();
        }
        newChainPtr->setNext(nullptr);
    }
}
template<class T>
LinkedStack<T>::~LinkedStack()
{
    // Pop until stack is empty
    while (!isEmpty())
        pop();
}
template<class T>
bool LinkedStack<T>::isEmpty() const
{
    return topPtr == nullptr;
}
template<class T>
unsigned long long int LinkedStack<T>::size()
{
    return _size;
}
template<class T>
T &LinkedStack<T>::top()
{
    assert(!isEmpty());
    return topPtr->getItem();
}
template<class T>
bool LinkedStack<T>::push(const T& newItem)
{
    Node<T>* newNodePtr = new Node<T>(newItem, topPtr);
    topPtr = newNodePtr;
    newNodePtr = nullptr;
    
    return true;
}

template<class T>
bool LinkedStack<T>::pop()
{
    bool result = false;
    if (!isEmpty())
    {
        // Stack is not empty; delete top
        Node<T>* nodeToDeletePtr = topPtr;
        topPtr = topPtr->getNext();
        // Return deleted node to system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        result = true;
    }
    return result;
}


using namespace std;

int main(int argc, const char * argv[]) {
    int choice, item;
    LinkedStack<int> sl;
    bool done = false;
    while (!done)
    {
        cout << "1.Push Element into the Stack" << endl;
        cout << "2.Pop Element from the Stack" << endl;
        cout << "3.Get top of the Stack" << endl;
        cout << "4.Quit" << endl;
        cout << "Enter your Choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                cout << "Enter value to be pushed into the stack: ";
                cin >> item;
                sl.push(item);
                break;
            case 2:
                sl.pop();
                break;
            case 3:
                cout << "Top of the stack: " << sl.top() << endl;
                break;
            default:
                done = true;
        }
    }
    return 0;
}
