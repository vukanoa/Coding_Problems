/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    445) Add Two Numbers II
    ===========================

    ============
    Description:
    ============

    You are given two non-empty linked lists representing two non-negative
    integers. The most significant digit comes first and each of their nodes
    contains a single digit. Add the two numbers and return the sum as a linked
    list.

    You may assume the two numbers do not contain any leading zero, except the
    number 0 itself.

    ==============================================================
    FUNCTION: ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: l1 = [7,2,4,3], l2 = [5,6,4]
    Output: [7,8,0,7]

    --- Example 2 ---
    Input: l1 = [2,4,3], l2 = [5,6,4]
    Output: [8,0,7]

    --- Example 3 ---
    Input: l1 = [0], l2 = [0]
    Output: [0]

    *** Constraints ***
    The number of nodes in each linked list is in the range [1, 100].
    0 <= Node.val <= 9
    It is guaranteed that the list represents a number that does not hav
    leading zeros.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 58.21% */
/* Space Beats: 61.68% */

/* Time  Complexity: O(M + N) */
/* Space Complexity: O(M + N) */

/**
 * Definition for singly-linked list.
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* reveresed_l1 = reverse_list(l1);
        ListNode* reversed_l2 = reverse_list(l2);

        int total_sum = 0;
        int carry = 0;
        ListNode* result = new ListNode();

        while (reveresed_l1 || reversed_l2)
        {
            if (reveresed_l1)
            {
                total_sum += reveresed_l1->val;
                reveresed_l1 = reveresed_l1->next;
            }

            if (reversed_l2)
            {
                total_sum += reversed_l2->val;
                reversed_l2 = reversed_l2->next;
            }

            result->val = total_sum % 10;
            carry = total_sum / 10;

            ListNode* head = new ListNode(carry);
            head->next = result;

            result = head;
            total_sum = carry;
        }

        return carry == 0 ? result->next : result;
    }

private:
    ListNode* reverse_list(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* tmp;

        while (head)
        {
            // Keep the next node.
             tmp = head->next;

            // Reverse the link
            head->next = prev;

            // Update the previous node and the current node.
            prev = head;
            head = tmp;
        }

        return prev;
    }
};
