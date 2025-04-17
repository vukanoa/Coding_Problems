/*
    ============
    === EASY ===
    ============

    =================================================
    2176) Count Equal and Divisible Pairs in an Array
    =================================================

    ============
    Description:
    ============

    Given a 0-indexed integer array nums of length n and an integer k, return
    the number of pairs (i, j) where 0 <= i < j < n, such that
    nums[i] == nums[j] and (i * j) is divisible by k.

    ===================================================
    FUNCTION: int countPairs(vector<int>& nums, int k);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,2,2,2,1,3], k = 2
    Output: 4
    Explanation:
    There are 4 pairs that meet all the requirements:
    - nums[0] == nums[6], and 0 * 6 == 0, which is divisible by 2.
    - nums[2] == nums[3], and 2 * 3 == 6, which is divisible by 2.
    - nums[2] == nums[4], and 2 * 4 == 8, which is divisible by 2.
    - nums[3] == nums[4], and 3 * 4 == 12, which is divisible by 2.

    --- Example 2 ---
    Input: nums = [1,2,3,4], k = 1
    Output: 0
    Explanation: Since no value in nums is repeated, there are no pairs (i,j)
    that meet all the requirements.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i], k <= 100

*/

#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute Force.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  31.03% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countPairs(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N-1; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if (nums[i] == nums[j] && ((i * j) % k == 0))
                    result++;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    If you know how to get factors of a number in O(sqrt(number)), then this
    shouldn't be that much of a problem.

        vector<int> factors;
        for (int f = 1; f * f <= k; f++)
        {
            if (f * f == k)
            {
                factors.push_back(f); // To STOP counting the same one twice
            }
            else if (k % f == 0)
            {
                factors.push_back(f);
                factors.push_back(k / f);
            }
        }

*/

/* Time  Beats: 28.60% */
/* Space Beats:  6.09% */

/* Time  Complexity: O(N * (logK + sqrt(K))) */
/* Space Complexity: O(N)           */
class Solution_Map_and_GCD {
public:
    int countPairs(vector<int>& nums, int k)
    {
        int result = 0;

        unordered_map<int, vector<int>> umap;

        for (int i = 0; i < nums.size(); i++)
            umap[nums[i]].push_back(i);

        vector<int> factors;
        for (int f = 1; f * f <= k; f++)
        {
            if (f * f == k)
            {
                factors.push_back(f); // To STOP counting the same one twice
            }
            else if (k % f == 0)
            {
                factors.push_back(f);
                factors.push_back(k / f);
            }
        }

        for (auto& [num, vec_of_indices] : umap)
        {
            unordered_map<int, int> umap_tmp;

            for (int i : vec_of_indices)
            {
                int curr_gcd = gcd(i, k);
                int need = k / curr_gcd;

                // Adding all previous j with j % need == 0
                result += umap_tmp[need];
                for (const int& f : factors)
                {
                    if (i % f == 0)
                        umap_tmp[f]++;
                }
            }
        }

        return result;
    }
};
