/*
    ============
    === EASY ===
    ============

    ===========================
    141) Linked List Cycle
    ===========================

    ============
    Description:
    ============

    Given "head", the head of a linked list, determine if the linked list has a
    cycle in it.

    There is a cycle in a linked list if there is some node in the list that
    can be reached again by continuously following the "next" pointer.
    Internally, "pos" is used to denote the index of the node that tail's
    "next" pointer is connected to.

    Note that "pos" is not passed as a parameter.

    Return "true" if there is a cycle in the linked list. Otheriwse, return
    "false".

    ========================================
    FUNCTION: bool hasCycle(ListNode *head);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================


    --- Example 1 ---

        3 -> 2 -> 0 -> -4
             ^          |
             |__________|

    Input:  head = [3, 2, 0, -4], pos = 1
    Output: true



    --- Example 2 ---

        1 -> 2
        ^    |
        |____|

    Input:  head = [1, 2], pos = 0
    Output: true



    --- Example 3 ---

        1

    Input:  head = [1], pos = -1
    Output: false

    *** Constraints ***
    The number of the nodes in the list is in the range [0, 10^4]
    -10^5 <= Node.val <= 10^5
    "pos" is -1 or a valid index in the linked list

*/

// Definition for singly-linked list.
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
    ------------
    --- IDEA ---
    ------------

    Fundamental "Linked List" Problem.

    One variation of this problem/teqchnique is to try and find the beginning
    of the cycle.

    Example:

        
        1 --> 2 --> 3 --> 4 ---
              ^               |
              |               |
              |_______________|


    In this case, the BEGINNING of the cycle would be node 2.
    But this technique is done is some other problems.

    It's important to be aware of it.

*/

/* Time  Beats: 97.17% */
/* Space Beats: 53.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool hasCycle(ListNode *head)
    {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true;
        }

        return false;
    }
};
