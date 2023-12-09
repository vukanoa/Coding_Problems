#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    86) Partition List
    ===========================

    ============
    Description:
    ============

    Given the head of a linked list and a value x, partition it such that all
    nodes less than x come before nodes greater than or equal to x.

    You should preserve the original relative order of the nodes in each of the
    two partitions.

    =====================================================
    FUNCTION: ListNode* partition(ListNode* head, int x);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,4,3,2,5,2], x = 3
    Output: [1,2,2,4,3,5]

    --- Example 2 ---
    Input: head = [2,1], x = 2
    Output: [1,2]


    *** Constraints ***
    The number of nodes in the list is in the range [0, 200].
    -100 <= Node.val <= 100
    -200 <= x <= 200

*/

/*
    ------------
    --- IDEA ---
    ------------

    The key here is to notice that you can use dummy nodes.

*/

/* Time  Beats: 79.99% */
/* Space Beats: 9.94% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* partition(ListNode* head, int x)
    {
        if (!head || !head->next)
            return head;

        ListNode dummy_left(0);
        ListNode dummy_right(0);
        dummy_left.next = &dummy_right;

        ListNode* left  = &dummy_left;
        ListNode* right = &dummy_right;

        ListNode* curr = head;
        while (curr)
        {
            ListNode* next;
            next = curr->next;

            if (curr->val < x)
            {
                curr->next = left->next;
                left->next = curr;

                left = left->next;
            }
            else
            {
                curr->next = nullptr;
                right->next = curr;

                right = right->next;
            }

            curr = next;
        }
        left->next = left->next->next; // Remove dummy_right from the Linked List

        return dummy_left.next;
    }
};
