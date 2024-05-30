#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    1669) Merge In Between Linked Lists
    ===================================

    ============
    Description:
    ============

    You are given two linked lists: list1 and list2 of sizes n and m
    respectively.

    Remove list1's nodes from the ath node to the bth node, and put list2 in
    their place.

    The blue edges and nodes in the following figure indicate the result:

    Build the result list and return its head.

    ===================================================================================
    FUNCTION: ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                       ___________
                       |  Remove |
                       |         |
    10 --> 1 --> 13 -->| 6 --> 9 |--> 5
                 |     |         |    ^
                 |     -----------    |____________________
                 |                                        |
                 |                                        |
                 |                                        |
                 ---->  1000000 --> 1000001 --> 1000002 ---

    Input: list1 = [10,1,13,6,9,5], a = 3, b = 4,
           list2 = [1000000,1000001,1000002]
    Output: [10,1,13,1000000,1000001,1000002,5]
    Explanation: We remove the nodes 3 and 4 and put the entire list2 in their
                 place. The blue edges and nodes in the above figure indicate
                 the result.


    --- Example 2 ---
               _____________________
               |       Remove      |
               |                   |
    0 --> 1 -->|2 --> 3 --> 4 --> 5|--> 6
          |    |                   |    ^
          |    ---------------------    |___________
          |                                        |
          |                                        |
          |                                        |
          -->  1000000 --> 1000001 --> 1000002 -----

    Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5,
           list2 = [1000000,1000001,1000002,1000003,1000004]
    Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
    Explanation: The blue edges and nodes in the above figure indicate the
                 result.


    *** Constraints ***
    3 <= list1.length <= 10^4
    1 <= a <= b < list1.length - 1
    1 <= list2.length <= 10^4

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

    Intuitive.

*/

/* Time  Beats: 79.50% */
/* Space Beats: 82.85% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(1)     */
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2)
    {
        ListNode* tail2 = list2;
        while (tail2->next)
            tail2 = tail2->next;

        ListNode* curr = list1;
        for (int count = 0; count < a-1; count++)
            curr = curr->next;

        ListNode* tmp = curr->next;
        curr->next = list2; // Link with the beginning node of list2
        curr = tmp;

        for (int count = a; count < b; count++)
            curr = curr->next;

        tail2->next = curr->next;
        curr->next = nullptr; // Unlink removed part

        return list1;
    }
};
