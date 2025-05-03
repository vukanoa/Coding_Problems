/*
    ============
    === EASY ===
    ============

    ========================================
    3079) Find the Sum of Encrypted Integers
    ========================================

    ============
    Description:
    ============

    You are given an integer array nums containing positive integers. We define
    a function encrypt such that encrypt(x) replaces every digit in x with the
    largest digit in x. For example, encrypt(523) = 555 and encrypt(213) = 333.

    Return the sum of encrypted elements.

    ===================================================
    FUNCTION: int sumOfEncryptedInt(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 6
    Explanation: The encrypted elements are [1,2,3]. The sum of encrypted
                 elements is 1 + 2 + 3 == 6.

    --- Example 2 ---
    Input: nums = [10,21,31]
    Output: 66
    Explanation: The encrypted elements are [11,22,33]. The sum of encrypted
                 elements is 11 + 22 + 33 == 66.


    *** Constraints ***
    1 <= nums.length <= 50
    1 <= nums[i] <= 1000

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem.

*/

/* Time  Beats: 6.96% */
/* Space Beats: 7.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int sumOfEncryptedInt(vector<int>& nums)
    {
        const int N = nums.size();
        int sum = 0;

        for (const int& num : nums)
            sum += encrypt(num);

        return sum;
    }

private:
    int encrypt(int x)
    {
        int count = 0;
        int maxx = 0;

        while (x > 0)
        {
            int num = x % 10;
            x /= 10;

            count++;

            maxx = max(maxx, num);
        }

        string str = "";
        while (count--)
            str += to_string(maxx);

        return stoi(str);
    }
};
