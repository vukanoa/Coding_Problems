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


/*
    ------------
    --- IDEA ---
    ------------

    The only thing that is difficult here is to come up with a "dummy node".
    However, once you know about the general trick for Linked List problems,
    i.e. using a "dummy node", then it becomes straightforward.

    The rest of the Solution is intuitive. It's not a trick or technique, it's
    just logic.

    Therefore, once you start using a "dummy node", you should be able to come
    up with this Solution. (Or the 2nd one down below).

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




/*
    ------------
    --- IDEA ---
    ------------

    Here, again, the whole point is to know about the "dummy node" trick. Once
    you do that, then there are myriad of ways to solve it.

    This is another way. It's more concise.

*/

/* Time  Beats: 88.66% */
/* Space Beats: 22.26% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
       ListNode dummy(-101, head);
       ListNode *prev = &dummy;

        while (head)
        {
            if(head->next && head->next->val == head->val)
            {
                while (head->next && head->next->val == head->val)
                    head = head->next;

                prev->next=head->next;
            }
            else
                prev = prev->next;

            head = head->next;
        }

        return dummy.next;
    }
};
