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

    Count how many nodes there are in total.
    Be always one node behind the i-th node we're trying to remove.

    if (i == n) // meaning we're behind the i-tn consecutive node and i == n
        set current node's next to point to current node's next's next pointer.

    That's it.

    However, this one requires two passes.

*/

/* Time  Beats: 67.28% */
/* Space Beats: 10.83% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Two_Passes {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        int nodes = count_nodes(head);

        ListNode dummy(0);
        dummy.next = head;

        ListNode* tmp = &dummy;

        while(tmp && tmp->next)
        {
            if (nodes == n)
            {
                tmp->next = tmp->next->next;
                break;
            }

            tmp = tmp->next;
            nodes--;
        }

        return dummy.next;
    }

private:
    int count_nodes(ListNode* head)
    {
        int count = 0;
        while (head)
        {
            count++;
            head = head->next;
        }

        return count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Here we move "right" pointer to point at n-th node FROM THE FRONT(not from
    the back!!!)

    Why are we doing that?
    Consider this:
            n = 2 // Meaning, we want to remove element 6
                                                  |
                                     _____________|
                                     |
                                     |
                                     v
            1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
            ^
         ___|
         |
       head

    We initialize pointer 'R'(right) to point to "head".

         R
         |___
            |
            v
            1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
            ^
         ___|
         |
       head


    Now we move it exactly 'n' times to the right. (You'll see why in a second)

                   R
                   |___
                      |
                      v
            1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
            ^
         ___|
         |
       head


    Now we want to start another pointer 'L'("left") at the beginning(head) and
    once the 'R'("right") pointer becomes nullptr, our 'L'("left") pointer is
    going to point at the node we want to remove.

      L            R
      |______      |___
            |         |
            v         v
            1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
            ^
         ___|
         |
       head

    ...
    ...
    ...

                               L            R
                               |______      |___
                                     |         |
                                     v         v
            1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
            ^
         ___|
         |
       head


    However, this isn't the desired behaviour. If we want to remove some node,
    we can't be on that node, we must be one node behind the node we're trying
    to remove.

    Therefore, we'll initialize a "dummy node".
    We'll create it on the stack since it's faster and we'll make dummy.next to
    point to "head".

       L                   R
       |___                |___
          |                   |
          v                   v
          0 ------> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
        dummy       ^
                 ___|
                 |
               head

    Now, when 'R'("right") pointer gets to point to nullptr, our 'L'("left")
    pointer is going to pointer at **one node BEFORE the one we're trying to
    remove**.

                                L                   R
                                |___                |___
                                   |                   |
                                   v                   v
          0 ------> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
        dummy       ^
                 ___|
                 |
               head


    Now we can simply say:

        L->next = L->next->next;

    And we'll have this:

                                L                   R
                                |___                |___
                                   |                   |
                                   v                   v
          0 ------> 1 -> 2 -> 3 -> 4 -> 5 ------> 7 -> nullptr
        dummy       ^
                 ___|
                 |
               head



    And now we can just return dummy.next(not dummy->next, 'cause it's an
                                          object, not a pointer)


    One additional reason we're using a "dummy node" is when we're asked to
    remove the very first node in our Linked List.

            n = 7 // Meaning, we want to remove element 1
                                                  |
            ______________________________________|
            |
            |
            v
            1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
            ^
         ___|
         |
       head


    If we must, as we've already concluded, be at one node BEFORE the one we're
    trying to remove, how are we going to remove the very first one?

    That's when "dummy node" shines.

    Now we can have our 'L' pointer point to "dummy node" and everything is
    alright.

*/

/* Time  Beats: 100% */
/* Space Beats: 8.95% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Single_Pass {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* right = head;
        for (int i = 0; i < n; i++)
            right = right->next;

        ListNode* tmp = &dummy;
        while (right)
        {
            tmp = tmp->next;
            right = right->next;
        }

        tmp->next = tmp->next->next;

        return dummy.next;
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
    Solution_Two_Passes   sol_two_passes;
    Solution_Single_Pass  sol_one_pass;


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
    head = sol_two_passes.removeNthFromEnd(head, n);
    head = sol_one_pass.removeNthFromEnd(head, n);


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
