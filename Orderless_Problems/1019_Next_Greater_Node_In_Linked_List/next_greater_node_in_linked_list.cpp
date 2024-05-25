#include <iostream>
#include <vector>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1019) Next Greater Node In Linked List
    ======================================

    ============
    Description:
    ============

    You are given the head of a linked list with n nodes.

    For each node in the list, find the value of the next greater node. That
    is, for each node, find the value of the first node that is next to it and
    has a strictly larger value than it.

    Return an integer array answer where answer[i] is the value of the next
    greater node of the ith node (1-indexed). If the ith node does not have a
    next greater node, set answer[i] = 0.

    ======================================================
    FUNCTION: vector<int> nextLargerNodes(ListNode* head);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

                      - - - -
                      |     |
                      |     v
                2 --> 1 --> 5
                |           ^
                |           |
                - - - - - - -

    Input: head = [2,1,5]
    Output: [5,5,0]


    --- Example 2 ---

                               - - --
                               |    |
                               |    v
                2 -> 7 -> 4 -> 3 -> 5
                |    ^    |         ^
                |    |    |         |
                - - --    - - - - - -

    Input: head = [2,7,4,3,5]
    Output: [7,0,5,5,0]


    *** Constraints ***
    The number of nodes in the list is n.
    1 <= n <= 10^4
    1 <= Node.val <= 10^9

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

/* Time  Beats: 95.12% */
/* Space Beats: 94.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> nextLargerNodes(ListNode* head)
    {
        int n = 0;
        head = reverse_linked_list(head, n);

        // Results
        std::vector<int> results(n, 0);

        std::stack<int>  stack; // Monotonically Decreasing
        stack.push(head->val);

        int i = n-2; // Penultimate
        ListNode* curr = head->next;
        while (curr)
        {
            while ( !stack.empty() && stack.top() <= curr->val)
                stack.pop();

            results[i] = stack.empty() ? 0 : stack.top();
            stack.push(curr->val);

            curr = curr->next;
            i--;
        }

        // Restore original Linked List
        head = reverse_linked_list(head, n);

        return results;
    }

private:
    ListNode* reverse_linked_list(ListNode* head, int& n)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr)
        {
            ListNode* next = curr->next;

            curr->next = prev;
            prev = curr;
            curr = next;

            n++;
        }

        return prev;
    }
};
