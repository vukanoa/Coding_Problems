/*
    ============
    === HARD ===
    ============

    =========================================================
    3013) Divide an Array Into Subarrays With Minimum Cost II 
    =========================================================

    ============
    Description:
    ============

    You are given a 0-indexed array of integers nums of length n, and two
    positive integers k and dist.

    The cost of an array is the value of its first element. For example, the
    cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.

    You need to divide nums into k disjoint contiguous subarrays, such that the
    difference between the starting index of the second subarray and the
    starting index of the kth subarray should be less than or equal to dist. In
    other words, if you divide nums into the subarrays nums[0..(i1 - 1)],
    nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)], then ik-1 - i1 <= dist.

    Return the minimum possible sum of the cost of these subarrays.

    ====================================================================
    FUNCTION: long long minimumCost(vector<int>& nums, int k, int dist);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
    Output: 5
    Explanation: The best possible way to divide nums into 3 subarrays is:
    [1,3], [2,6,4], and [2]. This choice is valid because ik-1 - i1 is 5 - 2 =
    3 which is equal to dist. The total cost is nums[0] + nums[2] + nums[5]
    which is 1 + 2 + 2 = 5.
    It can be shown that there is no possible way to divide nums into 3
    subarrays at a cost lower than 5.

    --- Example 2 ---
    Input: nums = [10,1,2,2,2,1], k = 4, dist = 3
    Output: 15
    Explanation: The best possible way to divide nums into 4 subarrays is:
    [10], [1], [2], and [2,2,1]. This choice is valid because ik-1 - i1 is 3 -
    1 = 2 which is less than dist. The total cost is nums[0] + nums[1] +
    nums[2] + nums[3] which is 10 + 1 + 2 + 2 = 15.
    The division [10], [1], [2,2,2], and [1] is not valid, because the
    difference between ik-1 and i1 is 5 - 1 = 4, which is greater than dist.
    It can be shown that there is no possible way to divide nums into 4
    subarrays at a cost lower than 15.

    --- Example 3 ---
    Input: nums = [10,8,18,9], k = 3, dist = 1
    Output: 36
    Explanation: The best possible way to divide nums into 4 subarrays is:
    [10], [8], and [18,9]. This choice is valid because ik-1 - i1 is 2 - 1 = 1
    which is equal to dist.The total cost is nums[0] + nums[1] + nums[2] which
    is 10 + 8 + 18 = 36.
    The division [10], [8,18], and [9] is not valid, because the difference
    between ik-1 and i1 is 3 - 1 = 2, which is greater than dist.
    It can be shown that there is no possible way to divide nums into 3
    subarrays at a cost lower than 36.


    *** Constraints ***
    3 <= n <= 10^5
    1 <= nums[i] <= 10^9
    3 <= k <= n
    k - 2 <= dist <= n - 2

*/

#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 62.50% */
/* Space Beats: 40.63% */

/* Time  Complexity: O(N * log(dist)) */
/* Space Complexity: O(dist)          */
class Solution {
private:
    long long curr_sum = 0;

    multiset<int> small_set;
    multiset<int> large_set;

    void add_value(int value, int max_small_size)
    {
        small_set.insert(value);
        curr_sum += value;

        if (small_set.size() > max_small_size)
        {
            auto iter = prev(small_set.end());
            int to_move = *iter;

            curr_sum -= to_move;
            large_set.insert(to_move);
            small_set.erase(iter);
        }
    }

    void remove_value(int value)
    {
        auto it_small = small_set.find(value);

        if (it_small != small_set.end())
        {
            curr_sum -= value;
            small_set.erase(it_small);

            if (!large_set.empty())
            {
                auto it_large = large_set.begin();
                int to_move = *it_large;

                curr_sum += to_move;
                small_set.insert(to_move);
                large_set.erase(it_large);
            }
        }
        else
        {
            auto it_large = large_set.find(value);

            if (it_large != large_set.end())
                large_set.erase(it_large);
        }
    }

public:
    long long minimumCost(vector<int>& nums, int k, int dist)
    {
        const int N = nums.size();

        k--; // need k-1 elements besides nums[0]
        const int INIT_R = dist + 2;

        vector<int> window(nums.begin() + 1, nums.begin() + INIT_R);

        /* Nth element */
        nth_element(window.begin(), window.begin() + k, window.end());

        small_set = multiset<int>(window.begin()    , window.begin() + k);
        large_set = multiset<int>(window.begin() + k, window.end())      ;

        /* Accumulate */
        curr_sum = accumulate(window.begin(), window.begin() + k, 0LL);

        long long min_cost = nums[0] + curr_sum;

        int L = 1;
        int R = INIT_R;
        while (R < N)
        {
            remove_value(nums[L]);
            add_value(nums[R], k);

            min_cost = min(min_cost, nums[0] + curr_sum);

            // Increment
            L++;
            R++;
        }

        return min_cost;
    }
};
