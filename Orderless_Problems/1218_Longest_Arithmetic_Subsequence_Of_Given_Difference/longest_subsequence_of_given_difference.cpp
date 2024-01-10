#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    1218) Longest Arithmetic Subsequence of Given Difference
    ========================================================

    ============
    Description:
    ============

    Given an integer array arr and an integer difference, return the length of
    the longest subsequence in arr which is an arithmetic sequence such that
    the difference between adjacent elements in the subsequence equals
    difference.

    A subsequence is a sequence that can be derived from arr by deleting some
    or no elements without changing the order of the remaining elements.

    ===================================================================
    FUNCTION: int longestSubsequence(vector<int>& arr, int difference);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,2,3,4], difference = 1
    Output: 4
    Explanation: The longest arithmetic subsequence is [1,2,3,4].

    --- Example 2 ---
    Input: arr = [1,3,5,7], difference = 1
    Output: 1
    Explanation: The longest arithmetic subsequence is any single element.

    --- Example 3 ---
    Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
    Output: 4
    Explanation: The longest arithmetic subsequence is [7,5,3,1].


    *** Constraints ***
    1 <= arr.length <= 10^5
    -10^4 <= arr[i], difference <= 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 57.06% */
/* Space Beats: 70.17% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_1 {
public:
    int longestSubsequence(std::vector<int>& arr, int difference)
    {
        int n = arr.size();

        std::unordered_map<int, int> umap;
        int longest = 1;

        for(auto num : arr)
        {
            if(umap.count(num - difference))
                umap[num] = umap[num - difference] + 1;
            else
                umap[num] = 1;

            longest = std::max(longest, umap[num]);
        }

        return longest;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The same as above, but this implementation is more intuitive to me for 1D
    Dynamic Programming problems.

*/

/* Time  Beats: 63.81% */
/* Space Beats: 57.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    int longestSubsequence(std::vector<int>& arr, int difference)
    {
        int n = arr.size();

        std::unordered_map<int, int> umap;
        int longest = 1;

        for(int i = n-1; i >= 0; i--)
        {
            if(umap.count(arr[i] + difference))
                umap[arr[i]] = umap[arr[i] + difference] + 1;
            else
                umap[arr[i]] = 1;

            longest = std::max(longest, umap[arr[i]]);
        }

        return longest;
    }
};
