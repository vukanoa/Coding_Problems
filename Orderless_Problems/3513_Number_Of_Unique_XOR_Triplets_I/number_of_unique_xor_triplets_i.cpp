/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3513) Number of Unique XOR Triplets I
    =====================================

    ============
    Description:
    ============

    You are given an integer array nums of length n, where nums is a
    permutation of the numbers in the range [1, n].

    A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j]
    XOR nums[k] where i <= j <= k.

    Return the number of unique XOR triplet values from all possible triplets
    (i, j, k).

    A permutation is a rearrangement of all the elements of a set.

    ===================================================
    FUNCTION: int uniqueXorTriplets(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2]
    Output: 2
    Explanation:
    The possible XOR triplet values are:
        (0, 0, 0) → 1 XOR 1 XOR 1 = 1
        (0, 0, 1) → 1 XOR 1 XOR 2 = 2
        (0, 1, 1) → 1 XOR 2 XOR 2 = 1
        (1, 1, 1) → 2 XOR 2 XOR 2 = 2

    The unique XOR values are {1, 2}, so the output is 2.


    --- Example 2 ---
    Input: nums = [3,1,2]
    Output: 4
    Explanation:
    The possible XOR triplet values include:
        (0, 0, 0) → 3 XOR 3 XOR 3 = 3
        (0, 0, 1) → 3 XOR 3 XOR 1 = 1
        (0, 0, 2) → 3 XOR 3 XOR 2 = 2
        (0, 1, 2) → 3 XOR 1 XOR 2 = 0

    The unique XOR values are {0, 1, 2, 3}, so the output is 4.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    1 <= nums[i] <= n
    nums is a permutation of integers from 1 to n.

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

/* Time  Beats: 5.02% */
/* Space Beats: 5.73% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        unordered_set<int> uset(nums.begin(), nums.end());

        vector<int> ones  (32, 0);
        vector<int> zeroes(32, 0);

        for (int i = 0; i < N; i++)
        {
            for (int idx = 31; idx >= 0; idx--)
            {
                if (nums[i] & (1 << idx))
                    ones[31 - idx]++;
                else
                    zeroes[31 - idx]++;
            }
        }

        int power = 0;

        for (int idx = 31; idx >= 0; idx--)
        {
            bool o = false; // Can xor three elements to get '1' at this pos.
            bool z = false; // Can xor three elements to get '0' at this pos.

            if (ones[idx] >= 3 || (ones[idx] >= 1 && zeroes[idx] >= 2))
                o = true;

            if (zeroes[idx] >= 3 || (ones[idx] >= 2 && zeroes[idx] >= 1))
                z = true;

            if (o && z)
                power++;
        }

        if (uset.size() == 3)
            return uset.size() + (1 << power);

        return (uset.size() > 3 ? (1 << power) : uset.size());
    }
};
