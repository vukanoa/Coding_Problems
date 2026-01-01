#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    2130) Maximum Twin Sum of a Linked List
    =======================================

    ============
    Description:
    ============

    In a linked list of size n, where n is even, the ith node (0-indexed) of
    the linked list is known as the twin of the (n-1-i)th node,
    if 0 <= i <= (n/ 2) - 1.

        For example, if n = 4, then node 0 is the twin of node 3, and node 1 is
        the twin of node 2. These are the only nodes with twins for n = 4.

    The twin sum is defined as the sum of a node and its twin.

    Given the head of a linked list with even length, return the maximum twin
    sum of the linked list.

    ======================================
    FUNCTION: int pairSum(ListNode* head);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [5,4,2,1]
    Output: 6
    Explanation: Nodes 0 and 1 are the twins of nodes 3 and 2, respectively.
                 All have twin sum = 6.  There are no other nodes with twins in
                 the linked list.  Thus, the maximum twin sum of the linked
                 list is 6.


    --- Example 2 ---
    Input: head = [4,2,2,3]
    Output: 7
    Explanation:
    The nodes with twins present in this linked list are:
    - Node 0 is the twin of node 3 having a twin sum of 4 + 3 = 7.
    - Node 1 is the twin of node 2 having a twin sum of 2 + 2 = 4.
    Thus, the maximum twin sum of the linked list is max(7, 4) = 7.


    --- Example 3 ---
    Input: head = [1,100000]
    Output: 100001
    Explanation: There is only one node with a twin in the linked list having
                 twin sum of 1 + 100000 = 100001.



    *** Constraints ***
    The number of nodes in the list is an even integer in the range [2, 105].
    1 <= Node.val <= 105

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

    @@@@@@@@@@@@@@@@@@@@@
    @@@ PREREQUISITES @@@
    @@@@@@@@@@@@@@@@@@@@@
        1. Reversing a Linked List


    While reversing the entire list, push all the values one-by-one in a vector
    "vec".

    Now, since we have a reversed Linked List, use only first n/2 elements to
    sum with corresponding vec[i] to get a correct twin_sum.

    After i exceeds n/2, stop adding, but cointinue reversing until we end up
    with a Linked List in the intial state.

        5 -> 4 -> 3 -> 6 -> 1 -> 2 
        ^
        |
       _|
      |
    head


    *** REVERSE LINKED LIST ***

        5 <- 4 <- 3 <- 6 <- 1 <- 2 
                                 ^
                                 |
                                _|
                               |
                             head
        
        vec = [5, 4, 3, 6, 1, 2]
               0  1  2  3  4  5


    
    While reversing the Linked List again, add ith with n-1-i, where i < n/2

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

                                  int max = 0; 

-------------------------------------------------------------------------------

    1.  i = 0

                        5 <- 4 <- 3 <- 6 <- 1 <- 2 
                                                 ^
                                                 |
                                                _|
                                               |
                                             head

                               i 
                        vec = [5, 4, 3, 6, 1, 2]
                               0  1  2  3  4  5


                        vec[i] + head->val = 5 + 2 = 7
                        max = max(max, 7) = (0, 7) = 7; // New max 7

-------------------------------------------------------------------------------

    1.  i = 1

                        5 <- 4 <- 3 <- 6 <- 1 -> 2 
                                            ^
                                            |
                                           _|
                                          |
                                        head

                                  i 
                        vec = [5, 4, 3, 6, 1, 2]
                               0  1  2  3  4  5


                        vec[i] + head->val = 4 + 1 = 5
                        max = max(max, 5) = (7, 5) = 7; // Remains 7

-------------------------------------------------------------------------------

    2.  i = 2

                        5 <- 4 <- 3 <- 6 <- 1 -> 2 
                                       ^
                                       |
                                      _|
                                     |
                                   head

                                  i 
                        vec = [5, 4, 3, 6, 1, 2]
                               0  1  2  3  4  5


                        vec[i] + head->val = 3 + 6 = 9
                        max = max(max, 9) = (7, 9) = 9; // Remains 9

-------------------------------------------------------------------------------

    3.  i = 3 // Now i is NOT < n/2, therefore we will ONLY keep reversing

                        5 <- 4 <- 3 -> 6 -> 1 -> 2 
                                  ^
                                  |
                                 _|
                                |
                              head
                        
                        if (i < n/2) // NOT TRUE

