/*
    ============
    === EASY ===
    ============

    =============================================
    2089) Find Target Indices After Sorting Array
    =============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums and a target element target.

    A target index is an index i such that nums[i] == target.

    Return a list of the target indices of nums after sorting nums in
    non-decreasing order. If there are no target indices, return an empty list.
    The returned list must be sorted in increasing order.

    ===================================================================
    FUNCTION: vector<int> targetIndices(vector<int>& nums, int target);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,5,2,3], target = 2
    Output: [1,2]
    Explanation: After sorting, nums is [1,2,2,3,5].
    The indices where nums[i] == 2 are 1 and 2.

    --- Example 2 ---
    Input: nums = [1,2,5,2,3], target = 3
    Output: [3]
    Explanation: After sorting, nums is [1,2,2,3,5].
    The index where nums[i] == 3 is 3.

    --- Example 3 ---
    Input: nums = [1,2,5,2,3], target = 5
    Output: [4]
    Explanation: After sorting, nums is [1,2,2,3,5].
    The index where nums[i] == 5 is 4.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i], target <= 100

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Using library's implementations of "lower_bound" and "upper_bound". In an
    interview, it's important to ask your interviewer if he prefers that you
    write your Binary Search manually.

    Generaly speaking, it's always better to write it yourself so that you can
    show your skills. Binary Search is simple enough.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  15.91% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // O(logN) is Space Compl. of C++'s sort
class Solution_CPP_way {
public:
    vector<int> targetIndices(vector<int>& nums, int target)
    {
        const int N = nums.size();


        /* Sort */
        sort(nums.begin(), nums.end());
        
        auto first     = lower_bound(nums.begin(), nums.end(), target);
        int  first_idx = distance(nums.begin(), first);

        if (first == nums.end())
            return {};

        auto immediately_after_last_target     = upper_bound(nums.begin(), nums.end(), target);
        int  immediately_after_last_target_idx = distance(nums.begin(), immediately_after_last_target);

        vector<int> result;
        result.reserve(immediately_after_last_target_idx - first_idx);

        for (int i = first_idx; i < immediately_after_last_target_idx; i++)
            result.push_back(i);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    When you're manually writing Binary Search it's very important to ask
    yourself:

   Can a result of "N"(i.e. index "N") be a VALID output?

   In our case with my_upper_bound that INDEED can be the case. If the target
   is on the right bound of the "nums" vector, then upper_bound will return
   index "N".

   That's why we're calling both "my_lower_bound" and "my_upper_bound" with:

    (0, N, nums, target) and NOT with (0, N-1, nums, target)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.38% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // O(logN) is Space Compl. of C++'s sort
class Solution_Manual {
public:
    vector<int> targetIndices(vector<int>& nums, int target)
    {
        const int N = nums.size();

        /* Sort */
        sort(nums.begin(), nums.end());
        
        int first_idx = my_lower_bound(0, N, nums, target);

        if (first_idx == N) // If target doesn't exist at all
            return {};

        int immediately_after_last_target_idx = my_upper_bound(0, N, nums, target);

        vector<int> result;
        result.reserve(immediately_after_last_target_idx - first_idx);

        for (int i = first_idx; i < immediately_after_last_target_idx; i++)
            result.push_back(i);

        return result;
    }

private:
    int my_lower_bound(int low, int high, vector<int>& nums, int target)
    {
        while (low < high)
        {
            int mid = low + (high - low) / 2; // Left-leaning

            if (nums[mid] < target)
                low  = mid + 1;
            else
                high = mid;
        }

        return low; // Or "high" it does NOT matter
    }

    int my_upper_bound(int low, int high, vector<int>& nums, int target)
    {
        return my_lower_bound(low, high, nums, target+1);
    }
};
