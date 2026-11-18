/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    3766) Minimum Operations to Make Binary Palindrome
    ==================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    For each element nums[i], you may perform the following operations any
    number of times (including zero):

        + Increase nums[i] by 1, or
        + Decrease nums[i] by 1.

    A number is called a binary palindrome if its binary representation without
    leading zeros reads the same forward and backward.

    Your task is to return an integer array ans, where ans[i] represents the
    minimum number of operations required to convert nums[i] into a binary
    palindrome.

    =======================================================
    FUNCTION: vector<int> minOperations(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,4]
    Output: [0,1,1]
    Explanation:

    One optimal set of operations:
    nums[i]    Binary(nums[i])    Nearest      Binary      Operations         ans[i]
                                 Palindrome  (Palindrome)  Required    
      1             1                1            1        Already palindrome    0
      2            10                3           11        Increase by 1         1
      4           100                3           11        Decrease by 1         1
    Thus, ans = [0, 1, 1].


    --- Example 2 ---
    Input: nums = [6,7,12]
    Output: [1,0,3]
    Explanation:
    
    One optimal set of operations:
    nums[i]    Binary(nums[i])    Nearest      Binary      Operations         ans[i]
                                   Palindrome  (Palindrome) Required
      6             110               5           101      Decrease by 1        1
      7             111               7           111      Already palindrome   0
     12            1100              15          1111      Increase by 3        3
    Thus, ans = [1, 0, 3].



    *** Constraints ***
    1 <= nums.length <= 5000
    1 <= nums[i] <= 5000

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.26% */
/* Space Beats: 5.26% */

/* Time  Complexity: O(N * D * 32) */ // D is the maximum number of incr/decr
/* Space Complexity: O(N)          */
class Solution {
public:
    vector<int> minOperations(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result(N, 0);
        
        for (int i = 0; i < N; i++)
        {
            string bin_str = to_bin_str(nums[i]);

            int diff = 0;
            for(;;)
            {
                string bin_str_inc = to_bin_str(nums[i] + diff);
                string bin_str_dec = to_bin_str(nums[i] - diff);

                if (is_palindrome(bin_str_inc) || is_palindrome(bin_str_dec))
                    break;

                ++diff;
            }

            result[i] = diff;
        }

        return result;
    }

private:
    bool is_palindrome(string bin_str)
    {
        const int M = bin_str.size();

        int i = 0;
        while (i < M && bin_str[i] == '0')
            ++i;

        int L = i;
        int R = M-1;

        while (L < R)
        {
            if (bin_str[L] != bin_str[R])
                return false;

            ++L;
            --R;
        }

        return true;
    }

    string to_bin_str(int num)
    {
        string bin_str;
        bin_str.reserve(32);

        for (int ith_bit = 31; ith_bit >= 0; ith_bit--)
        {
            if (num & (1 << ith_bit))
                bin_str += "1";
            else
                bin_str += "0";
        }

        return bin_str;
    }
};
