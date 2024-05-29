#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ====================================
    806) Number of Lines to Write String
    ====================================

    ============
    Description:
    ============

    You are given a string s of lowercase English letters and an array widths
    denoting how many pixels wide each lowercase English letter is.
    Specifically, widths[0] is the width of 'a', widths[1] is the width of 'b',
    and so on.

    You are trying to write s across several lines, where each line is no
    longer than 100 pixels. Starting at the beginning of s, write as many
    letters on the first line such that the total width does not exceed 100
    pixels. Then, from where you stopped in s, continue writing as many letters
    as you can on the second line. Continue this process until you have written
    all of s.

    Return an array result of length 2 where:

        + result[0] is the total number of lines.
        + result[1] is the width of the last line in pixels.


    ===================================================================
    FUNCTION: vector<int> numberOfLines(vector<int>& widths, string s);
    ===================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: widths =
    [10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10],
    s = "abcdefghijklmnopqrstuvwxyz"
    Output: [3,60]
    Explanation: You can write s as follows:
    abcdefghij  // 100 pixels wide
    klmnopqrst  // 100 pixels wide
    uvwxyz      // 60 pixels wide
    There are a total of 3 lines, and the last line is 60 pixels wide.


    --- Example 2 ---
    Input: widths =
    [4,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10],
    s = "bbbcccdddaaa"
    Output: [2,4]
    Explanation: You can write s as follows:
    bbbcccdddaa  // 98 pixels wide
    a            // 4 pixels wide
    There are a total of 2 lines, and the last line is 4 pixels wide.


    *** Constraints ***
    widths.length == 26
    2 <= widths[i] <= 10
    1 <= s.length <= 1000
    s contains only lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  39.09% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::vector<int> numberOfLines(std::vector<int>& widths, std::string s)
    {
        int lines = 0;
        int type_line = 0;

        for(const auto& x : s)
        {
            if(type_line + widths[x - 'a'] <= 100)
                type_line += widths[x - 'a'];
            else
            {
                lines++;
                type_line = widths[x - 'a'];
            }
        }

        if (type_line != 0)
            lines++;

        std::vector<int> result;

        result.push_back(lines);
        result.push_back(type_line);

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
/* Space Beats:   8.41% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    std::vector<int> numberOfLines(std::vector<int>& widths, std::string s)
    {
        int lines = 1;
        int width = 0;

        for(int i = 0; i < s.length(); i++)
        {
            if(widths[s[i] - 97] + width > 100) // lowercase 'a' is ASCII 97
            {
                lines++;
                width = widths[s[i] - 97];
            }
            else
                width += widths[s[i] - 97];
        }

        return {lines, width};
    }
};
