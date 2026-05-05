/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    61) Rotate List
    ===========================

    ============
    Description:
    ============

    Given the head of a linked list, rotate the list to the right by k places.

    =======================================================
    FUNCTION: ListNode* rotateRight(ListNode* head, int k);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    1 --> 2 --> 3 --> 4 --> 5

    5 --> 1 --> 2 --> 3 --> 4 // Rotate 1

    4 --> 5 --> 1 --> 2 --> 3 // Rotate 2

    Input: head = [1,2,3,4,5], k = 2
    Output: [4,5,1,2,3]




    --- Example 2 ---
    0 --> 1 --> 2

    2 --> 0 --> 1 // Rotate 1

    1 --> 2 --> 0 // Rotate 2

    0 --> 1 --> 2 // Rotate 3

    2 --> 0 --> 1 // Rotate 4 (Same as Rotate 1)
    Input: head = [0,1,2], k = 4
    Output: [2,0,1]




    *** Constraints ***
    The number of nodes in the list is in the range [0, 500].
    -100 <= Node.val <= 100
    0 <= k <= 2 * 109

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

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.62% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k)
    {
        if (head == nullptr || head->next == nullptr || k == 0)
            return head;

        int total_nodes = 0;
        ListNode* node = head;
        while (node)
        {
            total_nodes++;
            node = node->next;
        }

        k %= total_nodes;

        if (k == 0)
            return head;

        ListNode dummy(0); // Allocated on the Stack
        dummy.next = head;

        ListNode* left  = &dummy;
        ListNode* right = &dummy;

        /* Move right node exactly 'k' steps in */
        for (int i = 0; i < k; i++)
            right = right->next;

        while (right->next)
        {
            left  = left->next;
            right = right->next;
        }

        ListNode* new_head = left->next;

        left->next  = nullptr; // Unlink
        right->next = head;    // Add New Link

        return head = new_head;
    }
};
