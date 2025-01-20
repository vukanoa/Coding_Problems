/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2661) First Completely Painted Row or Column
    ============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array arr, and an m x n integer matrix
    mat. arr and mat both contain all the integers in the range [1, m * n].

    Go through each index i in arr starting from index 0 and paint the cell in
    mat containing the integer arr[i].

    Return the smallest index i at which either a row or a column will be
    completely painted in mat.

    =============================================================================
    FUNCTION: int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
    Output: 2
    Explanation: The moves are shown in order, and both the first row and
                 second column of the matrix become fully painted at arr[2].

    --- Example 2 ---
    Input: arr = [2,8,7,4,1,3,5,6,9], mat = [[3,2,5],[1,4,6],[8,7,9]]
    Output: 3
    Explanation: The second column becomes fully painted at arr[3].


    *** Constraints ***
    m == mat.length
    n = mat[i].length
    arr.length == m * n
    1 <= m, n <= 10^5
    1 <= m * n <= 10^5
    1 <= arr[i], mat[r][c] <= m * n
    All the integers of arr are unique.
    All the integers of mat are unique.

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since we have to, somehow, know both "row" and "col" in "mat" of the
    current element in "arr", it's better to do that beforehand than to,
    manually, search ROWS * COLS elements for every 'i' in "arr".

    That's why we have "umap", our HashMap. The key is the element value, and
    the value is a pair of {row, col} in "mat".

    Also, since we don't want to, again manually each time, check all the
    elements in the current row and all the elements in the current col, we
    can have our two additional vectors:

        1. remaining_in_row
        2. remaining_in_col

    However, it's VERY important to notice this:
    Initialization of the number of elements in each row should be COLS.
    Initialization of the number of elements in each col should be ROWS.

    It's counter-intuitive at a first glance, but consider this example:

        arr = [1,4,5,2,6,3]

        mat = [[4,3,5],
               [1,2,6]]


    Since we have TWO rows but THREE elements in each row and:

        ROWS = TWO
        COLS = THREE

    We need a vector of length TWO(i.e. ROWS), but each row has THREE(ie. COLS)
    elements.


    Also, we have THREE columns but TWO elements in each column:

        COLS = THREE
        ROWS = TWO

    We need a vector of length THREE(ie. COLS), but each row has TWO(i.e. ROWS)
    elements.



    Since all the elements in both "arr" and "mat" are UNIQUE, all we need to
    do is go through each element in "arr" and if we find out that the number
    of elements remaining to be painted in the current row of this element
    in "mat" is 1, then that means that painting this current element will
    result in a filled row.

    Same thing is true of painting a column. If there's only one remaining,
    ti's over, we've found our result - Just return index 'i'.


    If it's not, decrement one element from both:
        remaining_in_row[curr_row of element]
        remaining_in_row[curr_col of element]

    That's it.

*/

/* Time  Beats: 52.44% */
/* Space Beats: 23.48% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat)
    {
        const int N = arr.size();
        const int ROWS = mat.size();
        const int COLS = mat[0].size();

        int result = 0;

        vector<int> remaining_in_row(ROWS, COLS);
        vector<int> remaining_in_col(COLS, ROWS);

        unordered_map<int, pair<int,int>> umap; // elem : {row,col}

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                umap.insert( {mat[row][col], {row,col}} );
            }
        }

        for (int i = 0; i < N; i++)
        {
            int elem = arr[i];
            int row  = umap[elem].first;
            int col  = umap[elem].second;

            if (remaining_in_row[row] == 1 || remaining_in_col[col] == 1)
                return i;

            remaining_in_row[row]--;
            remaining_in_col[col]--;
        }

        return -1; // Unreachable code
    }
};
