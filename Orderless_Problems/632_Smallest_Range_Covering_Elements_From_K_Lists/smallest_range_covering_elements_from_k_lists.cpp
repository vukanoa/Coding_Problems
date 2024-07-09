#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === HARD ===
    ============

    ==================================================
    632) Smallest Range Covering Elements from K Lists
    ==================================================

    ============
    Description:
    ============

    You have k lists of sorted integers in non-decreasing order. Find the
    smallest range that includes at least one number from each of the k lists.

    We define the range [a, b] is smaller than range [c, d] if b - a < d - c or
    a < c if b - a == d - c.

    ===============================================================
    FUNCTION: vector<int> smallestRange(vector<vector<int>>& nums);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
    Output: [20,24]
    Explanation:
    List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
    List 2: [0, 9, 12, 20], 20 is in range [20,24].
    List 3: [5, 18, 22, 30], 22 is in range [20,24].


    --- Example 2 ---
    Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
    Output: [1,1]


    *** Constraints ***
    nums.length == k
    1 <= k <= 3500
    1 <= nums[i].length <= 50
    -10^5 <= nums[i][j] <= 10^5
    nums[i] is sorted in non-decreasing order.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 15.73% */
/* Space Beats:  6.04% */

/* Time  Complexity: O(N + M*log(N)) */
/* Space Complexity: O(N)            */
class Solution {
public:
    std::vector<int> smallestRange(std::vector<std::vector<int>>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        std::priority_queue<std::vector<int>,
                            std::vector<std::vector<int>>,
                            std::greater<std::vector<int>>> min_heap;

        int n = nums.size();
        int maximum = -1e9;

        for(int i = 0; i < n; i++)
        {
            min_heap.push({nums[i][0],i,0});
            maximum = std::max(maximum, nums[i][0]);
        }

        int left;
        int right;
        int range = 1e9;

        while (min_heap.size() > 0)
        {
            auto it = min_heap.top();
            min_heap.pop();

            int minimum = it[0];
            int i    = it[1];
            int j    = it[2];

            if (maximum - minimum < range)
            {
                left  = minimum;
                right = maximum;
                range = maximum - minimum;
            }

            if (j >= nums[i].size())
                break;

            min_heap.push({nums[i][j], i, j+1});
            maximum = std::max(maximum, nums[i][j]);
        }

        return {left,right};
    }
};
