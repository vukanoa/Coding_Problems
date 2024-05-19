#include <iostream>

/*
    ============
    === EASY ===
    ============

    =======================================================
    1290) Convert Binary Number in a Linked List to Integer
    =======================================================

    ============
    Description:
    ============

    Given head which is a reference node to a singly-linked list. The value of
    each node in the linked list is either 0 or 1. The linked list holds the
    binary representation of a number.

    Return the decimal value of the number in the linked list.

    The most significant bit is at the head of the linked list.

    ==============================================
    FUNCTION: int getDecimalValue(ListNode* head);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        1 --> 0 --> 1

    Input: head = [1,0,1]
    Output: 5
    Explanation: (101) in base 2 = (5) in base 10


    --- Example 2 ---
    Input: head = [0]
    Output: 0


    *** Constraints ***
    The Linked List is not empty.
    Number of nodes will not exceed 30.
    Each node's value is either 0 or 1.

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

    1. Reverse a given Linked List.

    2. Initialize degree to 0.

    3. Start iterating through the Reverse Linked List and each time you're on
       the node with value 1, add 2 to the power of the current value of
       variable degree.

    4. After each iteration increment degree so that it matches the binary
       representation of that bit.

    5. Return "result".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int getDecimalValue(ListNode* head)
    {
        head = reverse_linked_list(head);

        int degree = 0;
        int result = 0;
        while (head)
        {
            if (head->val == 1)
                result += 1 << degree;

            degree++;
            head = head->next;
        }

        return result;
    }

private:
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
};
