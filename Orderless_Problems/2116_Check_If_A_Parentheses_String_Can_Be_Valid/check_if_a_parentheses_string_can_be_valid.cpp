/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    2116) Check if a Parentheses String Can Be Valid
    ================================================

    ============
    Description:
    ============

    A parentheses string is a non-empty string consisting only of '(' and ')'.
    It is valid if any of the following conditions is true:

        + It is ().

        + It can be written as AB (A concatenated with B), where A and B are
          valid parentheses strings.

        + It can be written as (A), where A is a valid parentheses string.

    You are given a parentheses string s and a string locked, both of length n.
    locked is a binary string consisting only of '0's and '1's. For each index
    i of locked,

        + If locked[i] is '1', you cannot change s[i].

        + But if locked[i] is '0', you can change s[i] to either '(' or ')'.

    Return true if you can make s a valid parentheses string. Otherwise, return
    false.

    ===================================================
    FUNCTION: bool canBeValid(string s, string locked);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "))()))", locked = "010100"
    Output: true
    Explanation: locked[1] == '1' and locked[3] == '1', so we cannot change s[1] or s[3].
    We change s[0] and s[4] to '(' while leaving s[2] and s[5] unchanged to make s valid.

    --- Example 2 ---
    Input: s = "()()", locked = "0000"
    Output: true
    Explanation: We do not need to make any changes because s is already valid.

    --- Example 3 ---
    Input: s = ")", locked = "0"
    Output: false
    Explanation: locked permits us to change s[0].
    Changing s[0] to either '(' or ')' will not make s valid.


    *** Constraints ***
    n == s.length == locked.length
    1 <= n <= 10^5
    s[i] is either '(' or ')'.
    locked[i] is either '0' or '1'.

*/

#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 81.22% */
/* Space Beats: 16.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool canBeValid(string s, string lockedStatus)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int N = s.size();

        if (N % 2 == 1)
            return false;

        stack<int> open_indices;
        stack<int> unlocked_indices;

        for (int i = 0; i < N; i++)
        {
            if (lockedStatus[i] == '0')
            {
                unlocked_indices.push(i);
            }
            else if (s[i] == '(')
            {
                open_indices.push(i);
            }
            else if (s[i] == ')')
            {
                if ( ! open_indices.empty())
                {
                    open_indices.pop();
                }
                else if ( ! unlocked_indices.empty())
                {
                    unlocked_indices.pop();
                }
                else
                    return false;
            }
        }

        while ( ! open_indices.empty() && ! unlocked_indices.empty() && open_indices.top() < unlocked_indices.top())
        {
            open_indices.pop();
            unlocked_indices.pop();
        }

        if (open_indices.empty() && ! unlocked_indices.empty())
            return unlocked_indices.size() % 2 == 0;

        return open_indices.empty();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.52% */
/* Space Beats:  8.88% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    bool canBeValid(string s, string locked)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = s.length();

        if (N & 1)
            return false;

        if (s[0] == ')' && locked[0] == '1')
            return false;

        if (s[N-1] == '(' && locked[N-1] == '1')
            return false;



        // Forward
        vector<int> forward (N, 0);
        int open = 0;;

        if (s[0] == '(')
            open++;
        else if (locked[0] == '0')
            forward[0]++;

        for (int i = 1; i < N; i++)
        {
            forward[i] = forward[i-1];

            if (s[i] == '(')
                open++;
            else if (locked[i] == '0')
                forward[i]++;

            if (locked[i] == '1' && s[i] == ')')
            {
                if (open + forward[i] < static_cast<int>(ceil(1.0 * (i+1) / 2)))
                    return false;
            }
        }

        // Backward
        vector<int> backward(N, 0);
        int closed = 0;

        if (s[N-1] == ')')
            closed++;
        else if (locked[N-1] == '0')
            backward[N-1]++;

        for (int i = N-2; i >= 0; i--)
        {
            backward[i] = backward[i+1];

            if (s[i] == ')')
                closed++;
            else if (locked[i] == '0')
                backward[i]++;

            if (locked[i] == '1' && s[i] == '(')
            {
                if (closed + backward[i] < static_cast<int>(ceil(1.0 * (N-i) / 2)))
                    return false;
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This is just Space Optimization of the above Solution)`

*/

/* Time  Beats: 90.61% */
/* Space Beats: 34.26% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    bool canBeValid(string s, string locked)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int N = s.length();

        if (N % 2 != 0)
            return false; // Odd length cannot form valid parentheses

        if (s[0]   == ')' && locked[0]   == '1') return false;
        if (s[N-1] == '(' && locked[N-1] == '1') return false;


        // Left-to-right pass: Ensure there are enough open brackets
        int open_or_unlocked = 0;
        for (int i = 0; i < N; i++)
        {
            if (s[i] == '(' || locked[i] == '0')
            {
                open_or_unlocked++;
            }
            else // s[i] == ')' and locked[i] == '1'
            {
                open_or_unlocked--;
            }

            if (open_or_unlocked < 0)
                return false; // Too many locked ')' encountered
        }

        // Right-to-left pass: Ensure there are enough closing brackets
        int closed_or_unlocked = 0;
        for (int i = N - 1; i >= 0; i--)
        {
            if (s[i] == ')' || locked[i] == '0')
            {
                closed_or_unlocked++;
            }
            else // s[i] == '(' and locked[i] == '1'
            {
                closed_or_unlocked--;
            }

            if (closed_or_unlocked < 0)
                return false; // Too many locked '(' encountered
        }

        return true;
    }
};
