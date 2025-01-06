/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    1769) Minimum Number of Operations to Move Each Ball
    ====================================================

    ============
    Description:
    ============

    You have n boxes. You are given a binary string boxes of length n, where
    boxes[i] is '0' if the ith box is empty, and '1' if it contains one ball.

    In one operation, you can move one ball from a box to an adjacent box. Box
    i is adjacent to box j if abs(i - j) == 1. Note that after doing so, there
    may be more than one ball in some boxes.

    Return an array answer of size n, where answer[i] is the minimum number of
    operations needed to move all the balls to the ith box.

    Each answer[i] is calculated considering the initial state of the boxes.

    ==================================================
    FUNCTION: vector<int> minOperations(string boxes);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: boxes = "110"
    Output: [1,1,3]
    Explanation: The answer for each box is as follows:
    1) First box: you will have to move one ball from the second box to the first box in one operation.
    2) Second box: you will have to move one ball from the first box to the second box in one operation.
    3) Third box: you will have to move one ball from the first box to the third box in two operations,
       and move one ball from the second box to the third box in one operation.


    --- Example 2 ---
    Input: boxes = "001011"
    Output: [11,8,5,4,3,4]

    *** Constraints ***
    n == boxes.length
    1 <= n <= 2000
    boxes[i] is either '0' or '1'.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The idea is fairly simple, but you need to be careful when implementing.

    Let me ask you a question, if we know that the number of moves to get all
    of the 1s, on the right side of current index 0, is 19, how many is needed
    for index 1?


        0  0  1  0  1  1  0  0  1
        0  1  2  3  4  5  6  7  8
        ^
        |
     We need 19 moves to get every zero from the right, to this box.

     How many, do you think, we need, at index 1? (forget about the left side
     for now)

     We need:
        19(i.e. previous result) - ones_to_the_right

     because now every '1' needs to "travel" one position less than before.
     The amount of 1s to the right of the current possition, EXCLUDING the 1
     at the current position(if there is '1').

     One important thing as well--If we're at some position X and at that
     position there is 1-bit, then we--FIRST--need to subtract 1 from the
     'ones_to_the_right", since now there is one less than at position before.

     We're going to store the number of needed moves, to vector from_R of size
     N, where for each index we'll have how many moves we'd need to move all
     the 1s from right to this very position.


     That would be a Solution if we were only asked to moves 1s from
     right-to-left, however since that is not the case, we need to do similar
     thing by counting moves of 1s from left-to-right.


     However, since we're asked to move 1s from both left and right, we need
     to use "from_L" vector of size N, where at each position of i, we'll
     pre-calculate how many moves of 1s we need so that all the 1s end up in
     this very position.

     We do that in a similar way, however this time we're going from
     left-to-right so it's a bit easier to grasp.

     It is probably better to look at the Solution_2, since it is a bit easier
     to understand, however this one utilizes two different methods, for
     didactic purposes.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  24.96% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<int> minOperations(string boxes)
    {
        const int N = boxes.length();
        vector<int> answer(N, 0);

        int ones_to_the_left  = 0;
        int ones_to_the_right = 0;

        vector<int> from_L(N, 0);
        ones_to_the_left = boxes[0] == '1' ? 1 : 0;

        for (int i = 1; i < N; i++)
        {
            from_L[i] = from_L[i-1] + ones_to_the_left;
            ones_to_the_left += boxes[i] == '1' ? 1 : 0;
        }

        vector<int> from_R(N, 0);
        for (int i = 1; i < N; i++)
        {
            if (boxes[i] == '1')
            {
                from_R[0] += i;
                ones_to_the_right++;
            }
        }

        for (int i = 1; i < N; i++)
        {
            if (boxes[i] == '1')
            {
                ones_to_the_right--;
                from_R[i]--;
            }

            from_R[i] += from_R[i-1] - ones_to_the_right;
        }

        for (int i = 0; i < N; i++)
            answer[i] = from_L[i] + from_R[i];

        return answer;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is much easier to grasp, but essentially same IDEA as above.

*/

/* Time  Beats: 66.27% */
/* Space Beats: 15.16% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    vector<int> minOperations(string boxes)
    {
        const int N = boxes.length();
        vector<int> answer(N, 0);

        int ones_to_the_left  = 0;

        /* From Left-To-Right */
        vector<int> from_L(N, 0);
        ones_to_the_left = boxes[0] == '1' ? 1 : 0;

        for (int i = 1; i < N; i++)
        {
            from_L[i] = from_L[i-1] + ones_to_the_left;
            ones_to_the_left += boxes[i] == '1' ? 1 : 0;
        }

        /* From Right-To-Left */
        int ones_to_the_right = 0;
        vector<int> from_R(N, 0);
        ones_to_the_right = boxes[N-1] == '1' ? 1 : 0;

        for (int i = N-2; i >= 0; i--)
        {
            from_R[i] = from_R[i+1] + ones_to_the_right;
            ones_to_the_right += boxes[i] == '1' ? 1 : 0;
        }

        /* Final */
        for (int i = 0; i < N; i++)
            answer[i] = from_L[i] + from_R[i];

        return answer;
    }
};
