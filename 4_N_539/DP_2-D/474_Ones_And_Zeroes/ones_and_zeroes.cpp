#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    474) Ones and Zeroes
    ===========================

    ============
    Description:
    ============

    You are given an array of binary strings strs and two integers m and n.

    Return the size of the largest subset of strs such that there are at most m
    0's and n 1's in the subset.

    A set x is a subset of a set y if all elements of x are also elements of y.

    ==============================================================
    FUNCTION: int findMaxForm(vector<string>& strs, int m, int n);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
    Output: 4

    Explanation: The largest subset with at most 5 0's and 3 1's is {"10",
                 "0001", "1", "0"}, so the answer is 4.  Other valid but
                 smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
                 {"111001"} is an invalid subset because it contains 4 1's,
                 greater than the maximum of 3.


    ["0", "1", "00", "01", "011", "010101"] m = 3, n = 6
    Out: 4


    --- Example 2 ---
    Input: strs = ["10","0","1"], m = 1, n = 1
    Output: 2

    Explanation: The largest subset is {"0", "1"}, so the answer is 2.




    *** Constraints ***
    1 <= strs.length <= 600
    1 <= strs[i].length <= 100
    strs[i] consists only of digits '0' and '1'.
    1 <= m, n <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    Clasical 1-0 Knapsack Dynamic Programming technique.

    This one is implemented using the Bottom-Up approach.

*/

/* Time  Beats: 73.08% */
/* Space Beats: 96.54% */

/* Time  Complexity: O(SIZE * m * n) */
/* Space Complexity: O(m * n)        */ //More Space efficient than memoization
class Solution_Bottom_Up {
public:
    int findMaxForm(std::vector<std::string>& strs, int m, int n)
    {
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

        for(auto& s : strs)
        {
            int zeros = std::count(s.begin(), s.end(), '0');
            int ones  = s.size() - zeros;

            for(int i = m; i >= zeros; i--)
            {
                for(int j = n; j >= (ones); j--)
                    dp[i][j] = std::max(dp[i][j], 1 + dp[i - zeros][j - ones]);
            }
        }

        return dp[m][n];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Clasical 1-0 Knapsack Dynamic Programming technique.

    This one is implemented using memoization.

*/

/*****************************************************************************/
/******************************** Memoization ********************************/
/*****************************************************************************/

/* Time  Beats: 58.21% */
/* Space Beats: 20.08% */

/* Time  Complexity: O(SIZE * m * n) */
/* Space Complexity: O(SIZE * m * n) */
class Solution_Memoization {
public:
    int findMaxForm(std::vector<std::string>& strs, int m, int n)
    {
        const int SIZE = strs.size();

        std::vector<std::vector<std::vector<int>>> cache(SIZE + 1, std::vector<std::vector<int>>(m + 1, std::vector(n + 1, -1)));

        std::vector<std::pair<int, int>> zeroes_ones;
        for (std::string& str : strs)
            zeroes_ones.push_back(count_0s_and_1s(str));

        return dfs(zeroes_ones, 0, m, n, cache);
    }

private:
    int dfs(std::vector<std::pair<int, int>>& zeroes_ones, int idx, int m, int n,
            std::vector<std::vector<std::vector<int>>>& cache)
    {
        // Base
        if(idx == zeroes_ones.size())
            return 0;

        if(cache[idx][m][n] != -1) // If already computed
            return cache[idx][m][n];

        int curr_zeroes = zeroes_ones[idx].first;
        int curr_ones  = zeroes_ones[idx].second;

        int take = 0;
        int skip = 0;

        // Take
        if(m - curr_zeroes >=0 && n - curr_ones >= 0)
            take = 1 + dfs(zeroes_ones, idx+1, m-curr_zeroes, n-curr_ones, cache);

        // Skip
        skip = 0 + dfs(zeroes_ones, idx+1, m, n, cache);

        cache[idx][m][n] = std::max(take, skip);

        return cache[idx][m][n];
    }

    std::pair<int,int> count_0s_and_1s(std::string str)
    {
        int zero = 0;
        int one  = 0;

        while (!str.empty())
        {
            char c = str[str.size()-1];
            str.pop_back();

            if (c == '1')
                one++;
            else
                zero++;
        }

        return {zero, one};
    }
};
