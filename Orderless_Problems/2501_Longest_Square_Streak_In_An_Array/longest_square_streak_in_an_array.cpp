#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bitset>

/*
    ==============
    === MEDIUM ===
    ==============

    =======================================
    2501) Longest Square Streak in an Array
    =======================================

    ============
    Description:
    ============

    You are given an integer array nums. A subsequence of nums is called a
    square streak if:

        + The length of the subsequence is at least 2, and

        + after sorting the subsequence, each element (except the first
          element) is the square of the previous number.

    Return the length of the longest square streak in nums, or return -1 if
    there is no square streak.

    A subsequence is an array that can be derived from another array by
    deleting some or no elements without changing the order of the remaining
    elements.

    =====================================================
    FUNCTION: int longestSquareStreak(vector<int>& nums);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,6,16,8,2]
    Output: 3
    Explanation: Choose the subsequence [4,16,2]. After sorting it, it becomes
                 [2,4,16].
    - 4 = 2 * 2.
    - 16 = 4 * 4.
    Therefore, [4,16,2] is a square streak.
    It can be shown that every subsequence of length 4 is not a square streak.

    --- Example 2 ---
    Input: nums = [2,3,5,6,7]
    Output: -1
    Explanation: There is no square streak in nums so return -1.


    *** Constraints ***
    2 <= nums.length <= 10^5
    2 <= nums[i] <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    Since max streak has to be a SUBSEQUENCE, you would think that we need to
    keep everything and order and must NOT sort the Input, however the next
    sentence disputes that. It is said:

        "after sorting the subsequence, each element (except the first element)
         is the square of the previous number."

    Which ultimately means that "Subsequence" doesn't actually play any role.
    It's kind of a deception to use that word. If we are allowed to SORT the
    SUBSEQUENCE, then "SUBSEQUENCE" loses all of its meaning and value.

    Since that is that case and we know that we can sort the Input, let's
    extend our intuition further.

    Since now we have a sorted Input of "nums", and we need to find longest
    "streak" of square numbers, it makes sense that if some streak starts with
    2 and has 4 and 16(streak of length 3) that once we try to find longest
    streak using a substreak of the earlier streak(i.e. we begin from number 4
    or number 16), we are CERTAIN that we WON'T find a longer streak.

    So, since we've sorted and since we're seeking for long streaks from
    SMALLER number, any LATER number that was already in some EARLIER streak is
    GUARANTEED not to have a longer streak.

    That's why we're going to had a HashSet called "used_in_longer_streak". If
    we find that under the current 'i'(index) we're on is the number that is
    ALREADY USED in some EARLIER streak, that certainly means we will NOT find
    any longer streak starting with this number and we can safery ignore and
    try to begin a streak with the very next number.


    Okay, now let's see what is the easiest way to find if a current number
    SQUARED is present in the Input "nums".

    That is easy - HashSet. Construct a HashSet from the Input "nums" in O(n)
    and now anytime we need to check the presence of some number, we can
    achieve that in O(1).


    We're almost there.

    Now we need a way to count the length of streaks for each strating number.
    We can achieve that using a Hash Map. Plus, we've seen that there is no
    point in counting the length of the streak for numbers that were a part of
    some EARLIER streak, therefore our HashMap will, on average, have even less
    than n numbers.

    But that is besides the point. The point is that we need to use a HashMap.

    After we've counted streaks for each number(probably not each since some
    were a part of an earlier streak), we must iterate over this HashMap and
    find the longest value from {key, value} pairs in it.

    At the end, if the longest value from {key, value} pairs is 1, then we
    haven't fulfilled the first point - "The length of the subsequence is at
    least 2" and we should, therefore, return -1.

    Otherwise, return "result" which hold the longest streak.

    (Notice that we've had to use "unsigned long long" since multiplication
    grows very fast and we could have an overflow)

*/

