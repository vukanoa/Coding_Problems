/*
    ============
    === EASY ===
    ============

    ==========================================
    3289) The two Sneaky Numbers of Digitville
    ==========================================

    ============
    Description:
    ============

    In the town of Digitville, there was a list of numbers called nums
    containing integers from 0 to n - 1. Each number was supposed to appear
    exactly once in the list, however, two mischievous numbers sneaked in an
    additional time, making the list longer than usual.

    As the town detective, your task is to find these two sneaky numbers.
    Return an array of size two containing the two numbers (in any order), so
    peace can return to Digitville.

    ==========================================================
    FUNCTION: vector<int> getSneakyNumbers(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,1,0]
    Output: [0,1]
    Explanation:
    The numbers 0 and 1 each appear twice in the array.

    --- Example 2 ---
    Input: nums = [0,3,2,1,3,2]
    Output: [2,3]
    Explanation:
    The numbers 2 and 3 each appear twice in the array.

    --- Example 3 ---
    Input: nums = [7,1,5,4,3,4,6,0,9,5,8,2]
    Output: [4,5]
    Explanation:
    The numbers 4 and 5 each appear twice in the array.


    *** Constraints ***
    2 <= n <= 100
    nums.length == n + 2
    0 <= nums[i] < n
    The input is generated such that nums contains exactly two repeated elements.

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.66% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> getSneakyNumbers(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result;

        unordered_set<int> uset;
        for (const int& num : nums)
        {
            if (uset.count(num))
                result.push_back(num);

            uset.insert(num);
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

/* Time  Beats: 100.00% */
/* Space Beats:  75.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_XOR {
public:
    vector<int> getSneakyNumbers(vector<int>& nums)
    {
        const int N = nums.size() - 2;
        int XOR = 0;

        for (int num : nums)
            XOR ^= num;            

        for (int i = 0; i < N; i++)
            XOR ^= i;

        int diffBit = XOR & -XOR;

        int a = 0;
        int b = 0;
        for (int num : nums)
        {
            if ((num & diffBit) == 0)
                a ^= num;
            else
                b ^= num;
        }

        for (int i = 0; i < N; i++)
        {
            if ((i & diffBit) == 0)
                a ^= i;
            else
                b ^= i;
        }

        return {a, b};
    }
};
