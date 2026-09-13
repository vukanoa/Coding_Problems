/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    835) Image Overlap
    ===========================

    ============
    Description:
    ============

    You are given two images, img1 and img2, represented as binary, square
    matrices of size n x n. A binary matrix has only 0s and 1s as values.

    We translate one image however we choose by sliding all the 1 bits left,
    right, up, and/or down any number of units. We then place it on top of the
    other image. We can then calculate the overlap by counting the number of
    positions that have a 1 in both images.

    Note also that a translation does not include any kind of rotation. Any 1
    bits that are translated outside of the matrix borders are erased.

    Return the largest possible overlap.

    ===================================================================================
    FUNCTION: int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 = [[0,0,0],[0,1,1],[0,0,1]]
    Output: 3
    Explanation: We translate img1 to right by 1 unit and down by 1 unit.

    --- Example 2 ---
    Input: img1 = [[1]], img2 = [[1]]
    Output: 1

    --- Example 3 ---
    Input: img1 = [[0]], img2 = [[0]]
    Output: 0


    *** Constraints ***
    n == img1.length == img1[i].length
    n == img2.length == img2[i].length
    1 <= n <= 30
    img1[i][j] is either 0 or 1.
    img2[i][j] is either 0 or 1.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute Force.

    Not even written in an "elegant" way, but it works, it's not bad either.

*/

/* Time  Beats: 86.32% */
/* Space Beats: 68.83% */

/* Time  Complexity: O(N^4) */
/* Space Complexity: O(N^4) */
class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2)
    {
        const int N = img1.size();
        int result = 0;

        for (int shifts_left = 0; shifts_left < N; shifts_left++)
            move_left(shifts_left, img1, img2, result);

        for (int shifts_right = 0; shifts_right < N; shifts_right++)
            move_right(shifts_right, img1, img2, result);

        return result;
    }

private:
    void move_left(int shifts_left, vector<vector<int>>& img1, vector<vector<int>>& img2, int& result)
    {
        const int N = img1.size();

        /* Move DOWN */
        int shifts_down = 0;
        while (shifts_down < N)
        {
            int count = 0;
            for (int row = 0; row < N - shifts_down; row++)
            {
                for (int col = shifts_left; col < N; col++)
                {
                    if (img1[row][col] == 1 && img2[row + shifts_down][col - shifts_left] == 1)
                        ++count;
                }

                result = max(result, count);
            }

            // Increment
            ++shifts_down;
        }


        /* Move UP */
        int shifts_up = 0;
        while (shifts_up < N)
        {
            int count = 0;
            for (int row = shifts_up; row < N; row++)
            {
                for (int col = shifts_left; col < N; col++)
                {
                    if (img1[row][col] == 1 && img2[row - shifts_up][col - shifts_left] == 1)
                        ++count;
                }

                result = max(result, count);
            }

            // Increment
            ++shifts_up;
        }
    }

    void move_right(int shifts_right, vector<vector<int>>& img1, vector<vector<int>>& img2, int& result)
    {
        const int N = img1.size();

        /* Move DOWN */
        int shifts_down = 0;
        while (shifts_down < N)
        {
            int count = 0;
            for (int row = 0; row < N - shifts_down; row++)
            {
                for (int col = 0; col < N - shifts_right; col++)
                {
                    if (img1[row][col] == 1 && img2[row + shifts_down][col + shifts_right] == 1)
                        ++count;
                }

                result = max(result, count);
            }

            // Increment
            ++shifts_down;
        }


        /* Move UP */
        int shifts_up = 0;
        while (shifts_up < N)
        {
            int count = 0;
            for (int row = shifts_up; row < N; row++)
            {
                for (int col = 0; col < N - shifts_right; col++)
                {
                    if (img1[row][col] == 1 && img2[row - shifts_up][col + shifts_right] == 1)
                        ++count;
                }

                result = max(result, count);
            }

            // Increment
            ++shifts_up;
        }
    }
};
