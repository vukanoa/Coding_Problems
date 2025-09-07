/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3675) Minimum Operations to Transform String
    ============================================

    ============
    Description:
    ============

    You are given a string s consisting only of lowercase English letters.

    You can perform the following operation any number of times(including zero)

        + Choose any character c in the string and replace every occurrence of
          c with the next lowercase letter in the English alphabet.

    Return the minimum number of operations required to transform s into a
    string consisting of only 'a' characters.

    =====
    Note: Consider the alphabet as circular, thus 'a' comes after 'z'.
    =====

    ======================================
    FUNCTION: int minOperations(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "yz"
    Output: 2
    Explanation:
        Change 'y' to 'z' to get "zz".
        Change 'z' to 'a' to get "aa".
        Thus, the answer is 2.


    --- Example 2 ---
    Input: s = "a"
    Output: 0
    Explanation:
        The string "a" only consists of 'a' characters. Thus, the answer is 0.


    *** Constraints ***
    1 <= s.length <= 5 * 10^5
    s consists only of lowercase English letters.

*/

#include <queue>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    All we need to know is find the lexicographically LOWEST character, that is
    NOT 'a', in string s.

    Once we do that, we simply
        return 26 - (that_char - 'a')

    However, had ALL the characters in string s been 'a', then we return 0,
    since we don't have to transform anything.


    (Obviously we could've done this WITHOUT using priority_queue. It was just
     easiest to implement during a contest, and I knew it could pass because of
     the constraints)

*/

/* Time  Beats: 36.84% */
/* Space Beats:     -% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Priority_Queue {
public:
    int minOperations(string s)
    {
        const int N = s.length();
        int result = 0;

        priority_queue<int, vector<int>, greater<int>> min_heap;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == 'a')
                continue;

            min_heap.push(s[i] - 'a');
        }

        if (min_heap.empty())
            return 0;

        return 26 - min_heap.top();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea as above, but instead of using a priority_queue, we just keep
    track of the lowest non-a character in string s.

    If we have NOT found any non-a character in string s, i.e. our "chr"
    variable is '{"(open brace, character after lowercase 'z' in ASCII), then
    we return 0;

    Otherwise return how many changes would that lowest non-a character require

*/

/* Time  Beats: 47.37% */
/* Space Beats: 52.63% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int minOperations(string s)
    {
        const int N = s.length();
        int result = 0;

        char chr = '{'; // (open-brace) Character after lowercase 'z' in ASCII

        for (int i = 0; i < N; i++)
        {
            if (s[i] == 'a')
                continue;

            chr = min(chr, s[i]);
        }

        if (chr == '{')
            return 0;

        return 26 - (chr - 'a');
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
    int minOperations(string s)
    {
        int result = 0;
        for (const char& chr : s)
        {
            result = max(result, ('a' + 26 - chr) % 26);

            // Could also be written like this: (whichever is easier)
            // result = max(result, 26 - (chr - 'a'));
        }

        return result;
    }
};
