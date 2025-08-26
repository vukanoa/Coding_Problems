/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2718) Sum of Matrix After Queries
    =================================

    ============
    Description:
    ============

    You are given an integer n and a 0-indexed 2D array queries where
    queries[i] = [typei, indexi, vali].

    Initially, there is a 0-indexed n x n matrix filled with 0's. For each
    query, you must apply one of the following changes:

        + if typei == 0, set the values in the row with indexi to vali,
          overwriting any previous values.

        + if typei == 1, set the values in the column with indexi to vali,
          overwriting any previous values.

    Return the sum of integers in the matrix after all queries are applied.

    ==========================================================================
    FUNCTION: long long matrixSumQueries(int n, vector<vector<int>>& queries);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, queries = [[0,0,1],[1,2,2],[0,2,3],[1,0,4]]
    Output: 23
    Explanation: The image above describes the matrix after each query. The sum
    of the matrix after all queries are applied is 23.

    --- Example 2 ---
    Input: n = 3, queries = [[0,0,4],[0,1,2],[1,0,1],[0,2,3],[1,2,1]]
    Output: 17
    Explanation: The image above describes the matrix after each query. The sum
    of the matrix after all queries are applied is 17.


    *** Constraints ***
    1 <= n <= 10^4
    1 <= queries.length <= 5 * 10^4
    queries[i].length == 3
    0 <= typei <= 1
    0 <= indexi < n
    0 <= vali <= 10^5

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The trick is to start processing queries from the back. That makes the
    problem pretty trivial.

*/

/* Time  Beats: 36.79% */
/* Space Beats: 28.50% */

/* Time  Complexity: O(QUERIES_SIZE) */
/* Space Complexity: O(QUERIES_SIZE) */
class Solution {
public:
    long long matrixSumQueries(int n, vector<vector<int>>& queries)
    {
        const int QUERIES_SIZE = queries.size();
        long long result = 0LL;

        unordered_set<int> row;
        unordered_set<int> col;

        for (int i = QUERIES_SIZE-1; i >= 0; i--)
        {
            const int& type = queries[i][0];
            const int& idx  = queries[i][1];
            const int& val  = queries[i][2];

            if (type == 0) // Row
            {
                if ( ! row.count(idx))
                {
                    row.insert(idx);
                    result += (n - col.size()) * val;
                }
            }
            else
            {
                if ( ! col.count(idx))
                {
                    col.insert(idx);
                    result += (n - row.size()) * val;
                }
            }
        }

        return result;
    }
};
