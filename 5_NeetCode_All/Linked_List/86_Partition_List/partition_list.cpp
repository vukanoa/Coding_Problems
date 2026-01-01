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

/* Time  Beats: 100.00% */
/* Space Beats:  33.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* partition(ListNode* head, int x)
    {
        if (!head || !head->next)
            return head;

        ListNode dummy_head(0);
        ListNode dummy_x(x);

        dummy_head.next = &dummy_x;

        ListNode* left_tail  = &dummy_head;
        ListNode* right_tail = &dummy_x;

        while (head)
        {
            ListNode* next = head->next;

            if (head->val < x)
            {
                head->next = &dummy_x;
                left_tail->next = head;

                left_tail = left_tail->next;
            }
            else
            {
                head->next = nullptr;
                right_tail->next = head;

                right_tail = right_tail->next;
            }

            head = next;
        }
        left_tail->next = dummy_x.next;

        return dummy_head.next;
    }
};
