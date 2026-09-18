/*
    ============
    === EASY ===
    ============

    ==========================================================
    1365) HOw Many Numbers are Smaller than the Current Number
    ==========================================================

    ============
    Description:
    ============

    Given the array nums, for each nums[i] find out how many numbers in the
    array are smaller than it. That is, for each nums[i] you have to count the
    number of valid j's such that j != i and nums[j] < nums[i].

    Return the answer in an array.

    ===================================================================
    FUNCTION: vector<int> smallerNumbersThanCurrent(vector<int>& nums);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [8,1,2,2,3]
    Output: [4,0,1,1,3]
    Explanation: 
    For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3). 
    For nums[1]=1 does not exist any smaller number than it.
    For nums[2]=2 there exist one smaller number than it (1). 
    For nums[3]=2 there exist one smaller number than it (1). 
    For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).

    --- Example 2 ---
    Input: nums = [6,5,4,8]
    Output: [2,1,0,3]

    --- Example 3 ---
    Input: nums = [7,7,7,7]
    Output: [0,0,0,0]


    *** Constraints ***
    2 <= nums.length <= 500
    0 <= nums[i] <= 100

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
/* Space Beats:  25.84% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result;
        int count_smaller_than[101] = {};

        for (int i = 0 ; i < N; i++)
            ++count_smaller_than[nums[i]];

        for (int num = 1; num <= 100; num++)
            count_smaller_than[num] += count_smaller_than[num - 1];

        for (int i = 0; i < N; i++)
        {
            if (nums[i] == 0)
                result.push_back(0);
            else
                result.push_back(count_smaller_than[nums[i] - 1]);
        }

        return result;
    }
};
