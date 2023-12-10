#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    707) Designed Linked List
    ===========================

    ============
    Description:
    ============

    Design your implementation of the linked list. You can choose to use a
    singly or doubly linked list.  A node in a singly linked list should have
    two attributes: val and next. val is the value of the current node, and
    next is a pointer/reference to the next node.  If you want to use the
    doubly linked list, you will need one more attribute prev to indicate the
    previous node in the linked list. Assume all nodes in the linked list are
    0-indexed.

    Implement the MyLinkedList class:

    MyLinkedList() Initializes the MyLinkedList object.  int get(int index) Get
    the value of the indexth node in the linked list. If the index is invalid,
    return -1.  void addAtHead(int val) Add a node of value val before the
    first element of the linked list. After the insertion, the new node will be
    the first node of the linked list.  void addAtTail(int val) Append a node
    of value val as the last element of the linked list.  void addAtIndex(int
    index, int val) Add a node of value val before the indexth node in the
    linked list. If index equals the length of the linked list, the node will
    be appended to the end of the linked list.  If index is greater than the
    length, the node will not be inserted.  void deleteAtIndex(int index)
    Delete the indexth node in the linked list, if the index is valid.

    ===============================
    CLASS:
    class MyLinkedList {
    public:
        MyLinkedList() {}

        int get(int index)
        {

        }

        void addAtHead(int val)
        {

        }

        void addAtTail(int val)
        {

        }

        void addAtIndex(int index, int val)
        {

        }

        void deleteAtIndex(int index)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get",
    "deleteAtIndex", "get"]
    [[], [1], [3], [1, 2], [1], [1], [1]]
    Output
    [null, null, null, null, 2, null, 3]

    Explanation
    MyLinkedList myLinkedList = new MyLinkedList();
    myLinkedList.addAtHead(1);
    myLinkedList.addAtTail(3);
    myLinkedList.addAtIndex(1, 2);    // linked list becomes 1->2->3
    myLinkedList.get(1);              // return 2
    myLinkedList.deleteAtIndex(1);    // now the linked list is 1->3
    myLinkedList.get(1);              // return 3



    *** Constraints ***
    0 <= index, val <= 1000
    Please do not use the built-in LinkedList library.
    At most 2000 calls will be made to get, addAtHead, addAtTail, addAtIndex and deleteAtIndex.

*/

/* Time  Beats: 82.64% */
/* Space Beats: 66.55% */
struct Node {
    int val;
    Node* next;

    Node(int val)
    {
        this->val = val;
        next = nullptr;
    }
};

class MyLinkedList {
public:
    MyLinkedList() {}

    int get(int index)
    {
        if(index >= size)
            return -1;

        Node* tmp = head;
        for(int i = 0; i < index; ++i)
            tmp = tmp->next;

        return tmp->val;
    }

    void addAtHead(int val)
    {
        Node* new_node = new Node(val);

        new_node->next = head;
        head = new_node;

        if(size == 0)
            tail = new_node;

        size++;
    }

    void addAtTail(int val)
    {
        if(size == 0)
        {
            addAtHead(val);
            return;
        }

        Node* new_node = new Node(val);
        tail->next = new_node;
        tail = new_node;

        size++;
    }

    void addAtIndex(int index, int val)
    {
        if(index > size)
            return;
        else if(index == size)
            addAtTail(val);
        else if(index == 0)
            addAtHead(val);
        else
        {
            Node* tmp =head;
            Node* new_node = new Node(val);
            for(int i = 0; i < index-1; i++)
                tmp = tmp->next;

            new_node->next = tmp->next;
            tmp->next = new_node;
            size++;
        }
    }

    void deleteAtIndex(int index)
    {
        if(index >= size)
            return;
        else if(index == size-1)
        {
            if(index == 0)
            {
                head == nullptr;
                tail == nullptr;
            }
            else
            {
                Node* tmp = head;
                while (tmp->next != tail)
                    tmp = tmp->next;

                tail = tmp;
                tmp->next = nullptr;
            }
        }
        else if(index == 0)
        {
            Node* tmp = head;
            head = head->next;
            tmp = nullptr;
        }
        else
        {
            Node* tmp = head;
            for(int i = 0; i < index-1; ++i)
                tmp = tmp->next;

            Node* t = tmp->next;
            tmp->next = tmp->next->next;
            t->next = nullptr;
        }

        size--;
    }

private:
    int size = 0;

    Node* head = nullptr;
    Node* tail = nullptr;
};
