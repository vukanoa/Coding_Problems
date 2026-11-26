/*
    ============
    === EASY ===
    ============

    ====================================
    2506) Count Pairs of Similar Strings
    ====================================

    ============
    Description:
    ============

    You are given a 0-indexed string array words.

    Two strings are similar if they consist of the same characters.

        + For example, "abca" and "cba" are similar since both consist of
          characters 'a', 'b', and 'c'.

        + However, "abacba" and "bcfd" are not similar since they do not
          consist of the same characters.

    Return the number of pairs (i, j) such that 0 <= i < j <= word.length - 1
    and the two strings words[i] and words[j] are similar.

    ==================================================
    FUNCTION: int similarPairs(vector<string>& words);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["aba","aabb","abcd","bac","aabc"]
    Output: 2
    Explanation: There are 2 pairs that satisfy the conditions:
    - i = 0 and j = 1 : both words[0] and words[1] only consist of characters 'a' and 'b'. 
    - i = 3 and j = 4 : both words[3] and words[4] only consist of characters 'a', 'b', and 'c'. 


    --- Example 2 ---
    Input: words = ["aabb","ab","ba"]
    Output: 3
    Explanation: There are 3 pairs that satisfy the conditions:
    - i = 0 and j = 1 : both words[0] and words[1] only consist of characters 'a' and 'b'. 
    - i = 0 and j = 2 : both words[0] and words[2] only consist of characters 'a' and 'b'.
    - i = 1 and j = 2 : both words[1] and words[2] only consist of characters 'a' and 'b'.


    --- Example 3 ---
    Input: words = ["nba","cba","dba"]
    Output: 0
    Explanation: Since there does not exist any pair that satisfies the conditions, we return 0.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] consist of only lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 44.07% */
/* Space Beats: 45.76% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution_Brute_Force {
public:
    int similarPairs(vector<string>& words)
    {
        const int N = words.size();
        int result = 0;

        vector<unordered_set<char>> vec_of_usets(N, unordered_set<char>());

        for (int i = 0; i < N; i++)
        {
            for (const char& chr : words[i])
                vec_of_usets[i].insert(chr);
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if (vec_of_usets[i] == vec_of_usets[j])
                    ++result;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 88.98% */
/* Space Beats: 70.34% */

/* Time  Complexity: O(N * W) */
/* Space Complexity: O(N)     */
class Solution_Optimal {
public: 
    int similarPairs(vector<string>& words)
    {
        int result = 0; 

        unordered_map<int, int> freq; 
        for (const auto& word : words)
        {
            int mask = 0; 

            for (const char& chr : word)
                mask |= 1 << (chr - 'a'); 

            result += freq[mask]; 
            ++freq[mask];
        }

        return result; 
    }
};
