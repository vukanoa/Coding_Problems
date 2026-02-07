/*
    ============
    === EASY ===
    ============

    ===========================
    206) Reverse Linked List
    ===========================

    ============
    Description:
    ============

    Given the "head" of a singly-linked list, reverse the list, and return the
    reversed list.

    ================================================
    FUNCTION: ListNode* reverseList(ListNode* head);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  head = [1, 2, 3, 4, 5]
    Output: [5, 4, 3, 2, 1]

    --- Example 2 ---
    Input:  head = [1, 2]
    Output: [2, 1]

    --- Example 3 ---
    Input:  []
    Output: []

    *** Constraints ***
    The number of nodes in the list is the range [, 5000]
    -5000 <= Node.val <= 5000

    Follow-up: a linked list can be reversed either iterateively or
    recursively. Could you implement both?

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

    Iterative implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  42.01% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Iterative {
public:
    ListNode* reverseList(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr)
        {
            ListNode *next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Recursive implementation. (I HIGHLY suggest you taking a look at the
    Solution_Recursion_2) as it's much easier to understand.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.58% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Recursion_1 {
public:
    ListNode* reverseList(ListNode* head)
    {
        if (head == nullptr)
            return nullptr;

        ListNode* new_head = head;

        if (head->next)
        {
            new_head = reverseList(head->next);
            head->next->next = head;
        }

        head->next = nullptr;

        return new_head;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This implementation is much easier to grasp in my opinion.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  91.85% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Recursion_2 {
public:
    ListNode* reverseList(ListNode* head)
    {
        if ( ! head)
            return nullptr;

        return helper_reverse(nullptr, head);
    }

private:
    ListNode* helper_reverse(ListNode* prev, ListNode* curr)
    {
        ListNode* next = curr->next;
        curr->next = prev;

        if ( ! next)
            return curr;

        return helper_reverse(curr, next);
    }
};
