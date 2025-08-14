/*
    ============
    === EASY ===
    ============

    ============================
    2784) Check if Array is Good
    ============================

    ============
    Description:
    ============

    You are given an integer array nums. We consider an array good if it is a
    permutation of an array base[n].

    base[n] = [1, 2, ..., n - 1, n, n] (in other words, it is an array of
    length n + 1 which contains 1 to n - 1 exactly once, plus two occurrences
    of n). For example, base[1] = [1, 1] and base[3] = [1, 2, 3, 3].

    Return true if the given array is good, otherwise return false.

    =====
    Note: A permutation of integers represents an arrangement of these numbers.
    =====

    =========================================
    FUNCTION: bool isGood(vector<int>& nums);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2, 1, 3]
    Output: false
    Explanation: Since the maximum element of the array is 3, the only
                 candidate n for which this array could be a permutation of
                 base[n], is n = 3. However, base[3] has four elements but
                 array nums has three. Therefore, it can not be a permutation
                 of base[3] = [1, 2, 3, 3]. So the answer is false.

    --- Example 2 ---
    Input: nums = [1, 3, 3, 2]
    Output: true
    Explanation: Since the maximum element of the array is 3, the only
                 candidate n for which this array could be a permutation of
                 base[n], is n = 3. It can be seen that nums is a permutation
                 of base[3] = [1, 2, 3, 3] (by swapping the second and fourth
                 elements in nums, we reach base[3]). Therefore, the answer is
                 true.

    --- Example 3 ---
    Input: nums = [1, 1]
    Output: true
    Explanation: Since the maximum element of the array is 1, the only
                 candidate n for which this array could be a permutation of
                 base[n], is n = 1. It can be seen that nums is a permutation
                 of base[1] = [1, 1]. Therefore, the answer is true.

    --- Example 4 ---
    Input: nums = [3, 4, 4, 1, 2, 1]
    Output: false
    Explanation: Since the maximum element of the array is 4, the only
                 candidate n for which this array could be a permutation of
                 base[n], is n = 4. However, base[4] has five elements but
                 array nums has six. Therefore, it can not be a permutation of
                 base[4] = [1, 2, 3, 4, 4]. So the answer is false.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= num[i] <= 200

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 34.39% */
/* Space Beats: 39.76% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    bool isGood(vector<int>& nums)
    {
        const int SIZE = nums.size(); // Not to confuse it with 'n'

        if (SIZE == 2)
            return nums[0] == 1 && nums[1] == 1;

        /* Sort */
        sort(nums.begin(), nums.end());
        
        int last = nums.back();
        nums.pop_back();

        vector<int> sorted(SIZE - 1);
        iota(sorted.begin(), sorted.end(), 1);

        return nums == sorted && last == SIZE - 1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.98% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Space Complexity of C++'s sort
class Solution_Sorting_Simple {
public:
    bool isGood(vector<int>& nums)
    {
        const size_t n = nums.size() - 1;

        /* Sort */
        sort(begin(nums), end(nums));

        for (size_t i = 0; i < nums.size(); i++)
        {
            if (nums[i] != min(n, i + 1))
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.98% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    bool isGood(vector<int>& nums)
    {
        const int SIZE = nums.size();

        for (int i = 0; i < SIZE;)
        {
            if (nums[i] > SIZE)
                return false;

            int correct_idx = nums[i] - 1;

            if (nums[correct_idx] == nums[i])
                i++;
            else
                swap(nums[correct_idx], nums[i]);
        }

        for (int i = 0; i < SIZE; i++)
        {
            if (nums[i] != i + 1 && i != SIZE - 1)
                return false;
        }

        return SIZE >= 2 && nums[SIZE-1] == SIZE-1 && nums[SIZE-2] == SIZE-1;
    }
};
