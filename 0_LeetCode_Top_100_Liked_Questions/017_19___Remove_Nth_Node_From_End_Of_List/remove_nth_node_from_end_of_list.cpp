#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    19) Remove Nth Node From End of List
    ====================================

    ============
    Description:
    ============

    Given the "head" of a linked list, remove the "n-th" node from the end of
    the list and return its head.

    ==========================================================================
    FUNCTION: struct ListNode* removeNthFromEnd(struct ListNode* head, int n);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  head = [1, 2, 3, 4, 5], n = 2
    Output: [1, 2, 3, 5]

    Input:  1 -> 2 -> 3 -> 4 -> 5
    Output: 1 -> 2 -> 3 -> 5



    --- Example 2 ---
    Input:  head = [1], n = 1
    Output: []

    Input:  1
    Output:



    --- Example 3 ---
    Input:  head = [1, 2], n = 1
    Output: [1]

    Input:  1 -> 2
    Output: 1



    --- Example 4 ---
    Input:  head = [1, 2, 3], n = 3
    Output: [2, 3]

    Input:  1 -> 2 -> 3
    Output: 2 -> 3



    *** Constraints ***
    The number of nodes in the list is sz.
    1 <= sz < 30
    0 <= Node.val <= 100
    1 <= n <= sz

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

    Iterate through "n" nodes to the right with "second" pointer and then after
    that - move both "second" and "first" pointer by one node until you hit the
    nullptr with "second" pointer. At that moment we will be "n" nodes from the
    end of a list.

    However, here we have to be on node before that n-th node, so that we can
    relink one node before and after the "n-th node from the end".

    If we have:
        1 -> 2 -> 3
        and n = 3

    then that means that after n nodes to the right the "second" pointer will
    be nullptr. If that's the case, then that means that we need to remove the
    head element, so we need to return head's next;

    If that's not the case, move "second" to the right by one so that once we
    hit the nullptr with "second" pointer, our "first" pointer will be ponting
    to the one we need to remove and thus we will be able to successfully
    relink with:
        first->next = first->next->next;

    Note: Memory leak happens for code is shorter.
*/

/* Time  Beats: 100%   */
/* Space Beats: 91.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if (head == nullptr || head->next == nullptr)
            return nullptr;

        struct ListNode* first = head;
        struct ListNode* second = head;

        for (int i = 0; i < n && second != nullptr; i++)
            second = second->next;

        // If we have to remove the head element
        if (second == nullptr)
            return head->next;
        else
            second = second->next; // So that we can relink

        while (second != nullptr)
        {
            first = first->next;
            second = second->next;
        }

        first->next = first->next->next;

        return head;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely equivalent Idea to the one above, however I think this is much
    more elegant.

    For some reason the "Space Beats" seems worse, but I have no idea why that
    is the case.

    Both Time and Space Complexities are the same.

*/

/* Time  Beats: 100% */
/* Space Beats: 8.95% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode* left  = head;
        ListNode* right = head;

        for (int i = 0; i < n; i++)
            right = right->next;

        // If right is nullptr n is equal to the length of the Linked List and
        // we have to remove the head
        if (right == NULL)
            return head->next;

        while (right->next)
        {
            left  = left->next;
            right = right->next;
        }

        left->next = left->next->next;

        return head;
    }
};


void
print_list(struct ListNode* head)
{
    std::cout << "\n\t[";

    bool first = true;
    while (head)
    {
        if (!first)
            std::cout << " -> ";
        else
            first = false;

        std::cout << head->val;
        head = head->next;
    }

    std::cout << "]\n\n";
}


int
main()
{
    Solution   sol;
    Solution_2 sol2;


    /* Example 1 */
    // struct ListNode five (5);
    // struct ListNode four (4, &five);
    // struct ListNode three(3, &four);
    // struct ListNode two  (2, &three);
    // struct ListNode one  (1, &two);
    // int n = 2;

    /* Example 2 */
    // struct ListNode one(1);
    // int n = 1;

    /* Example 3 */
    // struct ListNode two(2);
    // struct ListNode one(1, &two);
    // int n = 1;

    /* Example 4 */
    struct ListNode three(3);
    struct ListNode two  (2, &three);
    struct ListNode one  (1, &two);
    int n = 3;


    struct ListNode* head = &one;


    std::cout << "\n\t========================================";
    std::cout << "\n\t=== REMOVE NTH NODE FROM END OF LIST ===";
    std::cout << "\n\t========================================\n";


    /* Write Input */
    std::cout << "\n\tOriginal List:";
    print_list(head);


    /* Solution */
    // head = sol.removeNthFromEnd(head, n);
    head = sol2.removeNthFromEnd(head, n);


    /* Write Output */
    if (n == 1)
        std::cout << "\n\tAfter removal of 1st node from the End:";
    else if (n == 2)
        std::cout << "\n\tAfter removal of 2nd node from the End:";
    else if (n == 3)
        std::cout << "\n\tAfter removal of 3rd node from the End:";
    else
        std::cout << "\n\tAfter removal of n-th node from the End:";

    print_list(head);

    return 0;
}
