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

#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We can ONLY profit from the projects we can afford to start, i.e. we have
    (w + obtained_capital_so_far) >= capita[i];

    But, since we can finish at most k projects, we always want to finish
    projects that will give us the biggest ROI(Return of Investement).

    However, it is VERY important to note this: We don't actually "invest"
    anything. Meaning, once we start some project with capital X, we don't lose
    X profit.

    This is unintuitive, but that's how it's specified in the Description.

    But the point still remains--We should ALWAYS take the biggest profits from
    the projects we can afford to start.

        (i.e. our (w + obtained_capital_so_far) > capital[i])


    Therefore, first, we push all of the projects we can afford to work on and
    we push it to a MAX_HEAP. However, we're only interested in profits,
    therefore we'll have only priority_queue<int> and not of pair<int,int>.

    Then, after we're done obtaining the highest profit from the projects we
    can afford to start, we decrement our 'k' and since we know have a new:
    "final_capital" values, which is incremeneted by the highest profit of a
    project we can afford, we know need to push all of the additional projects
    we can afford to work on.

    It's important to note that the while loop below will execute N times
    IN TOTAL, per problem. We'll process each profit AT MOST once.

        // This block will execute N times IN TOTAL and NOT N times per k
        while (i < N && final_capital >= capitals_profits[i].first)
        {
            max_heap.push(capitals_profits[i].second);

            // Increment
            i++;
        }

    At the end we simply return "final_capital".

*/

/* Time  Beats: 61.52% */
/* Space Beats: 71.14% */

/* Time  Complexity: O(N * logN + K * logN) */
/* Space Complexity: O(N)                   */
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital)
    {
        const int N = profits.size();
        int final_capital = w;

        priority_queue<int> max_heap;

        vector<pair<int,int>> capitals_profits;
        for (int i = 0; i < N; i++)
            capitals_profits.push_back( {capital[i], profits[i]} );

        /* Sort */
        sort(capitals_profits.begin(), capitals_profits.end());

        int i = 0;
        // This block will execute N times IN TOTAL, per problem
        while (i < N && final_capital >= capitals_profits[i].first)
        {
            max_heap.push(capitals_profits[i].second);

            // Increment
            i++;
        }

        // O(K * logN) (entire block)
        while (k > 0 && ! max_heap.empty()) // O(K)
        {
            int curr_profit = max_heap.top();
            max_heap.pop(); // O(logN)

            final_capital += curr_profit;

            // This block will execute N times IN TOTAL and NOT N times per k
            while (i < N && final_capital >= capitals_profits[i].first)
            {
                max_heap.push(capitals_profits[i].second);

                // Increment
                i++;
            }

            // Decrement
            k--;
        }

        return final_capital;
    }
};
