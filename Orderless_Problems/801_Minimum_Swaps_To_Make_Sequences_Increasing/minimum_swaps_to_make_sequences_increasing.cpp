#include <iostream>
#include <vector>
#include <climits>

/*
    ============
    === HARD ===
    ============

    ===============================================
    801) Minimum Swaps To Make Sequences Increasing
    ===============================================

    ============
    Description:
    ============

    You are given two integer arrays of the same length nums1 and nums2. In one
    operation, you are allowed to swap nums1[i] with nums2[i].

        For example, if nums1 = [1,2,3,8], and nums2 = [5,6,7,4], you can swap
        the element at i = 3 to obtain nums1 = [1,2,3,4] and nums2 = [5,6,7,8].

    Return the minimum number of needed operations to make nums1 and nums2
    strictly increasing. The test cases are generated so that the given input
    always makes it possible.

    An array arr is strictly increasing if and only if arr[0] < arr[1] < arr[2]
    < ... < arr[arr.length - 1].

    ==============================================================
    FUNCTION: int minSwap(vector<int>& nums1, vector<int>& nums2);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,3,5,4], nums2 = [1,2,3,7]
    Output: 1
    Explanation:
    Swap nums1[3] and nums2[3]. Then the sequences are:
    nums1 = [1, 3, 5, 7] and nums2 = [1, 2, 3, 4]
    which are both strictly increasing.


    --- Example 2 ---
    Input: nums1 = [0,3,5,8,9], nums2 = [2,1,4,6,9]
    Output: 1


    *** Constraints ***
    2 <= nums1.length <= 10^5
    nums2.length == nums1.length
    0 <= nums1[i], nums2[i] <= 2 * 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    DP Using Memoization.

    TODO

*/

/* Time  Beats: 95.93% */
/* Space Beats: 82.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minSwap(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int n = nums1.size();
        int dp[n][2];

        for(int i = 0; i < n; i++)
        {
            dp[i][0]=INT_MAX;
            dp[i][1]=INT_MAX;
        }

        dp[0][0] = 0;
        dp[0][1] = 1;
        int prenums1;
        int prenums2;

        for(int i = 1; i < n; i++)
        {
            // Prev position swapped
            prenums1 = nums2[i-1];
            prenums2 = nums1[i-1];

            if(dp[i-1][1] != INT_MAX)
            {
                // Swap at current position
                if(nums2[i] > prenums1 && nums1[i] > prenums2)
                    dp[i][1] = 1 + dp[i-1][1];

                // No swap at current position
                if(nums1[i] > prenums1 && nums2[i] > prenums2)
                    dp[i][0] = dp[i-1][1];
            }

            // Prev position no swap
            prenums1 = nums1[i-1];
            prenums2 = nums2[i-1];
            if(dp[i-1][0] != INT_MAX)
            {
                // Swap at current position
                if(nums2[i] > prenums1 && nums1[i] > prenums2)
                    dp[i][1] = std::min(dp[i][1], 1 + dp[i-1][0]);

                // No swap at current position
                if(nums1[i] > prenums1 && nums2[i] > prenums2)
                    dp[i][0] = std::min(dp[i][0], dp[i-1][0]);
            }
        }

        return std::min(dp[n-1][0], dp[n-1][1]);
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<int> nums1 = {1, 4, 4, 9};
    // std::vector<int> nums2 = {2, 3, 5, 10};

    /* Example 2 */
    // std::vector<int> nums1 = {1, 2, 3, 8};
    // std::vector<int> nums2 = {5, 6, 7, 4};

    /* Example 3 */
    // std::vector<int> nums1 = {2, 3, 4, 5};
    // std::vector<int> nums2 = {1, 2, 3, 6};

    /* Example 4 */
    // std::vector<int> nums1 = {1, 4, 6, 9};
    // std::vector<int> nums2 = {2, 2, 5, 10};

    /* Example 5 */
    // std::vector<int> nums1 = {4, 1, 9};
    // std::vector<int> nums2 = {0, 5, 10};

    /* Example 6 */
    // std::vector<int> nums1 = {4, 4, 9};
    // std::vector<int> nums2 = {3, 5, 10};

    /* Example 7 */
    // std::vector<int> nums1 = {1, 3, 3};
    // std::vector<int> nums2 = {1, 2, 4};

    /* Example 8 */
    // std::vector<int> nums1 = {0, 7, 8};
    // std::vector<int> nums2 = {1, 2, 3};

    /* Example 9 */
    // std::vector<int> nums1 = {2};
    // std::vector<int> nums2 = {0};

    /* Example 10 */
    // std::vector<int> nums1 = {};
    // std::vector<int> nums2 = {};

    /* Example 11 */
    // std::vector<int> nums1 = {3, 3};
    // std::vector<int> nums2 = {4, 4};

    /* Example 12 */
    // std::vector<int> nums1 = {3, 3};
    // std::vector<int> nums2 = {0, 4};

    /* Example 13 */
    std::vector<int> nums1 = {0, 7, 8, 10, 10, 11, 12, 13, 19, 18};
    std::vector<int> nums2 = {4, 4, 5,  7, 11, 14, 15, 16, 17, 20};



    std::cout << "\n\t==================================================";
    std::cout << "\n\t=== MINIMUM SWAPS TO MAKE SEQUENCES INCREASING ===";
    std::cout << "\n\t==================================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tNums1: [";
    for (auto x: nums1)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";

    first = true;
    std::cout << "\n\tNums2: [";
    for (auto x: nums2)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    int  result = sol.minSwap(nums1, nums2);


    /* Write Output */
    std::cout << "\n\tResult: " << result;

    std::cout << "\n\n";
    return 0;
}
