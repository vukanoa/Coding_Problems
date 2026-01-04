#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =======================================================
    1897) Redistribute Characters to Make All Strings Equal
    =======================================================

    ============
    Description:
    ============

    You are given an array of strings words (0-indexed).

    In one operation, pick two distinct indices i and j, where words[i] is a
    non-empty string, and move any character from words[i] to any position in
    words[j].

    Return true if you can make every string in words equal using any number of
    operations, and false otherwise.

    ================================================
    FUNCTION: bool makeEqual(vector<string>& words);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["abc","aabc","bc"]
    Output: true
    Explanation: Move the first 'a' in words[1] to the front of words[2],
    to make words[1] = "abc" and words[2] = "abc".
    All the strings are now equal to "abc", so return true.

    --- Example 2 ---
    Input: words = ["ab","a"]
    Output: false
    Explanation: It is impossible to make all the strings equal using the
                 operation.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] consists of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This part of the description is CRUCIAL:

    Return true IF YOU CAN MAKE EVERY STRING IN WORDS EQUAL USING ANY NUMBER OF
    OPERATIONS, and false otherwise.

    That even means if we had, for example,

    words = {"abc", "acb"}, we should return true.

    Why?
    Because we can move 'b' from words[0] to the end of words[1] and then we
    can move it back to the end of words[0], making both equal "acb".

    Since that is that case and since all of them have to be equal, then that
    means all of them have to:
        1) Be of EQUAL size
        2) Have EQUAL amount of occurrences of each letter

    Once you notice this, it becomes trivial.

    Now it becomes a "counting game".
    We must collect all of the used characters and their number of occurrences
    in total in all of the words.

    Then we need to see if diving that number with N(which is the total amount
    of different words) is equal to 0.

    If it is, then it means that that specific letter can indeed be rearranged
    in a way to appear the same amount of times in all of the strings.

    If it is not, we return "false" immediately.

    Also, notice that we do NOT care about the number of operations in which
    we have to make all the strings equal. We're not even counting that.

    That's why this becomes a counting game of occurrences of each letter and
    dividing by N, which is the number of words.

*/

/* Time  Beats: 98.64% */
/* Space Beats: 64.84% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool makeEqual(vector<string>& words)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = words.size();

        vector<int> occurrences(26, 0);
        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words[i].size(); j++)
                occurrences[words[i][j] - 'a']++;
        }

        for (int i = 0; i < 26; i++)
        {
            if (occurrences[i] % N != 0)
                return false;
        }

        return true;
    }
};
