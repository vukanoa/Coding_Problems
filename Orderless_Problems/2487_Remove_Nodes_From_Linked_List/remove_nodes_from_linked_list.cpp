#include <iostream>
#include <vector>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    2487) Remove Nodes From Linked List
    ===================================

    ============
    Description:
    ============

    You are given the head of a linked list.

    Remove every node which has a node with a greater value anywhere to the
    right side of it.

    Return the head of the modified linked list.

    ================================================
    FUNCTION: ListNode* removeNodes(ListNode* head);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        5 --> 2 --> 13 --> 3 --> 8         ===>      13 -> 8

    Input: head = [5,2,13,3,8]
    Output: [13,8]
    Explanation: The nodes that should be removed are 5, 2 and 3.
    - Node 13 is to the right of node 5.
    - Node 13 is to the right of node 2.
    - Node 8 is to the right of node 3.



    --- Example 2 ---
    Input: head = [1,1,1,1]
    Output: [1,1,1,1]
    Explanation: Every node has value 1, so no nodes are removed.


    *** Constraints ***
    The number of the nodes in the given list is in the range [1, 10^5].
    1 <= Node.val <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    1) Reverse Linked List and count how many nodes there are(num_of_nodes)

    2) Create a vector of size num_of_nodes + 1

    3) Start iterating through the Reversed Linked List and start filling the
       vector from the back.

    4) Reverse Linked List again. (Restoring it to original order)

    5) Create a dummy node

    6) Iterate through the original Linked List and check each time if the
       current value is greater than or equals to the greatest_to_the_right of
       that node. If it is, then include it in our new Linked List whose "head"
       is pointed to by a dummy.next

    7) Return dummy.next




    As for 2)
        The reason we're creating a vector of size num_of_nodes + 1 is to make
        our lives easy by not having to check the edge-case(i.e. if the current
        node is the last one)

    As for 3)
        We are iterating through a REVERSED Linked List from the front, while
        we are iterating through the vector from the back, however in the
        vector, we are starting from num_of_nodes-1 position and not
        num_of_nodes, because as we've said in 2), we are having +1 element
        because we want to skip checking the edge case.

*/

/* Time  Beats: 94.03% */
/* Space Beats: 72.49% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_1 {
public:
    ListNode* removeNodes(ListNode* head)
    {
        int num_of_nodes = 0;
        head = reverse_linked_list(head, num_of_nodes);

        std::vector<int> greatest_to_the_right(num_of_nodes + 1, 0);

        int i = num_of_nodes - 1;
        ListNode* tmp = head;
        while (tmp)
        {
            greatest_to_the_right[i] = std::max(tmp->val, greatest_to_the_right[i+1]);

            tmp = tmp->next;
            i--;
        }

        num_of_nodes = 0;
        head = reverse_linked_list(head, num_of_nodes);

        ListNode dummy(0);
        ListNode* curr = &dummy;

        i = 0;
        while (head)
        {
            if (head->val >= greatest_to_the_right[i])
            {
                curr->next = head;
                curr = head;
            }

            head = head->next;
            i++;
        }

        return dummy.next;
    }

private:
    ListNode* reverse_linked_list(ListNode* head, int& num_of_nodes)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr)
        {
            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;

            num_of_nodes++;
        }

        return prev;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    One approach is to traverse the linked list and maintain a stack to store
    nodes in non-decreasing order of their values. While traversing, if we
    encounter a node with a value greater than the top element of the stack, we
    pop elements from the stack until the condition is met. This ensures that
    the stack contains only nodes with the highest values seen so far. Finally,
    we reverse the stack to get the modified linked list.


    1. Initialize a stack to store nodes in non-increasing order of their
       values.

    2. Traverse the linked list:
        + If the current node's value is greater than the top element of the
          stack, pop elements from the stack until the condition is met.

        + Push the current node onto the stack.

    3. Reverse the stack to obtain the modified linked list.

    4. Return the head of the modified linked list.

*/

/* Time  Beats: 76.34% */
/* Space Beats: 44.51% */

/*
    Time  Complexity: O(n)

    Outer while: O(n)
    Inner while: O(n - k), where k is length of resultand linked list
    Stack while: O(k)

    Total Time complexity: O(n) + O(n-k) + O(k) = O(2n) -> O(n). This is a
                           linear 2 pass solution.

    Note: Even though there is nested while loop TC is O(n) because a node is
          pushed and popped from the stack at most once.

*/
/* Space Complexity: O(n) */
class Solution_2 {
public:
    ListNode* removeNodes(ListNode* head)
    {
        std::stack<ListNode*> stack;

        ListNode* curr = head;
        while (curr)
        {
            while (!stack.empty() && stack.top()->val < curr->val)
                stack.pop();

            stack.push(curr);
            curr = curr->next;
        }

        ListNode* next = nullptr;
        while ( ! stack.empty())
        {
            curr = stack.top();
            stack.pop();

            curr->next = next;
            next = curr;
        }

        return curr;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We can use recursion to traverse the linked list and at each step, we
    compare the current node's value with the value of the next greater node.
    If the next greater node has a value less than the current node, we keep
    the current node; otherwise, we skip the current node.


    1. Recursively traverse the linked list.

    2. At each step, compare the current node's value with the value of the
       next greater node.

    3. If the next greater node has a value less than the current node, keep
       the current node; otherwise, skip the current node.

    4. Return the head of the modified linked list.

*/

/* Time  Beats: 82.82% */
/* Space Beats: 72.49% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_3 {
public:
    ListNode* removeNodes(ListNode* head)
    {
        if ( ! head)
            return nullptr;

        ListNode* node = head;
        ListNode* next_greater = removeNodes(node->next);

        node->next = next_greater;
        if ( ! next_greater || node->val >= next_greater->val)
            return node;

        return next_greater;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is similar to Solution 1, however this one doesn't use any extra
    Space.

    We can reverse the given linked list first. Then we traverse the reversed
    list, keeping nodes whose values are greater than or equal to the previous
    node's value. After traversing, we reverse the resulting list to obtain the
    modified linked list.

    1. Reverse the given linked list.

    2. Initialize a dummy node to hold the result.

    3. Traverse the reversed list, keeping nodes whose values are greater
       than or equal to the previous node's value.

    4. Reverse the resulting list to obtain the modified linked list.

    5. Return the head of the modified linked list.

*/

/* Time  Beats: 97.11% */
/* Space Beats: 90.63% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_4 {
public:
    ListNode* removeNodes(ListNode* head)
    {
        ListNode* prev = nullptr;
        head = reverse_linked_list(head);

        ListNode  dummy(-1);
        ListNode* tmp_prev = &dummy;

        while (head)
        {
            if (head->val >= tmp_prev->val)
            {
                tmp_prev->next = head;
                tmp_prev = head;
                head = head->next;
            }
            else
                head = head->next;
        }
        tmp_prev->next = nullptr;

        // Reverse Newly Linked List
        return reverse_linked_list(dummy.next);
    }

private:
    ListNode* reverse_linked_list(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr)
        {
            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};
