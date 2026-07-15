/*
    ==============
    === MEDIUM ===
    ==============

    ============================================================
    1764) Form Array by Concatenating Subarrays of Another Array
    ============================================================

    ============
    Description:
    ============

    You are given a 2D integer array groups of length n. You are also given an
    integer array nums.

    You are asked if you can choose n disjoint subarrays from the array nums
    such that the ith subarray is equal to groups[i] (0-indexed), and if i > 0,
    the (i-1)th subarray appears before the ith subarray in nums (i.e. the
    subarrays must be in the same order as groups).

    Return true if you can do this task, and false otherwise.

    =====
    Note: that the subarrays are disjoint if and only if there is no index k
          such that nums[k] belongs to more than one subarray. A subarray is a
          contiguous sequence of elements within an array. 
    =====

    =========================================================================
    FUNCTION: bool canChoose(vector<vector<int>>& groups, vector<int>& nums);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: groups = [[1,-1,-1],[3,-2,0]], nums = [1,-1,0,1,-1,-1,3,-2,0]
    Output: true
    Explanation: You can choose the 0th subarray as [1,-1,0,1,-1,-1,3,-2,0] and
                 the 1st one as [1,-1,0,1,-1,-1,3,-2,0]. These subarrays are
                 disjoint as they share no common nums[k] element.

    --- Example 2 ---
    Input: groups = [[10,-2],[1,2,3,4]], nums = [1,2,3,4,10,-2]
    Output: false
    Explanation: Note that choosing the subarrays [1,2,3,4,10,-2] and
                 [1,2,3,4,10,-2] is incorrect because they are not in the same
                 order as in groups. [10,-2] must come before [1,2,3,4].

    --- Example 3 ---
    Input: groups = [[1,2,3],[3,4]], nums = [7,7,1,2,3,4,7,7]
    Output: false
    Explanation: Note that choosing the subarrays [7,7,1,2,3,4,7,7] and
                 [7,7,1,2,3,4,7,7] is invalid because they are not disjoint.
                 They share a common elements nums[4] (0-indexed).


    *** Constraints ***
    groups.length == n
    1 <= n <= 10^3
    1 <= groups[i].length, sum(groups[i].length) <= 10^3
    1 <= nums.length <= 10^3
    -10^7 <= groups[i][j], nums[k] <= 10^7

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    KMP but on Vectors instead of strings.

*/

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(M) */

/* Time  Beats: 100.00% */
/* Space Beats:  17.65% */
class KMP_Vector {
public:
    int kmp_algo(vector<int>& nums, vector<int>& pattern, int start_idx)
    {
        const int N = nums.size();
        const int M = pattern.size();

        /* Populate LPS */
        vector<int> LPS = calculate_LPS(pattern);

        int i = start_idx;
        int j = 0;

        while (i < N && j < M)
        {
            if (nums[i] == pattern[j])
            {
                i++;
                j++;

                if (j == M)
                    return i;
            }
            else
            {
                if (j > 0)
                    j = LPS[j - 1];
                else
                    i++;
            }
        }

        return -1;
    }

private:
    vector<int> calculate_LPS(vector<int>& pattern)
    {
        const int PATTERN_SIZE = pattern.size();

        /* Initialize with ZEROES */
        vector<int> LPS(PATTERN_SIZE, 0);

        int prefix_len = 0;
        int i          = 1;

        while (i < PATTERN_SIZE)
        {
            if (pattern[prefix_len] == pattern[i])
            {
                LPS[i] = prefix_len + 1;
                prefix_len++;
                i++;
            }
            else
            {
                if (prefix_len > 0)
                    prefix_len = LPS[prefix_len - 1];
                else
                    i++;
            }
        }

        return LPS;
    }
};

class Solution {
public:
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums)
    {
        const int N = groups.size();
        const int M = nums.size();

        KMP_Vector kmp;

        int num_idx   = 0;
        int group_idx = 0;

        while (group_idx < N && num_idx < M)
        {
            num_idx = kmp.kmp_algo(nums, groups[group_idx], num_idx);

            if (num_idx == -1)
                return false;

            group_idx++;
        }

        return group_idx == N;
    }
};
