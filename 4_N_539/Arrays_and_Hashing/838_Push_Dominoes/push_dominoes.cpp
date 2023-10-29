#include <iostream>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    838) Push Dominoes
    ===========================

    ============
    Description:
    ============

    There are n dominoes in a line, and we place each domino vertically
    upright. In the beginning, we simultaneously push some of the dominoes
    either to the left or to the right.

    After each second, each domino that is falling to the left pushes the
    adjacent domino on the left. Similarly, the dominoes falling to the right
    push their adjacent dominoes standing on the right.

    When a vertical domino has dominoes falling on it from both sides, it stays
    still due to the balance of the forces.

    For the purposes of this question, we will consider that a falling domino
    expends no additional force to a falling or already fallen domino.

    You are given a string dominoes representing the initial state where:

        dominoes[i] = 'L', if the ith domino has been pushed to the left,
        dominoes[i] = 'R', if the ith domino has been pushed to the right, and
        dominoes[i] = '.', if the ith domino has not been pushed.

    Return a string representing the final state.

    ===============================================
    FUNCTION: string pushDominoes(string dominoes);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: dominoes = "RR.L"
    Output: "RR.L"
    Explanation: The first domino expends no additional force on the second
                 domino.


    --- Example 2 ---
    Input: dominoes = ".L.R...LR..L.."
    Output: "LL.RR.LLRRLL.."


    *** Constraints ***
    n == dominoes.length
    1 <= n <= 105
    dominoes[i] is either 'L', 'R', or '.'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.68% */
/* Space Beats: 64.11% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::string pushDominoes(std::string dominoes)
    {
        std::queue<int> queue;

        for (int i = 0; i < dominoes.length(); i++)
        {
            if (dominoes[i] != '.')
                queue.push(i);
        }

        while (!queue.empty())
        {
            int size = queue.size();

            for (int i = 0; i < size; i++)
            {
                int index = queue.front();
                queue.pop();

                if (dominoes[index] == 'L' && index > 0 && dominoes[index-1] == '.')
                {
                    dominoes[index-1] = 'L';
                    queue.push(index-1);
                }
                else if (dominoes[index] == 'R' && index+1 < dominoes.length() && dominoes[index+1] == '.')
                {
                    if ((index+2 == dominoes.length()) || (index+2 < dominoes.length() && dominoes[index+2] != 'L'))
                    {
                        dominoes[index+1] = 'R';
                        queue.push(index+1);
                    }
                    else
                    {
                        queue.pop();
                        i++;
                    }
                }
            }
        }

        return dominoes;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.02% */
/* Space Beats: 90.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
    std::string pushDominoes(std::string dominoes)
    {
        int right = -1;

        for (int i = 0; i < dominoes.size(); ++i)
        {
            if (dominoes[i] == 'L')
            {
                if (right == -1)
                {
                    for (int j = i - 1; j >= 0 && dominoes[j] == '.'; --j)
                      dominoes[j] = 'L';
                }
                else
                {
                    for (int j = right + 1, k = i - 1; j < k; ++j, --k)
                    {
                        dominoes[j] = 'R';
                        dominoes[k] = 'L';
                    }
                    right = -1;
                }
            }
            else if (dominoes[i] == 'R')
            {
                if (right != -1)
                {
                    for (int j = right + 1; j < i; ++j)
                        dominoes[j] = 'R';
                }
                right = i;
            }
        }

        if (right != -1)
        {
            for (int j = right + 1; j < dominoes.size(); ++j)
                dominoes[j] = 'R';
        }

        return dominoes;
    }
};
