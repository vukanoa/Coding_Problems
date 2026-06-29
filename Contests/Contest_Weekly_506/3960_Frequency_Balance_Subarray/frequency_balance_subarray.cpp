/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3960) Frequency Balance Subarray
    ================================

    ============
    Description:
    ============

    You are given an integer array subarray nums.

    Define a frequency balance as follows:

        + If the subarray contains only one distinct value, it is frequency
          balanced.

        + Otherwise, there must exist a positive integer f such that every
          distinct value in the subarray occurs either f or 2 * f times, and
          both occur among the distinct values.

    Return an integer denoting the length of the longest frequency balance
    subarray.

    ===========================================
    FUNCTION: int getLength(vector<int>& nums);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2,1,2,3,3,3]
    Output: 5
    Explanation:
        The longest frequency balance subarray is [2, 1, 2, 3, 3].
        The elements that appear most frequently are 2 and 3, both appearing twice.
        The remaining element 1 appears once, meeting the requirements.

    --- Example 2 ---
    Input: nums = [5,5,5,5]
    Output: 4
    Explanation:
        The longest frequency balance subarray is [5, 5, 5, 5].
        The element that appears most frequently is 5.
        There are no other elements meeting the requirements.

    --- Example 3 ---
    Input: nums = [1,2,3,4]
    Output: 1
    Explanation:
    Since all elements appear only once, the length of the longest frequency
    balance subarray is 1.


    *** Constraints ***
    1 <= nums.length <= 10^3
    1 <= nums[i] <= 10^9

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Constraints are allowing that we go through each individual subarray,
    therefore it's a kind of Brute-Force Solution.

*/

/* Time  Beats: 52.71% */
/* Space Beats: 39.46% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int getLength(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            unordered_map<int, int> freq_of_number;
            unordered_map<int, int> count_of_numbers_with_freq;

            for (int j = i; j < N; j++)
            {
                if (freq_of_number.find(nums[j]) == freq_of_number.end())
                {
                    freq_of_number[nums[j]]++;
                    count_of_numbers_with_freq[1]++;
                }
                else
                {
                    int curr_freq = freq_of_number[nums[j]];

                    count_of_numbers_with_freq[curr_freq]--;
                    if (count_of_numbers_with_freq[curr_freq] == 0)
                        count_of_numbers_with_freq.erase(curr_freq);

                    int new_freq = ++freq_of_number[nums[j]];
                    count_of_numbers_with_freq[new_freq]++;
                }

                if (count_of_numbers_with_freq.size() == 1 && count_of_numbers_with_freq.begin()->second == 1) // Only ONE distinct value
                {
                    result = max(result, j-i+1);
                }
                else
                {
                    if (count_of_numbers_with_freq.size() == 1)
                        continue;

                    if (count_of_numbers_with_freq.size() >= 3)
                        continue;

                    int one_freq = count_of_numbers_with_freq.begin()->first;
                    int two_freq = next(count_of_numbers_with_freq.begin())->first;

                    if (2 * one_freq == two_freq || 2 * two_freq == one_freq)
                        result = max(result, j - i + 1);
                }

            }

        }

        return result;
    }
};
