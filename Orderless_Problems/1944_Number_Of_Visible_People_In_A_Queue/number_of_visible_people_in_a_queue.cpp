#include <iostream>
#include <vector>
#include <stack>

/*
    ============
    === HARD ===
    ============

    =========================================
    1944) Number of Visible People in a Queue
    =========================================

    ============
    Description:
    ============

    There are n people standing in a queue, and they numbered from 0 to n - 1
    in left to right order. You are given an array heights of distinct integers
    where heights[i] represents the height of the ith person.

    A person can see another person to their right in the queue if everybody in
    between is shorter than both of them. More formally, the ith person can see
    the jth person if i < j and min(heights[i], heights[j]) > max(heights[i+1],
    heights[i+2], ..., heights[j-1]).

    Return an array answer of length n where answer[i] is the number of people
    the ith person can see to their right in the queue.

    ===============================
    FUNCTION:   
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: heights = [10,6,8,5,11,9]
    Output: [3,1,2,1,1,0]
    Explanation:
    Person 0 can see person 1, 2, and 4.
    Person 1 can see person 2.
    Person 2 can see person 3 and 4.
    Person 3 can see person 4.
    Person 4 can see person 5.
    Person 5 can see no one since nobody is to the right of them.

    --- Example 2 ---
    Input: heights = [5,1,2,3,10]
    Output: [4,1,1,1,0]


    *** Constraints ***
    n == heights.length
    1 <= n <= 10^5
    1 <= heights[i] <= 10^5
    All the values of heights are unique.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.34% */
/* Space Beats: 5.88%  */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> canSeePersonsCount(std::vector<int>& h)
    {
        const int n = h.size();

        std::stack<int> stack;
        stack.push(h[n-1]);

        std::vector<int> result;
        result.push_back(0);

        for(int i = n-2; i >= 0; i--)
        {
            int c = 0;

            while ( ! stack.empty() && stack.top()<h[i])
            {
                stack.pop();
                c++;
            }

            if ( ! stack.empty())
                c++;

            stack.push(h[i]);
            result.push_back(c);
        }

        std::reverse(result.begin(), result.end());   
        return result;
    }
};
