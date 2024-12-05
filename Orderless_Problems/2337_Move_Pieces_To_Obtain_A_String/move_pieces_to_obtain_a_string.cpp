#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    2337) Move Pieces to Obrain a String
    ====================================

    ============
    Description:
    ============

    You are given two strings start and target, both of length n. Each string
    consists only of the characters 'L', 'R', and '_' where:

        + The characters 'L' and 'R' represent pieces, where a piece 'L' can
          move to the left only if there is a blank space directly to its left,
          and a piece 'R' can move to the right only if there is a blank space
          directly to its right.

        + The character '_' represents a blank space that can be occupied by
          any of the 'L' or 'R' pieces.

    Return true if it is possible to obtain the string target by moving the
    pieces of the string start any number of times. Otherwise, return false.

    ===============================
    FUNCTION: bool canChange(string start, string target);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: start = "_L__R__R_", target = "L______RR"
    Output: true
    Explanation: We can obtain the string target from start by doing the following moves:
    - Move the first piece one step to the left, start becomes equal to "L___R__R_".
    - Move the last piece one step to the right, start becomes equal to "L___R___R".
    - Move the second piece three steps to the right, start becomes equal to "L______RR".
    Since it is possible to get the string target from start, we return true.

    --- Example 2 ---
    Input: start = "R_L_", target = "__LR"
    Output: false
    Explanation: The 'R' piece in the string start can move one step to the
    right to obtain "_RL_". After that, no pieces can move anymore, so it is
    impossible to obtain the string target from start.

    --- Example 3 ---
    Input: start = "_R", target = "R_"
    Output: false
    Explanation: The piece in the string start can move only to the right, so
                 it is impossible to obtain the string target from start.


    *** Constraints ***
    n == start.length == target.length
    1 <= n <= 10^5
    start and target consist of the characters 'L', 'R', and '_'.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We don't care about Blank '_' characters. We only care about Ls and Rs.
    Thus, create a vector with Ls and Rs for both strings separately, but it
    needs to be in the same relative order.

    Exapmle:
        start = "L___R_R_L__R"  -->  start_order{L, R, R, L, R}

    However, we can't only have a vector of characters since we need to check
    if we can move them according to target order. Thus, we also must keep a
    index of that character(L or R) in the start and target order.

    Why?

    Let's consider the very first example:

        Input: start = "_L__R__R_", target = "L______RR"
                        012345678             012345678
        Output: true

        We'll convert start string to start_order:

            start_order  = {{L,1}, {R,4}, {R,7}}
            target_order = {{L,0}, {R,7}, {R,8}}


    Now all we have to do is check three things:

        1. If the relative order of CHARACTERS(i.e. Ls and Rs) is THE SAME in
           start_order and in target_order, because 'L' and never "jump over"
           'R' and vice-versa.

        2. Check if current 'L' from the start_order can be moved TO THE LEFT
           to match the position of that same 'L' in target_order.

        3. Check if current 'R' from the start_order can be moved TO THE RIGHT
           to match the position of that same 'R' in target_order.


    1st thing is obvious already explained. Ls and Rs cannot change their
    respective relative order. They cannot jump over each other.

    If we have this:
        start = "___L_____R____"   -->    start_order:{L, R}

        'L' can NEVER "jump over" 'R' to becomes like this: {R, L}.
        That is absolutely FORBIDDEN.

        Therefore if current character from start_order is NOT the same as
        current character in target_order, we immediately return true. We know
        it's IMPOSSIBLE to obtain given target string.


    2nd thing is if we we find two current characters from start_order and
    target_order to both be 'L', then we have to check if 'L's index in the
    start string is GREATER THAN OR EQUAL to 'L's position in target string.

        Why?
        Because 'L' from start string can ONLY BE MOVED TO THE LEFT(!!!).

        Consider this:
            start = "L___",  target = "___L"
                     0123              0123

        How are you EVER going to move 'L' in stirng start from index 0 to
        index 3?

        It's IMPOSSIBLE!

        We can EITHER leave it at the same index OR move it to the left as many
        times as we want.

        So if index of 'L' in start string is LESS THAN index of 'L' in the
        target string - We immediately return FALSE. It is IMPOSSIBLE to obrain
        given target string.


    3rd thing is "the photo negative" of the 2nd thing up above. 'R' can ONLY
    be moved to the right. Therefore, if we find a 'R' character in string
    start to already be GREATER THAN 'R' character in string target, we
    immediately return FALSE.

    Example 3 designates such case:

        Input: start = "_R", target = "R_"
        Output: false
        Explanation: The piece in the string start can move only to the right,
                     so it is impossible to obtain the string target from start

*/

/* Time  Beats: 16.67% */
/* Space Beats:  5.40% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool canChange(string start, string target)
    {
        const int n = start.length();

        vector<pair<char, int>> start_order;
        vector<pair<char, int>> target_order;

        for (int i = 0; i < n; i++)
        {
            if (start[i] != '_')
                start_order.push_back( {start[i], i} );

            if (target[i] != '_')
                target_order.push_back( {target[i], i} );
        }

        // Check if there are differents amounts of Ls and Rs on one and on the other side.
        if (start_order.size() != target_order.size())
            return false;

        for (int i = 0; i < start_order.size(); i++)
        {
            if (start_order[i].first != target_order[i].first) // Check relative order
                return false;

            // If 'L' on the start side is on lower index than 'L' on the
            // target side - Then it's impossible to change that since we're
            // allowed to move 'L' from start side ONLY even more to the left
            if (start_order[i].first == 'L' && start_order[i].second < target_order[i].second)
                return false;

            // If 'R' on the start side is on higher index than 'R' on the
            // target side - Then it's impossible to change that since we're
            // allowed to move 'R' from start side ONLY even more to the right
            if (start_order[i].first == 'R' && start_order[i].second > target_order[i].second)
                return false;
        }

        return true;
    }
};
