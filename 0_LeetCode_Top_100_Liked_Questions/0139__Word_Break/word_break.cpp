/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    139) Word Break
    ===========================

    ============
    Description:
    ============

    Given a string 's' and a dictionary of strings "wordDict", return true
    if 's' can be segmented a space-separated sequence of one or more
    dictrionary words.

    =====
    Node: The same word in the dictionary may be reused multiple times in the
    ===== segmentation.

    =============================================================
    FUNCTION: bool wordBreak(string s, vector<string>& wordDict);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "leetcode", wordDict = ["leet", "code"]
    Output: true

    --- Example 2 ---
    Input:  s = "applepenapple", wordDict = ["apple", "pen"]
    Output: pen

    --- Example 3 ---
    Input:  s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
    Output: false

    *** Constraints ***
    1 <= s.length <= 300
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 20
    s and wordDict[i] consist of only lowercase English letters.
    All the strings of wordDict are unique.

*/


#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;



/* TLE (Time Limit Exceeded) */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n) */
class Solution_Brute{
private:
    bool backtracking(string& s, unordered_set<string>& dict_uset, int start)
    {
        if (start == s.length())
            return true;

        for (int i = start; i < s.length(); i++)
        {
            string current_str = s.substr(start, i - start + 1);

            if (dict_uset.find(current_str) != dict_uset.end())
            {
                if (backtracking( s, dict_uset, i + 1))
                    return true;
            }
        }

        return false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        unordered_set<string> dict_uset(wordDict.begin(), wordDict.end());

        return backtracking(s, dict_uset, 0);
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    --- Brute force(Using recursion) ---

    It starts with an index = 0;
    Then tries to find the substring of a string s that is present in the
    wordDict. As soon as it finds, it calls recursion again but now with:
        i + 1 as a starting index
    Essentially - Do the same thing but for a subproblem.

    Algorithm goes something like this:
        1. "l"
            doesn't exist in wordDict.
        2. "le"
            doesn't exist in wordDict.
        3. "lee"
            doesn't exist in wordDict.
        4. "leet"
            does indeed exist in wordDict => Enter recursion with (4, s, wordDict);
            1. "c"
                doesn't exist in wordDict.
            2. "co"
                doesn't exist in wordDict.
            3. "cod"
                doesn't exist in wordDict.
            4. "code"
                does indeed exist in wordDict => Enter recursion with (8, s, wordDict);
                8 == s.length() => Return true

    At first glance, this will seem more efficient than the Memoization
    solution explained below, but consider this example:

    string s = "aaaaaaaaaaaaaaaaaaaab";
    vector<string> wordDict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa"};

    If you try to simulate this program, you'll find that it will have an
    enormous amount of inefficient, unnecessary attempts in finding if this
    substring is able to be assembled from the words in wordDict.

    This Algorithm causes TLE(Time Limit Exceeded). Now consider this:


    --- Memoization ---

    We can notice that we're doing a lot of unnecessary attepmts, thus we can
    try and remember some of the previous results so that we don't have to
    spend our precious time down the recursion we knew were going to fail.

    So what is the idea?

    Since we're only asked to return if it is possible or not that means
    we only need to say either "true" or "false".

    Therefore, we're going to make a vector of booleans called dp
    (Dynamic Programming).

    So how are we going to utilize this vector? We're going to change the way
    we're traversing the string s. We're going to try and go backwards.
    And any time we get that a certain word is able to be found in the wordDict
    we're going to say:
        If we found that the prefix of this word is possible to be assembled
        then the rest(meaning this word we've just found) is also possible
        to assemble thus the whole word is possible to be assembled => return
        "true"

    We're going to do that essentially for every letter in string s, thus that
    makes it O(n^2), but every time we do that, we're using a function
    "s.substr(index, i - index + 1) which is always going to be O(n), thus,
    the Time Complexity of the whole algorithm is:
        O(n^2 * n) => O(n^3)

    On the fist example, Algorithm works like this:

    String s = "leetcode"
    wordDict["leet", "code"];


    1.
        'e' // start: 7
    i = 7   "e"

    2.
        'd' // start: 6
    i = 6   "d"
    i = 7   "de"

    3.
        'o' // start: 5
    i = 5   "o"
    i = 6   "od"
    i = 7   "ode"

    4.
        'c' //start: 4       start --------
    i = 4   "c"                           |
    i = 5   "co"                          |
    i = 6   "cod"                         v
    i = 7   "code" && dp[8] == true => dp[4] = true
                         ^
                         |
        i + 1 ------------


    5. 't' // start: 3
    i = 3   "t"
    i = 4   "tc"
    i = 5   "tco"
    i = 6   "tcod"
    i = 7   "tcode"

    6. 'e' // start: 2
    i = 2   "e"
    i = 3   "et"
    i = 4   "etc"
    i = 5   "etco"
    i = 6   "etcod"
    i = 7   "etcode"

    7. 'e' // start: 1
    i = 1   "e"
    i = 2   "ee"
    i = 3   "eet"
    i = 4   "eetc"
    i = 5   "eetco"
    i = 6   "eetcod"
    i = 7   "eetcode"

    8. 'l' // start: 0       start --------
    i = 0   "l"                           |
    i = 1   "le"                          |
    i = 2   "lee"                         v
    i = 3   "leet" && dp[4] == true => dp[0] = true
                         ^
                         |
        i + 1 ------------

    9. Exit the for loop

    10. return dp[0]; // Which in this case is "true".


    dp of index 'i' tells us that the subproblem, string s starting from the
    index 'i', is able to be solved. That's why we're going backwards and that
    is why, at the very end, we're returning "dp[0]".



    TODO:
        1. BFS
        2. DFS + Trie

*/

/* Time  Beats: 64.74% */
/* Space Beats: 34.50% */

/*
    Time  Complexity: O(n^2 * n) => O(n^3)

*/
/*
    Space Complexity: O(n)
*/
class Solution_DP {
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.length() + 1, false);

        dp[s.length()] = true;

        for (int start = s.length() - 1; start >= 0; start--)
        {
            for (int i = start; i < s.length(); i++)
            {
                string current_substr = s.substr(start, i - start + 1);

                // if (dict.find(current_substr) != dict.end() && dp[start + current_substr.length()])
                if (dict.find(current_substr) != dict.end() && dp[i + 1])
                {
                    dp[start] = true;
                    break;
                }
            }
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Almost equivalent IDEA to the the one above. The only difference is that
    we're iterating through wordDict instead of every possible substring.

*/

/* Time  Beats:   100% */
/* Space Beats: 89.60% */

/*
    Time  Complexity: O(n * m * n) => O(n^2 * m)
    Where 'm' is the size of wordDict.

    I'm confused why is this faster if in the Description it says:
        *** Constraints ***
        1 <= s.length <= 300
        1 <= wordDict.length <= 1000

    Since wordDict.length is greater than s.length, i.e. m > n, then:
        O(n^3) should preffered over O(n^2 * m)
    although that is the exact opposite of what I find.
*/
/*
    Space Complexity: O(n)
*/
class Solution_DP_Neat {
public:
    bool wordBreak(string& s, vector<string> wordDict)
    {
        int n = s.length();
        int m = wordDict.size();

        vector<bool> dp(n + 1, false);
        dp[n] = true; // Empty String is always possible to make

        for (int i = n-1; i >= 0; i--)
        {
            for (int j = 0; j < m; j++)
            {
                int substr_len = wordDict[j].length();

                if (i + substr_len <= n
                    &&
                    s.substr(i, substr_len) == wordDict[j] // O(n)
                    &&
                    dp[i + substr_len] == true)
                {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A very unnatural Memoization. Bottom-Up DP feels much more natural.

*/

/* Time  Beats: 48.93% */
/* Space Beats: 36.66% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Memoization {
private:
    bool memo[301];
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        const int N = s.length();

        unordered_set<string> uset(wordDict.begin(), wordDict.end());

        /* Allocate on the Stack */
        memset(memo, false, sizeof(memo));
        memo[N] = true;

        for (int i = N-1; i >= 0; i--)
        {
            solve(i, s, uset, N);
        }

        return memo[0];
    }

private:
    void solve(int idx, string& s, unordered_set<string>& uset, const int& N)
    {
        if (idx == N)
            return;

        for (int j = idx; j < N; j++)
        {
            string substr = s.substr(idx, j - idx + 1);

            if (uset.count(substr) && memo[j+1])
            {
                memo[idx] = true;
                return;
            }
        }
    }
};
