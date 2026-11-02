/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    4099) Minimum Operations to Sort with Locked Indices
    ====================================================

    ============
    Description:
    ============

    You are given an integer array nums of length n, where nums is a
    permutation of the integers in the range [1, n].

    You are also given a binary array locked of length n and an integer k.

        + locked[i] = 1 means index i is locked.
        + locked[i] = 0 means index i is unlocked.

    You may perform the following operations in any order:

        + Swap: Choose an index i such that both indices i and i + 1 are
                currently unlocked, and swap nums[i] and nums[i + 1].

        + Unlock: Choose an index i such that locked[i] = 1 and permanently
                  unlock it by setting locked[i] = 0.

    You may perform any number of swap operations but at most k unlock
    operations.

    Return the minimum total number of operations required to sort nums in
    strictly increasing order. If it is impossible, return -1.


    ---------------
    -- Follow Up --
    ---------------
    
        Can you solve this in O(nlog(n))?


    ===========================================================================
    FUNCTION: int minOperations(vector<int>& nums, vector<int>& locked, int k);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,3,4], locked = [0,1,0,1], k = 1
    Output: 2
    Explanation:
        Unlock index 1. The array locked becomes [0,0,0,1].
        Swap nums[0] and nums[1]. The array nums becomes [1,2,3,4].
    The total number of operations is 1 + 1 = 2.

    --- Example 2 ---
    Input: nums = [3,1,2], locked = [1,0,1], k = 2
    Output: 4
    Explanation:
        Unlock indices 0 and 2. All indices are now unlocked.
        Swap indices 0 and 1. The array nums becomes [1,3,2].
        Swap indices 1 and 2. The array nums becomes [1,2,3].
    The total number of operations is 2 + 2 = 4.

    --- Example 3 ---
    Input: nums = [2,3,1], locked = [1,0,0], k = 0
    Output: -1
    Explanation:
    Index 0 is locked, so its value cannot be moved. Since k = 0, no indices
    can be unlocked. Therefore, sorting the array is impossible.


    *** Constraints ***
    1 <= n == nums.length == locked.length <= 2000
    1 <= nums[i] <= n
    0 <= locked[i] <= 1
    nums is a permutation of the integers in the range [1, n].
    0 <= k <= n

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  57.14% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k)
    {
        const int N = nums.size();
        int unlock_count = 0;
        int swap_count   = 0;

        int max_val_so_far = -1;
        for (int i = 0; i < N; i++)
        {
            max_val_so_far = max(max_val_so_far, nums[i]);

            if (locked[i] == 1 && !(nums[i] == i+1 && max_val_so_far == i+1))
                ++unlock_count; // Unlock
        }


        if (unlock_count > k) // MORE unlocks are required than we are allowed
            return -1;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if (nums[i] > nums[j])
                    ++swap_count; // Swap
            }
        }

        return unlock_count + swap_count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Using Fenwick Tree (aka "BIT - Binary Indexed Tree").

*/

/* Time  Beats:  92.86% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Sum_Freqs_Fenwick_Tree { // 1-based
private:
    vector<long long> sum_freqs_fenwick;
    int n;

public:
    Sum_Freqs_Fenwick_Tree(int n)
        : n(n), sum_freqs_fenwick(n + 1, 0)
    {}

    long long sum(int L, int R)
    {
        return sum(R) - sum(L - 1);
    }

    long long sum(int number)
    {
        long long sum = 0;

        int i = number;
        while (i > 0)
        {
            sum += sum_freqs_fenwick[i];

            // Clear last SET bit
            i -= i & -i;
        }

        return sum;
    }

    void increase(int idx, long long delta)
    {
        int i = idx;
        while (i <= n)
        {
            sum_freqs_fenwick[i] += delta;

            // Add last SET bit
            // (Add value consisted of ONLY last bit of the current 'i' value)
            i += i & -i;
        }
    }
};

class Solution_Fenwick {
public:
    int minOperations(vector<int>& nums, vector<int>& locked, int k)
    {
        const int N = nums.size();
        long long unlock_count    = 0LL;
        long long inversion_count = 0LL;


        /* Find Required Unlocks */
        int max_val_so_far = -1;
        for (int i = 0; i < N; i++)
        {
            max_val_so_far = max(max_val_so_far, nums[i]);

            if (locked[i] == 1 && !(nums[i] == i+1 && max_val_so_far == i+1))
                ++unlock_count; // Unlock
        }

        if (unlock_count > k) // MORE unlocks are required than we are allowed
            return -1;



        /* Count Inversions */
        Sum_Freqs_Fenwick_Tree sum_fenwick(N);

        for (int i = N-1; i >= 0; i--)
        {
            inversion_count += sum_fenwick.sum(1, nums[i] - 1);
            sum_fenwick.increase(nums[i], 1);
        }

        return inversion_count + unlock_count;
    }
};
