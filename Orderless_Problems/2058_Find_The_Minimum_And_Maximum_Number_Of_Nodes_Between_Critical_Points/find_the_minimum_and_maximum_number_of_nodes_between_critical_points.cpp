#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================================
    2058) Find the Minimum and Maximum Number of Nodes Between Critical Points
    ==========================================================================

    ============
    Description:
    ============

    A critical point in a linked list is defined as either a local maxima or a
    local minima.

    A node is a local maxima if the current node has a value strictly greater
    than the previous node and the next node.

    A node is a local minima if the current node has a value strictly smaller
    than the previous node and the next node.

    Note that a node can only be a local maxima/minima if there exists both a
    previous node and a next node.

    Given a linked list head, return an array of length 2 containing
    [minDistance, maxDistance] where minDistance is the minimum distance
    between any two distinct critical points and maxDistance is the maximum
    distance between any two distinct critical points. If there are fewer than
    two critical points, return [-1, -1].

    =================================================================
    FUNCTION: vector<int> nodesBetweenCriticalPoints(ListNode* head);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [3,1]
    Output: [-1,-1]
    Explanation: There are no critical points in [3,1].

    --- Example 2 ---
    Input: head = [5,3,1,2,5,1,2]
    Output: [1,3]
    Explanation: There are three critical points:
    - [5,3,1,2,5,1,2]: The third node is a local minima because 1 is less than 3 and 2.
    - [5,3,1,2,5,1,2]: The fifth node is a local maxima because 5 is greater than 2 and 1.
    - [5,3,1,2,5,1,2]: The sixth node is a local minima because 1 is less than 5 and 2.
    The minimum distance is between the fifth and the sixth node. minDistance = 6 - 5 = 1.
    The maximum distance is between the third and the sixth node. maxDistance = 6 - 3 = 3.

    --- Example 3 ---
    Input: head = [1,3,2,2,3,2,2,2,7]
    Output: [3,3]
    Explanation: There are two critical points:
    - [1,3,2,2,3,2,2,2,7]: The second node is a local maxima because 3 is greater than 1 and 2.
    - [1,3,2,2,3,2,2,2,7]: The fifth node is a local maxima because 3 is greater than 2 and 2.
    Both the minimum and maximum distances are between the second and the fifth node.
    Thus, minDistance and maxDistance is 5 - 2 = 3.
    Note that the last node is not considered a local maxima because it does not have a next node.


    *** Constraints ***
    The number of nodes in the list is in the range [2, 10^5].
    1 <= Node.val <= 10^5

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

/* Time  Beats: 82.68% */
/* Space Beats: 35.95% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> nodesBetweenCriticalPoints(ListNode* head)
    {
        std::vector<int> criticals;
        int minima = INT_MAX;
        int maxima = INT_MIN;

        int index = 1; // Starts at 1

        ListNode* prev = nullptr;
        ListNode* next;

        ListNode* curr = head;
        while (curr)
        {
            next = curr->next;

            if (prev && next)
            {
                if ((prev->val < curr->val && curr->val > next->val) ||
                    (prev->val > curr->val && curr->val < next->val))
                {
                    if ( ! criticals.empty())
                    {
                        minima = std::min(minima, index - criticals.back());
                        maxima = index - criticals[0];
                    }

                    criticals.push_back(index);
                }
            }

            prev = curr;
            curr = curr->next;

            index++;
        }

        if (minima == INT_MAX || maxima == INT_MAX)
            return {-1, -1};

        return {minima, maxima};
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Improve Space Complexity from O(n) to O(1).

    Actually, it was maximally O(n/2), but that is consideredd O(n).

*/

/* Time  Beats: 99.85% */
/* Space Beats: 99.71% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::vector<int> nodesBetweenCriticalPoints(ListNode* head)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int minima = INT_MAX;
        int maxima = INT_MIN;

        int first_critical_idx = -1;
        int last_critical_idx  = -1;

        int index = 1; // Starts at 1

        ListNode* prev = nullptr;
        ListNode* next;

        ListNode* curr = head;
        while (curr)
        {
            next = curr->next;

            if (prev && next)
            {
                if ((prev->val < curr->val && curr->val > next->val) ||
                    (prev->val > curr->val && curr->val < next->val))
                {
                    if (first_critical_idx > -1)
                    {
                        minima = std::min(minima, index - last_critical_idx);
                        maxima = index - first_critical_idx;
                    }
                    else
                        first_critical_idx = index;

                    last_critical_idx = index;
                }
            }

            prev = curr;
            curr = curr->next;

            index++;
        }

        if (minima == INT_MAX || maxima == INT_MAX)
            return {-1, -1};

        return {minima, maxima};
    }
};
