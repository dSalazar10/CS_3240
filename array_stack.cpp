// Array Stack

#include <cassert>
#include <iostream>
#define MAX_STACK (int)1028

using namespace std;

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

#ifndef ArrayStack_h
#define ArrayStack_h

#define DEFAULT (int)10

#ifndef Array_h
#define Array_h

template<typename T>
class Array
{
    
private:
    T *_a;
    int _n;
public:
    Array();
    Array(int num);
    Array(const Array &m);
    Array(Array &&m);
    ~Array();
    T &At(int i) { if(_n > 0) return _a[i]; }
    T &operator[](int i) { assert(_n > 0); return _a[i]; }
    int size(void) const { return _n; }
    bool empty(void) const { return _n == 0; }
    Array &operator=(Array &rhs);
    Array &operator=(Array &&rhs);
};
#endif /* Array_h */

template<typename T>
Array<T>::Array()
{
    int i;
    _a = new T[DEFAULT];
    _n = 10;
    for(i = 0; i < 10; i++) _a[i] = 0;
}

template<typename T>
Array<T>::Array(int num)
{
    int i;
    if(num <= 0) num = DEFAULT;
    _a = new T[num];
    _n = num;
    for(i = 0; i < num; i++) _a[i] = 0;
}

template<typename T>
Array<T>::Array(const Array &m)
{
    _a = new int[m._n];
    _n = m._n;
    for(int i = 0; i <m._n; i++) _a[i] = m._a[i];
}

template<typename T>
Array<T>::Array(Array &&m)
{
    _a = m._a;
    m._a = nullptr;
}

template<typename T>
Array<T>::~Array()
{
    delete[] _a;
}

template<typename T>
Array<T> &Array<T>::operator =(Array &rhs)
{
    int i;
    if(&rhs == this) return *this;
    if(rhs._n != _n)
    {
        delete[] _a;
        _a = new T[rhs._n];
        _n = rhs._n;
    }
    for(i = 0; i < rhs._n; i++) _a[i] = rhs._a[i];
    return *this;
}

template<typename T>
Array<T> &Array<T>::operator =(Array &&rhs)
{
    if(&rhs == this) return *this;
    delete[] _a;
    _a = rhs._a;
    _n = rhs._n;
    rhs._a = nullptr;
    return *this;
}

template<typename T>
class ArrayStack
{
private:
    Array<T> array;
    int _t;
    
public:
    ArrayStack();
    bool empty() const { return array.empty(); }
    bool push(const T& newEntry);
    bool pop();
    T peek() { return array[0]; }
};
#endif /* ArrayStack_h */

template<typename T>
ArrayStack<T>::ArrayStack() : _t(-1)
{
}

template<typename T>
bool ArrayStack<T>::push(const T& newEntry)
{
    bool result = false;
    if (_t < MAX_STACK - 1)
    {
        ++_t;
        array[_t] = newEntry;
        result = true;
    }
    return result;
}

template<typename T>
bool ArrayStack<T>::pop()
{
    bool result = false;
    if (!array.empty())
    {
        --_t;
        result = true;
    }
    return result;
}

int main(int argc, const char * argv[]) {
    int choice, item;
    ArrayStack<int> sl;
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
                cout << "Top of the stack: " << sl.peek() << endl;
                break;
            default:
                done = true;
        }
    }
    return 0;
}
