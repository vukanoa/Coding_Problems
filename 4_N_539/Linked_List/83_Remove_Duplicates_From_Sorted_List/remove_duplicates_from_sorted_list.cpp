#include <iostream>

/*
    ============
    === EASY ===
    ============

    ======================================
    83) Remove Duplicates from Sorted List
    ======================================

    ============
    Description:
    ============

    Given the head of a sorted linked list, delete all duplicates such that
    each element appears only once. Return the linked list sorted as well.

    =====================================================
    FUNCTION: ListNode* deleteDuplicates(ListNode* head);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,1,2]
    Output: [1,2]

    --- Example 2 ---
    Input: head = [1,1,2,3,3]
    Output: [1,2,3]

    *** Constraints ***
    The number of nodes in the list is in the range [0, 300].
    -100 <= Node.val <= 100
    The list is guaranteed to be sorted in ascending order.

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

    It is very very similar to problem:
        (LeetCode 203) "Remove Linked List Elements"

    It is actually a short-version of that problem.

    Since we're promised the List is sorted, the only thing we have to do here
    is to check whether tmp->next exists and if it is the same as tmp->val.

    As long as that's the case, we want out tmp Node's next to point even
    farther.

    That's why we must have an inner "while loop" - We can have more than one
    duplicate.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.04% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode* tmp = head;
        while (tmp && tmp->next)
        {
            while (tmp->next && tmp->next->val == tmp->val)
                tmp->next = tmp->next->next;

            tmp = tmp->next;
        }

        return head;
    }
};
