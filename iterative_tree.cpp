// Iterative Tree
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstring>
#include <new>
#include <cstddef>

using namespace std;

typedef char ItemType;

struct NodeType;
struct TreeNode;

class FullQueue
{};
class EmptyQueue
{};

class QueType
{
public:
    QueType();
    // Class constructor.
    // Because there is a default constructor, the precondition
    // that the queue has been initialized is omitted.
    QueType(int max);
    // Parameterized class constructor.
    ~QueType();
    // Class destructor.
    QueType(const QueType& anotherQue);
    // Copy constructor
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
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is at rear of queue.
    void Dequeue(ItemType& item);
    // Function: Removes front item from the queue and returns it in item.
    // Post: If (queue is empty) EmptyQueue exception is thrown
    //       and item is undefined
    //       else front element has been removed from queue and
    //       item is a copy of removed element.
private:
    
    NodeType* front;
    NodeType* rear;
};

struct NodeType
{
    ItemType info;
    NodeType* next;
};



QueType::QueType()          // Class constructor.
// Post:  front and rear are set to NULL.
{
    front = NULL;
    rear = NULL;
}


void QueType::MakeEmpty()
// Post: Queue is empty; all elements have been deallocated.
{
    NodeType* tempPtr;
    
    while (front != NULL)
    {
        tempPtr = front;
        front = front->next;
        delete tempPtr;
    }
    rear = NULL;
}

// Class destructor.
QueType::~QueType()
{
    MakeEmpty();
}


bool QueType::IsFull() const
// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
{
    NodeType* location;
    try
    {
        location = new NodeType;
        delete location;
        return false;
    }
    catch(std::bad_alloc)
    {
        return true;
    }
}


bool QueType::IsEmpty() const
// Returns true if there are no elements on the queue; false otherwise.
{
    return (front == NULL);
}


void QueType::Enqueue(ItemType newItem)
// Adds newItem to the rear of the queue.
// Pre:  Queue has been initialized.
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.

{
    if (IsFull())
        throw FullQueue();
    else
    {
        NodeType* newNode;
        
        newNode = new NodeType;
        newNode->info = newItem;
        newNode->next = NULL;
        if (rear == NULL)
            front = newNode;
        else
            rear->next = newNode;
        rear = newNode;
    }
}


void QueType::Dequeue(ItemType& item)
// Removes front item from the queue and returns it in item.
// Pre:  Queue has been initialized and is not empty.
// Post: If (queue is not empty) the front of the queue has been
//       removed and a copy returned in item;
//       othersiwe a EmptyQueue exception has been thrown.
{
    if (IsEmpty())
        throw EmptyQueue();
    else
    {
        NodeType* tempPtr;
        
        tempPtr = front;
        item = front->info;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        delete tempPtr;
    }
}

QueType::QueType
(const QueType& anotherQue)
{
    NodeType* ptr1;
    NodeType* ptr2;
    
    if (anotherQue.front == NULL)
        front = NULL;
    else
    {
        front = new NodeType;
        front->info = anotherQue.front->info;
        ptr1 = anotherQue.front->next;
        ptr2 = front;
        while (ptr1 != NULL)
        {
            ptr2->next = new NodeType;
            ptr2 = ptr2->next;
            ptr2->info = ptr1->info;
            ptr1 = ptr1->next;
        }
        ptr2->next = NULL;
        rear = ptr2;
    }
}


enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};
class TreeType
{
public:
    TreeType();                     // constructor
    ~TreeType();                    // destructor
    TreeType(const TreeType& originalTree);
    void operator=(const TreeType& originalTree);
    // copy constructor
    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull() const;
    int GetLength() const;
    ItemType GetItem(ItemType item, bool& found);
    void PutItem(ItemType item);
    void DeleteItem(ItemType item);
    void ResetTree(OrderType order);
    ItemType GetNextItem (OrderType order, bool& finished);
    void Print(std::ofstream& outFile) const;
private:
    TreeNode* root;
    QueType preQue;
    QueType inQue;
    QueType postQue;
};
struct TreeNode
{
    ItemType info;
    TreeNode* left;
    TreeNode* right;
};

bool TreeType::IsFull() const
// Returns true if there is no room for another item
//  on the free store; false otherwise.
{
    TreeNode* location;
    try
    {
        location = new TreeNode;
        delete location;
        return false;
    }
    catch(std::bad_alloc exception)
    {
        return true;
    }
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
    return root == NULL;
}

int CountNodes(TreeNode* tree);

int TreeType::GetLength() const
// Calls recursive function CountNodes to count the
// nodes in the tree.
{
    return CountNodes(root);
}


int CountNodes(TreeNode* tree)
// Post: returns the number of nodes in the tree.
{
    if (tree == NULL)
        return 0;
    else
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

void Retrieve(TreeNode* tree,
              ItemType& item, bool& found);

ItemType TreeType::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
    Retrieve(root, item, found);
    return item;
}


