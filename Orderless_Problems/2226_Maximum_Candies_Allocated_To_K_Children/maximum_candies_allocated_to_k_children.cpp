/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    2226) Maximum Candies Allocated to K Children
    =============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array candies. Each element in the array
    denotes a pile of candies of size candies[i]. You can divide each pile into
    any number of sub piles, but you cannot merge two piles together.

    You are also given an integer k. You should allocate piles of candies to k
    children such that each child gets the same number of candies. Each child
    can be allocated candies from only one pile of candies and some piles of
    candies may go unused.

    Return the maximum number of candies each child can get.

    ================================================================
    FUNCTION: int maximumCandies(vector<int>& candies, long long k);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: candies = [5,8,6], k = 3
    Output: 5
    Explanation: We can divide candies[1] into 2 piles of size 5 and 3, and
                 candies[2] into 2 piles of size 5 and 1. We now have five
                 piles of candies of sizes 5, 5, 3, 5, and 1. We can allocate
                 the 3 piles of size 5 to 3 children. It can be proven that
                 each child cannot receive more than 5 candies.


    --- Example 2 ---
    Input: candies = [2,5], k = 11
    Output: 0
    Explanation: There are 11 children but only 7 candies in total, so it is
                 impossible to ensure each child receives at least one candy.
                 Thus, each child gets no candy and the answer is 0.


    *** Constraints ***
    1 <= candies.length <= 10^5
    1 <= candies[i] <= 10^7
    1 <= k <= 10^12

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 14.61% */
/* Space Beats: 73.33% */

/* Time  Complexity: O(N * logM) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k)
    {
        const int N = candies.size();
        unsigned long long result = 0;

        unsigned long long L = 1;
        unsigned long long R = accumulate(candies.begin(), candies.end(), 0ULL);

        if (R < k)
            return 0;
        else if (R == k)
            return 1;

        /* Binary Search */
        while (L <= R)
        {
            unsigned long long mid = L + (R - L) / 2; // To prevent Overflow, i.e. (L + R) / 2

            if (can_allocate_mid_for_k_children(candies, mid, k))
            {
                L = mid + 1;

                result = max(result, mid);
            }
            else
                R = mid - 1;
        }

        return result;
    }

private:
    bool can_allocate_mid_for_k_children(vector<int>& candies, unsigned long long& mid, long long k)
    {
        const int N = candies.size();

        unsigned long long can_allocate = 0;
        for (int i = 0; i < N; i++)
            can_allocate += static_cast<unsigned long long>(candies[i]) / mid;

        return can_allocate >= k;
    }
};
