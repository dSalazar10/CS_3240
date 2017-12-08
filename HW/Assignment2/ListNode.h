//Name: Daniel Salazar
//Email: dsalazar10@csueastbay.edu
//
// This is a container for Table


#include "LinkedList.h"
#ifndef ListNode_h
#define ListNode_h

template<typename T>
class ListNode
{
private:
    LinkedList<T> list;
    ListNode<T>* next;
    ListNode<T>* prev;
public:
    // Default Constructor
    ListNode(void);
    // Copy Constructor
    ListNode(ListNode<T>& aList);
    // Move Constructor
    ListNode(ListNode<T> &&aList) noexcept;
    // Destructor
    ~ListNode() noexcept;
    // Copy assignment
    ListNode<T> &operator= (ListNode<T> &aList);
    // Move assignment
    ListNode<T>& operator= (ListNode<T>&& aList) noexcept;
    // Modifies the list
    void Set(std::string aList);
    // Modifes next
    void SetNext(ListNode<T>* Next);
    // Modifies prev
    void SetPrev(ListNode<T>* Prev);
    // Get a reference to the list
    LinkedList<T> &GetList(void);
    // Get a pointer to next
    ListNode<T>* GetNext(void);
    // Get a pointer to prev
    ListNode<T>* GetPrev(void);
};

#endif /* ListNode_h */
// Default
template<typename T>
ListNode<T>::ListNode(void) :list(), next(nullptr), prev(nullptr)
{
}
// Copy
template<typename T>
ListNode<T>::ListNode(ListNode<T>& aList) : list(aList.list), next(aList.next), prev(aList.prev)
{
}
// Move
template<typename T>
ListNode<T>::ListNode(ListNode<T> &&aList) noexcept : list(aList.list), next(aList.next), prev(aList.prev)
{
    aList.~ListNode<T>();
    aList.next = nullptr;
    aList.prev = nullptr;
}
// Destructor
template<typename T>
ListNode<T>::~ListNode() noexcept
{
}
// Copy assignment
template<typename T>
ListNode<T> &ListNode<T>::operator= (ListNode<T> &aList)
{
    ListNode<T> tmp(aList);
   * this = std::move(tmp);
   return * this;
}
// Move assignment
template<typename T>
ListNode<T>& ListNode<T>::operator= (ListNode<T>&& aList) noexcept
{
    list = aList.list;
    next = aList.next;
    prev = aList.prev;
    aList.~ListNode<T>();
    aList.next = nullptr;
    aList.prev = nullptr;
   return * this;
}
// Calls LikedList's operator=(string)
template<typename T>
void ListNode<T>::Set(std::string aList)
{
    list = aList;
}
// Modifies next
template<typename T>
void ListNode<T>::SetNext(ListNode<T>* Next)
{
    next = Next;
}
// Modifies prev
template<typename T>
void ListNode<T>::SetPrev(ListNode<T>* Prev)
{
    prev = Prev;
}
// Get a reference to the list
template<typename T>
LinkedList<T> &ListNode<T>::GetList(void)
{
    return list;
}
// Get a pointer to next
template<typename T>
ListNode<T>* ListNode<T>::GetNext(void)
{
    return next;
}
// Get a pointer to prev
template<typename T>
ListNode<T>* ListNode<T>::GetPrev(void)
{
    return prev;
}