-------------------------------------------------------------------------------

    4.  i = 4 // Now i is NOT < n/2, therefore we will ONLY keep reversing

                        5 <- 4 -> 3 -> 6 -> 1 -> 2 
                             ^
                             |
                            _|
                           |
                         head
                        
                        if (i < n/2) // NOT TRUE

-------------------------------------------------------------------------------

    5.  i = 5 // Now i is NOT < n/2, therefore we will ONLY keep reversing

                        5 -> 4 -> 3 -> 6 -> 1 -> 2 
                        ^
                        |
                       _|
                      |
                    head
                        
                        if (i < n/2) // NOT TRUE

-------------------------------------------------------------------------------

    At the end, just return variable "max".

*/

/* Time  Beats: 97.13% */
/* Space Beats: 20.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int pairSum(ListNode* head)
    {
        std::vector<int> vec;

        /* Reverse Linked List & Fill vector "vec" */
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr)
        {
            vec.push_back(curr->val);

            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;

        prev = nullptr;
        curr = head;

        int n = vec.size();
        int max = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            if (i < n/2) // Only the "right half", vec[i] is "left half".
                max = std::max(max, vec[i] + curr->val);

            /* Re-reverse Linked list */
            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;

        return max;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's a classic Linked-List problem.

    @@@@@@@@@@@@@@@@@@@@@
    @@@ PREREQUISITES @@@
    @@@@@@@@@@@@@@@@@@@@@
        1. Find a middle node in a Linked List
        2. Reverse a Linked List


    Since we need to sum ith and n-1-i (where i is < n/2, where n is even),
    that means we want to sum first with the last, second with the second to
    last, etc.

    How would we do that if we had an array "nums"?

        nums = [5, 4, 3, 2, 1, 2]

    We would use a "two pointer" technique, right?
    We'd have a pointer 'L' and a pointer 'R' set to the first and last index,
    respectively. Then we would sum two numbers at index 'L' and index 'R' and
    we would check if this "twin sum" is the greatest so far.

    It would be something like this:
        max = 0;
    
        nums = [5, 4, 3, 6, 1, 2]
                L              R

        twin_sum = 5 + 2 = 7
        max = max(max, twin_sum) = max(0, 7) = 7 // New max 7


        nums = [5, 4, 3, 6, 1, 2]
                   L        R

        twin_sum = 4 + 1 = 5
        max = max(max, twin_sum) = max(7, 5) = 7 // Remains 7


        nums = [5, 4, 3, 2, 1, 2]
                      L  R

        twin_sum = 3 + 6 = 9
        max = max(max, twin_sum) = max(7, 9) = 9 // New max 9

        Finally: return max; // max = 9



    Now ask yourself - How would we do this if we had Linked List instead of an
    array?

    We certainly can't have "two pointers" technique, right?
    Wrong! We actually can.

        5 -> 4 -> 3 -> 6 -> 1 -> 2 

    So, "how can we have "two pointers" here?" you may ask.

    We can unlink two half right at the middle. Since 'n' is an even number, we
    can have two halves of equal lengths.

    We're going to have this:

        5 -> 4 -> 3 -> 6 -> 1 -> 2 
        ^         ^    ^
        |         |    |
       _|         |    |_____
      |           |         |
    head    left_tail     right_head



    Now we're going to unlink left and right half by setting:
        
        left_tail->next = nullptr;

        5 -> 4 -> 3        6 -> 1 -> 2 
        ^         ^        ^
        |         |        |
       _|         |        |_____
      |           |             |
    head    left_tail         right_head
    

    Since we want to sum first with the very last, second with second to last,
    etc. We must reverse the "right half".


        5 -> 4 -> 3        6 <- 1 <- 2 
        ^         ^                  ^
        |         |                  |
       _|         |             _____|
      |           |             |
    head    left_tail         right_head


    Now we can iterate through these halves in the same way we did with our
    array "nums", however if we were to just iterate with:

        "head" and "right_head"

    we wouldn't be able to restore the original Linked List at the end.
    It's a good programming practice to leave everything as it was.

    Therefore, to circumvent this problem, we can assign "twin1" to the head of
    the "left half" and "twin2" to the head of the "right half".

    twin1                     twin2
      |__                       |_____
        |                            |
        |                            |
        v                            v
        5 -> 4 -> 3        6 <- 1 <- 2 
        ^         ^                  ^
        |         |                  |
       _|         |             _____|
      |           |             |
    head    left_tail         right_head


    Now we sum in the same way and we move twin1 and twin2 to the next one
    until we reach a nullptr, i.e. the end of each half(we're going to reach it
    at the same time since both halves are of equal length).

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

                                  int max = 0;

-------------------------------------------------------------------------------

    1.
                        twin1                     twin2
                          |__                       |_____
                            |                            |
                            |                            |
                            v                            v
                            5 -> 4 -> 3        6 <- 1 <- 2 
                            ^         ^                  ^
                            |         |                  |
                           _|         |             _____|
                          |           |             |
                        head    left_tail         right_head
    
                        
                        twin_sum = 5 + 2 = 7
                        max = max(max, twin_sum) = (0, 7) = 7; // New max 7
    
-------------------------------------------------------------------------------

    2.
                             twin1                twin2
                               |__                  |
                                 |                  |
                                 |                  |
                                 v                  v
                            5 -> 4 -> 3        6 <- 1 <- 2 
                            ^         ^                  ^
                            |         |                  |
                           _|         |             _____|
                          |           |             |
                        head    left_tail         right_head
    
                        
                        twin_sum = 4 + 1 = 5
                        max = max(max, twin_sum) = (7, 5) = 7; // Remains 7
    
-------------------------------------------------------------------------------

    3.
                                  twin1           twin2
                                    |__        _____|
                                      |        |
                                      |        |
                                      v        v
                            5 -> 4 -> 3        6 <- 1 <- 2 
                            ^         ^                  ^
                            |         |                  |
                           _|         |             _____|
                          |           |             |
                        head    left_tail         right_head
    
                        
                        twin_sum = 3 + 6 = 9
                        max = max(max, twin_sum) = (7, 9) = 9; // New max 9
    
-------------------------------------------------------------------------------

    4.
          (now points to nullptr) twin1           twin2 (now points to nullptr)
                                    |____    _______|
                                        |    |
                                        |    |
                                        v    v
                            5 -> 4 -> 3        6 <- 1 <- 2 
                            ^         ^                  ^
                            |         |                  |
                           _|         |             _____|
                          |           |             |
                        head    left_tail         right_head
    
                        
                        twin_sum = 3 + 6 = 9
                        max = max(max, twin_sum) = (7, 9) = 9; // New max 9
    
-------------------------------------------------------------------------------

    
    Now we want to get the entire Linked List in a state it was before we did
    all of this.

    Therefore, we must reverse "right half";

        5 -> 4 -> 3        6 -> 1 -> 2 
        ^         ^        ^
        |         |        |
       _|         |        |_____
      |           |             |
    head    left_tail         right_head
    

    And the we must "relink" two halves by setting:
        
        left_tail->next = right_head

        5 -> 4 -> 3 -> 6 -> 1 -> 2 
        ^         ^    ^
        |         |    |
       _|         |    |_____
      |           |         |
    head    left_tail     right_head


    And we just return variable "max"

*/

/* Time  Beats: 71.93% */
/* Space Beats: 66.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // More Space Efficient than the one above
class Solution {
public:
    int pairSum(ListNode* head)
    {
        ListNode* left_tail  = middle(head);
        ListNode* right_head = left_tail->next;

        /* Unlink left and right half */
        left_tail->next = nullptr;

        /* Reverse right half */
        right_head = reverse_list(right_head);

        ListNode* twin1 = head;
        ListNode* twin2 = right_head;

        int max = 0;
        while (twin1 && twin2)
        {
            int twin_sum = twin1->val + twin2->val;

            max = std::max(max, twin_sum);

            twin1 = twin1->next;
            twin2 = twin2->next;
        }

        /* Reverse Right half back */
        right_head = reverse_list(right_head);

        /* Relink left and right half */
        left_tail->next = right_head;

        return max;
    }

private:
    ListNode* middle(ListNode* head)
    {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    ListNode* reverse_list(ListNode* head)
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
