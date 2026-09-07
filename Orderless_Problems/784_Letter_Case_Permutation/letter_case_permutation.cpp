/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    784) Letter Case Permutation
    ============================

    ============
    Description:
    ============

    Given a string s, you can transform every letter individually to be
    lowercase or uppercase to create another string.

    Return a list of all possible strings we could create. Return the output in
    any order.

    =========================================================
    FUNCTION: vector<string> letterCasePermutation(string s);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "a1b2"
    Output: ["a1b2","a1B2","A1b2","A1B2"]

    --- Example 2 ---
    Input: s = "3z4"
    Output: ["3z4","3Z4"]


    *** Constraints ***
    1 <= s.length <= 12
    s consists of lowercase English letters, uppercase English letters, and
    digits.

*/

#include <queue>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  63.30% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution_BFS {
public:
    vector<string> letterCasePermutation(string S)
    {
        if (S.empty())
            return {};

        const int N = S.size();

        queue<string> queue;
        queue.push(S);

        for (int i = 0; i < N; i++)
        {
            if (isdigit(S[i]))
                continue;

            int level_size = queue.size();

            for (int j = 0; j < level_size; j++)
            {
                string node = queue.front();
                queue.pop();

                node[i] = toupper(node[i]);
                queue.push(node);

                node[i] = tolower(node[i]);
                queue.push(node);
            }
        }

        vector<string> result;
        while ( ! queue.empty())
        {
            result.push_back(queue.front());
            queue.pop();
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

/* Time  Beats: 20.38% */
/* Space Beats: 36.11% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution_DFS_1 {
public:
    vector<string> letterCasePermutation(string s)
    {
        const int N = s.size();
        vector<string> result;

        dfs(0, "", s, result);

        return result;
    }

private:
    void dfs(int idx, string curr_str, const string& s, vector<string>& result)
    {
        const int N = s.size();

        if (idx == N)
        {
            result.push_back(curr_str);
            return;
        }

        if (isdigit(s[idx]))
        {
            dfs(idx + 1, curr_str + s[idx], s, result);
            return;
        }

        dfs(idx+1, curr_str + string(1, tolower(s[idx])), s, result);
        dfs(idx+1, curr_str + string(1, toupper(s[idx])), s, result);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but a bit more efficiently implemented.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  63.39% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution_DFS_2 {
public:
    vector<string> letterCasePermutation(string s)
    {
        const int N = s.size();
        vector<string> result;

        string curr_str;
        curr_str.reserve(N); // To prevent repeated reallocations

        dfs(0, curr_str, s, result);

        return result;
    }

private:
    void dfs(int idx, string& curr_str, const string& s, vector<string>& result)
    {
        const int N = s.size();

        if (idx == N)
        {
            result.push_back(curr_str);
            return;
        }

        if (isdigit(s[idx]))
        {
            curr_str.push_back(s[idx]);
            dfs(idx + 1, curr_str, s, result);
            curr_str.pop_back();

            return;
        }

        /* Lowercase */
        curr_str.push_back(tolower(s[idx]));
        dfs(idx + 1, curr_str, s, result);
        curr_str.pop_back();

        /* Uppercase */
        curr_str.push_back(toupper(s[idx]));
        dfs(idx + 1, curr_str, s, result);
        curr_str.pop_back();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but written in the MOST efficient way out of all 3 DFS
    Solutions.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.38% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N * 2^N) */
class Solution_DFS_3 {
public:
    vector<string> letterCasePermutation(string s)
    {
        if (s.empty())
            return {};

        vector<string> result;
        dfs(0, s, result);

        return result;
    }

    void dfs(int idx, string& s, vector<string>& result)
    {
        const int N = s.size();

        if (idx == N)
        {
            result.push_back(s);
            return;
        }

        if (isdigit(s[idx]))
        {
            dfs(idx+1, s, result);
            return;
        }

         char original_chr = s[idx]; // Save original character

        s[idx] = tolower(s[idx]);
        dfs(idx+1, s, result);

        s[idx] = toupper(s[idx]);
        dfs(idx+1, s, result);

        s[idx] = original_chr;      // Restore (optional but good practice)
    }
};
