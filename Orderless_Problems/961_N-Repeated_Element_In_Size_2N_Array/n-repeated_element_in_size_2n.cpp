/*
    ============
    === EASY ===
    ============

    ========================================
    961) N-Repeated Element in Size 2N Array
    ========================================

    ============
    Description:
    ============

    You are given an integer array nums with the following properties:

        + nums.length == 2 * n.
        + nums contains n + 1 unique elements.
        + Exactly one element of nums is repeated n times.

    Return the element that is repeated n times.

    ================================================
    FUNCTION: int repeatedNTimes(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,3]
    Output: 3

    --- Example 2 ---
    Input: nums = [2,1,2,5,3,2]
    Output: 2

    --- Example 3 ---
    Input: nums = [5,1,5,2,5,3,5,4]
    Output: 5


    *** Constraints ***
    2 <= n <= 5000
    nums.length == 2 * n
    0 <= nums[i] <= 10^4
    nums contains n + 1 unique elements and one of them is repeated exactly n
    times.

*/

#include <bitset>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Naive way of solving this problem. Use additional data structure, i.e.
    HashSet in this case, to determine if we've already seen this number.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.60% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Naive {
public:
    int repeatedNTimes(vector<int>& nums)
    {
        const int N = nums.size();

        unordered_set<int> uset;
        for (const int& num : nums)
        {
            if (uset.count(num))
                return num;

            uset.insert(num);
        }

        return 0; // Unreachable
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Pigeonwhole principle states something that seems obvious at first, but its
    surprisingly practical once you formally know it. It seems to appear
    everywhere all of a sudden.

    If we have:
        + N pigeons and
        + M pigeonholes and
        + N > M

    Then at least ONE pigeonhole will CERTAINLY have at least 2 pigeons.

        Pigeons:       X   X   X   X   X
                       0   1   2   3   4

                     -----------------
        Pigeonholes: |   |   |   |   |
                     -----------------
                       0   1   2   3

    Seeems obvious right?
    But that's exactly what we have here.

    Since we're told there are N+1 unique elements, and that only one element
    repeats N times, we know that there is at least ONE CONSECUTIVE group of
    three elements where 2 out of 3 elements are the same.

    Once we find that group, we simply return the duplicate element as a
    result.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.61% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Pigeonhole_Principle {
public:
    int repeatedNTimes(vector<int>& nums)
    {
        const int N = nums.size();

        for (int i = 0; i < N-2; i++)
        {
            if (nums[i] == nums[i+1] || nums[i] == nums[i+2])
                return nums[i];
        }

        // In case N == 2 and both repeating elements are at the end
        return nums.back();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Use std::bitset from C++.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // Practically, Asymptotically O(1)
class Solution_Bitset {
public:
    int repeatedNTimes(vector<int>& nums)
    {
        bitset<10001> seen = 0;

        for (const int& num : nums)
        {
            if (seen[num])
                return num;

            seen[num] = 1;
        }

        return -1; // Unreachable code
    }
};
