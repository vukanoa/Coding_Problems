#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===========================
    645) Set Mismatch
    ===========================

    ============
    Description:
    ============

    You have a set of integers s, which originally contains all the numbers
    from 1 to n. Unfortunately, due to some error, one of the numbers in s got
    duplicated to another number in the set, which results in repetition of one
    number and loss of another number.

    You are given an integer array nums representing the data status of this
    set after the error.

    Find the number that occurs twice and the number that is missing and return
    them in the form of an array.

    =======================================================
    FUNCTION: vector<int> findErrorNums(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2,4]
    Output: [2,3]

    --- Example 2 ---
    Input: nums = [1,1]
    Output: [1,2]

    *** Constraints ***
    2 <= nums.length <= 10^4
    1 <= nums[i] <= 10^4

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 25.64% */
/* Space Beats: 9.95% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums)
    {
        int n = nums.size();       
        unordered_map<int, int>freq;

        // Storing frequecny of each number
        for (int i = 0; i < n ; i++)
            freq[nums[i]]++;

        vector<int>result(2);

        // First part: finding number whose frequency is 2
        for (auto& i: freq)
        {
            if (2 == i.second)
            {
                result[0] = i.first;
                break;
            }
        }
        
        // Second part: finding the missing number
        for (int i = 1; i < n+1; i++)
        {
            if (0 == freq[i])
            {
                result[1] = i;
                break;
            }
        }

        return result;
    }
};
