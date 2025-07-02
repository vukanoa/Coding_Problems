/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    3030) Find the Grid of Region Average
    =====================================

    ============
    Description:
    ============

    You are given m x n grid image which represents a grayscale image, where
    image[i][j] represents a pixel with intensity in the range [0..255].

    You are also given a non-negative integer threshold.

    Two pixels are adjacent if they share an edge.

    A region is a 3 x 3 subgrid where the absolute difference in intensity
    between any two adjacent pixels is less than or equal to threshold.

    All pixels in a region belong to that region, note that a pixel can belong
    to multiple regions.

    You need to calculate a m x n grid result, where result[i][j] is the
    average intensity of the regions to which image[i][j] belongs, rounded down
    to the nearest integer. If image[i][j] belongs to multiple regions,
    result[i][j] is the average of the rounded-down average intensities of
    these regions, rounded down to the nearest integer. If image[i][j] does not
    belong to any region, result[i][j] is equal to image[i][j].

    Return the grid result.

    ====================================================================================
    FUNCTION: vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: image = [[5,6,7,10],[8,9,10,10],[11,12,13,10]], threshold = 3
    Output: [[9,9,9,9],[9,9,9,9],[9,9,9,9]]
    Explanation: There are two regions as illustrated above. The average
                 intensity of the first region is 9, while the average
                 intensity of the second region is 9.67 which is rounded down
                 to 9. The average intensity of both of the regions is
                 (9 + 9) / 2 = 9. As all the pixels belong to either region 1,
                 region 2, or both of them, the intensity of every pixel in the
                 result is 9.

    Please note that the rounded-down values are used when calculating the
    average of multiple regions, hence the calculation is done using 9 as the
    average intensity of region 2, not 9.67.


    --- Example 2 ---
    Input: image = [[10,20,30],[15,25,35],[20,30,40],[25,35,45]], threshold = 12
    Output: [[25,25,25],[27,27,27],[27,27,27],[30,30,30]]
    Explanation: There are two regions as illustrated above. The average
                 intensity of the first region is 25, while the average
                 intensity of the second region is 30. The average intensity of
                 both of the regions is (25 + 30) / 2 = 27.5 which is rounded
                 down to 27.

                All the pixels in row 0 of the image belong to region 1, hence
                all the pixels in row 0 in the result are 25. Similarly, all
                the pixels in row 3 in the result are 30. The pixels in rows 1
                and 2 of the image belong to region 1 and region 2, hence their
                assigned value is 27 in the result.


    --- Example 3 ---
    Input: image = [[5,6,7],[8,9,10],[11,12,13]], threshold = 1
    Output: [[5,6,7],[8,9,10],[11,12,13]]
    Explanation: There is only one 3 x 3 subgrid, while it does not have the
                 condition on difference of adjacent pixels, for example, the
                 difference between image[0][0] and image[1][0] is
                 |5 - 8| = 3 > threshold = 1. None of them belong to any valid
                 regions, so the result should be the same as image.


    *** Constraints ***
    3 <= n, m <= 500
    0 <= image[i][j] <= 255
    0 <= threshold <= 255

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 83.13% */
/* Space Beats: 91.57% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold)
    {
        const int ROWS = image.size();
        const int COLS = image[0].size();

        int reg[501][501][2] = {};

        for (int row = 0; row < ROWS-2; row++)
        {
            for (int col = 0; col < COLS-2; col++)
            {
                int sum = 0;
                int is_region = true;

                for (int k = row; k < row+3; k++)
                {
                    for (int l = col; l < col+3; l++)
                    {
                        sum += image[k][l];
                        is_region &= k == row || abs(image[k][l] - image[k - 1][l]) <= threshold;
                        is_region &= l == col || abs(image[k][l] - image[k][l - 1]) <= threshold;
                    }
                }

                if (is_region)
                {
                    for (int k = row; k < row + 3; k++)
                    {
                        for (int left = col; left < col + 3; left++)
                        {
                            reg[k][left][0] += sum / 9;
                            reg[k][left][1] += 1;
                        }
                    }
                }
            }
        }


        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                if (reg[i][j][1])
                    image[i][j] = reg[i][j][0] / reg[i][j][1];
            }
        }

        return image;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  97.59% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution_Space_Optimized {
public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold)
    {
        const int ROWS = image.size();
        const int COLS = image[0].size();

        for (int row = 0; row < ROWS - 2; row++)
        {
            for (int col = 0; col < COLS - 2; col++)
            {
                int sum = 0;
                bool is_region = true;

                for (int i = row; i < row + 3; i++)
                {
                    for (int j = col; j < col + 3; j++)
                    {
                        int pixel = image[i][j] & 255;
                        sum += pixel;

                        if (i > row && abs(pixel - (image[i - 1][j] & 255)) > threshold)
                            is_region = false;
                        if (j > col && abs(pixel - (image[i][j - 1] & 255)) > threshold)
                            is_region = false;
                    }
                }

                if (is_region)
                {
                    int avg = sum / 9;
                    for (int i = row; i < row + 3; i++)
                    {
                        for (int j = col; j < col + 3; j++)
                        {
                            image[i][j] += (avg << 16); // Add to sum
                            image[i][j] += (1 << 8);    // Increment count
                        }
                    }
                }
            }
        }

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                int count = (image[i][j] >> 8) & 255;
                if (count > 0)
                {
                    int total_sum = image[i][j] >> 16;
                    image[i][j] = total_sum / count;
                }
                else
                {
                    image[i][j] &= 255;
                }
            }
        }

        return image;
    }
};
