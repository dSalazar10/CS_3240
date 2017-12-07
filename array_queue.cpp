// Array Queue

#include <iostream>
#include <string>
#include <cassert>

using namespace std;
const int MAX_QUEUE = 50;

#ifndef Queue_h
#define Queue_h

template<typename T>
class ArrayQueue
{
private:
    T items[MAX_QUEUE]; // Array of queue items
    int front;                 // Index to front of queue
    int back;                  // Index to back of queue
    int count;                 // Number of items currently in the queue
    
public:
    ArrayQueue();
    int size() { return count; }
    bool isEmpty() const;
    bool enqueue(const T& newEntry);
    bool dequeue();
    T peekFront() const throw(std::logic_error);
    T peekBack() const throw(std::logic_error);
};

#endif /* Queue_h */

template<typename T>
ArrayQueue<T>::ArrayQueue() : front(0), back(MAX_QUEUE - 1), count(0)
{
} // end default constructor

template<typename T>
bool ArrayQueue<T>::isEmpty() const
{
    return count == 0;
} // end isEmpty

template<typename T>
bool ArrayQueue<T>::enqueue(const T& newEntry)
{
    bool result = false;
    if (count < MAX_QUEUE)
    {
        // Queue has room for another item
        back = (back + 1) % MAX_QUEUE;
        items[back] = newEntry;
        count++;
        result = true;
    } // end if
    
    return result;
} // end enqueue

template<typename T>
bool ArrayQueue<T>::dequeue()
{
    bool result = false;
    if (!isEmpty())
    {
        front = (front + 1) % MAX_QUEUE;
        count--;
        result = true;
    } // end if
    
    return result;
} // end dequeue

template<typename T>
T ArrayQueue<T>::peekFront() const throw(std::logic_error)
{
    // Enforce precondition
    if (isEmpty()) throw std::logic_error("peekFront() called with empty queue");
    else return items[front];
}
template<typename T>
T ArrayQueue<T>::peekBack() const throw(std::logic_error)
{
    // Enforce precondition
    if (isEmpty()) throw std::logic_error("peekBack() called with empty queue");
    else return items[back];
}

int main()
{
    ArrayQueue<int> q;
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
                item = q.peekFront();
                q.dequeue();
                cout << "Element " << item << " Deleted" << endl;
                break;
            case 3:
                cout << "Size of the Queue: ";
                cout << q.size() << endl;
                break;
            case 4:
                cout<<"Front Element of the Queue: ";
                cout<<q.peekFront()<<endl;
                break;
            case 5:
                cout<<"Back Element of the Queue: ";
                cout<<q.peekBack()<<endl;
                break;
            default:
                done = true;
        }
    }
    return 0;
}
