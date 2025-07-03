/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    3025) Find the Number of Ways to Place People I
    ===============================================

    ============
    Description:
    ============

    You are given a 2D array points of size n x 2 representing integer
    coordinates of some points on a 2D plane, where points[i] = [xi, yi].

    Count the number of pairs of points (A, B), where

        + A is on the upper left side of B, and

        + there are no other points in the rectangle (or line) they make
          (including the border).

    Return the count.

    =========================================================
    FUNCTION: int numberOfPairs(vector<vector<int>>& points);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[1,1],[2,2],[3,3]]
    Output: 0
    Explanation: There is no way to choose A and B so A is on the upper left
                 side of B.

    --- Example 2 ---
    Input: points = [[6,2],[4,4],[2,6]]
    Output: 2
    Explanation:
    The left one is the pair (points[1], points[0]), where points[1] is on the
    upper left side of points[0] and the rectangle is empty.

    The middle one is the pair (points[2], points[1]), same as the left one it
    is a valid pair.

    The right one is the pair (points[2], points[0]), where points[2] is on the
    upper left side of points[0], but points[1] is inside the rectangle so it's
    not a valid pair.


    --- Example 3 ---
    Input: points = [[3,1],[1,3],[1,1]]
    Output: 2
    The left one is the pair (points[2], points[0]), where points[2] is on the
    upper left side of points[0] and there are no other points on the line they
    form. Note that it is a valid state when the two points form a line.
    The middle one is the pair (points[1], points[2]), it is a valid pair same
    as the left one.
    The right one is the pair (points[1], points[0]), it is not a valid pair as
    points[2] is on the border of the rectangle.


    *** Constraints ***
    2 <= n <= 50
    points[i].length == 2
    0 <= points[i][0], points[i][1] <= 50
    All points[i] are distinct.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since 'n' is SO SMALL, we don't have to worry about anything other than the
    logic.

*/

/* Time  Beats: 7.35% */
/* Space Beats: 5.88% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points)
    {
        const int N = points.size();
        int result = 0;

        for (int i = 0; i < N-1; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                vector<int> A = points[i];
                vector<int> B = points[j];

                if (A[0] > B[0])
                    swap(A, B);
                else if (A[0] == B[0] && A[1] < B[1])
                    swap(A,B);

                if (A[0] == B[0])
                {
                    bool valid = true;
                    for (int x = 0; x < N; x++)
                    {
                        if (points[x] == A || points[x] == B)
                            continue;

                        if (points[x][0] != A[0])
                            continue;

                        if (points[x][1] > A[1] || points[x][1] < B[1])
                            continue;

                        valid = false;
                        break;
                    }

                    if (valid)
                    {
                        // cout << "\n\tOvdee";
                        result++;
                    }
                }
                else
                {
                    if (A[1] < B[1])
                        continue;

                    bool valid = true;
                    for (int x = 0; x < N; x++)
                    {
                        if (points[x] == A || points[x] == B)
                            continue;

                        if (points[x][0] < A[0])
                            continue;

                        if (points[x][0] > B[0])
                            continue;

                        if (points[x][1] > A[1])
                            continue;

                        if (points[x][1] < B[1])
                            continue;

                        valid = false;
                        break;
                    }

                    if (valid)
                        result++;
                }
            }
        }

        return result;
    }
};
