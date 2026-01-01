#include <iostream>

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

    When you look at this example:

        1 --> 2 --> 3 --> 4 --> 5

                 |
                 |
                 V

        1 --> 5 --> 2 --> 4 --> 3


    Since we need to alternate, it's like we need two merge two lists. But if
    we were to just merge two halves, we'd get this:

        1 --> 2 --> 3 --> 4 --> 5

                 |
                 |
                 V

        1 --> 4 --> 2 --> 5 --> 3

    Which is incorrect. Why? Because we're trying to merge two halves in their
    given order, but we're told that we need to alternate:
        front, back, front, back, front, ...

    So when we look at the desired output again:
        1 --> 5 --> 2 --> 4 --> 3


    We can see that we want to merge two halves with alternating values, but
    we're not merging the 2nd half from the beginning, but from the back.
    The 2nd half needs to be merged FROM THE BACK.

    As soon as wee see that, it becomes obvious that we need to reverse the 2nd
    list and the merge two halves.

    Solution:
    1. Find the middle node
    2. Unlink two halves
    3. Reverse the 2nd half
    4. Merge two halves

*/

/* Time  Beats: 97.96% */
/* Space Beats: 83.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    void reorderList(ListNode* head)
    {
        ListNode* left_tail  = middle(head);
        ListNode* right_head = left_tail->next;

        // Unlink
        left_tail->next = nullptr;

        // Reverse "right"(second) list
        right_head = reverse_list(right_head);

        // Merge two lists alternating
        merge_alternating(head, right_head);
    }

private:
    ListNode* middle(ListNode* head)
    {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverse_list(ListNode* head)
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

    void merge_alternating(ListNode* list1, ListNode* list2)
    {
        while (list1 != nullptr && list2 != nullptr)
        {
            ListNode* list1_next = list1->next;
            ListNode* list2_next = list2->next;

            list1->next = list2;
            list2->next = list1_next;

            list1 = list1_next;
            list2 = list2_next;
        }
    }
};
