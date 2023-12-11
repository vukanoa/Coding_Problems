#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    1498) Number of Subsequences That Satisfy the Given Sum Condition
    =================================================================

    ============
    Description:
    ============

    You are given an array of integers nums and an integer target.

    Return the number of non-empty subsequences of nums such that the sum of
    the minimum and maximum element on it is less or equal to target. Since the
    answer may be too large, return it modulo 109 + 7.

    =======================================================
    FUNCTION: int numSubseq(vector<int>& nums, int target);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,5,6,7], target = 9
    Output: 4
    Explanation: There are 4 subsequences that satisfy the condition.
    [3] -> Min value + max value <= target (3 + 3 <= 9)
    [3,5] -> (3 + 5 <= 9)
    [3,5,6] -> (3 + 6 <= 9)
    [3,6] -> (3 + 6 <= 9)


    --- Example 2 ---
    Input: nums = [3,3,6,8], target = 10
    Output: 6
    Explanation: There are 6 subsequences that satisfy the condition. (nums can
    have repeated numbers).
    [3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]


    --- Example 3 ---
    Input: nums = [2,3,3,4,6,7], target = 12
    Output: 61
    Explanation: There are 63 non-empty subsequences, two of them do not
    satisfy the condition ([6,7], [7]).
    Number of valid subsequences (63 - 2 = 61).


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6
    1 <= target <= 10^6

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one does NOT work for C++ because of the type-boundary. This would
    work for something like Python.

*/

class Solution_Does_NOT_work {
public:
    int numSubseq(vector<int>& nums, int target)
    {
        unsigned long long result = 0;
        int mod_value = std::pow(10, 9) + 7;

        std::sort(nums.begin(), nums.end());

        int right = nums.size() - 1;
        for (int left = 0; left < nums.size(); left++)
        {
            while (left <= right && (nums[left] + nums[right]) > target)
                right--;

            if (left <= right)
            {
                result += (1 << (right - left));
                result %= mod_value;
            }
        }

        return static_cast<int>(result);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.54% */
/* Space Beats: 72.84% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Inefficient {
public:
    int numSubseq(vector<int>& nums, int target)
    {
        std::sort(nums.begin(), nums.end());
        int result = 0;
        int mod_value = 1e9 + 7;

        for(int i = 0; i < nums.size(); ++i)
        {
            int val = target - nums[i];
            int idx = std::upper_bound(nums.begin(), nums.end(), val) - nums.begin();
            idx--;

            if(idx >= i)
                result = (result + power(2, idx-i, mod_value)) % mod_value;
        }

        return result % mod_value;
    }

private:
    int power(long long x, unsigned int y, int p)
    {
        int res = 1;
        x = x % p;
        if (x == 0) return 0;
        while (y > 0)
        {
            if (y & 1)
                res = (res*x) % p;
            y = y >> 1;
            x = (x*x) % p;
        }
        return res;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.76% */
/* Space Beats: 54.46% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_Efficient {
public:
    int numSubseq(vector<int>& nums, int target)
    {
        const int MOD = 1e9 + 7;
        const int n = nums.size();

        std::sort(nums.begin(), nums.end());

        int result = 0;


        std::vector<int> power(n,1);
        for(int i = 1; i < n; i++)
            power[i] = (power[i-1] * 2) % MOD;

        int left  = 0;
        int right = n - 1;
        while(left <= right)
        {
            if( (nums[left] + nums[right]) <= target )
                result = (result + power[right - left++]) % MOD;
            else
                right--;
        }

        return result;
    }
};
