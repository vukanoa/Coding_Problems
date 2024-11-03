#include <iostream>
#include <sstream>

/*
    ============
    === EASY ===
    ============

    ===========================
    796) Rotate String
    ===========================

    ============
    Description:
    ============

    Given two strings s and goal, return true if and only if s can become goal
    after some number of shifts on s.

    A shift on s consists of moving the leftmost character of s to the
    rightmost position.

        For example, if s = "abcde", then it will be "bcdea" after one shift.

    ===================================================
    FUNCTION: bool rotateString(string s, string goal);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcde", goal = "cdeab"
    Output: true

    --- Example 2 ---
    Input: s = "abcde", goal = "abced"
    Output: false


    *** Constraints ***
    1 <= s.length, goal.length <= 100
    s and goal consist of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    After we're sure that the lengths of strings s and goal are the same, then
    if s can becomes goal by shifting, then it must be one of the rotations.

    Therefore, manually rotate the string and compare. After we've rotated it
    for n-1 times, we are at the initial state. If any rotation of goal is
    equal to string s then we return true. If no rototation nor initial string
    of goal is equal to string s then we return false.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  22.17% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool rotateString(string s, string goal)
    {
        if (s.length() != goal.length())
            return false;

        if (s == goal)
            return true;

        ostringstream out;
        string tmp = goal;

        for (int x = 0; x < goal.length()-1; x++)
        {
            char last_chr = tmp.back();
            tmp.pop_back();

            out << last_chr << tmp;

            if (out.str() == s)
                return true;

            tmp = out.str();
            out.str("");
            out.clear();
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We don't actually have to literally rotate as that would take way too much
    time, as previously shown in the above Solution(even though for EASY
    problems like these LeetCode rates even those Solutions as Beating 100.00%)

    Instead we can concatenate string s to itself and the simply use the "find"
    function to see if there is a substring goal anywhere in that new string
    composed of two s strings concatenated.

    Example:
        Input: s = "abcde", goal = "cdeab"

        new_str = s + s;
        // new_str = "abcdeabcde" 

        Can you match string goal="cdeab" as a substring in this new_str?
        The answer is - Yes!

        // new_str = "abcdeabcde" 
                        ^^^^^
                        |||||
                        |||||
        //    goal =    cdeab

*/

/* Time  Beats: 100.00% */
/* Space Beats:  55.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Elegant {
public:
    bool rotateString(string s, string goal)
    {
        if (s.length() != goal.length())
            return false;

        return (s + s).find(goal) != string::npos;
    }
};
