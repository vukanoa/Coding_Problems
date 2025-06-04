/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================================
    3403) Find the Lexicographically Largest String From the Box I
    ==============================================================

    ============
    Description:
    ============

    You are given a string word, and an integer numFriends.

    Alice is organizing a game for her numFriends friends. There are multiple
    rounds in the game, where in each round:

    word is split into numFriends non-empty strings, such that no previous
    round has had the exact same split. All the split words are put into a box.

    Find the lexicographically largest string from the box after all the rounds
    are finished.

    A string a is lexicographically smaller than a string b if in the first
    position where a and b differ, string a has a letter that appears earlier
    in the alphabet than the corresponding letter in b. If the first
    min(a.length, b.length) characters do not differ, then the shorter string
    is the lexicographically smaller one.

    ===========================================================
    FUNCTION: string answerString(string word, int numFriends);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "dbca", numFriends = 2
    Output: "dbc"
    Explanation:
    All possible splits are:
        "d" and "bca".
        "db" and "ca".
        "dbc" and "a".


    --- Example 2 ---
    Input: word = "gggg", numFriends = 4
    Output: "g"
    Explanation:
    The only possible split is: "g", "g", "g", and "g".


    *** Constraints ***
    1 <= word.length <= 5 * 10^3
    word consists only of lowercase English letters.
    1 <= numFriends <= word.length

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    There's not much to "not know" here. Literally just code-up what you're
    told.

*/

/* Time  Beats: 7.58% */
/* Space Beats: 5.89% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    string answerString(string word, int numFriends)
    {
        if (numFriends == 1)
            return word;

        const int N = word.length();
        string result = "";

        int len = N - (numFriends - 1);
        if (N == numFriends)
            len = 1;

        for (int i = 0; i < N; i++)
        {
            string prev;
            prev.append(1, word[i]);

            string curr = prev;
            for (int j = i+1; j < N && j-i+1 <= len; j++)
                curr += word[j];

            if (result.compare(curr) < 0)
                result = curr;
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

/* Time  Beats: 100.00% */
/* Space Beats:  87.31% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Two_Pointers {
public:
    string answerString(string word, int numFriends)
    {
        if (numFriends == 1)
            return word;

        const int N = word.size();

        string last = last_substring(word);
        const int M = last.size();

        int len = min(M, N - numFriends + 1);

        return last.substr(0, len);
    }

private:
    string last_substring(string s)
    {
        const int N = s.size();

        int i = 0;
        int j = 1;
        while (j < N)
        {
            int k = 0;
            while (j + k < N && s[i + k] == s[j + k])
                k++;

            if (j + k < N && s[i + k] < s[j + k])
            {
                int tmp = i;
                i = j;
                j = max(j + 1, tmp + k + 1);
            }
            else
            {
                j = j + k + 1;
            }
        }

        return s.substr(i, N - i);
    }
};