/* Time  Beats: 6.67% */
/* Space Beats: 6.43% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int longestSquareStreak(vector<int>& nums)
    {
        // Calculate the maximum safe integer that can be squared
        unsigned long long max_safe = static_cast<unsigned long long>(std::sqrt(std::numeric_limits<unsigned long long>::max()));

        // Sort nums since we are looking for a subsequence AFTER the sort. That's why it's allowed.
        sort(nums.begin(), nums.end());

        unordered_map<int, int> streak_start_number;
        unordered_set<int> used_in_longer_streaks;
        unordered_set<int> uset_nums(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            if (used_in_longer_streaks.find(nums[i]) != used_in_longer_streaks.end()) // Exists
                continue;

            streak_start_number[nums[i]]++;
            used_in_longer_streaks.insert(nums[i]);

            unsigned long long x = nums[i];

            if (x <= max_safe)
                x = x * x;
            else
                break;

            while (uset_nums.find(x) != uset_nums.end() &&                         // Exists
                   used_in_longer_streaks.find(x) == used_in_longer_streaks.end()) // Doesn't exist
            {
                streak_start_number[nums[i]]++;
                used_in_longer_streaks.insert(x);

                // Check if the input number is within this range
                if (x <= max_safe)
                    x = x * x;
                else
                    break;
            }
        }

        // Find the longest value from {key, value} pairs.
        int result = 1;
        for (const auto& entry : streak_start_number)
            result = max(result, entry.second);

        return result == 1 ? -1 : result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent to the above one, written in a much moce concise and
    elegant way.

*/

/* Time  Beats: 51.11% */
/* Space Beats: 52.73% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_Elegant {
public:
    int longestSquareStreak(vector<int>& nums)
    {
        unordered_map<int, int> umap;

        // Sort
        sort(nums.begin(), nums.end());

        int result = -1;
        for (int num : nums)
        {
            int squared_num = std::sqrt(num);

            if (squared_num * squared_num == num && umap.find(squared_num) != umap.end())
            {
                umap[num] = umap[squared_num] + 1;
                result = max(result, umap[num]);
            }
            else
                umap[num] = 1;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 87.14% */
/* Space Beats: 93.87% */

/* Time  Complexity: O(n + N) */
/* Space Complexity: O(N)     */
const long long N = 100001;
class Solution {
public:
    int longestSquareStreak(vector<int>& nums)
    {
        bitset<N> number_exists = 0;
        int max_num = 0;
        for (int num : nums)
        {
            number_exists[num] = 1;
            max_num = max(max_num, num);
        }

        int max_streak = 0;

        for (long long num : nums)
        {
            int streak = 1;

            for (long long next_square = num*num; next_square <= max_num; next_square *= next_square)
            {
                if (number_exists[next_square])
                    streak++;
                else
                    break;
            }

            max_streak = max(max_streak, streak);

            if (max_streak == 5)
                break;
        }

        return max_streak < 2 ? -1 : max_streak;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  93.87% */

/* Time  Complexity: O(n + sqrt(max_num) * log(max_num)) */
/* Space Complexity: O(N) */
const long long N = 100001;
class Solution_Counting_Sort {
public:
    int longestSquareStreak(vector<int>& nums)
    {
        bitset<N> number_exists = 0;

        int max_num = 0;
        for (int num : nums)
        {
            number_exists[num] = 1;
            max_num = max(max_num, num);
        }

        int max_streak = 0;
        int sqrt_of_max_num = sqrt(max_num);

        for (long long num = 2; num <= sqrt_of_max_num; num++)
        {
            if (number_exists[num] == 0)
                continue;

            int streak = 1;
            for (long long next_square = num*num; next_square <= max_num; next_square *= next_square)
            {
                if (number_exists[next_square])
                {
                    streak++;
                    number_exists[next_square] = 0;
                }
                else
                    break;
            }

            max_streak = max(max_streak, streak);

            if (max_streak == 5)
                break;
        }

        return max_streak < 2 ? -1 : max_streak;
    }
};
