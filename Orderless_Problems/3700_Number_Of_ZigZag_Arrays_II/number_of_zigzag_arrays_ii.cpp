/*
    ============
    === HARD ===
    ============

    ================================
    3700) Number of ZigZag Arrays II
    ================================

    ============
    Description:
    ============

    You are given three integers n, l, and r.

    A ZigZag array of length n is defined as follows:

        + Each element lies in the range [l, r].

        + No two adjacent elements are equal.

        + No three consecutive elements form a strictly increasing or strictly
          decreasing sequence.

    Return the total number of valid ZigZag arrays.

    Since the answer may be large, return it modulo 109 + 7.

    A sequence is said to be strictly increasing if each element is strictly
    greater than its previous one (if exists).

    A sequence is said to be strictly decreasing if each element is strictly
    smaller than its previous one (if exists).

    ===============================
    FUNCTION:  
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    `

    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.50% */
/* Space Beats: 76.47% */

/* Time  Complexity: O(M^3 * logn) */
/* Space Complexity: O(M^2)        */
class Solution {
private:
    static const long long MOD = 1e9 + 7;

    using Matrix = vector<vector<long long>>;

public:
    int zigZagArrays(int n, int l, int r)
    {
        const int M = r - l + 1;

        vector<long long> initial_state(M);

        for (int value = 0; value < M; value++)
            initial_state[value] = value;

        Matrix transition_matrix(M, vector<long long>(M, 0));

        for (int row = 1; row < M; row++)
        {
            for (int col = M - row; col < M; col++)
                transition_matrix[row][col] = 1;
        }

        Matrix transition_matrix_power = matrix_power(transition_matrix, n - 2, M);

        long long result = 0;
        for (int row = 0; row < M; row++)
        {
            for (int col = 0; col < M; col++)
            {
                result = (result  +  transition_matrix_power[row][col] * initial_state[col]) % MOD;
            }
        }

        return result * 2 % MOD;
    }

private:
    Matrix matrix_multiplication(Matrix& matrix_A, Matrix& matrix_B, int matrix_size)
    {
        Matrix result(matrix_size, vector<long long>(matrix_size, 0));

        for (int row = 0; row < matrix_size; row++)
        {
            for (int intermediate = 0; intermediate < matrix_size; intermediate++)
            {
                if ( ! matrix_A[row][intermediate])
                    continue;

                for (int col = 0; col < matrix_size; col++)
                {
                    result[row][col] = (result[row][col]  +  matrix_A[row][intermediate] * matrix_B[intermediate][col]) % MOD;
                }
            }
        }

        return result;
    }

    Matrix matrix_power(Matrix matrix_base, int exponent, int matrix_size)
    {
        Matrix result(matrix_size, vector<long long>(matrix_size, 0));

        for (int row = 0; row < matrix_size; row++)
            result[row][row] = 1;

        while (exponent > 0)
        {
            if (exponent & 1)
                result = matrix_multiplication(result, matrix_base, matrix_size);

            matrix_base = matrix_multiplication(matrix_base, matrix_base, matrix_size);

            exponent /= 2;
        }

        return result;
    }
};
