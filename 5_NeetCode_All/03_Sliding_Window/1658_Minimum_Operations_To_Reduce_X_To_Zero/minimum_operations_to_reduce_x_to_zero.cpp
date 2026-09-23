/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1658) Minimum Operations to Reduce X to Zero
    ============================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer x. In one operation, you
    can either remove the leftmost or the rightmost element from the array nums
    and subtract its value from x. Note that this modifies the array for future
    operations.

    Return the minimum number of operations to reduce x to exactly 0 if it is
    possible, otherwise, return -1.

    ======================================================
    FUNCTION: int minOperations(vector<int>& nums, int x);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,4,2,3], x = 5
    Output: 2
    Explanation: The optimal solution is to remove the last two elements to
                 reduce x to zero.


    --- Example 2 ---
    Input: nums = [5,6,7,8,9], x = 4
    Output: -1


    --- Example 3 ---
    Input: nums = [3,2,20,1,1,3], x = 10
    Output: 5
    Explanation: The optimal solution is to remove the last three elements and
                 the first two elements (5 operations in total) to reduce x to
                 zero.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4
    1 <= x <= 10^9

*/

#include <algorithm>
#include <climits>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is one of those problems where they are deliberately trying to trick
    us with the Description.

    If you were to think about this problem in the way they are describing it,
    you'd quickly realize it's almost impossible to do it in an efficient way.

    What are they asking us to find?
        1. Minimum Operations(removals)
        2. Either remove the leftmost or the rightmost element from the array

    Instead, we ought to INVERT the problem! Instead, we are searching for:

        MAXIMUM elements that are NOT the result

    or in other words:

        Elements that are consecutive and are at most connected to ONE edge


    So we want to get the biggest consecutive window of elements that are NOT
    the result, so that the remaining elements sum up to x.

    By MAXIMIZING our NON-RESULT elements, we are MINIMIZING the result
    elements.

    However, instead of finding different length windows--that when subtracted
    from the total sum of the array--and taking the biggest one, we can only
    search for a window that sums up to (total_sum - x) instead.

    Therefore, we'll use a standard "Sliding Window" technique.

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

    This is a good example to show how difficult it would be if we were to do
    it in a way they're describing.

    You can try to think of a Solution to solve it in a way they've described,
    but I'm going to simulate my Solution.


            nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7

            total_sum = 29
            inverted_x = total_sum - x ==> 29 - 7 => 22

            curr_sum = 0

-------------------------------------------------------------------------------

    1.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L
                R

        curr_sum = 3

        if (curr_sum > inverted_x)     // It is NOT
            /

        if (curr_sum == inverted_x)    // It is NOT
            /

-------------------------------------------------------------------------------

    2.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L  R

        curr_sum = 5

        if (curr_sum > inverted_x)     // It is NOT
            /

        if (curr_sum == inverted_x)    // It is NOT
            /

-------------------------------------------------------------------------------

    3.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L     R

        curr_sum = 7

        if (curr_sum > inverted_x)     // It is NOT
            /

        if (curr_sum == inverted_x)    // It is NOT
            /

-------------------------------------------------------------------------------

    4.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L        R

        curr_sum = 16

        if (curr_sum > inverted_x)     // It is NOT
            /

        if (curr_sum == inverted_x)    // It is NOT
            /

-------------------------------------------------------------------------------

    5.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L           R

        curr_sum = 22

        if (curr_sum > inverted_x)     // It is NOT
            /

        if (curr_sum == inverted_x)    // IT is INDEED
            max_window = max(max_window, R - L + 1) ==> max(0, 5) ==> 5;

-------------------------------------------------------------------------------

    6.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L              R

        curr_sum = 23

        if (curr_sum > inverted_x)    // IT is INDEED
            curr_sum -= nums[L]
            ++L


        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                L              R

        curr_sum = 20

        if (curr_sum == inverted_x)    // It is NOT
            /

-------------------------------------------------------------------------------

    7.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                   L              R

        curr_sum = 21

        if (curr_sum > inverted_x)     // It is NOT
            /

        if (curr_sum == inverted_x)    // It is NOT
            /

-------------------------------------------------------------------------------

    8.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                   L                 R

        curr_sum = 23

        if (curr_sum > inverted_x)     // It is NOT
            curr_sum -= nums[L]
            L++


        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                      L              R

        curr_sum = 21

        if (curr_sum == inverted_x)    // It is NOT
            /

-------------------------------------------------------------------------------

    9.
        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                      L                 R

        curr_sum = 24

        if (curr_sum > inverted_x)     // IT is INDEED
            curr_sum -= nums[L]
            L++

        nums = [3, 2, 2, 9, 6, 1, 1, 2, 3],  x = 7
                0  1  2  3  4  5  6  7  8
                      L                 R


        curr_sum = 22

        if (curr_sum == inverted_x)    // IT is INDEED
            max_window = max(max_window, R - L + 1) ==> max(5, 7) ==> 7;


    return max_window; // 7

*/

