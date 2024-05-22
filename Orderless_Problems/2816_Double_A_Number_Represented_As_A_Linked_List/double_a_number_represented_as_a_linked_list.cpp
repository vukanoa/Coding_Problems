#include <iostream>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    2816) Double a Number Represented as a Linked List
    ==================================================

    ============
    Description:
    ============

    You are given the head of a non-empty linked list representing a
    non-negative integer without leading zeroes.

    Return the head of the linked list after doubling it.

    =============================================
    FUNCTION: ListNode* doubleIt(ListNode* head);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        1 --> 8 --> 9

    Input: head = [1,8,9]
    Output: [3,7,8]
    Explanation: The figure above corresponds to the given linked list which
                 represents the number 189. Hence, the returned linked list
                 represents the number 189 * 2 = 378.


    --- Example 2 ---

        9 --> 9 --> 9

    Input: head = [9,9,9]
    Output: [1,9,9,8]
    Explanation: The figure above corresponds to the given linked list which
                 represents the number 999. Hence, the returned linked list
                 reprersents the number 999 * 2 = 1998.


    *** Constraints ***
    The number of nodes in the list is in the range [1, 10^4]
    0 <= Node.val <= 9
    The input is generated such that the list represents a number that does not
    have leading zeros, except the number 0 itself.

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

    1. Reverse Original Linked List

    2. Repeat the while loop as long as head isn't nullptr or carry > 0 or both

    3. num = head ? head->val : 0;
       Ensures that this part won't Seg. fault if head is nullptr.

    4. num <<= 1;    // Multiply current value by 2

    5. num += carry; // Add carry

    6. Create a new Linked List node with a value that is num % 10;

    7. carry becomes num / 10.

    8. Move head to the next node. (If head is currently nullptr, then let it
       stay that way)

    9. Make tmp_prev->next to point to a newly created node "new_node" and move
       tmp_prev to point to "new_node".

    10. At the end reverse a newly linked list that is pointed to by our dummy
        node and return that. (i.e. return reverse_linked_list(dummy.next))

*/

/* Time  Beats: 39.15% */
/* Space Beats: 33.45% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* doubleIt(ListNode* head)
    {
        if (head->val == 0)
            return head;

        ListNode  dummy(-1);
        ListNode* tmp_prev = &dummy;

        // Reverse Original Linked List
        head = reverse_linked_list(head);

        int carry = 0;
        while (head || carry > 0)
        {
            int num = head ? head->val : 0;
            num <<= 1; // num *= 2
            num += carry;

            ListNode* new_node = new ListNode(num % 10);
            carry = num / 10;

            head = head ? head->next : nullptr;

            tmp_prev->next = new_node;
            tmp_prev = tmp_prev->next;
        }

        // Reverse Newly created Linked List so that it matches desired format
        return reverse_linked_list(dummy.next);
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
