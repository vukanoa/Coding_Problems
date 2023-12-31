#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    673) Number of Longest Increasing Subsequence
    =============================================

    ============
    Description:
    ============

    Given an integer array nums, return the number of longest increasing
    subsequences.

    Notice that the sequence has to be strictly increasing.

    =================================================
    FUNCTION: int findNumberOfLIS(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,5,4,7]
    Output: 2
    Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and
    [1, 3, 5, 7].


    --- Example 2 ---
    Input: nums = [2,2,2,2,2]
    Output: 5
    Explanation: The length of the longest increasing subsequence is 1, and
    there are 5 increasing subsequences of length 1, so output 5.


    *** Constraints ***
    1 <= nums.length <= 2000
    -10^6 <= nums[i] <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

                       +-----+-----+-----+-----+-----+-----+
                 dp =  |     |     |     |     |     | 1:1 |
                       +-----+-----+-----+-----+-----+-----+
                          0     1     2     3     4     5

                          |     |     |     |     |     |
                          |     |     |     |     |     |
                          v     v     v     v     v     v

                       +-----+-----+-----+-----+-----+-----+
    longest increasing |     |     |     |     |     |  1  |
                       +-----+-----+-----+-----+-----+-----+
                 count |     |     |     |     |     |  1  |
                       +-----+-----+-----+-----+-----+-----+
                          0     1     2     3     4     5

    You must solve LIS(Longest Increasing Subsequence) Problem first. It's from
    the Blind75 list.

    This explanation assumes you know know LIS is supposed to be solved.

    Since we're not just asked to find the LIS, but the total number of
    different sequences that have the same, but maximum, strictly increasing
    subsequence length.

    So in order to solve this, at each outer iteration, we'll have two inner
    iterations.

    Why?

    The first one to determine the length of the longest increasing subsequence
    without including the starting, current, position.

    Then, we want to count how many subsequences, of that length, can be found
    from i+1th position until the end of the array.

    Since we are told the subsequence must be strictly increasing we always
    have to check if(nums[i] < nums[j]) is true.

    Once we've found the length of the longest increasing subsequence from i+1
    position until the end of the array, now we have to count how many such
    subsequences exist from i+1th position until the end of the array.

    However, it would be a mistake if we increased the counter by one if we
    stumble upon a position from which the subsequence is equal to the length
    of the longest subsequence until the end of the array.

    Why?

    Because it may be true that from the position, until the end of the array,
    it's true that we can have multiple increasing subsequences and we must
    take into account every single unique subsequence.

    Therefore, instead of doing "count++", we should do count += dp[j].second
    which represents the number of subsequences to achieve dp[i].first length.

    The "flag" variable is of use for cases where we don't increase the length
    of the longest subsequence.

    One such example is already given:
        nums = [2, 2, 2, 2, 2]

    If we were not to have this "flag" variable, we'd make a mistake since we'd
    count subsequences of "1" multiples times since they are the longest,
    however that's the default value and we shall not consider it.

    At the end of the outer loop, we must keep track of the total/global max
    length of the longest increasing subsequence.

    In the very first example, our result happens to be in the dp[0], however
    that does not necessarily have to be the case, thus, we have to know what
    that max length is and then, after finisihing the main part of this
    solution, we shall count how many starting positions are beginnings of
    unique longest increasing subsequences.

    However, again, we should not only "result++" those starting positions(i.e.
    we should not just count them), instead we should add all the dp[x].second
    values since each dp[x].second value represents a unique subsequence.

    if dp[x].first is equal to max_longest_increasing then take dp[x].second
    into acount by adding it to the the result variable.

    AT the end return result.

*/

/* Time  Beats: 41.01% */
/* Space Beats: 88.42% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums)
    {
        const int n = nums.size();

        if (n == 1)
            return 1;

        std::vector<std::pair<int, int>> dp(n, std::pair<int, int>());
        dp[n-1].first  = 1;
        dp[n-1].second = 1;

        int max_longest_increasing = 0;

        for (int i = n-2; i >= 0; i--)
        {
            int longest_increasing = 1;
            bool flag = false;
            for (int j = i+1; j < n; j++)
            {
                if (nums[i] < nums[j])
                {
                    longest_increasing = std::max(longest_increasing, dp[j].first);
                    flag = true;
                }
            }

            int count = 0;
            for (int j = i+1; j < n; j++)
            {
                if (nums[i] < nums[j] && dp[j].first == longest_increasing)
                    count += dp[j].second;
            }

            dp[i].first  = longest_increasing;
            dp[i].first  += flag ? 1 : 0;
            dp[i].second = flag ? count : 1;

            max_longest_increasing = std::max(max_longest_increasing, dp[i].first);
        }

        int result = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp[i].first == max_longest_increasing)
                result += dp[i].second;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Equivalent to the above Solution, but written in a different way.
    This one seems to be much more efficient.

*/

/* Time  Beats: 92.33% */
/* Space Beats: 88.42% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution_Neat {
public:
    int findNumberOfLIS(vector<int>& nums)
    {
        if (nums.size() == 1)
            return 1;

        const int n = nums.size();

        std::vector<std::pair<int, int>> dp(n, std::pair<int, int>());

        int result = 0;
        int max_longest_increasing = 0;

        // i = start of subseq
        for (int i = n-1; i >= 0; i--)
        {
            int longest_increasing = 1;
            int count = 1;

            for (int j = i+1; j < n; j++)
            {
                if (nums[i] < nums[j])
                {
                    if (dp[j].first + 1 > longest_increasing)
                    {
                        longest_increasing = dp[j].first + 1;
                        count = dp[j].second;
                    }
                    else if (dp[j].first + 1 == longest_increasing)
                        count += dp[j].second;
                }
            }

            if (longest_increasing > max_longest_increasing)
            {
                max_longest_increasing = longest_increasing;
                result = count;
            }
            else if (longest_increasing == max_longest_increasing)
                result += count;

            dp[i].first  = longest_increasing;
            dp[i].second = count;
        }

        return result;
    }
};
