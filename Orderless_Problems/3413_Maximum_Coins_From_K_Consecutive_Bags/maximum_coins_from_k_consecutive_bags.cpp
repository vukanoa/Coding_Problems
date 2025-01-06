/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    3413) Maximum Coins From K Consecutive Bags
    ===========================================

    ============
    Description:
    ============

    There are an infinite amount of bags on a number line, one bag for each
    coordinate. Some of these bags contain coins.

    You are given a 2D array coins, where coins[i] = [li, ri, ci] denotes that
    every bag from li to ri contains ci coins.

    The segments that coins contain are non-overlapping.

    You are also given an integer k.

    Return the maximum amount of coins you can obtain by collecting k
    consecutive bags.

    ====================================================================
    FUNCTION: long long maximumCoins(vector<vector<int>>& coins, int k);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: coins = [[8,10,1],[1,3,2],[5,6,4]], k = 4
    Output: 10
    Explanation: Selecting bags at positions [3, 4, 5, 6] gives the maximum
                 number of coins: 2 + 0 + 4 + 4 = 10.


    --- Example 2 ---
    Input: coins = [[1,10,3]], k = 2
    Output: 6
    Explanation: Selecting bags at positions [1, 2] gives the maximum number of
                 coins: 3 + 3 = 6.


    *** Constraints ***
    1 <= coins.length <= 10^5
    1 <= k <= 10^9
    coins[i] == [li, ri, ci]
    1 <= li <= ri <= 10^9
    1 <= ci <= 1000
    The given segments are non-overlapping.

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.89% */
/* Space Beats: 77.78% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_2 {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k)
    {
        // Sort the array and store starts and ends of interval seperately to make binary search easier
        const int N = coins.size();

        /* Sort */
        sort(coins.begin(), coins.end()); 

        vector<long long> prefix(coins.size()+1, 0); 

        vector<int> starts(N);
        vector<int> ends(N);

        //precalculate the prefix sum for calculation of score
        for (int i = 0; i < N; i++)
        {
            int& L = coins[i][0];
            int& R = coins[i][1];
            int& curr_coins = coins[i][2];

            starts[i] = L;
            ends[i]   = R; 

            prefix[i+1] = prefix[i] + 1LL*(R - L + 1) * curr_coins;
        }

        long long result = 0;

        // First loop: Treat each coin-containing interval as the start of the k-length interval
        for (int i = 0; i < N; i++)
        {
            long long curr = 0; // Score for this iteration

            int& L = coins[i][0];
            int& R = coins[i][1];
            int& curr_coins = coins[i][2];

            int target = L + k - 1; 

            int idx = lower_bound(ends.begin(), ends.end(), target) - ends.begin();
            curr += 1LL*(prefix[idx] - prefix[i]); 

            if (idx < N)
                curr += 1LL*(max(0, target - coins[idx][0] + 1)) * coins[idx][2]; // Handle partial overlap


            result = max(curr, result); 
        }

        // Second loop: Treat each coin-containing interval as the end of the k-length interval
        for (int i = 0; i < N; i++)
        {
            long long curr = 0; // Score for this iteration

            int& L = coins[i][0];
            int& R = coins[i][1];
            int& curr_coins = coins[i][2];

            int target = R - k + 1; 
            int idx = lower_bound(starts.begin(), starts.end(), target) - starts.begin();

            curr += 1LL*(prefix[i+1] - prefix[idx]); 

            if (idx > 0)
                curr += 1LL*(max(0,  coins[idx-1][1] - target + 1)) * coins[idx-1][2]; // Handle partial overlap

            result = max(curr, result); 
        }
        
        return result;
    }
};
