/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3761) Minimum Absolute Distance Between Mirror Pairs
    ====================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    A mirror pair is a pair of indices (i, j) such that:

        0 <= i < j < nums.length, and

        reverse(nums[i]) == nums[j], where reverse(x) denotes the integer
        formed by reversing the digits of x. Leading zeros are omitted after
        reversing, for example reverse(120) = 21.

    Return the minimum absolute distance between the indices of any mirror
    pair. The absolute distance between indices i and j is abs(i - j).

    If no mirror pair exists, return -1.

    =======================================================
    FUNCTION: int minMirrorPairDistance(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [12,21,45,33,54]
    Output: 1
    Explanation:
    The mirror pairs are:
        (0, 1) since reverse(nums[0]) = reverse(12) = 21 = nums[1], giving an absolute distance abs(0 - 1) = 1.
        (2, 4) since reverse(nums[2]) = reverse(45) = 54 = nums[4], giving an absolute distance abs(2 - 4) = 2.
    The minimum absolute distance among all pairs is 1.

    --- Example 2 ---
    Input: nums = [120,21]
    Output: 1
    Explanation:
    There is only one mirror pair (0, 1) since reverse(nums[0]) = reverse(120) = 21 = nums[1].
    The minimum absolute distance is 1.

    --- Example 3 ---
    Input: nums = [21,120]
    Output: -1
    Explanation:
    There are no mirror pairs in the array.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9

*/

#include <climits>
#include <cstdlib>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    A more elegant way of reversing a number, while ALSO taking care of our
    trailing zeores, is this:

            for (rev = 0; num > 0; num /= 10)
                rev = rev * 10 + (num % 10);

    However, for readability purposes, I'm going to leave it like this.

*/

class Solution {
public:
    int minMirrorPairDistance(vector<int>& nums)
    {
        const int N = nums.size();
        if (N == 1)
            return -1;

        int result = INT_MAX;

        unordered_map<int, int> num_to_idx;
        for (int i = N-1; i >= 0; i--)
        {
            int rev = reverse_number(nums[i]);
            if (num_to_idx.find(rev) != num_to_idx.end())
            {
                int j = num_to_idx[rev];
                result = min(result, abs(i - j));
            }

            num_to_idx[nums[i]] = i;
        }

        return result == INT_MAX ? -1 : result;
    }

private:
    int reverse_number(int num)
    {
        /* Get rid of the trailing zeroes */
        while (num % 10 == 0)
            num /= 10;

        int rev = 0;
        while (num > 0)
        {
            rev *= 10;
            rev += num % 10;

            // Get rid of the last digit
            num /= 10;
        }

        return rev;
    }
};
