/*
    ============
    === EASY ===
    ============

    =====================================
    821) Shortest Distance to a Character
    =====================================

    ============
    Description:
    ============

    Given a string s and a character c that occurs in s, return an array of
    integers answer where answer.length == s.length and answer[i] is the
    distance from index i to the closest occurrence of character c in s.

    The distance between two indices i and j is abs(i - j), where abs is the
    absolute value function.

    =======================================================
    FUNCTION: vector<int> shortestToChar(string s, char c);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "loveleetcode", c = "e"
    Output: [3,2,1,0,1,0,0,1,2,2,1,0]
    Explanation: The character 'e' appears at indices 3, 5, 6, and 11 (0-indexed).
    The closest occurrence of 'e' for index 0 is at index 3, so the distance is abs(0 - 3) = 3.
    The closest occurrence of 'e' for index 1 is at index 3, so the distance is abs(1 - 3) = 2.
    For index 4, there is a tie between the 'e' at index 3 and the 'e' at index 5, but the distance is still the same: abs(4 - 3) == abs(4 - 5) = 1.
    The closest occurrence of 'e' for index 8 is at index 6, so the distance is abs(8 - 6) = 2.

    --- Example 2 ---
    Input: s = "aaab", c = "b"
    Output: [3,2,1,0]


    *** Constraints ***
    1 <= s.length <= 10^4
    s[i] and c are lowercase English letters.
    It is guaranteed that c occurs at least once in s.

*/

#include <climits>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  26.88% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> shortestToChar(string s, char c)
    {
        const int N = s.length();

        if (N == 1)
            return {0}; // Since it is guaranteed that c is once in s

        vector<int> result(N, INT_MAX);

        vector<int> prefix(N, INT_MAX);
        vector<int> suffix(N, INT_MAX);


        prefix[0] = (s[0] == c) ? 0 : INT_MAX;
        for (int i = 1; i < N; i++)
        {
            if (s[i] == c)
                prefix[i] = 0;
            else
                prefix[i] = (prefix[i-1] == INT_MAX) ? INT_MAX : prefix[i-1] + 1;
        }

        suffix[N-1] = (s[N-1] == c) ? 0 : INT_MAX;
        for (int i = N-2; i >= 0; i--)
        {
            if (s[i] == c)
                suffix[i] = 0;
            else
                suffix[i] = (suffix[i + 1] == INT_MAX) ? INT_MAX : suffix[i+1] + 1;
        }

        for (int i = 0; i < N; i++)
        {
            result[i] = min(prefix[i], suffix[i]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A much more concise Solutoin.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.13% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */ // This one can be O(1) since result is not extra
class Solution_Concise {
public:
    vector<int> shortestToChar(string s, char c)
    {
        const int N = s.size();

        int distance_to_nearest_c = -N;
        vector<int> result(N, N);

        for (int i = 0; i < N; i++)
        {
            if (s[i] == c)
                distance_to_nearest_c = i;

            result[i] = i - distance_to_nearest_c;
        }

        for (int i = distance_to_nearest_c - 1; i >= 0; --i)
        {
            if (s[i] == c)
                distance_to_nearest_c = i;

            result[i] = min(result[i], distance_to_nearest_c - i);
        }

        return result;
    }
};
