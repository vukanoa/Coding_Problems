#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

/*
    ============
    === HARD ===
    ============

    ===========================
    502) IPO
    ===========================

    ============
    Description:
    ============

    Suppose LeetCode will start its IPO soon. In order to sell a good price of
    its shares to Venture Capital, LeetCode would like to work on some projects
    to increase its capital before the IPO. Since it has limited resources, it
    can only finish at most k distinct projects before the IPO. Help LeetCode
    design the best way to maximize its total capital after finishing at most k
    distinct projects.

    You are given n projects where the ith project has a pure profit profits[i]
    and a minimum capital of capital[i] is needed to start it.

    Initially, you have w capital. When you finish a project, you will obtain
    its pure profit and the profit will be added to your total capital.

    Pick a list of at most k distinct projects from given projects to maximize
    your final capital, and return the final maximized capital.

    The answer is guaranteed to fit in a 32-bit signed integer.

    =============================================================================================
    FUNCTION: int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital);
    =============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
    Output: 4
    Explanation: Since your initial capital is 0, you can only start the
    project indexed 0.  After finishing it you will obtain profit 1 and your
    capital becomes 1.  With capital 1, you can either start the project
    indexed 1 or the project indexed 2.  Since you can choose at most 2
    projects, you need to finish the project indexed 2 to get the maximum
    capital.  Therefore, output the final maximized capital, which is 0 + 1 + 3
    = 4.


    --- Example 2 ---
    Input: k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
    Output: 6


    *** Constraints ***
    1 <= k <= 10^5
    0 <= w <= 10^9
    n == profits.length
    n == capital.length
    1 <= n <= 10^5
    0 <= profits[i] <= 10^4
    0 <= capital[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    1. Sort Projects by Capital:
       Begin by sorting the projects based on the capital required to ensure
       you look at the cheapest projects first.

    2. Use Max-Heap for Profits:
       Employ a max-heap (inverted to a min-heap using negative values) to
       always have quick access to the project with the highest available
       profit.

    3. Process Projects Within Capital:
       As long as there are projects you can afford, add their profits
       (negatively) to the heap.

    4. Select Top Profit Projects:
       For up to k iterations, choose the most profitable project you can
       afford by popping from the heap, increasing your capital.

    5. Resulting Capital:
       After potentially choosing k projects, the resulting capital is the
       maximum capital achieved.

*/

/* Time  Beats: 76.67% */
/* Space Beats: 42.83% */

/* Time  Complexity: O(n * logn + k * logn) */
/* Space Complexity: O(n)                   */
class Solution {
public:
    int findMaximizedCapital(int k, int w, std::vector<int>& profits, std::vector<int>& capital)
    {
        const int n = profits.size();

        std::vector<std::pair<int, int>> projects;

        // Creating vector of pairs (capital, profits)
        for (int i = 0; i < n; ++i)
            projects.emplace_back(capital[i], profits[i]);

        // Sorting projects by capital required
        std::sort(projects.begin(), projects.end());

        // Max-heap to store profits, using greater to create a max-heap
        std::priority_queue<int> maxHeap;
        int i = 0;

        // Main loop to select up to k projects
        for (int j = 0; j < k; ++j)
        {
            // Add all profitable projects that we can afford
            while (i < n && projects[i].first <= w)
            {
                maxHeap.push(projects[i].second);
                i++;
            }

            // If no projects can be funded, break out of the loop
            if (maxHeap.empty())
                break;

            // Otherwise, take the project with the maximum profit
            w += maxHeap.top();
            maxHeap.pop();
        }

        return w;
    }
};
