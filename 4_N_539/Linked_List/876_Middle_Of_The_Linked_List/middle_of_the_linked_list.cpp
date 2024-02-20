#include <iostream>

/*
    ============
    === EASY ===
    ============

    ==============================
    876) Middle of the Linked List
    ==============================

    ============
    Description:
    ============

    Given the head of a singly linked list, return the middle node of the
    linked list.

    If there are two middle nodes, return the second middle node.

    ===============================================
    FUNCTION: ListNode* middleNode(ListNode* head);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,2,3,4,5]
    Output: [3,4,5]
    Explanation: The middle node of the list is node 3.

    --- Example 2 ---
    Input: head = [1,2,3,4,5,6]
    Output: [4,5,6]
    Explanation: Since the list has two middle nodes with values 3 and 4, we
                 return the second one.


    *** Constraints ***
    The number of nodes in the list is in the range [1, 100].
    1 <= Node.val <= 100

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
    ------------
    --- IDEA ---
    ------------

    We're told that "the number of nodes in the list is in the rnage [1, 100]",
    therefore, we don't check if (!head), only if (!head->next).

    Also, notice which node do they want us to return as a "middle node".

    It depends on that if we need to start our "fast" pointer from "head" or
    from "head->next".

    In this case, since they are asking us to return this one, from the list:
                                                      |
                                                      |
                                   ___________________|
                                   |
                                   v
                    1 -> 2 -> 3 -> 4 -> 5 -> 6


    It's important to node that this is DIFFERENT than the usual function we're
    writing for Linked List problems when we are looking for the "middle node".

    Usually we have a need to "unlink" two parts and thus the "middle node" is
    not 4, but 3, since we want to have two equals halves.

    In that usual function we'd initialize our "fast" pointer to "head->next",
    however now, since they want us to return 4 from this list, we have to
    initialize "fast" to "head->next".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  29.71% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* middleNode(ListNode* head)
    {
        if (!head->next)
            return head;

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
};
