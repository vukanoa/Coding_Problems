/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2) Add Two Numbers
    ===========================

    ============
    Description:
    ============

    You are given two non-empty linked lists representing two non-negative
    integers. The digits are stored in reverse order, and each of their nodes
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
    Input l1 = [2, 4, 3], l2 = [5, 6, 4]
    Output   = [7, 0, 8]
    Explanation: 342 + 465 + 807

    2 -> 4 -> 3
    5 -> 6 -> 4
    -----------
    7 -> 0 -> 8


    --- Example 2 ---
    Input l1 = [0], l2 = [0]
    Output   = [0]

    0
    0
    -----------
    0


    --- Example 3 ---
    Input l1 = [9, 9, 9, 9, 9, 9, 9], l2 = [9, 9, 9, 9]
    Output   = [8, 9, 9, 9, 0, 0, 0, 1]

    9 -> 9 -> 9 -> 9 -> 9 -> 9 -> 9
    9 -> 9 -> 9 -> 9
    -----------
    8 -> 9 -> -> 9 -> 9 -> 0 -> 0 -> 1


    *** Constraints ***
    The number of nodes in each linked list is in the range [1, 100]
    0 <= Node.val <= 9
    It is guaranteed that the list represents a number that does not have
    leading zeros.

*/

/* Definition for singly-linked list */
struct ListNode {
     int val;
     ListNode *next;

     // Constructors
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
    ------------
    --- IDEA ---
    ------------

    We make a dummy node on the Stack and initialize it with any value;
    We take the "tail" pointer to point at this "dummy node".

    Now as long as we haven't iterated through both lists(they can be of
    different sizes) or "carry" is != 0)

    Do the self-explanatory algorithm in the "while loop".

    After the "while loop" is finished, return "dummy head"'s next pointer
    points at the beginning of our list that we're required to return.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  73.87% */

/* Time  Complexity: O(M + N) */
/* Space Complexity: O(1)     */ // List we return is not "extra" Space
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode dummy(-1);
        ListNode* tail = &dummy;

        int carry = 0;

        // O(max(M, N)) (entire block)
        while (l1 || l2 || carry)
        {
            int l1_val = l1 ? l1->val : 0;
            int l2_val = l2 ? l2->val : 0;

            int sum = l1_val + l2_val + carry;

            ListNode* new_node = new ListNode(sum % 10); // digit <==> sum % 10
            carry = sum / 10;

            tail->next = new_node; // Link next digit

            // Move forward
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
            tail = tail->next;
        }

        return dummy.next;
    }
};
