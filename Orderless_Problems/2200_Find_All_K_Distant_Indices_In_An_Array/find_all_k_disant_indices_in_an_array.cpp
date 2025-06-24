/*
    ============
    === EASY ===
    ============

    ============================================
    2200) Find All K-Distant Indices in an Array
    ============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums and two integers key and k.
    A k-distant index is an index i of nums for which there exists at least one
    index j such that |i - j| <= k and nums[j] == key.

    Return a list of all k-distant indices sorted in increasing order.

    =============================================================================
    FUNCTION: vector<int> findKDistantIndices(vector<int>& nums, int key, int k);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,4,9,1,3,9,5], key = 9, k = 1
    Output: [1,2,3,4,5,6]
    Explanation: Here, nums[2] == key and nums[5] == key.
    - For index 0, |0 - 2| > k and |0 - 5| > k, so there is no j where |0 - j| <= k and nums[j] == key. Thus, 0 is not a k-distant index.
    - For index 1, |1 - 2| <= k and nums[2] == key, so 1 is a k-distant index.
    - For index 2, |2 - 2| <= k and nums[2] == key, so 2 is a k-distant index.
    - For index 3, |3 - 2| <= k and nums[2] == key, so 3 is a k-distant index.
    - For index 4, |4 - 5| <= k and nums[5] == key, so 4 is a k-distant index.
    - For index 5, |5 - 5| <= k and nums[5] == key, so 5 is a k-distant index.
    - For index 6, |6 - 5| <= k and nums[5] == key, so 6 is a k-distant index.
    Thus, we return [1,2,3,4,5,6] which is sorted in increasing order.

    --- Example 2 ---
    Input: nums = [2,2,2,2,2], key = 2, k = 2
    Output: [0,1,2,3,4]
    Explanation: For all indices i in nums, there exists some index j such that
    |i - j| <= k and nums[j] == key, so every index is a k-distant index.
    Hence, we return [0,1,2,3,4].


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 1000
    key is an integer from the array nums.
    1 <= k <= nums.length

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.85% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k)
    {
        const int N = nums.size();
        vector<int> result;

        int R = 0;  // unjudged minimum index
        for (int i = 0; i < N; i++)
        {
            if (nums[i] == key)
            {
                int L = max(R, i - k);

                R = min(N-1, i + k) + 1;

                for (int j = L; j < R; j++)
                    result.push_back(j);
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Even though this one is less Space efficient, it's beneficial to be aware
    of this "Sweep Line" technique as it comes were frequently, especially in
    contests.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  32.45% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Line_Sweep {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k)
    {
        const int N = nums.size();
        vector<int> result;

        int sweep_line[1001] = {0};
        int rightmost_modified_index = -1;

        for (int current_index = 0; current_index < N; current_index++)
        {
            if (nums[current_index] == key)
            {
                int interval_start_idx = max(0, current_index - k);
                int interval_end_idx = min(N, current_index + k + 1);

                sweep_line[interval_start_idx]++;
                sweep_line[interval_end_idx]--;

                rightmost_modified_index = max(rightmost_modified_index, interval_end_idx);
            }
        }

        int current_coverage = 0;
        for (int index = 0; index <= rightmost_modified_index; index++)
        {
            current_coverage += sweep_line[index];

            if (current_coverage > 0)
                result.push_back(index);
        }

        return result;
    }
};