void Retrieve(TreeNode* tree,
              ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem;
//       otherwise found is false and item is unchanged.
{
    if (tree == NULL)
        found = false;                     // item is not found.
    else if (item < tree->info)
        Retrieve(tree->left, item, found); // Search left subtree.
    else if (item > tree->info)
        Retrieve(tree->right, item, found);// Search right subtree.
    else
    {
        item = tree->info;                 // item is found.
        found = true;
    }
}

void FindNode(TreeNode* tree, ItemType item,
              TreeNode*& nodePtr, TreeNode*& parentPtr)
// Post: If a node is found with the same key as itemπs, then
//       nodePtr points to that node and parentPtr points to its
//       parent node. If the root node has the same key as itemπs,
//       parentPtr is NULL. If no node has the same key, then
//       nodePtr is NULL and parentPtr points to the node in the
//       tree that is the logical parent of item.

{
    nodePtr = tree;
    parentPtr = NULL;
    bool found = false;
    while (nodePtr != NULL && !found)
    {
        if (item < nodePtr->info)
        {
            parentPtr = nodePtr;
            nodePtr = nodePtr->left;
        }
        else if (item > nodePtr->info)
        {
            parentPtr = nodePtr;
            nodePtr = nodePtr->right;
        }
        else
            found = true;
    }
}
void GetPredecessor(TreeNode* tree, ItemType& data);
void Delete(TreeNode*& tree, ItemType item);

void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no
//       longer in the tree.  If tree is a leaf node or has only
//       non-NULL child pointer the node pointed to by tree is
//       deleted; otherwise, the user's data is replaced by its
//       logical predecessor and the predecessor's node is deleted.
{
    ItemType data;
    TreeNode* tempPtr;
    
    tempPtr = tree;
    if (tree->left == NULL)
    {
        tree = tree->right;
        delete tempPtr;
    }
    else if (tree->right == NULL)
    {
        tree = tree->left;
        delete tempPtr;
    }
    else
    {
        GetPredecessor(tree->left, data);
        tree->info = data;
        Delete(tree->left, data);
    }
}

void Delete(TreeNode*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
    if (item < tree->info)
        Delete(tree->left, item);   // Look in left subtree.
    else if (item > tree->info)
        Delete(tree->right, item);  // Look in right subtree.
    else
        DeleteNode(tree);           // Node found; call DeleteNode.
}

void GetPredecessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
    while (tree->right != NULL)
        tree = tree->right;
    data = tree->info;
}


void TreeType::PutItem(ItemType item)
// Post: item is in tree.
{
    TreeNode* newNode;
    TreeNode* nodePtr;
    TreeNode* parentPtr;
    
    newNode = new TreeNode;
    newNode->info = item;
    newNode->left = NULL;
    newNode->right = NULL;
    
    FindNode(root, item, nodePtr, parentPtr);
    
    if (parentPtr == NULL)        // Insert as root.
        root = newNode;
    else if (item < parentPtr->info)
        parentPtr->left = newNode;
    else parentPtr->right = newNode;
}



void TreeType::DeleteItem(ItemType item)
// Post: There is no node in the tree whose info member
//       matches item.
{
    TreeNode* nodePtr;
    TreeNode* parentPtr;
    
    FindNode(root, item, nodePtr, parentPtr);
    
    if (nodePtr == root)
        DeleteNode(root);
    else
        if (parentPtr->left == nodePtr)
            DeleteNode(parentPtr->left);
        else DeleteNode(parentPtr->right);
}

void PrintTree(TreeNode* tree, std::ofstream& outFile)
// Prints info member of items in tree in sorted order on outFile.
{
    if (tree != NULL)
    {
        PrintTree(tree->left, outFile);   // Print left subtree.
        outFile << tree->info;
        PrintTree(tree->right, outFile);  // Print right subtree.
    }
}

void TreeType::Print(std::ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
    PrintTree(root, outFile);
}

TreeType::TreeType()
{
    root = NULL;
}

void Destroy(TreeNode*& tree);

TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
    Destroy(root);
}


void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
    if (tree != NULL)
    {
        Destroy(tree->left);
        Destroy(tree->right);
        delete tree;
    }
}

void TreeType::MakeEmpty()
{
    Destroy(root);
    root = NULL;
}


void CopyTree(TreeNode*& copy,
              const TreeNode* originalTree);

