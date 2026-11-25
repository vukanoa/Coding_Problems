/*
    ============
    === HARD ===
    ============

    ==============================
    3934) Smallest Unique Subarray
    ==============================

    ============
    Description:
    ============

    You are given an integer array nums.

    Find the minimum length of a subarray that is not identical to any other
    subarray in nums.

    Return an integer denoting the minimum possible length of such a subarray.

    Two subarrays are considered identical if they have the same length and the
    same elements in corresponding positions.

    ========================================================
    FUNCTION: int smallestUniqueSubarray(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,3,3]
    Output: 3
    Explanation:
        Subarrays of length 1: [3] → appears 3 times
        Subarrays of length 2: [3, 3] → appears 2 times
        Subarrays of length 3: [3, 3, 3] → appears once
    The subarray [3, 3, 3] is unique, so the smallest unique subarray length is
    3.


    --- Example 2 ---
    Input: nums = [2,1,2,3,3]
    Output: 1
    Explanation:
    Subarrays of length 1:
        [2] → appears 2 times
        [1] → appears once
        [3] → appears 2 times
    The subarray [1] is unique, so the smallest unique subarray length is 1.


    --- Example 3 ---
    Input: nums = [1,1,2,2,1]
    Output: 2
    Explanation:
    Subarrays of length 1:
        [1] → appears 3 times
        [2] → appears 2 times
    Subarrays of length 2:
        [1, 1] → appears once
        [1, 2] → appears once
        [2, 2] → appears once
        [2, 1] → appears once
    There is at least one subarray of length 2 that is unique, so the smallest
    unique subarray length is 2.



    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.58% */
/* Space Beats: 26.74% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class RollingHash {
public:
    const long long BASE = 1e5 + 3;
    const long long MOD  = 1e9 + 7;

    vector<long long> hash;
    vector<long long> power;

    RollingHash(vector<int>& nums)
    {
        int N = nums.size();

        hash.resize(N + 1, 0);
        power.resize(N + 1, 1);

        // Precompute PREFIX hashes and powers
        for (int i = 0; i < N; i++)
        {
            hash[i + 1]  = (hash[i]  * BASE + nums[i]) % MOD;
            power[i + 1] = (power[i] * BASE          ) % MOD;
        }
    }

    long long get_hash(int L, int R) // 0-based indices
    {
        return (hash[R + 1]  -  hash[L] * power[R - L + 1] % MOD + MOD) % MOD;
    }
};

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums)
    {
        const int N = nums.size();

        RollingHash rolling_hash(nums);

        int low  = 1;
        int high = N;

        while (low < high)
        {
            int mid = low + (high - low) / 2; // Low-leaning mid
            int& subarray_len = mid;

            unordered_map<long long, int> hash_frequencies;

            // Count frequencies of subarray hashes of length "subarray_len"
            for (int i = 0; i + subarray_len <= N; i++)
            {
                int start_idx = i;
                int end_idx   = i + subarray_len - 1;

                long long hash = rolling_hash.get_hash(start_idx, end_idx);

                ++hash_frequencies[hash];
            }

            // Check if a unique subarray exists
            bool has_unique_subarray = false;

            for (const auto& [hash, frequency] : hash_frequencies)
            {
                if (frequency == 1)
                {
                    has_unique_subarray = true;
                    break;
                }
            }

            if (has_unique_subarray)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};
