/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    611) Valid Triangle Number
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, return the number of triplets chosen from the
    array that can make triangles if we take them as side lengths of a triangle

    ================================================
    FUNCTION: int triangleNumber(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,2,3,4]
    Output: 3
    Explanation: Valid combinations are: 
    2,3,4 (using the first 2)
    2,3,4 (using the second 2)
    2,2,3

    --- Example 2 ---
    Input: nums = [4,2,3,4]
    Output: 4


    *** Constraints ***
    1 <= nums.length <= 1000
    0 <= nums[i] <= 1000

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 27.74% */
/* Space Beats: 42.88% */

/* Time  Complexity: O(N^2 * logN) */
/* Space Complexity: O(logN) */
class Solution {
public:
    int triangleNumber(vector<int>& nums)
    {
        /* Sort */
        sort(nums.begin(), nums.end());

        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N - 2; i++)
        {
            if (nums[i] == 0)
                continue; // Skip zero-length sides

            for (int j = i + 1; j < N - 1; j++)
            {
                /*
                    upper_bound returns first element > nums[i] + nums[j]

                    But why are we doing this?
                    I'm just going to leave this code here:

                    sort(nums.begin(), nums.end());

                    if (nums[0] + nums[1] <= nums[2]) // If this is TRUE we CANNOT form it
                        return "none";

                    if (nums[0] == nums[2])
                        return "equilateral";

                    if (nums[0] == nums[1] || nums[1] == nums[2])
                        return "isosceles";

                    return "scalene";



                    I.e. the only NON-valid triangle is ONLY

                        if (nums[0] + nums[1] <= nums[2])

                    is true.

                    Therefore, we want the OPPOSITE of that, i.e. we need our
                    nums[0] + nums[1] to be STRICTLY GREATER than nums[2].
                
                */
                auto iter = upper_bound(nums.begin() + j + 1, nums.end(), nums[i] + nums[j] - 1);
                
                result += iter - (nums.begin() + j + 1);
            }
        }

        return result;
    }
};
