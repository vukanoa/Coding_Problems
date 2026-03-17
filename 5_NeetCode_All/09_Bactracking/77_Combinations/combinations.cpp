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

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The most basic Backtracking.

*/

/* Time  Beats: 95.04% */
/* Space Beats: 69.74% */

/* Time  Complexity: O(C(n,k) * k) */
/* Space Complexity: O(k)          */ // O(C(n,k) * k) because of "results"
class Solution {
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> results;

        vector<int> curr_combination;
        backtracking(1, curr_combination, results, n, k);

        return results;
    }

private:
    void backtracking(int num, vector<int>& curr_combination, vector<vector<int>>& results, int n, int k)
    {
        if (curr_combination.size() == static_cast<unsigned>(k))
        {
            results.push_back(curr_combination); // O(k)
            return;
        }

        for (int i = num; i <= n; i++)
        {
            curr_combination.push_back(i);
            backtracking(i+1, curr_combination, results, n, k);
            curr_combination.pop_back();
        }
    }
};
