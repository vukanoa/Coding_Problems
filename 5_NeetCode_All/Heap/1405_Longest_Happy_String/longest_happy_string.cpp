#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1405) Longest Happy String
    ===========================

    ============
    Description:
    ============

    A string s is called happy if it satisfies the following conditions:

        s only contains the letters 'a', 'b', and 'c'.
        s does not contain any of "aaa", "bbb", or "ccc" as a substring.
        s contains at most a occurrences of the letter 'a'.
        s contains at most b occurrences of the letter 'b'.
        s contains at most c occurrences of the letter 'c'.

    Given three integers a, b, and c, return the longest possible happy string.
    If there are multiple longest happy strings, return any of them. If there
    is no such string, return the empty string "".

    A substring is a contiguous sequence of characters within a string.

    ===========================================================
    FUNCTION: string longestDiverseString(int a, int b, int c);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: a = 1, b = 1, c = 7
    Output: "ccaccbcc"
    Explanation: "ccbccacc" would also be a correct answer.

    --- Example 2 ---
    Input: a = 7, b = 1, c = 0
    Output: "aabaa"
    Explanation: It is the only correct answer in this case.


    *** Constraints ***
    0 <= a, b, c <= 100
    a + b + c > 0

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Good example to consider:
    a = 0, b = 8, c = 11

    This is NOT    the longest string: "ccbbccbbccbbccbbcc"

    This is INDEED the longest stirng: "ccbccbbccbbccbbccbc"

*/

/* Time  Beats:   100% */
/* Space Beats: 42.57% */

/* Time  Complexity: O(1) */ // But in general it could be n
/* Space Complexity: O(1) */ // We don't count result string as additional
class Solution {
public:
    string longestDiverseString(int a, int b, int c)
    {
        std::priority_queue<std::pair<int, char>> max_heap;

        if (a > 0) max_heap.push( {a, 'a'} );
        if (b > 0) max_heap.push( {b, 'b'} );
        if (c > 0) max_heap.push( {c, 'c'} );

        std::string str;
        while (!max_heap.empty())
        {
            std::pair<int, char> one = max_heap.top();
            max_heap.pop();

            if (
                str.length() >= 2 &&
                str[str.length() - 2] == str[str.length() - 1] &&
                str[str.length() - 1] == one.second
               )
            {
                if (max_heap.empty())
                    break;

                std::pair<int, char> two = max_heap.top();
                max_heap.pop();

                str += two.second;
                two.first--;

                if (two.first > 0)
                    max_heap.push(two);
            }
            else
            {
                str += one.second;
                one.first--;
            }

            if (one.first > 0)
                max_heap.push(one);
        }

        return str;
    }
};
