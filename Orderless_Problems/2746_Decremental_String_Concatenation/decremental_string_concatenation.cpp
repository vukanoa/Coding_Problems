/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2746) Decremental String Concatenation
    ======================================

    ============
    Description:
    ============

    You are given a 0-indexed array words containing n strings.

    Let's define a join operation join(x, y) between two strings x and y as
    concatenating them into xy. However, if the last character of x is equal
    to the first character of y, one of them is deleted.

    For example join("ab", "ba") = "aba" and join("ab", "cde") = "abcde".

    You are to perform n - 1 join operations. Let str0 = words[0]. Starting
    from i = 1 up to i = n - 1, for the ith operation, you can do one of the
    following:

        + Make stri = join(stri - 1, words[i])
        + Make stri = join(words[i], stri - 1)

    Your task is to minimize the length of strn - 1.

    Return an integer denoting the minimum possible length of strn - 1.

    ================================================================
    FUNCTION: int minimizeConcatenatedLength(vector<string>& words);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["aa","ab","bc"]
    Output: 4
    Explanation: In this example, we can perform join operations in the
    following order to minimize the length of str2: 
    str0 = "aa"
    str1 = join(str0, "ab") = "aab"
    str2 = join(str1, "bc") = "aabc" 
    It can be shown that the minimum possible length of str2 is 4.

    --- Example 2 ---
    Input: words = ["ab","b"]
    Output: 2
    Explanation: In this example, str0 = "ab", there are two ways to get str1: 
    join(str0, "b") = "ab" or join("b", str0) = "bab". 
    The first string, "ab", has the minimum length. Hence, the answer is 2.

    --- Example 3 ---
    Input: words = ["aaa","c","aba"]
    Output: 6
    Explanation: In this example, we can perform join operations in the
    following order to minimize the length of str2: 
    str0 = "aaa"
    str1 = join(str0, "c") = "aaac"
    str2 = join("aba", str1) = "abaaac"
    It can be shown that the minimum possible length of str2 is 6.


    *** Constraints ***
    1 <= words.length <= 1000
    1 <= words[i].length <= 50
    Each character in words[i] is an English lowercase letter

*/

#include <vector>
#include <string>
#include <cstring>
#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classical Memoization Problem.

*/

/* Time  Beats: 60.63% */
/* Space Beats: 66.25% */

/* Time  Complexity: O(26 * 26 * N) --> O(N) */ 
/* Space Complexity: O(26 * 26 * N) --> O(N) */
class Solution {
private:
    int memo[26][26][1001];

public:
    int minimizeConcatenatedLength(vector<string>& words)
    {
        const int N = words.size();

        memset(memo, 0x3f, sizeof(memo));

        return words[0].length() + solve(words[0][0] - 'a', words[0].back() - 'a', 1, words);
    }

private:

    int solve(int start_chr, int end_chr, int idx, vector<string>& words)
    {
        const int N = words.size();

        if (idx >= N)
            return 0;

        if (memo[start_chr][end_chr][idx] != 0x3f3f3f3f)
            return memo[start_chr][end_chr][idx];

        int normal_concat  = INT_MAX;
        int swapped_concat = INT_MAX;

        if (end_chr == (words[idx][0] - 'a'))
            normal_concat = -1 + words[idx].length() + solve(start_chr, words[idx].back() - 'a', idx + 1, words);
        else
            normal_concat =  0 + words[idx].length() + solve(start_chr, words[idx].back() - 'a', idx + 1, words);


        if ((words[idx].back() - 'a') == start_chr)
            swapped_concat = -1 + words[idx].length() + solve(words[idx][0] - 'a', end_chr, idx + 1, words);
        else
            swapped_concat =  0 + words[idx].length() + solve(words[idx][0] - 'a', end_chr, idx + 1, words);

        return memo[start_chr][end_chr][idx] = min(normal_concat, swapped_concat);
    }
};
