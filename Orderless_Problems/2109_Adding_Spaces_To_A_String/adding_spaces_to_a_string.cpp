#include <iostream>
#include <vector>
#include <sstream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    2109) Adding Spaces to a String
    ===============================

    ============
    Description:
    ============

    You are given a 0-indexed string s and a 0-indexed integer array spaces
    that describes the indices in the original string where spaces will be
    added. Each space should be inserted before the character at the given
    index.

        For example, given s = "EnjoyYourCoffee" and spaces = [5, 9], we place
        spaces before 'Y' and 'C', which are at indices 5 and 9 respectively.
        Thus, we obtain "Enjoy Your Coffee".

    Return the modified string after the spaces have been added.

    ==========================================================
    FUNCTION: string addSpaces(string s, vector<int>& spaces);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "LeetcodeHelpsMeLearn", spaces = [8,13,15]
    Output: "Leetcode Helps Me Learn"
    Explanation:
    The indices 8, 13, and 15 correspond to the underlined characters in
    "LeetcodeHelpsMeLearn". We then place spaces before those characters.
             ^    ^ ^

    --- Example 2 ---
    Input: s = "icodeinpython", spaces = [1,5,7,9]
    Output: "i code in py thon"
    Explanation:
    The indices 1, 5, 7, and 9 correspond to the underlined characters in
    "icodeinpython". We then place spaces before those characters.
     ^    ^   ^

    --- Example 3 ---
    Input: s = "spacing", spaces = [0,1,2,3,4,5,6]
    Output: " s p a c i n g"
    Explanation:
    We are also able to place spaces before the first character of the string.


    *** Constraints ***
    1 <= s.length <= 3 * 10^5
    s consists only of lowercase and uppercase English letters.
    1 <= spaces.length <= 3 * 10^5
    0 <= spaces[i] <= s.length - 1
    All the values of spaces are strictly increasing.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    I have no idea why is this considered "MEDIUM". Very intuitive, just read
    the code and you'll understand it.

*/

/* Time  Beats:  6.93% */
/* Space Beats:  6.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution { // Using "String Builder"
public:
    string addSpaces(string s, vector<int>& spaces)
    {
        ostringstream out;

        int i = 0;
        for (int chr_idx = 0; chr_idx < s.length(); chr_idx++)
        {
            if (i < spaces.size() && chr_idx == spaces[i])
            {
                out << " ";
                i++;
            }

            out << s[chr_idx];
        }

        return out.str();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, though this one uses "string" instead of "ostringstream"(aka
    "String Builder"). This one is considered faster since we've construced a
    new string of size: s.length() + spaces.size() in advance and then just
    populated that string.

    In the above Solution we were pushing element-by-element which is a lot
    slower, at least according to LeetCode.

*/

/* Time  Beats: 96.69% */
/* Space Beats: 93.30% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    string addSpaces(string& s, vector<int>& spaces)
    {
        string result_str(s.length() + spaces.size(), ' ');
        
        int i = 0; // Pointer for spaces
        for (int chr_idx = 0; chr_idx < s.length(); chr_idx++)
        {
            if (i < spaces.size() && chr_idx == spaces[i])
            {
                result_str[chr_idx + i] = ' '; 
                i++;
            }

            result_str[chr_idx + i] = s[chr_idx];
        }

        return result_str;
    }
};