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

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  29.71% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* middleNode(ListNode* head)
    {
        if (!head || !head->next)
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
