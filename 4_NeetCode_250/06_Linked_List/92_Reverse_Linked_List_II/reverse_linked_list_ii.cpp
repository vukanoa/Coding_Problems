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

    This is a single pass which satisfies "Follow Up" as well.

    Dummy node is the only important part of this Solution. Use it. Do not
    forget that in Linked List problems, it can simplify Solution drastically.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.59% */

/* Time  Complexity: O(N) */ // One Pass
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right)
    {
        if (left == right)
            return head;

        ListNode dummy(-1);
        dummy.next = head; // Link with "head"

        ListNode* before_left = &dummy;
        ListNode* after_right = nullptr; // For now

        for (int i = 1; i < left ; i++)
        {
            // Move forward
            before_left = before_left->next;
        }

        /* Reverse Linked List */
        ListNode* prev = before_left;
        ListNode* curr = before_left->next;

        while (left <= right)
        {
            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;

            // Increment
            left++;
        }
        after_right = curr;

        ListNode* head_of_reversed_list = prev;
        ListNode* tail_of_reversed_list = before_left->next;

        // It MUST be in this order
        tail_of_reversed_list->next = after_right;
        before_left->next           = head_of_reversed_list;

        return dummy.next;
    }
};
