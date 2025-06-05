/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    1061) Lexicographically Smallest Equivalent String
    ==================================================

    ============
    Description:
    ============

    You are given two strings of the same length s1 and s2 and a string baseStr

    We say s1[i] and s2[i] are equivalent characters.

        For example, if s1 = "abc" and s2 = "cde", then we have:

            'a' == 'c'
            'b' == 'd'
            'c' == 'e'

    Equivalent characters follow the usual rules of any equivalence relation:

        Reflexivity: 'a' == 'a'.
        Symmetry: 'a' == 'b' implies 'b' == 'a'.
        Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.

    For example, given the equivalency information from s1 = "abc" and
    s2 = "cde", "acd" and "aab" are equivalent strings of baseStr = "eed", and
    "aab" is the lexicographically smallest equivalent string of baseStr.

    Return the lexicographically smallest equivalent string of baseStr by using
    the equivalency information from s1 and s2.

    ================================================================================
    FUNCTION: string smallestEquivalentString(string s1, string s2, string baseStr);
    ================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s1 = "parker", s2 = "morris", baseStr = "parser"
    Output: "makkek"
    Explanation: Based on the equivalency information in s1 and s2, we can
                 group their characters as [m,p], [a,o], [k,r,s], [e,i]. The
                 characters in each group are equivalent and sorted in
                 lexicographical order. So the answer is "makkek".


    --- Example 2 ---
    Input: s1 = "hello", s2 = "world", baseStr = "hold"
    Output: "hdld"
    Explanation: Based on the equivalency information in s1 and s2, we can
                 group their characters as [h,w], [d,e,o], [l,r]. So only the
                 second letter 'o' in baseStr is changed to 'd', the answer is
                 "hdld".


    --- Example 3 ---
    Input: s1 = "leetcode", s2 = "programs", baseStr = "sourcecode"
    Output: "aauaaaaada"
    Explanation: We group the equivalent characters in s1 and s2 as
                 [a,o,e,r,s,c], [l,p], [g,t] and [d,m], thus all letters in
                 baseStr except 'u' and 'd' are transformed to 'a', the answer
                 is "aauaaaaada".


    *** Constraints ***
    1 <= s1.length, s2.length, baseStr <= 1000
    s1.length == s2.length
    s1, s2, and baseStr consist of lowercase English letters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    One of the most basic DFS uses once the adjacency list is constructed.

*/

/* Time  Beats:  5.57% */
/* Space Beats: 26.72% */

/* Time  Complexity: O(N + M * 26)  ---> O(N + M) */
/* Space Complexity: O(26 * N)      ---> O(N)     */
class Solution {
public:
    string smallestEquivalentString(string s1, string s2, string baseStr)
    {
        const int N = s1.length();

        /* Construct an Adjacency List */
        unordered_map<char, vector<char>> adj_list;

        for (int i = 0; i < N; i++)
        {
            if (s1[i] == s2[i])
                continue;

            /* Undirected Graph */
            adj_list[s1[i]].push_back(s2[i]);
            adj_list[s2[i]].push_back(s1[i]);
        }

        for (unsigned i = 0; i < baseStr.size(); i++)
        {
            vector<bool> visited(26, false);
            char lex_smallest = baseStr[i];

            dfs(baseStr[i], adj_list, lex_smallest, visited);

            baseStr[i] = lex_smallest;
        }

        return baseStr;
    }

private:
    void dfs(char curr_chr, unordered_map<char, vector<char>>& adj_list, char& lex_smallest, vector<bool>& visited)
    {
        if (visited[curr_chr - 'a'])
            return;

        visited[curr_chr - 'a'] = true;

        lex_smallest = min(lex_smallest, curr_chr);

        for (const char& neighbor_char : adj_list[curr_chr])
        {
            dfs(neighbor_char, adj_list, lex_smallest, visited);
        }
    }
};
