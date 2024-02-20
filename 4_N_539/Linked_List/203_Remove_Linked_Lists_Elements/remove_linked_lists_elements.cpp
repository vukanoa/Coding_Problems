#include <iostream>

/*
    ============
    === EASY ===
    ============

    =================================
    203) Remove Linked Lists Elements
    =================================

    ============
    Description:
    ============

    Given the head of a linked list and an integer val, remove all the nodes of
    the linked list that has Node.val == val, and return the new head.

    ============================================================
    FUNCTION: ListNode* removeElements(ListNode* head, int val);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,2,6,3,4,5,6], val = 6
    Output: [1,2,3,4,5]


    --- Example 2 ---
    Input: head = [], val = 1
    Output: []


    --- Example 3 ---
    Input: head = [7,7,7,7], val = 7
    Output: []


    *** Constraints ***
    The number of nodes in the list is in the range [0, 104].
    1 <= Node.val <= 50
    0 <= val <= 50

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

    The only "tricky" thing here is if the "val" is at the beginning and/or it
    repeats multiple times.

    If it is at the beginning we must "cut off" all of those elements first.
    We do that with:

        while (head && head->val == val)
            head = head->next;

    Once that is done, all we do is - While tmp->next is not nullptr(tmp also
    since we don't want to get a Segmentation Fault) we are checking if the

        tmp->next->val

    is the value we want to skip.

    One more thing that needs to be noted here is that there can be multiple
    **consecutive** values that we want to skip, therefore we must have an
    inner "while loop".

    That won't make it O(n^2) since we will, still, iterate through the entire
    Linked List only once.

    Example:
        1 -> 2 -> 3 -> -> 3 -> -> 3 -> 4 -> 5

    If we want to remove Element '3', we must do it within an inner loop.

*/

/* Time  Beats: 98.93% */
/* Space Beats: 44.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val)
    {
        if (!head)
            return nullptr;

        while (head && head->val == val)
            head = head->next;

        ListNode* tmp = head;
        while (tmp && tmp->next)
        {
            while (tmp->next && tmp->next->val == val)
                tmp->next = tmp->next->next;

            tmp = tmp->next;
        }

        return head;
    }
};
