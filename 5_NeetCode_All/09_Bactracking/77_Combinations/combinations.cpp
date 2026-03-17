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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.04% */
/* Space Beats: 99.05% */

/* Time  Complexity: O(C(n,k) * k) */
/* Space Complexity: O(C(n,k) * k) */
class Solution_Iterative {
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> result;
        vector<int> curr_combination(k, 0);

        int idx = 0;
        while (idx >= 0)
        {
            curr_combination[idx]++;

            if (curr_combination[idx] > n)
            {
                idx--;
                continue;
            }

            if (idx == k - 1)
            {
                result.push_back(curr_combination);
                continue;
            }

            curr_combination[idx + 1] = curr_combination[idx];

            // Increment
            idx++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is much slower than the previous ones, however it's still good
    to be aware of this approach.

*/

/* Time  Beats: 5.01% */
/* Space Beats: 5.36% */

/* Time  Complexity: O(n * 2^n) */
/* Space Complexity: O(n)       */
class Solution_Bit_Manipulation {
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> result;

        for (int mask = 0; mask < (1 << n); mask++)
        {
            vector<int> curr_combination;

            for (int bit = 0; bit < n; bit++)
            {
                if (mask & (1 << bit))
                    curr_combination.push_back(bit + 1);
            }

            if (curr_combination.size() == static_cast<unsigned>(k))
                result.push_back(curr_combination);
        }

        return result;
    }
};
