/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================================
    3191) Minimum Operations to Make Binary Array Elements Equal to One I
    =====================================================================

    ============
    Description:
    ============

    You are given a binary array nums.

    You can do the following operation on the array any number of times
    (possibly zero):

        + Choose any 3 consecutive elements from the array and flip all of them

    Flipping an element means changing its value from 0 to 1, and from 1 to 0.

    Return the minimum number of operations required to make all elements in
    nums equal to 1. If it is impossible, return -1.

    ===============================================
    FUNCTION: int minOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,1,1,0,0]
    Output: 3
    Explanation:
    We can do the following operations:
        Choose the elements at indices 0, 1 and 2. The resulting array is nums = [1,0,0,1,0,0].
        Choose the elements at indices 1, 2 and 3. The resulting array is nums = [1,1,1,0,0,0].
        Choose the elements at indices 3, 4 and 5. The resulting array is nums = [1,1,1,1,1,1].


    --- Example 2 ---
    Input: nums = [0,1,1,1]
    Output: -1
    Explanation:
    It is impossible to make all elements equal to 1.


    *** Constraints ***
    3 <= nums.length <= 10^5
    0 <= nums[i] <= 1

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It is difficult to prove the correctness of this Solution, but Solution
    itself is very easy and intuitive. It comes to mind almost instantenously,
    but it's difficult to know whether it will work or not, other than to try
    and see if it's going to pass.

    Or to prove it mathematically, which is difficult.

*/

/* Time  Beats: 64.84% */
/* Space Beats: 15.99% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minOperations(vector<int>& nums)
    {
        int count = 0;

        for (int i = 2; i < nums.size(); i++)
        {
            if (nums[i - 2] == 0)
            {
                count++;

                nums[i - 2] ^= 1;
                nums[i - 1] ^= 1;
                nums[i] ^= 1;
            }
        }

        int sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum == nums.size())
            return count;

        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above. It's intuitive, but very difficult to prove that it will
    work in all cases.

*/

/* Time  Beats: 89.05% */
/* Space Beats: 47.55% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Greedy {
public:
    int minOperations(vector<int>& nums)
    {
        const int N = nums.size();

        int count = 0;

        for (int i = 0; i <= N - 3; i++)
        {
            if (nums[i] == 0)
            {
                nums[i] = 1;

                nums[i + 1] = nums[i + 1] == 0 ? 1 : 0;
                nums[i + 2] = nums[i + 2] == 0 ? 1 : 0;

                count++;
            }
        }

        if (nums[N - 2] == 0 || nums[N - 1] == 0)
            return -1;

        return count;
    }
};
