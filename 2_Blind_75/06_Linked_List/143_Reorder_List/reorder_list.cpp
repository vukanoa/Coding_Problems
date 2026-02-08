/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    143) Reorder List
    ===========================

    ============
    Description:
    ============

    You are given the head of a singly linked-list. The list can be represented
    as:
        L0 -> L1 -> ... -> Ln - 1 -> Ln

    Reorder the list to be on the following form:
        L0 -> Ln -> L1 -> Ln - 1 -> L2 -> Ln - 2 -> ...

    You may not modify the values in the list's nodes. Only nodes themselves
    may be changed.

    ===========================================
    FUNCTION: void reorderList(ListNode* head);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    1 --> 2 --> 3 --> 4

             |
             |
             V

    1 --> 4 --> 2 --> 3

    Input: head = [1,2,3,4]
    Output: [1,4,2,3]






    --- Example 2 ---
    1 --> 2 --> 3 --> 4 --> 5

             |
             |
             V

    1 --> 5 --> 2 --> 4 --> 3

    Input: head = [1,2,3,4,5]
    Output: [1,5,2,4,3]





    *** Constraints ***
    The number of nodes in the list is in the range [1, 5 * 10^4].
    1 <= Node.val <= 1000

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

    This is a Linked list problem which uses 3 fundamental techniques for
    "Linked List" problems:

        1. Find middle node(try lists with both odd and even lengths)

        2. Reverse a linked list

        3. Merge two lists in an alternating fashion

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    void reorderList(ListNode* head)
    {
        // Find mid node
        ListNode* mid_node = find_mid_node(head);

        // Start of the 2nd half
        ListNode* head2 = mid_node->next;

        // Unlink two halves
        mid_node->next = nullptr;

        // Reverse 2nd half
        head2 = reverse_linked_list(head2);

        // Merge alternating
        head = merge_alternating(head, head2);
    }

private:
    ListNode* find_mid_node(ListNode* head)
    {
        ListNode* slow = head;
        ListNode* fast = head->next; // "head' is NEVER nullptr

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverse_linked_list(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr)
        {
            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }

    ListNode* merge_alternating(ListNode* head1, ListNode* head2)
    {
        ListNode dummy(-1);
        ListNode* tail = &dummy;

        bool turn = true; // True - head1, False - head2
        while (head1 || head2)
        {
            if (turn)
            {
                tail->next = head1;
                head1 = head1->next;
            }
            else
            {
                tail->next = head2;
                head2 = head2->next;
            }

            tail = tail->next;
            turn = ! turn; // Toggle
        }

        return dummy.next;
    }
};
