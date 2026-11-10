/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3819) Rotate Non Negative Elements
    ==================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    Rotate only the non-negative elements of the array to the left by k
    positions, in a cyclic manner.

    All negative elements must stay in their original positions and must not
    move.

    After rotation, place the non-negative elements back into the array in the
    new order, filling only the positions that originally contained
    non-negative values and skipping all negative positions.

    Return the resulting array.

    ===============================================================
    FUNCTION: vector<int> rotateElements(vector<int>& nums, int k);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,-2,3,-4], k = 3
    Output: [3,-2,1,-4]
    Explanation:
        The non-negative elements, in order, are [1, 3].
        Left rotation with k = 3 results in:
            [1, 3] -> [3, 1] -> [1, 3] -> [3, 1]
        Placing them back into the non-negative indices results in [3, -2, 1, -4].

    --- Example 2 ---
    Input: nums = [-3,-2,7], k = 1
    Output: [-3,-2,7]
    Explanation:
        The non-negative elements, in order, are [7].
        Left rotation with k = 1 results in [7].
        Placing them back into the non-negative indices results in [-3, -2, 7].

    --- Example 3 ---
    Input: nums = [5,4,-9,6], k = 2
    Output: [6,5,-9,4]
    Explanation:
        The non-negative elements, in order, are [5, 4, 6].
        Left rotation with k = 2 results in [6, 5, 4].
        Placing them back into the non-negative indices results in [6, 5, -9, 4].


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^5 <= nums[i] <= 10^5
    0 <= k <= 10^5

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

/* Time  Beats: 5.11% */
/* Space Beats: 5.84% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> rotateElements(vector<int>& nums, int k)
    {
        const int N = nums.size();

        unordered_map<int, vector<int>> umap; // {idx, {val, new_idx}}

        int jth_negative = 0;
        for (int i = 0; i < N; i++)
        {
            if (nums[i] < 0) // Negative
                continue;

            // Non-negative
            umap[i] = {nums[i], jth_negative};
            ++jth_negative;
        }

        const int SIZE = umap.size();
        if (SIZE <= 1)
            return nums;


        k %= SIZE;

        vector<int> vec(SIZE, 0);
        for (const auto& [idx, v] : umap)
        {
            const int& value        = v[0];
            const int& jth_negative = v[1];

            vec[jth_negative] = value;
        }


        for (const auto& [idx, v] : umap)
        {
            const int& value        = v[0];
            const int& jth_negative = v[1];

            int new_idx = (jth_negative - k + SIZE) % SIZE;

            vec[new_idx] = value;           
        }


        for (int i = N-1; i >= 0 &&  ! vec.empty(); i--)
        {
            if (nums[i] < 0)
                continue;

            nums[i] = vec.back();
            vec.pop_back();
        }


        return nums;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 58.76% */
/* Space Beats: 88.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    vector<int> rotateElements(vector<int>& nums, int k)
    {
        const int N = nums.size();

        vector<int> non_negs;
        non_negs.reserve(N);

        for (int i = 0; i < N; i++)
        {
            if (nums[i] >= 0)
                non_negs.push_back(nums[i]);
        }

        const int NON_NEGATIVES = non_negs.size();

        if (NON_NEGATIVES <= 1)
            return nums;

        k %= NON_NEGATIVES;

        // Rotate: left by k, equivalent to
        //     rotate(non_negs.begin(), non_negs.begin() + k, non_negs.end());
        if (k != 0)
        {
            vector<int> rotated(NON_NEGATIVES);

            for (int i = 0; i < NON_NEGATIVES; ++i)
            {
                int new_idx = (i - k + NON_NEGATIVES) % NON_NEGATIVES;
                rotated[new_idx] = non_negs[i];
            }
            non_negs = std::move(rotated);
        }

        int j = 0;
        for (int& val : nums)
        {
            if (val >= 0)
                val = non_negs[j++];
        }

        return nums;
    }
};
