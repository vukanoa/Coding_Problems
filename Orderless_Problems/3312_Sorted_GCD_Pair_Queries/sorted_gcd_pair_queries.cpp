/*
    ============
    === HARD ===
    ============

    =============================
    3312) Sorted GCD Pair Queries
    =============================

    ============
    Description:
    ============

    You are given an integer array nums of length n and an integer array
    queries.

    Let gcdPairs denote an array obtained by calculating the GCD of all
    possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting
    these values in ascending order.

    For each query queries[i], you need to find the element at index queries[i]
    in gcdPairs.

    Return an integer array answer, where answer[i] is the value at
    gcdPairs[queries[i]] for each query.

    The term gcd(a, b) denotes the greatest common divisor of a and b.

    ===============================================================================
    FUNCTION: vector<int> gcdValues(vector<int>& nums, vector<long long>& queries);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,4], queries = [0,2,2]
    Output: [1,2,2]
    Explanation:
    gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].
    After sorting in ascending order, gcdPairs = [1, 1, 2].
    So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].

    --- Example 2 ---
    Input: nums = [4,4,2,1], queries = [5,3,1,0]
    Output: [4,2,1,1]
    Explanation:
    gcdPairs sorted in ascending order is [1, 1, 1, 2, 2, 4].

    --- Example 3 ---
    Input: nums = [2,2], queries = [0,0]
    Output: [2,2]
    Explanation:
    gcdPairs = [2].


    *** Constraints ***
    2 <= n == nums.length <= 10^5
    1 <= nums[i] <= 5 * 10^4
    1 <= queries.length <= 10^5
    0 <= queries[i] < n * (n - 1) / 2

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    M is the maximum value in nums.

    First thing that comes to mind is a Brute-Force generation of ALL of the
    pairs and the finding the GCD of each pair. However since N--i.e. the size
    of nums--is 10^5, this is impossible without getting TLE, since O(N^2) is
    10^10 which will NOT pass on any Coding platform.


    The key things here is to realize that even though there are N^2 pairs, the
    range of possible GCD values is actually small--EVery GCD lies in the
    range [1, max_value_in_nums], where max_value_in_nums = 5 * 10^4.

    Therefore instead of generating all of the pairs, we consider only all the
    possible GCD values and count how many pairs have that GCD value.


    First, we have to obtain the frequency count of each element in nums. We
    do that by storing it in the "freq_of_elem" vector.

    Then, for every possible val--i.e. GCD_value--[1, max_value_in_nums],
    enumerate all of its multiples to count how many elements in nums are
    divisible by this val, i.e. by this GCD_value.

    Any pair formed from these elements has a GCD of AT LEAST "curr_gcd".

    However, "at least curr_gcd" is NOT the same as "exactly curr_gcd", because
    it also includes pairs whose GCD is:

        (2 * curr_gcd), (3 * curr_gcd), ...

    To obtain the number of pairs whose GCD is EXACTLY curr_gcd, we traverse
    curr_gcd from large to small and apply the INCLUSION-EXCLUSION principle.

    Specifically, we first count ALL pairs whose GCD is AT LEAST "curr_gcd",
    then we subtract the number of pairs whose GCD is:

        (2 * curr_gcd), (3 * curr_gcd), ...

    The REMAINING count is EXACTLY the number of pairs whose GCD equals EXACTLY
    "curr_gcd".

    
    And finally we compute the Prefix_Sum of these counts. THe prefix sum at
    index i represents th enumber of pairs whose GCD is AT MOST 'i'. Foe each
    query "queries[i]", we perform a Binary_Search on the Prefix_Sum array to
    find the smallest GCD value whose cumulative count exceeeds the query.

*/

/* Time  Beats: 78.67% */
/* Space Beats: 86.167% */

/* Time  Complexity: O(M * logM  +  Q * logM) */ // M is max(nums[i])
/* Space Complexity: O(M)                     */
class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries)
    {
        const int N = nums.size();
        const int Q = queries.size();
        vector<int> result(Q);

        int max_val = *max_element(nums.begin(), nums.end());

        vector<int>       freq_of_elem     (max_val + 1, 0);
        vector<long long> pair_count_of_gcd(max_val + 1, 0);

        for (const int& num : nums)
            freq_of_elem[num]++;

        for (int curr_gcd = max_val; curr_gcd > 0; curr_gcd--)
        {
            long long divisible_element_count     = 0;
            long long pair_count_with_higher_gcd  = 0;

            for (int multiple = curr_gcd; multiple <= max_val; multiple += curr_gcd)
            {
                divisible_element_count    += freq_of_elem[multiple];
                pair_count_with_higher_gcd += pair_count_of_gcd[multiple];
            }

            pair_count_of_gcd[curr_gcd] = (divisible_element_count * (divisible_element_count - 1) / 2) - pair_count_with_higher_gcd;
        }

        /* Prefix Sum */
        partial_sum(pair_count_of_gcd.begin(), pair_count_of_gcd.end(), pair_count_of_gcd.begin());


        for (int query_idx = 0; query_idx < Q; query_idx++)
        {
            auto first_greater_prefix = upper_bound(pair_count_of_gcd.begin(), pair_count_of_gcd.end(), queries[query_idx]);

            result[query_idx] = first_greater_prefix - pair_count_of_gcd.begin();
        }

        return result;
    }
};
