/*
    ==============
    === MEDIUM ===
    ==============

    ================================================================
    2962) Count Subarrays Where Max Element Appears at Least K Times
    ================================================================

    ============
    Description:
    ============

    You are given an integer array nums and a positive integer k.

    Return the number of subarrays where the maximum element of nums appears at
    least k times in that subarray.

    A subarray is a contiguous sequence of elements within an array.

    =============================================================
    FUNCTION: long long countSubarrays(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2,3,3], k = 2
    Output: 6
    Explanation: The subarrays that contain the element 3 at least 2 times are:
                 [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].


    --- Example 2 ---
    Input: nums = [1,4,2,1], k = 3
    Output: 0
    Explanation: No subarray contains the element 4 at least 3 times.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6
    1 <= k <= 10^5

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.63% */
/* Space Beats: 32.77% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window {
public:
    long long countSubarrays(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int max_elem = *std::max_element(nums.begin(), nums.end());
        int max_cnt  = 0;

        long long result = 0;

        int left  = 0;
        int right = 0;

        while (right < N)
        {
            if (nums[right] == max_elem)
                max_cnt++;

            while (max_cnt == k)
            {
                if (nums[left] == max_elem)
                    max_cnt--;

                left++;
            }

            result += left;

            // Increment
            right++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one does NOT use any nested while-loop, instead it uses "smart"
    counting.

    It's usually better to use the above approach, but it's beneficial to know
    that you can sometimes count it in ways like this.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  12.30% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Counting {
public:
    long long countSubarrays(vector<int>& nums, int k)
    {
        const int N = nums.size();
        long long result = 0;

        int max_elem = *max_element(nums.begin(), nums.end());

        vector<int> indices;
        int idx = -1;

        int add = 0;

        int L = 0;
        int R = 0;

        while (R < N)
        {
            if (nums[R] == max_elem)
            {
                indices.push_back(R);

                if (indices.size() >= k)
                    idx++;

                if (idx == 0)
                    add += indices[idx] - L + 1;
                else if (idx > 0)
                    add += indices[idx] - indices[idx-1];
            }

            if (indices.size() >= k)
                result += add;

            // Increment
            R++;
        }

        return result;
    }
};
