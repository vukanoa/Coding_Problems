#include <iostream>

/*
    ============
    === EASY ===
    ============

    ===========================
    206) Reverse Linked List
    ===========================

    ============
    Description:
    ============

    Given the "head" of a singly-linked list, reverse the list, and return the
    reversed list.

    ================================================
    FUNCTION: ListNode* reverseList(ListNode* head);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  head = [1, 2, 3, 4, 5]
    Output: [5, 4, 3, 2, 1]

    --- Example 2 ---
    Input:  head = [1, 2]
    Output: [2, 1]

    --- Example 3 ---
    Input:  []
    Output: []

    *** Constraints ***
    The number of nodes in the list is the range [, 5000]
    -5000 <= Node.val <= 5000

    Follow-up: a linked list can be reversed either iterateively or
    recursively. Could you implement both?

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

    Self-explanatory.

*/

/* Time  Beats: 95.21% */
/* Space Beats: 98.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
    ListNode* reverseList(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr)
        {
            ListNode *next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same but using Recursion.

*/

/* Time  Beats: 70.42% */
/* Space Beats: 81.7% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursion{
public:
    ListNode* reverseList(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        reverseListRecursively(&prev, &curr);

        return prev;
    }

    void reverseListRecursively(ListNode** prev, ListNode** curr)
    {
        if ((*curr) == nullptr)
            return;

        ListNode* next = (*curr)->next;
        (*curr)->next = (*prev);
        (*prev) = (*curr);
        (*curr) = next;

        reverseListRecursively(prev, curr);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Much more simple recursive Solution.

*/

/* Time  Beats: 73.79% */
/* Space Beats:  5.53% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursion_1 {
public:
    ListNode* reverseList(ListNode* head)
    {
        if (head == nullptr)
            return nullptr;

        ListNode* new_head = head;

        if (head->next)
        {
            new_head = reverseList(head->next);
            head->next->next = head;
        }

        head->next = nullptr;

        return new_head;
    }
};




/* Time  Beats: 79.43% */
/* Space Beats: 31.84% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursion_2 {
public:
    ListNode* reverseList(ListNode* head)
    {
        if ( ! head)
            return nullptr;

        ListNode* prev = nullptr;
        head = helper(prev, head);

        return head;
    }

private:
    ListNode* helper(ListNode* prev, ListNode* curr)
    {
        ListNode* next = curr->next;
        curr->next = prev;

        if (next == nullptr)
            return curr;

        return helper(curr, next); // tail-recursion
    }
};




void
print_list(struct ListNode* head)
{
    std::cout << "\n\t\t[";

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
    Solution             sol;
    Solution_Recursion_1 sol_rec_1;
    Solution_Recursion_2 sol_rec_2;


    /* Example 1 */
    ListNode one(1);
    ListNode two(2);
    ListNode three(3);
    ListNode four(4);
    ListNode five(5);

    one.next = &two;
    two.next = &three;
    three.next = &four;
    four.next = &five;

    ListNode* head = &one;



    /* Example 2 */
    // ListNode one(1);
    // ListNode two(2);

    // one.next = &two;

    // ListNode* head = &one;



    /* Example 3 */
    // ListNode* head = nullptr;


    std::cout << "\n\t===========================";
    std::cout << "\n\t=== REVERSE LINKED LIST ===";
    std::cout << "\n\t===========================\n";


    /* Write Input */
    std::cout << "\n\tBefore:";
    print_list(head);


    /* Solution */
    // head = sol.reverseList(head);
    // head = sol_rec_1.reverseList(head);
    head = sol_rec_2.reverseList(head);


    /* Write Output */
    std::cout << "\n\tAfter:";
    print_list(head);


    return 0;
}
