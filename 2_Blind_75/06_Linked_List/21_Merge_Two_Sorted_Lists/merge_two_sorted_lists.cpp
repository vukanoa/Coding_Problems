/*
    ============
    === EASY ===
    ============

    ===========================
    21) Merge Two Sorted Lists
    ===========================

    ============
    Description:
    ============

    You are given the heads of two sorted linked lists list1 and list2.

    Merge the two lists in a one sorted list. The list should be made by
    splicing together the nodes of the first two lists.

    Return the head o fhte merged linked list.

    ====================================================================
    FUNCTION: ListNode* mergeTwoLists(ListNode* list1, ListNode* list2);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  list1 = [1, 2, 4], list2 = [1, 3, 4]
    Output: [1, 1, 2, 3, 4, 4]

    --- Example 2 ---
    Input:  list1 = [], list2 = []
    Output: []

    --- Example 3 ---
    Input:  list1 = [], list2 = [0]
    Output: [0]

    *** Constraints ***
    The number of nodes in both lists is in the range [0, 50]
    -100 <= Node.val <= 100
    Both list1 and list2 are sorted in non-decreasing order.

*/

// Definition for singly-linked list.
typedef struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
}ListNode;

/*
    ------------
    --- IDEA ---
    ------------

    This is a Fundamental Linked List technique and it's called exactly as the
    name of the problem--"Merge Two Sorted Linked Lists".

    The main idea is to get familiar with the use of "dummy" node that is,
    usually, allocated on the Stack(since it's faster) and it's used to access
    the new head of the merged list.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  27.02% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        // On the Stack
        ListNode dummy(0); // It's faster than ListNode* dummy = new ListNode()
        ListNode* tail = &dummy;

        while (list1 && list2)
        {
            if (list1->val <= list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }

            tail = tail->next;
        }

        if ( ! list1)
            tail->next = list2;
        else
            tail->next = list1;

        return dummy.next;
    }
};
