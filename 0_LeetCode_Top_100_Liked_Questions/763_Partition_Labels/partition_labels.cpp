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

    Let's look at the very first example:

    Input:  s = "ababcbacadefegdehijkhklij"
    Output: [9, 7, 8]

        "ababcbacadefegdehijkhklij"
         #

    Immediately, we know that we cannot partition this string as follows:

        "a" | "babcbacadefegdehijkhklij"

    if there are additional 'a' characters somewhere else in the string.
    And not only that, we can have multiple 'a' characters, and we do.
    We care about the last 'a' character the most. Once we stop here:

        "ababcbaca" | "defegdehijkhklij"
         #       ^
      first     last

    We are sure that all of the 'a' characters are in this first partition of
    the string.

    So that's what we're trying to do. To create a partition where all 'a'
    characters are in a single partition and not anywhere else in the string.

    So, wouldn't it be convenient for us that everytime we see a character
    we could automatically know the index at which index it occurs for the last
    time in string s?

    There can be cases such that some character is both the first and last
    occurrence of it, i.e. it appears only once in stirng s.

    We can do exactly that, we make an integer array of size 26 since we're
    working with only lowercase English characters.

    We'll call that array "last_occurrence" as the value in each of the 26
    slots will represents where is the LAST occurrence of that character in our
    string s.

        [8,  5,  7, 14, 15, 11, 13, 18, 22, 23, 20, 21,  ... ,  0]
         0   1   2   3   5   6   7   8   9  10  11  12   ...   25
         a   b   c   d   e   f   g   h   i   j   k   l          z

    Once we are on the partition_end index, we can conclude that we've finished
    with this partition, thus we push:

        result.push(end - start + 1)

    And we'll start a new partition at (partition_start + 1) index.
        partition_start = i+1;

    In a way, it's similar to "Merge Interval" Problem.

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


*/

/* Time  Beats: 100.00% */
/* Space Beats:  21.81% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> partitionLabels(string s)
    {
        const int N = s.size();
        vector<int> result;
        result.reserve(N); // To prevent subsequent reallocations

        int last_occurrence[26] = {0};
        for (int i = 0; i < N; i++)
            last_occurrence[s[i] - 'a'] = i;

        int partition_start = 0;
        int partition_end   = 0;

        for (int i = 0; i < N; i++)
        {
            partition_end = max(partition_end, last_occurrence[s[i] - 'a']);

            if (i == partition_end)
            {
                result.push_back(partition_end - partition_start + 1);
                partition_start = i+1;
            }
        }

        return result;
    }
};
