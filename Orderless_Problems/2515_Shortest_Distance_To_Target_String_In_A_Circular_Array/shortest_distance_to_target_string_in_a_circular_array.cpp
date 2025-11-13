/*
    ============
    === EASY ===
    ============

    ============================================================
    2515) Shortest Distance to Target String in a Circular Array
    ============================================================

    ============
    Description:
    ============

    You are given a 0-indexed circular string array words and a string target.
    A circular array means that the array's end connects to the array's
    beginning.

        + Formally, the next element of words[i] is words[(i + 1) % n] and the
          previous element of words[i] is words[(i - 1 + n) % n], where n is
          the length of words.

    Starting from startIndex, you can move to either the next word or the
    previous word with 1 step at a time.

    Return the shortest distance needed to reach the string target. If the
    string target does not exist in words, return -1.

    ==================================================================================
    FUNCTION: int closestTarget(vector<string>& words, string target, int startIndex);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["hello","i","am","leetcode","hello"], target = "hello", startIndex = 1
    Output: 1
    Explanation: We start from index 1 and can reach "hello" by
    - moving 3 units to the right to reach index 4.
    - moving 2 units to the left to reach index 4.
    - moving 4 units to the right to reach index 0.
    - moving 1 unit to the left to reach index 0.
    The shortest distance to reach "hello" is 1.

    --- Example 2 ---
    Input: words = ["a","b","leetcode"], target = "leetcode", startIndex = 0
    Output: 1
    Explanation: We start from index 0 and can reach "leetcode" by
    - moving 2 units to the right to reach index 3.
    - moving 1 unit to the left to reach index 3.
    The shortest distance to reach "leetcode" is 1.

    --- Example 3 ---
    Input: words = ["i","eat","leetcode"], target = "ate", startIndex = 0
    Output: -1
    Explanation: Since "ate" does not exist in words, we return -1.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] and target consist of only lowercase English letters.
    0 <= startIndex < words.length

*/

#include <climits>
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
/* Space Beats:  33.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex)
    {
        const int N = words.size();

        if (words[startIndex] == target)
            return 0;

        int L_dist = 1;
        int R_dist = 1;

        int L = ((startIndex - 1) + N) % N;
        int R =  (startIndex + 1)      % N;

        while (true)
        {
            if (words[L] == target)
                return L_dist;

            if (words[R] == target)
                return R_dist;

            if (L == R) // If they're at the same index and we' still haven't
                break;  // found "target", then break and return -1.

            L_dist++;
            R_dist++;

            L = ((L - 1) + N) % N;
            R =  (R + 1)      % N;
        }


        return -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  66.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Clean_One_Pass {
public:
    int closestTarget(vector<string>& words, string target, int startIndex)
    {
        const int N = words.size();
        int result = INT_MAX;

        for (int i = 0; i < N; i++)
        {
            if (target == words[i])
            {
                int absolute_distance = abs(i - startIndex);

                result = min(result, absolute_distance);
                result = min(result, N - absolute_distance);
            }
        }

        return result == INT_MAX ? -1 : result;
    }
};
