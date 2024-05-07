#include <iostream>
#include <vector>

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
class Solution {
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
