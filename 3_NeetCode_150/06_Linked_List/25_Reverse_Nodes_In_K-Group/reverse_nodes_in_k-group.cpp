/*
    ============
    === HARD ===
    ============

    ============================
    25) Reverse Nodes in k-Group
    ============================

    ============
    Description:
    ============

    Given the "head" of a linked list, reverse the nodes of the list "k" at a
    time, and return the modified list.

    "k" is a positive integer and is less than or equal to the length of the
    linked list. If the number of nodes is not a multiple of "k" then left-out
    nodes, in the end, should remain as it is.

    You may not alter the values in the list's nodes, only nodes themselves
    may be changed.

    =========================================================
    FUNCTION: ListNode* reverseKGroup(ListNode* head, int k);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  head = [1, 2, 3, 4, 5], k = 2
    Output: [2, 1, 4, 3, 5]

    --- Example 2 ---
    Input:  head = [1, 2, 3, 4, 5], k = 3
    Output: [3, 2, 1, 4, 5]

    *** Constraints ***
    The number of nodes in the list is "n".
    1 <= k <= n <= 5000
    0 <= Node.val <= 1000

*/


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.74% */
/* Space Beats: 15.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        ListNode* dummy = new ListNode(0, head);
        ListNode* group_prev = dummy;

        for(;;)
        {
            ListNode* kth = get_kth(group_prev, k);

            if (!kth)
                break;
            ListNode* group_next = kth->next;

            /* Reverse Linked List */
            ListNode* prev = kth->next;
            ListNode* curr = group_prev->next;

            while (curr != group_next)
            {
                ListNode* next = curr->next;

                curr->next = prev;
                prev = curr;
                curr = next;
            }

            /* Crucial part */
            ListNode* tmp = group_prev->next;
            group_prev->next = kth;
            group_prev = tmp;

        }

        return dummy->next;
    }

private:
    ListNode* get_kth(ListNode* group_prev, int k)
    {
        ListNode* tmp = group_prev;
        while (tmp && k > 0)
        {
            tmp = tmp->next;
            k--;
        }

        return tmp;
    }
};
