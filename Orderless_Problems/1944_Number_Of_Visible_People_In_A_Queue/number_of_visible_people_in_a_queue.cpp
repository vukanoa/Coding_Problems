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

    ===============================================================
    FUNCTION: vector<int> canSeePersonsCount(vector<int>& heights);
    ===============================================================

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

#include <vector>
#include <stack>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Classic "Monotonic Stack" problem)

*/

/* Time  Beats: 67.67% */
/* Space Beats: 96.02% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights)
    {
        int N = heights.size();
        vector<int> result(N);

        stack<int> monotonic_stack;
        for (int i = N-1; i >= 0; i--)
        {
            while ( ! monotonic_stack.empty() && heights[i] > monotonic_stack.top())
            {
                monotonic_stack.pop();
                result[i]++;
            }

            if ( ! monotonic_stack.empty())
                result[i]++;

            monotonic_stack.push(heights[i]);
        }

        return result;
    }
};
