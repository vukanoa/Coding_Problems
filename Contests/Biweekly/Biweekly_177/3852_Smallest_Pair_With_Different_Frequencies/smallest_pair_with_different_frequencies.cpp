/*
    ============
    === EASY ===
    ============

    ==============================================
    3852) Smallest Pair with Differetn Frequencies
    ==============================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Consider all pairs of distinct values x and y from nums such that:

        x < y
        x and y have different in nums.

    Among all such pairs:

        + Choose the pair with the smallest possible value of x.

        + If multiple pairs have the same x, choose the one with the smallest
          possible value of y.

    Return an integer array [x, y]. If no valid pair exists, return [-1, -1].

    =============================================================
    FUNCTION: vector<int> minDistinctFreqPair(vector<int>& nums);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2,2,3,4]
    Output: [1,3]
    Explanation:
    The smallest value is 1 with a frequency of 2, and the smallest value
    greater than 1 that has a different frequency from 1 is 3 with a frequency
    of 1. Thus, the answer is [1, 3].

    --- Example 2 ---
    Input: nums = [1,5]
    Output: [-1,-1]
    Explanation:
    Both values have the same frequency, so no valid pair exists.
    Return [-1,-1].

    --- Example 3 ---
    Input: nums = [7]
    Output: [-1,-1]
    Explanation:
    There is only one value in the array, so no valid pair exists.
    Return [-1, -1].


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <map>
#include <vector>
using namespace std;


/* Time  Complexity: O(N + M^2) */
/* Space Complexity: O(M)       */
class Solution {
public:
    vector<int> minDistinctFreqPair(vector<int>& nums)
    {
        vector<int> result(2);
        
        int freq[101] = {};
        for (const int& num : nums)
            ++freq[num]; 

        for (int num = 0; num < 101; num++)
        {
            if (freq[num] == 0)
                continue;

            for (int other_num = num+1; other_num < 101; other_num++)
            {
                if (freq[other_num] == 0)
                    continue;
                
                if (freq[num] != freq[other_num])
                    return {num, other_num};
            }
        }

        return {-1, -1};
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N * logD  +  D^2) */ // D = Number of DISTINCT values
/* Space Complexity: O(D)                */
class Solution_Ordered_Map {
public:
    vector<int> minDistinctFreqPair(vector<int>& nums)
    {
        map<int, int> map;

        for (const int& num : nums)
            ++map[num];

        for (auto it_one = map.begin(); it_one != map.end(); it_one++)
        {
            for (auto it_two = next(it_one); it_two != map.end(); it_two++)
            {
                if (it_one->second != it_two->second)
                    return {it_one->first, it_two->first};
            }
        }

        return {-1, -1};
    }
};
