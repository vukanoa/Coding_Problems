/*
    ============
    === HARD ===
    ============

    ===========================
    3850) Count Sequences to K
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums, and an integer k.

    Start with an initial value val = 1 and process nums from left to right. At
    each index i, you must choose exactly one of the following actions:

        + Multiply val by nums[i].
        + Divide val by nums[i].
        + Leave val unchanged.

    After processing all elements, val is considered equal to k only if its
    final rational value exactly equals k.

    Return the count of distinct sequences of choices that result in val == k.

    =====
    Note: Division is rational (exact), not integer division. For example, 2 /
          4 = 1 / 2. 
    =====

    =============================================================
    FUNCTION: int countSequences(vector<int>& nums, long long k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,2], k = 6
    Output: 2

    --- Example 2 ---
    Input: nums = [4,6,3], k = 2
    Output: 2

    --- Example 3 ---
    Input: nums = [1,5], k = 1
    Output: 3


    *** Constraints ***
    1 <= nums.length <= 19
    1 <= nums[i] <= 6
    1 <= k <= 10^15

*/

#include <map>
#include <tuple>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.45% */
/* Space Beats: 52.91% */

/* Time  Complexity: O(3^N * log(UNIQUE_STATES)) */
/* Space Complexity: O(3^N)                      */
class Solution {
private:
    struct State {
        long long idx;
        long long numinator;
        long long denominator;

        bool operator<(const State& other) const
        {
            return tie(idx      , numinator      , denominator      ) <
                   tie(other.idx, other.numinator, other.denominator);
        }
    };

    map<State, int> memo; // std::map has a built-in comparator!

public:
    int countSequences(vector<int>& nums, long long k)
    {
        memo.clear();

        return solve(0, 1, 1, nums, k); // (idx, numinator, denominator, nums, k)
    }

private:
    long long my_gcd(long long a, long long b)
    {
        long long result = 1LL;

        while (b > 0)
        {
            long long tmp = b;

            b = a % b;
            a = tmp;
        }

        return a;
    }

    pair<long long, long long> simplify_fraction(long long numinator, long long denominator)
    {
        long long curr_gcd = my_gcd(numinator, denominator);

        numinator   /= curr_gcd;
        denominator /= curr_gcd;

        return {numinator, denominator};
    }

    long long solve(long long idx, long long numinator, long long denominator, vector<int>& nums, long long k)
    {
        const int N = nums.size();

        auto fraction_components = simplify_fraction(numinator, denominator);
        numinator   = fraction_components.first;
        denominator = fraction_components.second;

        if (idx == N)
            return (numinator == k && denominator == 1) ? 1 : 0; // Could be without ternary, but it's more expressive like this

        State state = {idx, numinator, denominator};
        if (memo.count(state))
            return memo[state];

        long long result = 0LL;

        result += solve(idx+1, numinator            , denominator            , nums, k); // Leave    "val" unchanged
        result += solve(idx+1, numinator * nums[idx], denominator            , nums, k); // Multiply "val" by nums[i] (i.e. multiple the numinator   by nums[i])
        result += solve(idx+1, numinator            , denominator * nums[idx], nums, k); // Divide   "val" by nums[i] (i.e. multiply the denominator by nums[i])

        return memo[state] = result;
    }
};
