/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    2559) Count Vowel Strings in Ranges
    ===================================

    ============
    Description:
    ============

    You are given a 0-indexed array of strings words and a 2D array of integers
    queries.

    Each query queries[i] = [li, ri] asks us to find the number of strings
    present in the range li to ri (both inclusive) of words that start and end
    with a vowel.

    Return an array ans of size queries.length, where ans[i] is the answer to
    the ith query.

    =====
    Note: that the vowel letters are 'a', 'e', 'i', 'o', and 'u'.
    =====

    ========================================================================================
    FUNCTION: vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries);
    ========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
    Output: [2,3,0]
    Explanation: The strings starting and ending with a vowel are "aba", "ece", "aa" and "e".
    The answer to the query [0,2] is 2 (strings "aba" and "ece").
    to query [1,4] is 3 (strings "ece", "aa", "e").
    to query [1,1] is 0.
    We return [2,3,0].

    --- Example 2 ---
    Input: words = ["a","e","i"], queries = [[0,2],[0,1],[2,2]]
    Output: [3,2,1]
    Explanation: Every string satisfies the conditions, so we return [3,2,1].


    *** Constraints ***
    1 <= words.length <= 10^5
    1 <= words[i].length <= 40
    words[i] consists only of lowercase English letters.
    sum(words[i].length) <= 3 * 10^5
    1 <= queries.length <= 10^5
    0 <= li <= ri < words.length

*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only thing that is important here is to notice that you don't have to
    manually iterate over every range in "queries", instead you can
    pre-calculate the number of words that start and end with a vowel up to
    that point(inclusively).

    Once you have that figured out, you can simply use a standard, famous,
    prefixSum "trick":

        If you want to check how many words begin and end with a vowel between
        'x' and 'y', then here is the formula:

            prefix[y] - prefix[x - 1]

        That way you're ONLY consider the element within window [x, y],
        inclusively of course.

    If you didn't know this trick, it wouldn't be impossible to come up with
    this, but it's much easier if you've already seen. Now you know it.

*/

/* Time  Beats: 91.64% */
/* Space Beats: 70.64% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(M)     */
class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = words.size();
        const int M = queries.size();

        vector<int> answer(M, 0);

        vector<int> prefix(N, 0);
        prefix[0] = begins_and_ends_with_vowel(words[0]) ? 1 : 0;

        for (int i = 1; i < N; i++)
        {
            prefix[i] = prefix[i-1];

            if (begins_and_ends_with_vowel(words[i]))
            {
                prefix[i]++;
            }
        }

        for (int i = 0; i < M; i++)
        {
            const int& begin = queries[i][0];
            const int& end   = queries[i][1];

            answer[i] = prefix[end] - (begin-1 >= 0 ? prefix[begin-1] : 0);
        }

        return answer;
    }

private:
    bool begins_and_ends_with_vowel(const string& str)
    {
        int len = str.length();

        if (len == 1 && (str[0] == 'a' ||
                         str[0] == 'e' ||
                         str[0] == 'i' ||
                         str[0] == 'o' ||
                         str[0] == 'u'))
        {
            return true;
        }

        if ((str[0] == 'a' ||
             str[0] == 'e' ||
             str[0] == 'i' ||
             str[0] == 'o' ||
             str[0] == 'u')
                &&
            (str.back() == 'a' ||
             str.back() == 'e' ||
             str.back() == 'i' ||
             str.back() == 'o' ||
             str.back() == 'u'))
        {
            return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, though this one is implemented using HashSet and is more
    concise. It's not bad to see both Solutions if you chose C++ to solve these
    problems.

*/

/* Time  Beats: 81.49% */
/* Space Beats: 70.64% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(M)     */
class Solution_Set {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = words.size();
        const int M = queries.size();
        vector<int> answer(M, 0);

        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        vector<int> prefix(N, 0);
        prefix[0] = vowels.count(words[0][0]) && vowels.count(words[0][words[0].length() - 1]);

        for (int i = 1; i < N; i++)
        {
            prefix[i] = prefix[i-1];

            int last_letter  = words[i].length() - 1;
            if (vowels.count(words[i][0]) && vowels.count(words[i][last_letter]))
            {
                prefix[i]++;
            }
        }

        for (int i = 0; i < M; i++)
        {
            const int& begin = queries[i][0];
            const int& end   = queries[i][1];

            answer[i] = prefix[end] - (begin-1 >= 0 ? prefix[begin-1] : 0);
        }

        return answer;
    }
};
