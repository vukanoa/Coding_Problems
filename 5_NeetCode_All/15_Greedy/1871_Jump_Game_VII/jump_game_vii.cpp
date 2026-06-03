/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1871) Jump Game VII
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed binary string s and two integers minJump and
    maxJump. In the beginning, you are standing at index 0, which is equal to
    '0'. You can move from index i to index j if the following conditions are
    fulfilled:

        i + minJump <= j <= min(i + maxJump, s.length - 1), and
        s[j] == '0'.

    Return true if you can reach index s.length - 1 in s, or false otherwise.

    ============================================================
    FUNCTION: bool canReach(string s, int minJump, int maxJump);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "011010", minJump = 2, maxJump = 3
    Output: true
    Explanation:
    In the first step, move from index 0 to index 3.
    In the second step, move from index 3 to index 5.

    --- Example 2 ---
    Input: s = "01101110", minJump = 2, maxJump = 3
    Output: false


    *** Constraints ***
    2 <= s.length <= 10^5
    s[i] is either '0' or '1'.
    s[0] == '0'
    1 <= minJump <= maxJump < s.length

*/

#include <bits/stdc++.h>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.57% */
/* Space Beats: 57.30% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS_Greedy {
public:
    bool canReach(string s, int minJump, int maxJump)
    {
        const int N = s.size();

        if (s.back() != '0')
            return false;

        queue<int> queue;
        queue.push(0);

        int farthest = 0;
        while ( ! queue.empty())
        {
            int idx = queue.front();
            queue.pop();

            int start = max(idx + minJump, farthest + 1);
            int end   = min(idx + maxJump, N-1);

            for (int j = start; j <= end; j++)
            {
                if (s[j] == '1')
                    continue;

                if (j == N-1)
                    return true;

                queue.push(j);
            }

            farthest = idx + maxJump;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.50% */
/* Space Beats: 86.15% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Sweep_Line {
private:
    static constexpr int MAX_SIZE = 1e5;

public:
    bool canReach(string s, int minJump, int maxJump)
    {
        const int N = s.size();

        if (s.back() != '0')
            return false;

        int sweep_line[MAX_SIZE + 1] = {0};

        // In the Constraints it's guaranteed: 1 <= minJumps <= maxJumps < N
        // Marking reachability of starting jump
        ++sweep_line[0 + minJump];
        --sweep_line[0 + maxJump + 1];

        int tokens = 0;
        for (int i = 1; i < N; i++)
        {
            tokens += sweep_line[i];

            if (tokens == 0 || s[i] == '1')
                continue;

            if (i + minJump < N)
                ++sweep_line[i + minJump];

            if (i + maxJump + 1 < N)
                --sweep_line[i + maxJump + 1];
        }

        return tokens > 0;
    }
};
