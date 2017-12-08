//Name: Daniel Salazar
//Email: dsalazar10@csueastbay.edu
//
// This is a container for a Linked List

#ifndef Node_h
#define Node_h

template<typename T>
class Node
{
private:
    T item;
    Node<T>* next;
    Node<T>* prev;
    // Outputs item
    friend std::ostream& operator<< (std::ostream& os, Node<T>* aNode)
    {
        os << aNode->item;
        return os;
    }
public:
    // Default Constructor
    Node(void);
    // Copy Constructor
    Node(Node<T>& aNode);
    // Move Constructor
    Node(Node<T> &&aNode) noexcept;
    // Destructor
    ~Node() noexcept;
    // Copy assignment
    Node<T> &operator= (Node<T> &aNode);
    // Move assignment
    Node<T>& operator= (Node<T>&& aNode) noexcept;
    // Modifies item
    void Set(T& anItem);
    // Modifies next
    void SetNext(Node<T>* nextNode);
    // Modifies prev
    void SetPrev(Node<T>* prevNode);
    // Returns item
    T &GetNode(void);
    // Returns next
    Node<T>* GetNext(void);
    // Return prev
    Node<T>* GetPrev(void);
};
#endif /* Node_h */

// Sets everything to an empty state
template<typename T>
Node<T>::Node(void) :item(), next(nullptr), prev(nullptr)
{
}
// Shallow copy everything
template<typename T>
Node<T>::Node(Node<T>& aNode) : item(aNode.item), next(aNode.next), prev(aNode.prev)
{
}
// Move everything from aNode to this object
// and empty aNode
template<typename T>
Node<T>::Node(Node<T> &&aNode) noexcept : item(aNode.item), next(aNode.next), prev(aNode.prev)
{
    aNode.item = NULL;
    aNode.next = nullptr;
    aNode.prev = nullptr;
}
// No new memory allocation
// use default destructor
template<typename T>
Node<T>::~Node() noexcept
{
}
// Lets the compiler know that the given lvalue
// is supposed to be treated as an rvalue
// then it calls the move operator= on that
// static_casted xvalue
template<typename T>
Node<T> &Node<T>::operator= (Node<T> &aNode)
{
    Node<T> tmp(aNode);
   * this = std::move(tmp);
   return * this;
}
// Assign each of the values of aNode to this object
template<typename T>
Node<T>& Node<T>::operator= (Node<T>&& aNode) noexcept
{
    item = aNode.item;
    next = aNode.next;
    prev = aNode.prev;
    aNode.item = NULL;
    aNode.next = nullptr;
    aNode.prev = nullptr;
   return * this;
}
// Setters
template<typename T>
void Node<T>::Set(T& anItem)
{
    item = anItem;
}
template<typename T>
void Node<T>::SetNext(Node<T>* nextNode)
{
    next = nextNode;
}
template<typename T>
void Node<T>::SetPrev(Node<T>* prevNode)
{
    prev = prevNode;
}
// Getters
template<typename T>
T &Node<T>::GetNode(void)
{
    return item;
}
template<typename T>
Node<T>* Node<T>::GetNext(void)
{
    return next;
}
template<typename T>
Node<T>* Node<T>::GetPrev(void)
{
    return prev;
}
