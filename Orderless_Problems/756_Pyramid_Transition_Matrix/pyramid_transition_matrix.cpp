/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    756) Pyramid Transition Matrix
    ==============================

    ============
    Description:
    ============

    You are stacking blocks to form a pyramid. Each block has a color, which is
    represented by a single letter. Each row of blocks contains one less block
    than the row beneath it and is centered on top.

    To make the pyramid aesthetically pleasing, there are only specific
    triangular patterns that are allowed. A triangular pattern consists of a
    single block stacked on top of two blocks. The patterns are given as a list
    of three-letter strings allowed, where the first two characters of a
    pattern represent the left and right bottom blocks respectively, and the
    third character is the top block.

    For example, "ABC" represents a triangular pattern with a 'C' block stacked
    on top of an 'A' (left) and 'B' (right) block. Note that this is different
    from "BAC" where 'B' is on the left bottom and 'A' is on the right bottom.

    You start with a bottom row of blocks bottom, given as a single string,
    that you must use as the base of the pyramid.

    Given bottom and allowed, return true if you can build the pyramid all the
    way to the top such that every triangular pattern in the pyramid is in
    allowed, or false otherwise.

    =========================================================================
    FUNCTION: bool pyramidTransition(string bottom, vector<string>& allowed);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
    Output: true
    Explanation: The allowed triangular patterns are shown on the right.
    Starting from the bottom (level 3), we can build "CE" on level 2 and then
    build "A" on level 1. There are three triangular patterns in the pyramid,
    which are "BCC", "CDE", and "CEA". All are allowed.

    --- Example 2 ---
    Input: bottom = "AAAA", allowed = ["AAB","AAC","BCD","BBE","DEF"]
    Output: false
    Explanation: The allowed triangular patterns are shown on the right.
    Starting from the bottom (level 4), there are multiple ways to build level
    3, but trying all the possibilites, you will get always stuck before
    building level 1.


    *** Constraints ***
    2 <= bottom.length <= 6
    0 <= allowed.length <= 216
    allowed[i].length == 3
    The letters in all input strings are from the set {'A', 'B', 'C', 'D', 'E', 'F'}.
    All the values of allowed are unique.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 68.11% */
/* Space Beats: 27.03% */

/* Time  Complexity: O(N * 6^(N-1)) */
/* Space Complexity: O(N * 6^(N-1)) */
class Solution {
public:
    unordered_map<string, bool> memo;

    bool pyramidTransition(string bottom, vector<string> & allowed)
    {
        const int N = allowed.size();

        int mask[6][6] = {0};

        for (int i = 0; i < N; ++i)
        {
            int left  = allowed[i][0] - 'A';
            int right = allowed[i][1] - 'A';
            int top   = allowed[i][2] - 'A';

            mask[left][right] |= 1 << top;
        }

        return solve(bottom, 0, static_cast<int>(bottom.size()), mask);
    }

private:
    bool solve(string& curr_str, int curr_idx, int n, int mask[6][6])
    {
        if (n == 1)
            return true;

        string key = curr_str + to_string(curr_idx) + to_string(n);
        if (memo.count(key))
            return memo[key];

        bool result = false;

        if (curr_idx < n - 1)
        {
            int left  = curr_str[curr_idx]     - 'A';
            int right = curr_str[curr_idx + 1] - 'A';

            char original_char = curr_str[curr_idx];
            int  possible_tops = mask[left][right];

            while (possible_tops)
            {
                int lowest_bit = possible_tops & -possible_tops;

                int top_index = 0;
                while ((lowest_bit >> top_index) != 1)
                    top_index++;

                curr_str[curr_idx] = static_cast<char>('A' + top_index);
                result |= solve(curr_str, curr_idx + 1, n, mask);
                curr_str[curr_idx] = original_char;

                if (result)
                    break;

                possible_tops -= lowest_bit;
            }
        }
        else
        {
            result |= solve(curr_str, 0, n - 1, mask);
        }

        return memo[key] = result;
    }
};
