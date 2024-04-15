#include <iostream>

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
    ListNode(int x) : val(x), next(NULL) {}
};


/*
    ------------
    --- IDEA ---
    ------------

    Tortoise and the Hare Technique(Floyd's algorithm).

    Assign Slow pointer to head and Fast pointer to head->next at the
    beginning.
    At each iteration in while loop, move Slow pointer by one node forward and
    move Fast pointer by two nodes forward.
    If they point to the same node at some point, then that certainly means
    that there is a cycle.

    Solutions are almost equivalent, it's a matter of personal preference.

*/

/* Time  Beats: 95.15% */
/* Space Beats: 47.62% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_1 {
public:
    bool hasCycle(ListNode *head)
    {
        struct ListNode* slow = head;
        struct ListNode* fast = head;

        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                break;
        }

        if (fast == NULL || fast->next == NULL)
            return false;

        return true;
    }
};




/* Time  Beats: 95.15% */
/* Space Beats: 47.62% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool hasCycle(ListNode *head)
    {
        if (head == nullptr)
            return false;

        ListNode* slow = head;
        ListNode* fast = head->next;

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




/*
    =============================
    === This is just Printing ===
    =============================

*/

void
print_list(ListNode *head)
{
    ListNode* cur = head;
    printf("\n\t\t");

    if (head == nullptr)
        printf("Empty");

    while (cur)
    {
        if (cur->next == nullptr)
            printf("%d ", cur->val);
        else
            printf("%d -> ", cur->val);

        cur = cur->next;
    }
    printf("\n\n");
}


void
print_loop_list(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;

    // For printing
    ListNode* out  = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            break;
    }

    // There is no Loop in the List
    if (fast == NULL || fast->next == NULL)
    {
        print_list(head);
        return;
    }

    // Find the Loop
    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    /* PRINTING */
    printf("\n\t\t");
    // printf("\n\t\tLoop List:");
    // printf("\n\t");

    // Printing before Loop
    while (out != slow)
    {
        printf("%d -> ", out->val);
        out = out->next;
    }

    // Print the Looping Node
    printf("|%d| -> ", out->val);

    fast = fast->next;
    // Printing the Loop
    while (slow != fast)
    {
        printf("%d -> ", fast->val);
        fast = fast->next;
    }

    // Print the Looping Node
    if (slow->next == slow)
        printf("|%d| -> |%d| -> |%d| -> ... \n\n", slow->val, slow->val, slow->val);
    else
        printf("|%d| -> %d -> %d -> ... \n\n", slow->val, slow->next->val, slow->next->next->val);
}


int
main()
{
    Solution_1 sol_1;
    Solution_2 sol_2;

    /* Example 1 */
    /*
        3 -> 2 -> 0 -> -4
        ^---------------|
    */
    struct ListNode minus_four(-4);
    struct ListNode zero(0);
    struct ListNode two(2);
    struct ListNode three(3);
    minus_four.next = &three;
    zero.next       = &minus_four;
    two.next        = &zero;
    three.next      = &two;
    struct ListNode* head = &three;



    /* Example 2 */
    /*
        1 -> 2
        ^----|
    */
    // struct ListNode two(2);
    // struct ListNode one(1);
    // two.next = &one;
    // one.next = &two;
    // struct ListNode* head = &one;



    /* Example 3 */
    /*
        1 -> NULL
    */
    // struct ListNode one(1);
    // struct ListNode* head = &one;



    /* Example 4 */
    /*
                                 -----
                                 v   |
        1 -> 2 -> 3 -> 4 -> 5 -> 6   |
                                 -----
    */
    // struct ListNode six(6);
    // struct ListNode five(5);
    // struct ListNode four(4);
    // struct ListNode three(3);
    // struct ListNode two(2);
    // struct ListNode one(1);
    // six.next   = &six;
    // five.next  = &six;
    // four.next  = &five;
    // three.next = &four;
    // two.next   = &three;
    // one.next   = &two;
    // struct ListNode* head = &one;


    /* Example 5 */
    /*

        1 -> 2 -> 3 -> 4 -> 5 -> 6
                            ^----|
    */
    // struct ListNode six(6);
    // struct ListNode five(5);
    // struct ListNode four(4);
    // struct ListNode three(3);
    // struct ListNode two(2);
    // struct ListNode one(1);
    // six.next   = &five;
    // five.next  = &six;
    // four.next  = &five;
    // three.next = &four;
    // two.next   = &three;
    // one.next   = &two;
    // struct ListNode* head = &one;



    /* Example 6 */
    /*

        1 -> 2 -> 3 -> 4 -> 5 -> 6
                       ^---------|
    */
    // struct ListNode six(6);
    // struct ListNode five(5);
    // struct ListNode four(4);
    // struct ListNode three(3);
    // struct ListNode two(2);
    // struct ListNode one(1);
    // six.next   = &four;
    // five.next  = &six;
    // four.next  = &five;
    // three.next = &four;
    // two.next   = &three;
    // one.next   = &two;
    // struct ListNode* head = &one;

    /* Example 7 */
    /*

        1 -> 2 -> 3 -> 4 -> 5 -> 6
                  ^--------------|
    */
    // struct ListNode six(6);
    // struct ListNode five(5);
    // struct ListNode four(4);
    // struct ListNode three(3);
    // struct ListNode two(2);
    // struct ListNode one(1);
    // six.next   = &three;
    // five.next  = &six;
    // four.next  = &five;
    // three.next = &four;
    // two.next   = &three;
    // one.next   = &two;
    // struct ListNode* head = &one;


    /* Example 8 */
    /*

        1 -> 2 -> 3 -> 4 -> 5 -> 6
             ^-------------------|
    */
    // struct ListNode six(6);
    // struct ListNode five(5);
    // struct ListNode four(4);
    // struct ListNode three(3);
    // struct ListNode two(2);
    // struct ListNode one(1);
    // six.next   = &two;
    // five.next  = &six;
    // four.next  = &five;
    // three.next = &four;
    // two.next   = &three;
    // one.next   = &two;
    // struct ListNode* head = &one;


    /* Example 9 */
    /*

        1 -> 2 -> 3 -> 4 -> 5 -> 6
        ^------------------------|
    */
    // struct ListNode six(6);
    // struct ListNode five(5);
    // struct ListNode four(4);
    // struct ListNode three(3);
    // struct ListNode two(2);
    // struct ListNode one(1);
    // six.next   = &one;
    // five.next  = &six;
    // four.next  = &five;
    // three.next = &four;
    // two.next   = &three;
    // one.next   = &two;
    // struct ListNode* head = &one;


    /* Example 10 */
    /*
        3 -> 2 -> 0 -> -4
    */
    // struct ListNode minus_four(-4);
    // struct ListNode zero(0);
    // struct ListNode two(2);
    // struct ListNode three(3);
    // zero.next       = &minus_four;
    // two.next        = &zero;
    // three.next      = &two;
    // struct ListNode* head = &three;

