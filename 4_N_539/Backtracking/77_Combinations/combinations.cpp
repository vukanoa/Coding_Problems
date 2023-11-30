#include <iostream>
#include <vector>
#include <numeric>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    77) Combinations
    ===========================

    ============
    Description:
    ============

    Given two integers n and k, return all possible combinations of k numbers
    chosen from the range [1, n].

    You may return the answer in any order.

    ====================================================
    FUNCTION: vector<vector<int>> combine(int n, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, k = 2
    Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
    Explanation: There are 4 choose 2 = 6 total combinations.
    Note that combinations are unordered, i.e., [1,2] and [2,1] are considered
    to be the same combination.


    --- Example 2 ---
    Input: n = 1, k = 1
    Output: [[1]]
    Explanation: There is 1 choose 1 = 1 total combination.


    *** Constraints ***
    1 <= n <= 20
    1 <= k <= n

*/

/*
    ------------
    --- IDEA ---
    ------------

    The most basic Backtracking.

*/

/* Time  Beats: 95.82% */
/* Space Beats: 61.50% */

/* Time  Complexity: O(n * k) */
/* Space Complexity: O(k)     */
class Solution_Verbose {
public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<int> values(n);
        std::iota(values.begin(), values.end(), 1);

        std::vector<std::vector<int>> result;
        std::vector<int> curr_comb = {};

        backtracking(values, k, 0, curr_comb, result);

        return result;
    }

private:
    void backtracking(std::vector<int>& values, int k, int start, std::vector<int>& curr_comb, std::vector<std::vector<int>>& result)
    {
        if (curr_comb.size() == k)
        {
            result.push_back(curr_comb);
            return;
        }

        for (int i = start; i < values.size(); i++)
        {
            curr_comb.push_back(values[i]);

            backtracking(values, k, i+1, curr_comb, result);

            curr_comb.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The most basic Backtracking.

*/

/* Time  Beats: 97.17% */
/* Space Beats: 65.40% */

/* Time  Complexity: O(n * k) */
/* Space Complexity: O(k)     */
class Solution_Concise {
public:
    std::vector<std::vector<int>> combine(int n, int k)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> curr_comb = {};

        backtracking(result, curr_comb, n, k, 1);

        return result;
    }

private:
    void backtracking(std::vector<std::vector<int>>& result, std::vector<int>& curr_comb,
                      int n, int k, int start)
    {
        if (curr_comb.size() == k)
        {
            result.push_back(curr_comb);
            return;
        }

        for (int i = start; i <= n; i++)
        {
            curr_comb.push_back(i);

            backtracking(result, curr_comb, n, k, i+1);

            curr_comb.pop_back();
        }
    }
};


int main()
{
    Solution_Verbose sol_verbose;
    Solution_Concise sol_concise;


    /* Example 1 */
    int n = 4;
    int k = 2;

    /* Example 2 */
    // int n = 1;
    // int k = 1;

    /* Example 3 */
    // int n = 5;
    // int k = 3;

    std::cout << "\n\t====================";
    std::cout << "\n\t=== COMBINATIONS ===";
    std::cout << "\n\t====================\n";


    /* Write Input */
    std::cout << "\n\tn: " << n;
    std::cout << "\n\tk: " << k << "\n";


    /* Solution */
    std::vector<std::vector<int>> results = sol_verbose.combine(n, k);
    // std::vector<std::vector<int>> results = sol_concise.combine(n, k);


    /* Write Output */
    bool first = true;
    std::cout << "\n\tResults: [";
    for (auto x: results)
    {
        if (!first)
            std::cout << ", ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            std::cout << xx;
            first_first = false;
        }
        std::cout << "]";

        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
