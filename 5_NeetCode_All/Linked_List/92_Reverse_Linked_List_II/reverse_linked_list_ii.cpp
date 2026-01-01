#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    92) Reverse Linked List II
    ===========================

    ============
    Description:
    ============

    Given the head of a singly linked list and two integers left and right
    where left <= right, reverse the nodes of the list from position left to
    position right, and return the reversed list.

    Follow up: Could you do it in one pass?

    ========================================================================
    FUNCTION: ListNode* reverseBetween(ListNode* head, int left, int right);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,2,3,4,5], left = 2, right = 4
    Output: [1,4,3,2,5]

    --- Example 2 ---
    Input: head = [5], left = 1, right = 1
    Output: [5]


    *** Constraints ***
    The number of nodes in the list is n.
    1 <= n <= 500
    -500 <= Node.val <= 500
    1 <= left <= right <= n

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

    This is a single pass which satisfies "Follow Up" as well.

    Dummy node is the only important part of this Solution. Use it. Do not
    forget that in Linked List problems, it can simplify Solution drastically.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.39% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right)
    {
        if (!head || !head->next || left == right)
            return head;

        ListNode dummy(0);
        dummy.next = head;

        ListNode* tmp = &dummy;
        for (int i = 1; i < left; i++)
            tmp = tmp->next;

        ListNode* before = tmp; // One node before the reversion starting point

        ListNode* prev = tmp;
        ListNode* curr = tmp->next;

        int count = right - left + 1;
        while (count--)
        {
            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        before->next->next = curr;
        before->next = prev;

        return dummy.next;
    }
};
