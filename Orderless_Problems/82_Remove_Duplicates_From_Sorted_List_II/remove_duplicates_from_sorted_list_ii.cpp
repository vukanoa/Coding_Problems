#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    82) Remove Duplicates From Sorted List II
    =========================================

    ============
    Description:
    ============

    Given the head of a sorted linked list, delete all nodes that have
    duplicate numbers, leaving only distinct numbers from the original list.
    Return the linked list sorted as well.

    =====================================================
    FUNCTION: ListNode* deleteDuplicates(ListNode* head);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,2,3,3,4,4,5]
    Output: [1,2,5]

    --- Example 2 ---
    Input: head = [1,1,1,2,3]
    Output: [2,3]


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

/* Time  Beats: 88.66% */
/* Space Beats: 72.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (!head)
            return nullptr;

        ListNode dummy(-101);
        ListNode* prev = &dummy;
        ListNode* curr = head;

        while (curr)
        {
            bool duplicate = false;
            while (curr->next && curr->next->val == curr->val)
            {
                duplicate = true;
                curr = curr->next;
            }

            if (!duplicate)
            {
                prev->next = curr;
                prev = curr;
            }

            curr = curr->next;

            if (!duplicate)
                prev->next = nullptr; // Unlink from the original list
        }

        return dummy.next;
    }
};
