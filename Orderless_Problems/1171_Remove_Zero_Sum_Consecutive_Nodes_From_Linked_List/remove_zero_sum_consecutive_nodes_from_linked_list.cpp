#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    1171) Remove Zero Sum Consecutive Nodes from Linked List
    ========================================================

    ============
    Description:
    ============

    Given the head of a linked list, we repeatedly delete consecutive sequences
    of nodes that sum to 0 until there are no such sequences.

    After doing so, return the head of the final linked list.  You may return
    any such answer.


    =====
    Note: that in the examples below, all sequences are serializations of
          ListNode objects.
    =====

    ==========================================================
    FUNCTION: ListNode* removeZeroSumSublists(ListNode* head);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,2,-3,3,1]
    Output: [3,1]
    Note: The answer [1,2,1] would also be accepted.

    --- Example 2 ---
    Input: head = [1,2,3,-3,4]
    Output: [1,2,4]

    --- Example 3 ---
    Input: head = [1,2,3,-3,-2]
    Output: [1]


    *** Constraints ***
    The given linked list will contain between 1 and 1000 nodes.
    Each node in the linked list has -1000 <= node.val <= 1000.

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

    TODO

*/

/* Time  Beats: 79.97% */
/* Space Beats: 23.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head)
    {
        int prefix_sum = 0;
        std::unordered_map<int, ListNode*> prefix_map;

        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;

        prefix_map[0] = dummyHead;

        for (ListNode* curr = head; curr != nullptr; curr = curr->next)
        {
            prefix_sum += curr->val;

            if (prefix_map.find(prefix_sum) != prefix_map.end()) // Prefix exists
            {
                ListNode* prev_anchor = prefix_map[prefix_sum];

                int sum_to_remove = prefix_sum;
                while (prev_anchor != curr)
                {
                    prev_anchor = prev_anchor->next;
                    sum_to_remove += prev_anchor != nullptr ? prev_anchor->val : 0;

                    if (prev_anchor != curr)
                        prefix_map.erase(sum_to_remove);
                }

                prefix_map[prefix_sum]->next = curr->next;
            }
            else if (prefix_sum != 0)
                prefix_map[prefix_sum] = curr;
        }

        return dummyHead->next;
    }
};
