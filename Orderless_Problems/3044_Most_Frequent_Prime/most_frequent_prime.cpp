/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3044) Most Frequent Prime
    ===========================

    ============
    Description:
    ============

    You are given a m x n 0-indexed 2D matrix mat. From every cell, you can
    create numbers in the following way:

        + There could be at most 8 paths from the cells namely: east,
          south-east, south, south-west, west, north-west, north, and
          north-east.

        + Select a path from them and append digits in this path to the number
          being formed by traveling in this direction.

        Note that numbers are generated at every step, for example, if the
        digits along the path are 1, 9, 1, then there will be three numbers
        generated along the way: 1, 19, 191.

    Return the most frequent

    greater than 10 out of all the numbers created by traversing the matrix or
    -1 if no such prime number exists. If there are multiple prime numbers with
    the highest frequency, then return the largest among them.

    =====
    Note: It is invalid to change the direction during the move.
    =====

    ==========================================================
    FUNCTION: int mostFrequentPrime(vector<vector<int>>& mat);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: mat = [[1,1],[9,9],[1,1]]
    Output: 19
    Explanation:
    From cell (0,0) there are 3 possible directions and the numbers greater than 10 which can be created in those directions are:
    East: [11], South-East: [19], South: [19,191].
    Numbers greater than 10 created from the cell (0,1) in all possible directions are: [19,191,19,11].
    Numbers greater than 10 created from the cell (1,0) in all possible directions are: [99,91,91,91,91].
    Numbers greater than 10 created from the cell (1,1) in all possible directions are: [91,91,99,91,91].
    Numbers greater than 10 created from the cell (2,0) in all possible directions are: [11,19,191,19].
    Numbers greater than 10 created from the cell (2,1) in all possible directions are: [11,19,19,191].
    The most frequent prime number among all the created numbers is 19.

    --- Example 2 ---
    Input: mat = [[7]]
    Output: -1
    Explanation: The only number which can be formed is 7. It is a prime number
                 however it is not greater than 10, so return -1.

    --- Example 3 ---
    Numbers greater than 10 created from the cell (0,0) in all possible directions are: [97,978,96,966,94,942].
    Numbers greater than 10 created from the cell (0,1) in all possible directions are: [78,75,76,768,74,79].
    Numbers greater than 10 created from the cell (0,2) in all possible directions are: [85,856,86,862,87,879].
    Numbers greater than 10 created from the cell (1,0) in all possible directions are: [46,465,48,42,49,47].
    Numbers greater than 10 created from the cell (1,1) in all possible directions are: [65,66,68,62,64,69,67,68].
    Numbers greater than 10 created from the cell (1,2) in all possible directions are: [56,58,56,564,57,58].
    Numbers greater than 10 created from the cell (2,0) in all possible directions are: [28,286,24,249,26,268].
    Numbers greater than 10 created from the cell (2,1) in all possible directions are: [86,82,84,86,867,85].
    Numbers greater than 10 created from the cell (2,2) in all possible directions are: [68,682,66,669,65,658].
    The most frequent prime number among all the created numbers is 97.


    *** Constraints ***
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 6
    1 <= mat[i][j] <= 9

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Once you generate primes for all (1e7 - 1) numbers, simply go through the
    matrix in all directions starting at every cell and count the frequencies
    of primes that are >10 and <MAX_NUM and at the end return the most frequent
    one.

*/

/* Time  Beats: 92.44% */
/* Space Beats: 50.42% */

/*
    Time  Complexity: O(M * N * 8 * k)  -->  O(M * N * K)

    Where 'K' is the max length along a direction (<= max(m, n))
*/
/*
    Space Complexity: O(MAX_NUM + U)

    Where 'U' is number of unique prime numbers found.
*/
static const int MAX_NUM = 1e7 - 1;
static vector<bool> prime_sieve;

struct SieveInit {

    SieveInit()
    {
        prime_sieve.assign(MAX_NUM + 1, true);
        prime_sieve[0] = prime_sieve[1] = false;

        for (int i = 2; i * i <= MAX_NUM; i++)
        {
            if ( ! prime_sieve[i])
                continue;

            for (int j = i * i; j <= MAX_NUM; j += i)
                prime_sieve[j] = false;
        }
    }
};

class Solution {
public:
    int mostFrequentPrime(vector<vector<int>>& mat)
    {
        const int ROWS = (int)mat.size();
        const int COLS = (int)mat[0].size();

        unordered_map<int,int> prime_freq;
        int max_freq = 0;
        int result   = -1;

        // Directions: 8 possible directions        E     S-E     S     S-W       W      N-W       N      N-E
        const vector<pair<int,int>> directions = {{0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}, {-1,1}};

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                for (auto [dx, dy] : directions)
                {
                    int num = 0;
                    int r = row;
                    int c = col;

                    while (r >= 0 && r < ROWS && c >= 0 && c < COLS)
                    {
                        num = num * 10 + mat[r][c];

                        if (num > 10 && num <= MAX_NUM && prime_sieve[num])
                        {
                            prime_freq[num]++;
                            int freq = prime_freq[num];

                            if (freq > max_freq)
                            {
                                max_freq = freq;
                                result = num;
                            }
                            else if (freq == max_freq && num > result)
                            {
                                result = num;
                            }
                        }

                        // Continue in current direction {dx, dy}
                        r += dx;
                        c += dy;
                    }
                }
            }
        }

        return result;
    }
};
