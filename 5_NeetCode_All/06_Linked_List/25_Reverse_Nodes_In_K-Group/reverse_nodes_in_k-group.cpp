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
        ListNode dummy(-1);
        dummy.next = head;

        ListNode* node_before_group = &dummy;

        while (true)
        {
            // kth_node <==> last_node_of_the_current_group
            ListNode* kth_node = get_kth_node_from(node_before_group, k);

            if (kth_node == nullptr) // There are less than 'k' nodes left
                break;

            ListNode* node_after_group = kth_node->next;

            /* Reverse Linked List(current "group" of 'k' nodes) */
            ListNode* prev = node_after_group;     // This reduces re-linkage
            ListNode* curr = node_before_group->next;

            while (curr != node_after_group)
            {
                ListNode* next = curr->next;

                curr->next = prev;
                prev = curr;
                curr = next;
            }

            ListNode* old_head = node_before_group->next; // Tail of reversed
            ListNode* new_head = prev;                    // Head of reversed

            node_before_group->next = new_head;
            node_before_group       = old_head; // Tail of Reversed group
        }

        return dummy.next;
    }

private:
    ListNode* get_kth_node_from(ListNode* node_before_group, int k)
    {
        ListNode* iter_node = node_before_group;
        while (iter_node && k > 0)
        {
            iter_node = iter_node->next;
            k--;
        }

        return iter_node;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of solving it. Count the total number of nodes and then get
    the remaining_groups.

    Simply go through "remaining_groups" and reverse each one.

    Dummy node is also used here as it facilitates the job.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 69.75% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Counting_Groups {
public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        int remaining_groups = 0;
        int total_nodes = 0;

        /* Count Total Number of Nodes */
        ListNode* iter_node = head;
        while (iter_node) // O(N)
        {
            total_nodes++;

            // Move Forward
            iter_node = iter_node->next;
        }

        /* Create Dummy node */
        ListNode dummy(-1); // Allocated on the Stack
        dummy.next = head;

        /* Prepare for Reversal */
        ListNode* node_before_group = &dummy;
        ListNode* node_after_group  = nullptr; // For now

        remaining_groups = total_nodes / k; // Integer division
        while (remaining_groups > 0) // O(N)
        {
            ListNode* prev = nullptr;
            ListNode* curr = node_before_group->next;

            /* Reverse current "group" of 'k' nodes */
            for (int i = 0; i < k; i++)
            {
                ListNode* next = curr->next;

                curr->next = prev;
                prev = curr;
                curr = next;
            }
            node_after_group = curr;

            ListNode* old_head = node_before_group->next; // Tail of reversed
            ListNode* new_head = prev;                    // Head of reversed

            old_head->next          = node_after_group;
            node_before_group->next = new_head;

            remaining_groups--;

            // Prepare for the next iteration
            node_before_group = old_head; // Tail of reversed group
        }

        return dummy.next;
    }
};