TreeType::TreeType(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree
//  into root.
{
    CopyTree(root, originalTree.root);
}

void TreeType::operator=
(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree
// into root.
{
    {
        if (&originalTree == this)
            return;             // Ignore assigning self to self
        Destroy(root);      // Deallocate existing tree nodes
        CopyTree(root, originalTree.root);
    }
    
}
void CopyTree(TreeNode*& copy,
              const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate
//       of originalTree.
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->info = originalTree->info;
        CopyTree(copy->left, originalTree->left);
        CopyTree(copy->right, originalTree->right);
    }
}
// Function prototypes for auxiliary functions.

void PreOrder(TreeNode*, QueType&);
// Enqueues tree items in preorder.


void InOrder(TreeNode*, QueType&);
// Enqueues tree items in inorder.


void PostOrder(TreeNode*, QueType&);
// Enqueues tree items in postorder.


void TreeType::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in
// the desired order.
{
    switch (order)
    {
        case PRE_ORDER : PreOrder(root, preQue);
            break;
        case IN_ORDER  : InOrder(root, inQue);
            break;
        case POST_ORDER: PostOrder(root, postQue);
            break;
    }
}


void PreOrder(TreeNode* tree,
              QueType& preQue)
// Post: preQue contains the tree items in preorder.
{
    if (tree != NULL)
    {
        preQue.Enqueue(tree->info);
        PreOrder(tree->left, preQue);
        PreOrder(tree->right, preQue);
    }
}


void InOrder(TreeNode* tree,
             QueType& inQue)
// Post: inQue contains the tree items in inorder.
{
    if (tree != NULL)
    {
        InOrder(tree->left, inQue);
        inQue.Enqueue(tree->info);
        InOrder(tree->right, inQue);
    }
}


void PostOrder(TreeNode* tree,
               QueType& postQue)
// Post: postQue contains the tree items in postorder.
{
    if (tree != NULL)
    {
        PostOrder(tree->left, postQue);
        PostOrder(tree->right, postQue);
        postQue.Enqueue(tree->info);
    }
}


ItemType TreeType::GetNextItem (OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true;
//       otherwise finished is false.
{
    finished = false;
    ItemType item;
    switch (order)
    {
        case PRE_ORDER  : preQue.Dequeue(item);
            if (preQue.IsEmpty())
                finished = true;
            break;
        case IN_ORDER   : inQue.Dequeue(item);
            if (inQue.IsEmpty())
                finished = true;
            break;
        case  POST_ORDER: postQue.Dequeue(item);
            if (postQue.IsEmpty())
                finished = true;
            break;
    }
    return item;
}


int main()
{
    
    ifstream inFile;       // file containing operations
    ofstream outFile;      // file containing output
    string inFileName;     // input file external name
    string outFileName;    // output file external name
    string outputLabel;
    string command;        // operation to be executed
    
    char item;
    string orderItem;
    TreeType tree;
    OrderType order;
    bool found;
    bool finished;
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
        cout << command;
        if (command == "PutItem")
        {
            inFile >> item;
            tree.PutItem(item);
            outFile << item;
            outFile << " is inserted" << endl;
        }
        else if (command == "DeleteItem")
        {
            inFile >> item;
            tree.DeleteItem(item);
            outFile << item;
            outFile << " is deleted" << endl;
        }
        else if (command == "GetItem")
        {
            inFile >> item;
            
            item = tree.GetItem(item, found);
            if (found)
                outFile << item << " found in list." << endl;
            else outFile << item  << " not in list."  << endl;
        }
        else if (command == "GetLength")
            outFile << "Number of nodes is " << tree.GetLength() << endl;
        else if (command == "IsEmpty")
            if (tree.IsEmpty())
                outFile << "Tree is empty." << endl;
            else outFile << "Tree is not empty."  << endl;
        
            else if (command == "PrintTree")
            {
                tree.Print(outFile);
                outFile << endl;
            }
            else if (command == "ResetTree")
            {
                inFile >> orderItem;
                if (orderItem == "PRE_ORDER")
                    order = PRE_ORDER;
                else if (orderItem == "IN_ORDER")
                    order = IN_ORDER;
                else order = POST_ORDER;
                
                tree.ResetTree(order);
            }
            else if (command == "GetNextItem")
            {
                inFile >> orderItem;
                if (orderItem == "PRE_ORDER")
                    order = PRE_ORDER;
                else if (orderItem == "IN_ORDER")
                    order = IN_ORDER;
                else order = POST_ORDER;
                item = tree.GetNextItem(order,finished);
                outFile << "Next item is: " << item << endl;
                if (finished)
                    outFile << orderItem << " traversal is complete." << endl;
            }
            else if (command == "IsFull")
                if (tree.IsFull())
                    outFile << "Tree is full."  << endl;
                else outFile << "Tree is not full." << endl;
                else if (command == "MakeEmpty")
                {
                    tree.MakeEmpty();
                    outFile << "Tree has been made empty." << endl;
                }
                else cout << "Command not found." << endl;
        numCommands++;
        cout << " completed."
        << endl;
        inFile >> command;
    }
    
    cout << "Testing completed."  << endl;
    inFile.close();
    outFile.close();
    return 0;
}
