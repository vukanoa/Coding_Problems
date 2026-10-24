/*
    ============
    === EASY ===
    ============

    ========================================
    3769) Sort Integers by Binary Reflection
    ========================================

    ============
    Description:
    ============

    You are given an integer array nums.

    The binary reflection of a positive integer is defined as the number
    obtained by reversing the order of its binary digits (ignoring any leading
    zeros) and interpreting the resulting binary number as a decimal.

    Sort the array in ascending order based on the binary reflection of each
    element. If two different numbers have the same binary reflection, the
    smaller original number should appear first.

    Return the resulting sorted array.

    ==========================================================
    FUNCTION: vector<int> sortByReflection(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,5,4]
    Output: [4,4,5]
    Explanation:
    Binary reflections are:
        4 -> (binary) 100 -> (reversed) 001 -> 1
        5 -> (binary) 101 -> (reversed) 101 -> 5
        4 -> (binary) 100 -> (reversed) 001 -> 1
    Sorting by the reflected values gives [4, 4, 5].


    --- Example 2 ---
    Input: nums = [3,6,5,8]
    Output: [8,3,6,5]
    Explanation:
    Binary reflections are:
        3 -> (binary) 11 -> (reversed) 11 -> 3
        6 -> (binary) 110 -> (reversed) 011 -> 3
        5 -> (binary) 101 -> (reversed) 101 -> 5
        8 -> (binary) 1000 -> (reversed) 0001 -> 1
    Sorting by the reflected values gives [8, 3, 6, 5].
    Note that 3 and 6 have the same reflection, so we arrange them in
    increasing order of original value.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 10^9

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 13.00% */
/* Space Beats:  9.50% */

/* Time  Complexity: O(N * log2(nums[i])  +  N * logN) ===>
                     O(N * 32             +  N * logN) ===>
                     O(N                  +  N * logN) ===>
                     O(N * logN                      )
*/
/* Space Complexity: O(N)                                                                                               */
class Solution {
public:
    vector<int> sortByReflection(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result; // "result" space usually isn't count as "extra"
        result.reserve(N);
        
        vector<pair<int,int>> vec; // This makes Space Complexity O(N)
        vec.reserve(N);

        for (int i = 0; i < N; i++)
        {
            string bin_str;
            bin_str.reserve(32);

            // Create binary representation of nums[i]
            for (int bit = 31; bit >= 0; bit--)
            {
                if (nums[i] & (1 << bit))
                    bin_str += '1';
                else
                    bin_str += '0';
            }

            // Get rid of leading zeroes
            int idx = bin_str.find('1');
            string bin_str_without_leading_zeroes = bin_str.substr(idx);

            reverse(bin_str_without_leading_zeroes.begin(), 
                    bin_str_without_leading_zeroes.end());

            // Get rid of leading zeroes in "binary reflection"(i.e. reversed)
            idx = bin_str_without_leading_zeroes.find('1');
            bin_str_without_leading_zeroes = bin_str_without_leading_zeroes.substr(idx);
            
            vec.push_back( {stoi(bin_str_without_leading_zeroes, nullptr, 2), i} );
        }

        // Sort first by decimal representation of "binary reflection" and
        // if they're EQUAL, then make sure the originally smaller one gets
        // first
        sort(vec.begin(), vec.end(), [&](const pair<int,int>& a, const pair<int,int>& b){
            if (a.first == b.first)
                return nums[a.second] < nums[b.second];

            return a.first < b.first;
        });

        // Populate reuslt
        for (const auto& entry : vec)
            result.push_back(nums[entry.second]);

        return result;
    }
};
