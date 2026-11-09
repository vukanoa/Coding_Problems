/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3784) Minimum Deletion Cost to Make All Characters Equal
    ========================================================

    ============
    Description:
    ============

    You are given a string s of length n and an integer array cost of the same
    length, where cost[i] is the cost to delete the ith character of s.

    You may delete any number of characters from s (possibly none), such that
    the resulting string is non-empty and consists of equal characters.

    Return an integer denoting the minimum total deletion cost required.

    =========================================================
    FUNCTION: long long minCost(string s, vector<int>& cost);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aabaac", cost = [1,2,3,4,1,10]
    Output: 11
    Explanation:
    Deleting the characters at indices 0, 1, 2, 3, 4 results in the string "c",
    which consists of equal characters, and the total cost is cost[0] + cost[1]
    + cost[2] + cost[3] + cost[4] = 1 + 2 + 3 + 4 + 1 = 11.


    --- Example 2 ---
    Input: s = "abc", cost = [10,5,8]
    Output: 13
    Explanation:
    Deleting the characters at indices 1 and 2 results in the string "a", which
    consists of equal characters, and the total cost is cost[1] + cost[2] = 5 +
    8 = 13.


    --- Example 3 ---
    Input: s = "zzzzz", cost = [67,67,67,67,67]
    Output: 0
    Explanation:
    All characters in s are equal, so the deletion cost is 0.


    *** Constraints ***
    n == s.length == cost.length
    1 <= n <= 10^5
    1 <= cost[i] <= 10^9
    s consists of lowercase English letters.

*/

#include <climits>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.06% */
/* Space Beats: 34.31% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long minCost(string s, vector<int>& cost)
    {
        const int N = s.size();
        long long result = LLONG_MAX;

        long long cost_to_delete_all = 0LL;
        long long cost_to_delete[26] = {};

        for (int i = 0; i < N; i++)
        {
            cost_to_delete[s[i] - 'a'] += cost[i];
            cost_to_delete_all += cost[i];
        }

        for (int chr_idx = 0; chr_idx < 26; chr_idx++)
        {
            long long diff = (cost_to_delete_all - cost_to_delete[chr_idx]);

            if (diff < result)
                result = diff;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 63.24% */
/* Space Beats: 53.92% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_One_Pass {
public:
    long long minCost(string s, vector<int>& cost)
    {
        const int N = s.size();


        long long cost_to_delete_all         = 0LL;
        long long highest_single_letter_cost = 0LL;

        long long cost_to_delete[26] = {};

        for (int i = 0; i < N; i++)
        {
            int chr_idx = s[i] - 'a';
            cost_to_delete[chr_idx] += cost[i];

            highest_single_letter_cost = max(highest_single_letter_cost, cost_to_delete[chr_idx]);
            cost_to_delete_all += cost[i];
        }

        return cost_to_delete_all - highest_single_letter_cost;
    }
};
