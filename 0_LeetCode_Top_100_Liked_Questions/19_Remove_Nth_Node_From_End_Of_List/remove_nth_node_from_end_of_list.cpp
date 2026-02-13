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

    Here we move "right" pointer to point at n-th node FROM THE FRONT(not from
    the back!!!)

    Why are we doing that?
    Consider this:
            n = 2 // Meaning, we want to remove element 6(2-nd from the back)
                                                  |         (1-based index)
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

    **************************
    *** UNDESIRED BEHAVIOR ***
    **************************
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
    we can't be ON that node. We must be at one node BEFORE the node we're
    trying to remove.

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

    Now, when 'R'("right") pointer is at the LAST node, our 'L'("left") pointer
    is going to be at one node BEFORE the one we're trying to remove.

                                        --- n-th(2nd) node from the back
                                        |
                                        |
                                L       |      R
                                |___    |      |___
                                   |    |         |
                                   v    v         v
          0 ------> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
        dummy       ^
                 ___|
                 |
               head


    Now we can simply say:

        L->next = L->next->next;

    And we'll have this:

                                        --- n-th(2nd) node from the back
                                        |
                                        |
                                L       |      R
                                |___    |      |___
                                   |    |         |
                                   v    v         v
          0 ------> 1 -> 2 -> 3 -> 4    5 -> 6 -> 7 -> nullptr
        dummy       ^               \        ^
                    |                \      /
                 ___|                 \____/
                 |
               head



    And now we can just return dummy.next(not dummy->next, 'cause "dummy" is an
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

    That's when "dummy" node shines.

    Now we can have our 'L' pointer point to "dummy" node and everything is
    alright.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  58.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode dummy(-1);
        dummy.next = head;

        ListNode* left  = &dummy;
        ListNode* right = &dummy;

        // Move "right" pointer n nodes in
        for (int i = 0; i < n; i++)
            right = right->next;

        /*
            Move both pointers until "right" pointer is at the LAST node.
            Distance between "left" and "right", at any moment, is n+1 nodes.

                                            --- n-th(2nd) node from the back
                                            |
                                            |
                                  left      |    right
                                    |___    |      |___
                                       |    |         |
                                       v    v         v
              0 ------> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> nullptr
            dummy       ^              <~~~~~~~~~~~~~~>
                        |              distance = n + 1  // Where n = 2
                     ___|
                     |
                   head


            At that moment our "left" pointer will be at one node BEFORE the
            n-th node from the back.
        */
        while (right->next)
        {
            left  = left->next;
            right = right->next;
        }

        // Re-link AROUND the n-th node from the back
        left->next = left->next->next;

        return dummy.next;
    }
};
