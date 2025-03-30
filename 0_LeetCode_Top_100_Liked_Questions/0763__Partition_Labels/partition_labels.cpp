/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    763) Partition Labels
    ===========================

    ============
    Description:
    ============

    You are given a string s. We want to partition the string into as many
    parts as possible so that each letter appears in at most one part.

    Note that the partition is done so that after concatenating all the parts
    in order, the resultant string should be s.

    Return a list of integers representing the size of these parts.

    ================================================
    FUNCTION: vector<int> partitionLabels(string s);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "ababcbacadefegdehijhklij"
    Output: [9, 7, 8]
    Explanation:
    The partition is "ababcbaca", "defegde", "hijhklij".
    This is a partition so that each letter appears in at most one part.
    A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it
    splits s into less parts.

    --- Example 2 ---
    Input:  s = "eccbbbbdec"
    Output: [10]

    *** Constraints ***
    1 <= s.length <= 500
    s consists of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Input:  s = "ababcbacadefegdehijkhklij"
    Output: [9, 7, 8]

    a {0,   8}  00-------------08
    b {1,   5}   01------05
    c {4,   7}         04-----07
    d {9,  14}                   09--------14
    e {10, 15}                     10--------15
    f {11, -1}                       11
    g {13, -1}                           13
    h {16, 19}                                 16----19
    i {17, 22}                                   17--------22
    j {18, 23}                                     18--------23
    k {20, -1}                                         20
    l {21, -1}                                           21


    The rest of the Solution is Self-explanatory.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Let's look at the very first example:

    Input:  s = "ababcbacadefegdehijkhklij"
    Output: [9, 7, 8]

    a {0,   8}  00-------------08
    b {1,   5}   01------05
    c {4,   7}         04-----07
    d {9,  14}                   09--------14
    e {10, 15}                     10--------15
    f {11, -1}                       11
    g {13, -1}                           13
    h {16, 19}                                 16----19
    i {17, 22}                                   17--------22
    j {18, 23}                                     18--------23
    k {20, -1}                                         20
    l {21, -1}                                           21


        "ababcbacadefegdehijkhklij"
         #

    Immediately, we know that we cannot partition this string as follows:

        "a" | "babcbacadefegdehijkhklij"

    if there are additional "a" characters somewhere else in the string.
    And not only that, we can have multiple "a" characters, and we do.
    We care about the last "a" character the most. Once we stop here:

        "ababcbaca" | "defegdehijkhklij"
         #       ^
      first     last

    We are sure that all of the "a" characters are in this first portion of
    the string.

    So that's what we're trying to do, to create a partition where all "a"
    characters, in this case, are in a single partition and not anywhere
    else in the string.

    So, wouldn't it be convenient for us that everytime we see a character
    we could automatically know the index at which index it occurs for the last
    time in string s?

    Maybe that character itself is the last occurence of it.
    (It appears only once in string s).

    We can do exactly that, thus we will make a Hash Map:
    We put a character in Hash Map only if we stumble upon it while iterating
    over string s.

         char   last_index
        { Key : Value }
        |  a  :  -1  |
        |  b  :  -1  |
        |  c  :  -1  |
        |  d  :  -1  |
        |  e  :  -1  |
        |  f  :  -1  |
        |  g  :  -1  |
        |  h  :  -1  |
        |  i  :  -1  |
        |  j  :  -1  |
        |  k  :  -1  |
        |  l  :  -1  |
        |  m  :  -1  |
        |  n  :  -1  |
        |  o  :  -1  |
        |  p  :  -1  |
        |  q  :  -1  |
        |  r  :  -1  |
        |  s  :  -1  |
        |  t  :  -1  |
        |  u  :  -1  |
        |  v  :  -1  |
        |  w  :  -1  |
        |  x  :  -1  |
        |  y  :  -1  |
        |  z  :  -1  |


    We take every single unique character in the input string and we map it to
    the last index it occurs at.

     0 ...               ... 23
    "ababcbacadefegdehijkhklij"

    We will iterate through an entire string s, and this is what our Hash Map
    will look like after the iteration:

         char   last_index
        { Key : Value }
        |  a  :   8   |
        |  b  :   5   |
        |  c  :   7   |
        |  d  :  14   |
        |  e  :  15   |
        |  f  :  11   |
        |  g  :  13   |
        |  h  :  18   |
        |  i  :  22   |
        |  j  :  23   |
        |  k  :  20   |
        |  l  :  21   |

    However, instead of a HashMap, we'll use a vector of size 26, because it's
    a bit faster.

        [ 8,  5,  7, 14, 15, 11, 13, 18, 22, 23, 20, 21, -1, -1, ...]
          0   1   2   3   5   6   7   8   9  10  11  12  13  14 ...
         'a' 'b' 'c' 'd' 'e' 'f' 'g' 'h' 'i' 'j' 'k' 'l' 'm' 'n'

    (This is a trick you can always do since there are 26 english characters,
     which is a constant)

    Once we're on "last_in_this_part", we're concluding this partitiong and
    we'll push:

        R - L + 1

    L is the beginning of the curently unclosed partition.
    R is the current index

    Once we're at the closing character of the currently unclosed partition, we
    close it by pushing the size of it in "result" and we Reset variables:

        "L" and "last_in_this_part"

*/

/* Time  Beats: 100.00% */
/* Space Beats:  49.45% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> partitionLabels(string s)
    {
        const int N = s.size();
        vector<int> result;

        vector<int> end(26, -1);
        for (int i = 0; i < N; i++)
            end[s[i] - 'a'] = i;

        int L = 0;
        int R = 0;

        int last_in_this_part = -1;
        while (R < N)
        {
            last_in_this_part = max(last_in_this_part, end[s[R] - 'a']);

            // If we're on the last character in this partition--Push and Reset
            if (last_in_this_part == R)
            {
                // Push
                result.push_back(R - L + 1);

                // Reset
                L = R + 1;
                last_in_this_part = -1;
            }

            // Increment
            R++;
        }

        return result;
    }
};
