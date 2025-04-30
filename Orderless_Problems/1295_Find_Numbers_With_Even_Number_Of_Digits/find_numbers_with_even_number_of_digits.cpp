/*
    ============
    === EASY ===
    ============

    =============================================
    1295) Find Numbers with Even Number of Digits
    =============================================

    ============
    Description:
    ============

    Given an array nums of integers, return how many of them contain an even
    number of digits.

    =============================================
    FUNCTION: int findNumbers(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [12,345,2,6,7896]
    Output: 2
    Explanation:
    12 contains 2 digits (even number of digits).
    345 contains 3 digits (odd number of digits).
    2 contains 1 digit (odd number of digits).
    6 contains 1 digit (odd number of digits).
    7896 contains 4 digits (even number of digits).
    Therefore only 12 and 7896 contain an even number of digits.

    --- Example 2 ---
    Input: nums = [555,901,482,1771]
    Output: 1
    Explanation:
    Only 1771 contains an even number of digits.


    *** Constraints ***
    1 <= nums.length <= 500
    1 <= nums[i] <= 10^5

*/

#include <cmath>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.79% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int findNumbers(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int count = 0;
            while (nums[i] > 0)
            {
                count++;
                nums[i] /= 10;
            }

            if (count % 2 == 0)
                result++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since in the Constraints it is said:

        1 <= nums[i] <= 10^5

    Only numbers with either: 2, 4 or 6 digits have EVEN number of digits.
    We can write all of those bounds manually, since there are only 3 of them.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.79% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Manually {
public:
    int findNumbers(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            if ((nums[i] >= 10     && nums[i] < 100  ) ||
                (nums[i] >= 1000   && nums[i] < 10000) ||
                (nums[i] == 100000))
            {
                result++;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another good way of doing it. For these constraints log10(10^) is O(1),
    however in the general case, if the number of digits of the highest number
    is very high, then it would be considered O(log10(M)), where M is the
    highest number possible given the Constraints.

*/

/* Time  Complexity: O(N * log10(M)) */
/* Space Complexity: O(log10(M))     */
class Solution_Convert_To_String {
public:
    int findNumbers(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int len = to_string(nums[i]).length();

            if (len % 2 == 0)
                result++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar as above, but we are directly using math instead of masking it with
    strings.

*/

/* Time  Complexity: O(N * log10(M)) */
/* Space Complexity: O(log10(M))     */
class Solution_Using_Logarithm_Base_10 {
public:
    int findNumbers(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            int count = static_cast<int>(floor(log10(nums[i])) + 1);

            if (count % 2 == 0)
                result++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    + We can use the __builtin_clz function which basically returns the number
      of 0's in the binary format of a number.

    + Find the most significant bit in the number using 31 - __builtin_clz(i)

    + As we'd used log 10 in an earlier approach to compute the number of
      digits similarly here we can use

    int digits = (msb * 0.30103) + 1;

    + Where 0.30103 is the value of log10(2) written in integer form to avoid
      floating point errors.

    + Lastly we simply check whether i >= pow(10, digits) i.e whether there is
      an extra digit present in i.

    + Check whether the digits is even or odd.

    + For example : for 127,
        + int msb = 31 - 25 = 6
        + digits = (6 * 0.30103) + 1 = floor(1.80618) + 1 = 2
        + if (i >= pow(10, digits)) → (127 >= pow(10, 2)) so
        + count = 1 + 2 = 3

*/

/* Time  Beats: 100.00% */
/* Space Beats:  28.23% */

/* Time  Complexity: O(N * log10(M)) */
/* Space Complexity: O(log10(M))     */
class Solution_Bit_Manipulation {
public:
    int findNumbers(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        constexpr double LOG10_OF_2 = 0.30102999566;

        for (int i = 0; i < N; i++)
        {
            /*
                unsigned int x = 18;     // binary: 00000000 00000000 00000000 00010010
                                                                             ...  43210
                __builtin_clz(x) == 27   // 27 leading zeros                      ^
                                                                                  |
                                                            ______________________|
                                                            |
                31 - 27 == 4             // MSB is at index 4 (bit position of 16)

                Note:
                If nums[i] == 0, then __builtin_clz(0) is undefined behavior

            */
            unsigned highest_set_bit_idx = nums[i] ? 31 - __builtin_clz(nums[i]) : -1;

            int digits = (highest_set_bit_idx * LOG10_OF_2) + 1;

            if (nums[i] >= pow(10, digits))
                digits++;

            if (digits % 2 == 0)
                result++;
        }

        return result;
    }
};
