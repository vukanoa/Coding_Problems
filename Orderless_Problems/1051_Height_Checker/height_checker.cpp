#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ===========================
    1051) Height Checker
    ===========================

    ============
    Description:
    ============

    A school is trying to take an annual photo of all the students. The
    students are asked to stand in a single file line in non-decreasing order
    by height. Let this ordering be represented by the integer array expected
    where expected[i] is the expected height of the ith student in line.

    You are given an integer array heights representing the current order that
    the students are standing in. Each heights[i] is the height of the ith
    student in line (0-indexed).

    Return the number of indices where heights[i] != expected[i].

    ==================================================
    FUNCTION: int heightChecker(vector<int>& heights);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: heights = [1,1,4,2,1,3]
    Output: 3
    Explanation:
    heights:  [1,1,4,2,1,3]
    expected: [1,1,1,2,3,4]
    Indices 2, 4, and 5 do not match.

    --- Example 2 ---
    Input: heights = [5,1,2,3,4]
    Output: 5
    Explanation:
    heights:  [5,1,2,3,4]
    expected: [1,2,3,4,5]
    All indices do not match.

    --- Example 3 ---
    Input: heights = [1,2,3,4,5]
    Output: 0
    Explanation:
    heights:  [1,2,3,4,5]
    expected: [1,2,3,4,5]
    All indices match.


    *** Constraints ***
    1 <= heights.length <= 100
    1 <= heights[i] <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 31.17% */
/* Space Beats: 44.04% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_Counting_Sort {
public:
    int heightChecker(std::vector<int>& heights)
    {
        std::vector<char> sorted(heights.begin(), heights.end());

        // Counting sort
        char freq[101] = {0};

        for(const char& x: sorted)
            freq[x]++;

        int cnt = 0;

        for (int x = 1; x <= 100; x++)
        {
            int curr_freq = freq[x];
            std::vector<char> frequencies(curr_freq, x);
            std::copy(begin(frequencies), end(frequencies), sorted.begin() + cnt);
            cnt += curr_freq;
        }
        // End of count sort

        const int N = heights.size();
        int result = 0;
        for(int i = 0; i < N; i++)
            result += (heights[i] != sorted[i]);

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
/* Space Beats: 96.50% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_Builtin_Sort {
public:
    int heightChecker(std::vector<int>& heights)
    {
        const int N = heights.size();
        std::vector<char> sorted(heights.begin(), heights.end());
        std::sort(heights.begin(), heights.end());

        int result = 0;
        for(int i = 0; i < N; i++)
            result += (heights[i] != sorted[i]);

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
/* Space Beats: 96.50% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_Bit_Manipulation {
public:
    int heightChecker(std::vector<int>& heights)
    {
        // Reuse heights, no other container
        const int N = heights.size();

        for(int i = 0; i < N; i++) // Pack value for heights[i] & i in an int
            heights[i] = (heights[i] << 8) + i;

        std::sort(heights.begin(), heights.end());

        int result = 0;
        for(int i = 0; i < N; i++)
        {
            // Unpack heights[i] & index j. check if heights[j]==heights[i]
            result += (heights[(heights[i] & 255)] >> 8 != heights[i] >> 8);
        }

        return result;
    }
};
