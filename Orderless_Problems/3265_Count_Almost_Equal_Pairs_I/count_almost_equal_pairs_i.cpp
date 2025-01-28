/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3265) Count Almost Equal Pairs I
    ================================

    ============
    Description:
    ============

    You are given an array nums consisting of positive integers.

    We call two integers x and y in this problem almost equal if both integers
    can become equal after performing the following operation at most once:

        Choose either x or y and swap any two digits within the chosen number.

    Return the number of indices i and j in nums where i < j such that nums[i]
    and nums[j] are almost equal.

    Note that it is allowed for an integer to have leading zeros after
    performing an operation.

    ============================================
    FUNCTION: int countPairs(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,12,30,17,21]
    Output: 2
    Explanation:
    The almost equal pairs of elements are:
        3 and 30. By swapping 3 and 0 in 30, you get 3.
        12 and 21. By swapping 1 and 2 in 12, you get 21.

    --- Example 2 ---
    Input: nums = [1,1,1,1,1]
    Output: 10
    Explanation:
    Every two elements in the array are almost equal.

    --- Example 3 ---
    Input: nums = [123,231]
    Output: 0
    Explanation:
    We cannot swap any two digits of 123 or 231 to reach the other.


    *** Constraints ***
    2 <= nums.length <= 100
    1 <= nums[i] <= 106

*/

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Given the Constraints, we're allowed to do a basic BruteForce.

    First we take the maximum element from "nums" and we create str_nums which
    represents nums of strings where each element is of
    size number_of_digits_of_maximum_element.

    Example:

        nums = [1, 12, 7, 91842, 3]

        max_element = 91843
        digits = 5

    Since 91843 is a 5-digit number, our str_nums look like this:

        str_nums = ["00001", "00012", "00007", "91842", "00003"]


    Now do a basic BruteForce. For every 'i' check other elements to the right.

    In order for two elements in "nums" to be "almost equal" they have to
    either:
        1. Be identical already
        2. Have the frequencies of each digits COMPLETELY SAME and differ by 2

    Notice that if two elements differ by 1, then it's impossible to fulfill
    this:
        "Have the frequencies of each digits COMPLETELY SAME"

    However, if they differ by 2, then it can be fulfilled, but it doesn't have
    to.

    We need BOTH conditions to be true in order to say that two elements in
    "nums" are indeed "almost equal".

*/

/* Time  Beats: 19.09% */
/* Space Beats: 16.45% */

/* Time  Complexity: O(N^2 * M) */
/* Space Complexity: O(M)       */
class Solution {
public:
    int countPairs(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int digits = max_digits(*max_element(nums.begin(), nums.end()));

        stringstream ss;
        vector<string> str_nums;
        for (const int& num : nums)
        {
            ss << std::setw(digits) << std::setfill('0') << num;
            str_nums.push_back(ss.str());

            ss.str("");
            ss.clear();
        }

        for (int i = 0; i < N-1; i++)
        {
            for (int x = i+1; x < N; x++)
            {
                if (almost_equal(str_nums[i], str_nums[x]))
                    result++;
            }
        }

        return result;
    }

private:
    int max_digits(int max_num)
    {
        int count = 0;

        while (max_num > 0)
        {
            count++;
            max_num /= 10;
        }

        return count;
    }

private:
    bool almost_equal(string& str1, string& str2)
    {
        if (str1 == str2)
            return true;

        const int len = str1.length();

        unordered_map<int,int> umap1;
        unordered_map<int,int> umap2;

        int differences = 0;
        for (int i = 0; i < len; i++)
        {
            if (str1[i] != str2[i])
                differences++;

            umap1[str1[i]]++;
            umap2[str2[i]]++;
        }

        return differences == 2 && umap1 == umap2;
    }
};
