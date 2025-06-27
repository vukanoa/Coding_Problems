/*
    ============
    === HARD ===
    ============

    ==================================================================
    3041) Maximize Consecutive Elements in an Array After Modification
    ==================================================================

    ============
    Description:
    ============

    You are given a 0-indexed array nums consisting of positive integers.

    Initially, you can increase the value of any element in the array by at
    most 1.

    After that, you need to select one or more elements from the final array
    such that those elements are consecutive when sorted in increasing order.
    For example, the elements [3, 4, 5] are consecutive while [3, 4, 6] and
    [1, 1, 2, 3] are not.

    Return the maximum number of elements that you can select.

    =====================================================
    FUNCTION: int maxSelectedElements(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,5,1,1]
    Output: 3
    Explanation: We can increase the elements at indices 0 and 3. The resulting array is nums = [3,1,5,2,1].
    We select the elements [3,1,5,2,1] and we sort them to obtain [1,2,3], which are consecutive.
    It can be shown that we cannot select more than 3 consecutive elements.

    --- Example 2 ---
    Input: nums = [1,4,7,10]
    Output: 1
    Explanation: The maximum consecutive elements that we can select is 1.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 57.57% */
/* Space Beats: 49.09% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int maxSelectedElements(vector<int>& nums)
    {
        unordered_map<int, int> dp;

        /* Sort */
        sort(nums.begin(), nums.end());

        int result = 0;
        for (const int& num : nums)
        {
            result = max(result, dp[num + 1] = dp[num    ] + 1);
            result = max(result, dp[num    ] = dp[num - 1] + 1);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Virtually same as above, however it's maybe a bit easier to grasp it if we
    are using a vector instead of a HashMap since you see the initialized value
    immediately.

    1. Sort the array, because longest valid sequence ending at a num is
    dependent on num-1.

    2. Since nums[i]<=1e6, we can make a dp array of 1e6, where indices
    represent elements of nums (If elements were large we could've used a
    Hashmap as our dp array).

    3. Since an element(num) can act as both num and num+1, first consider it
    as num+1 and if there is a valid sequence ending at num, it'll
    automatically be considered by recurrence dp[num+1]=dp[num]+1.

    4. Now do same for num i.e. dp[num]=dp[num-1]+1. Maximum of this do array
    is the answer. (Since it represents maximum sequence ending at that
    number).

*/

/* Time  Beats:  5.45% */
/* Space Beats: 11.51% */

/* Time  Complexity: O(MAX_ELEMENT) */
/* Space Complexity: O(MAX_ELEMENT) */
class Solution_2 {
private:
    const int MAX_ELEMENT = 1e6 + 2;
public:
    int maxSelectedElements(vector<int>& nums)
    {
        /* Sort */
        sort(nums.begin(), nums.end());

        vector <int> dp(MAX_ELEMENT, 0);

        for (const auto& num : nums)
        {
            dp[num + 1] = 1 + dp[num];
            dp[num    ] = max(dp[num], 1 + dp[num-1]);
        }

        return *max_element(dp.begin(), dp.end());
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.79% */
/* Space Beats: 98.18% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // This is Space Comp. of C++'s Sort
class Solution_Space_Optimized {
public:
    int maxSelectedElements(vector<int>& nums)
    {
        /* Sort */
        sort(nums.begin(), nums.end());

        int pre = -10;
        int result = 1;
        int c1 = 1;
        int c2 = 1;

        for (const int& num : nums)
        {
            if (num == pre)
            {
                c2 = c1 + 1;
            }
            else if (num == pre + 1)
            {
                c1++;
                c2++;
            }
            else if (num == pre + 2)
            {
                c1 = c2 + 1;
                c2 = 1;
            }
            else
            {
                c1 = c2 = 1;
            }

            result = max(result, max(c1, c2));
            pre = num;
        }

        return result;
    }
};