/* Time  Beats: 99.23% */
/* Space Beats: 34.13% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(vector<int>& nums, int x)
    {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        int min_elem  = *min_element(nums.begin(), nums.end());

        if (total_sum < x || min_elem > x)
            return -1;

        const int N = nums.size();

        int inverted_x = total_sum - x; // Desired middle sum
        int curr_sum   = 0;

        int left  = 0;
        int right = 0;

        int max_window = -1; // Middle CONSECUTIVE window(i.e. subarray)
        while (right < N)
        {
            curr_sum += nums[right];

            while (left <= right && curr_sum > inverted_x)
            {
                curr_sum -= nums[left];

                // Increment
                ++left;
            }

            if (curr_sum == inverted_x)
                max_window = max(max_window, right - left + 1);

            // Increment
            ++right;
        }

        return max_window == -1 ? -1 : N - max_window;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    THis is a LESS efficient Solution than the one above, howver it's a very
    nice Solution to understand since it has a few of the fundamental
    techniques such as:

        1. How to populate both prefix_sum and suffix_sum in a single loop

        2. How to do a Binary Search (i.e. lower_bound) in REVERSE order, i.e.
           on an array that has elements sorted in DECREASING order, so it's
           INCREASING when going in REVERSE order.

*/

/* Time  Beats: 23.26% */
/* Space Beats: 23.26% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Binary_Search_on_Prefix_and_Suffix_sum {
public:
    int minOperations(vector<int>& nums, int x)
    {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        int min_elem  = *min_element(nums.begin(), nums.end()   );

        if (total_sum < x || min_elem > x)
            return -1;


        const int N = nums.size();
        int result = INT_MAX;

        vector<int> prefix_sum(N, 0);
        vector<int> suffix_sum(N, 0);

        prefix_sum[0  ] = nums[0];
        suffix_sum[N-1] = nums[N-1];
        for (int i = 1; i < N; i++)
        {
            prefix_sum[0   + i] = prefix_sum[0   + i - 1] + nums[0   + i];
            suffix_sum[N-1 - i] = suffix_sum[N-1 - i + 1] + nums[N-1 - i];
        }

        for (int i = 0; i < N && prefix_sum[i] < x; i++)
        {
            int left_sum = prefix_sum[i];
            int target   = x - left_sum;
            auto it = lower_bound(suffix_sum.rbegin(), suffix_sum.rend() - i, target);

            if (*it == target)
            {
                // +1 because indices are 0-based
                int left_elements_count  = i                        + 1;
                int right_elements_count = it - suffix_sum.rbegin() + 1;

                result = min(result, left_elements_count + right_elements_count);
            }
        }

        auto it_only_left = lower_bound(prefix_sum.begin(), prefix_sum.end(), x);
        if (*it_only_left == x)
            result = min(result, static_cast<int>(it_only_left - prefix_sum.begin() + 1));

        auto it_only_right = lower_bound(suffix_sum.rbegin(), suffix_sum.rend(), x);
        if (*it_only_right == x)
            result = min(result, static_cast<int>(it_only_right - suffix_sum.rbegin() + 1));

        return result == INT_MAX ? -1 : result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however this one uses my own forward and backward
    lower_bound imeplementations instead of the ones provided by the std
    library.

    It is VERY beneficial to learn how to implement your REVERSED binary search
    (and forward of course) since INterviewers usually don't like you to use
    the libraries for such simple algorithms.

    Therefore, learning these can pay the dividends in the future. Almost
    literally.

*/

/* Time  Beats: 22.34% */
/* Space Beats: 23.26% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_CUSTOM_Binary_Search_on_Prefix_and_Suffix_sum {
public:
    int minOperations(vector<int>& nums, int x)
    {
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        int min_elem  = *min_element(nums.begin(), nums.end());

        if (total_sum < x || min_elem > x)
            return -1;

        const int N = nums.size();
        int result = INT_MAX;

        vector<int> prefix_sum(N, 0);
        vector<int> suffix_sum(N, 0);

        prefix_sum[0]   = nums[0];
        suffix_sum[N-1] = nums[N-1];

        for (int i = 1; i < N; i++)
        {
            prefix_sum[0   + i] = prefix_sum[0   + i - 1] + nums[0   + i];
            suffix_sum[N-1 - i] = suffix_sum[N-1 - i + 1] + nums[N-1 - i];
        }

        for (int i = 0; i < N && prefix_sum[i] <= x; i++)
        {
            int left_sum = prefix_sum[i];
            int target   = x - left_sum;

            if (i + 1 >= N)
                continue;

            int suffix_idx = my_reversed_lower_bound(N-1, i+1, target, suffix_sum);

            if (suffix_idx != -1 && suffix_sum[suffix_idx] == target)
            {
                int left_elements_count  = i + 1;
                int right_elements_count = N - suffix_idx;

                result = min(result, left_elements_count + right_elements_count);
            }
        }

        /* Only elements from the LEFT */
        int left_idx = my_lower_bound(0, N - 1, x, prefix_sum);

        if (prefix_sum[left_idx] == x)
            result = min(result, left_idx + 1);

        /* Only elements from the RIGHT */
        int right_idx = my_reversed_lower_bound(N - 1, 0, x, suffix_sum);

        if (right_idx != -1 && suffix_sum[right_idx] == x)
            result = min(result, N - right_idx);


        return result == INT_MAX ? -1 : result;
    }

private:
    int my_lower_bound(int low, int high, int target, vector<int>& nums)
    {
        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (target > nums[mid])
                low = mid + 1;
            else
                high = mid;
        }

        return low;
    }

    int my_reversed_lower_bound(int low, int high, int target, vector<int>& nums)
    {
        while (high < low)
        {
            int mid = high + (low - high + 1) / 2;

            if (nums[mid] >= target)
                high = mid;
            else
                low = mid - 1;
        }

        const int N = nums.size();
        if (high >= 0 && high < N && nums[high] >= target)
            return high;

        return -1;
    }
};
