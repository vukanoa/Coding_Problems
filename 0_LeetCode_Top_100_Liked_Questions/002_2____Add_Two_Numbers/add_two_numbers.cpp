#include <iostream>

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

    We make a dummy node and initialize it with 0.
    "dummy_head" and "curr" point to this dummy node.

    Now as long as we haven't iterated through both lists(they can be of
    different sizes) or "carry" is != 0)

    do the self-explanatory algorithm in the "while loop".

    After the "while loop" is finished, return dummy_head->next, since we don't
    want the leading zero.

*/


/* Time  Beats: 64.29% */
/* Space Beats: 56.39% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode  dummy(0); // On the stack
        ListNode* curr = &dummy;

        int carry = 0;

        while (l1 || l2 || carry != 0)
        {
            int a = l1 ? l1->val : 0;
            int b = l2 ? l2->val : 0;

            int number = a + b + carry;

            int digit = number % 10;
            carry = number / 10;

            curr->next = new ListNode(digit);
            curr = curr->next;

            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        return dummy.next;
    }
};


void
print_list(ListNode* head)
{
    bool first = true;
    while (head != NULL)
    {
        if (!first)
            std::cout << " -> ";

        std::cout << head->val;
        first = false;

        head = head->next;
    }
}


int
main()
{
    Solution sol;

    /* Example 1 */
    ListNode *l1_3 = new ListNode(3);
    ListNode *l1_2 = new ListNode(4, l1_3);
    ListNode *l1   = new ListNode(2, l1_2);

    ListNode *l2_3 = new ListNode(4);
    ListNode *l2_2 = new ListNode(6, l2_3);
    ListNode *l2   = new ListNode(5, l2_2);


    /* Example 2 */
    // ListNode *l1   = new ListNode(0);
    // ListNode *l2   = new ListNode(0);


    /* Example 3 */
    // ListNode *l1_7 = new ListNode(9);
    // ListNode *l1_6 = new ListNode(9, l1_7);
    // ListNode *l1_5 = new ListNode(9, l1_6);
    // ListNode *l1_4 = new ListNode(9, l1_5);
    // ListNode *l1_3 = new ListNode(9, l1_4);
    // ListNode *l1_2 = new ListNode(9, l1_3);
    // ListNode *l1   = new ListNode(9, l1_2);

    // ListNode *l2_4 = new ListNode(9);
    // ListNode *l2_3 = new ListNode(9, l1_4);
    // ListNode *l2_2 = new ListNode(9, l1_3);
    // ListNode *l2   = new ListNode(9, l1_2);

    std::cout << "\n\t=======================";
    std::cout << "\n\t=== ADD TWO NUMBERS ===";
    std::cout << "\n\t=======================\n";


    /* Write Input */
    std::cout << "\n\t    ";
    print_list(l1);

    std::cout << "\n\t+   ";
    print_list(l2);

    std::cout << "\n\t---------------";
    std::cout << "\n\t    ";

    /* Solution */
    ListNode *l3 = sol.addTwoNumbers(l1, l2);

    /* Write Input */
    print_list(l3);
    std::cout << "\n\n\n";

    return 0;
}
