#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    1721) Swapping Nodes In A Linked List
    =====================================

    ============
    Description:
    ============

    You are given the head of a linked list, and an integer k.

    Return the head of the linked list after swapping the values of the kth
    node from the beginning and the kth node from the end (the list is
    1-indexed).

    =====================================================
    FUNCTION: ListNode* swapNodes(ListNode* head, int k);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,2,3,4,5], k = 2
    Output: [1,4,3,2,5]

    --- Example 2 ---
    Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
    Output: [7,9,6,6,8,7,3,0,9,5]


    *** Constraints ***
    The number of nodes in the list is n.
    1 <= k <= n <= 10^5
    0 <= Node.val <= 100

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

    Classical Two-Pointers technique for Linked Lists.
    It's important to say that we CAN modify values, we don't have to relink
    this Linked List.

*/

/* Time  Beats: 91.55% */
/* Space Beats: 33.40% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* swapNodes(ListNode* head, int k)
    {
        if (!head->next)
            return head;

        ListNode* left = head;
        for (int i = 1; i < k; i++)
            left = left->next;

        ListNode* right = head;
        ListNode* tmp   = left;

        while (tmp->next)
        {
            right = right->next;
            tmp = tmp->next;
        }

        std::swap(left->val, right->val);

        return head;
    }
};
