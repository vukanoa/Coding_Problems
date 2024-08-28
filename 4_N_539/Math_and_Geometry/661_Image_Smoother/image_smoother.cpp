#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    661) Image Smoother
    ===========================

    ============
    Description:
    ============

    An image smoother is a filter of the size 3 x 3 that can be applied to each
    cell of an image by rounding down the average of the cell and the eight
    surrounding cells (i.e., the average of the nine cells in the blue
    smoother). If one or more of the surrounding cells of a cell is not
    present, we do not consider it in the average (i.e., the average of the
    four cells in the red smoother).


    Given an m x n integer matrix img representing the grayscale of an image,
    return the image after applying the smoother on each cell of it.

    ======================================================================
    FUNCTION: vector<vector<int>> imageSmoother(vector<vector<int>>& img);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: img = [[1,1,1],[1,0,1],[1,1,1]]
    Output: [[0,0,0],[0,0,0],[0,0,0]]
    Explanation:
    For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
    For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
    For the point (1,1): floor(8/9) = floor(0.88888889) = 0

    --- Example 2 ---
    Input: img = [[100,200,100],[200,50,200],[100,200,100]]
    Output: [[137,141,137],[141,138,141],[137,141,137]]
    Explanation:
    For the points (0,0), (0,2), (2,0), (2,2): floor((100+200+200+50)/4) = floor(137.5) = 137
    For the points (0,1), (1,0), (1,2), (2,1): floor((200+200+50+200+100+100)/6) = floor(141.666667) = 141
    For the point (1,1): floor((50+200+200+200+200+100+100+100+100)/9) = floor(138.888889) = 138


    *** Constraints ***
    m == img.length
    n == img[i].length
    1 <= m, n <= 200
    0 <= img[i][j] <= 255

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 18.64% */
/* Space Beats: 35.90% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img)
    {
        const int ROWS = img.size();
        const int COLS = img[0].size();

        vector<vector<int>> res(ROWS, vector<int>(COLS, 0));

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                res[i][j] = smoothen(img, i, j);
            }
        }

        return res;
    }

private:
    int smoothen(const vector<vector<int>>& img, int x, int y)
    {
        const int ROWS = img.size();
        const int COLS = img[0].size();

        int sum = 0;
        int count = 0;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int nx = x + i;
                int ny = y + j;

                if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS)
                {
                    sum += img[nx][ny];
                    count++;
                }
            }
        }

        return sum / count;
    }
};
