#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    147) Insertion Sort List
    ===========================

    ============
    Description:
    ============

    Given the head of a singly linked list, sort the list using insertion sort,
    and return the sorted list's head.

    The steps of the insertion sort algorithm:

        1. Insertion sort iterates, consuming one input element each repetition
           and growing a sorted output list.

        2. At each iteration, insertion sort removes one element from the input
           data, finds the location it belongs within the sorted list and
           inserts it there.

        3. It repeats until no input elements remain.


    ======================================================
    FUNCTION: ListNode* insertionSortList(ListNode* head);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [4,2,1,3]
    Output: [1,2,3,4]

    --- Example 2 ---
    Input: head = [-1,5,3,4,0]
    Output: [-1,0,3,4,5]


    *** Constraints ***
    The number of nodes in the list is in the range [1, 5000].
    -5000 <= Node.val <= 5000

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

    It becomes very easy once you see that you can utilize a "dummy" node.

*/

/* Time  Beats: 60.20% */
/* Space Beats: 49.09% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* insertionSortList(ListNode* head)
    {
        ListNode dummy(0);

        ListNode* curr = head;
        while (curr)
        {
            ListNode* next = curr->next;
            ListNode* prev = &dummy;

            while (prev->next && prev->next->val < curr->val)
                prev = prev->next;

            curr->next = prev->next;
            prev->next = curr;
            curr = next;
        }

        return dummy.next;
    }
};
