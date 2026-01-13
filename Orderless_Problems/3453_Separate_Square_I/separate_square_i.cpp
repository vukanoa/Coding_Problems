/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3453) Separate Square I
    ===========================

    ============
    Description:
    ============

    You are given a 2D integer array squares. Each squares[i] = [xi, yi, li]
    represents the coordinates of the bottom-left point and the side length of
    a square parallel to the x-axis.

    Find the minimum y-coordinate value of a horizontal line such that the
    total area of the squares above the line equals the total area of the
    squares below the line.

    Answers within 10-5 of the actual answer will be accepted.

    =====
    Note: Squares may overlap. Overlapping areas should be counted multiple
          times. 
    =====

    ===============================================================
    FUNCTION: double separateSquares(vector<vector<int>>& squares);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: squares = [[0,0,1],[2,2,1]]
    Output: 1.00000

    --- Example 2 ---
    Input: squares = [[0,0,2],[1,1,1]]
    Output: 1.16667
Explanation:
    The areas are:

        Below the line: 7/6 * 2 (Red) + 1/6 (Blue) = 15/6 = 2.5.
        Above the line: 5/6 * 2 (Red) + 5/6 (Blue) = 15/6 = 2.5.

    Since the areas above and below the line are equal, the output is 7/6 =
    1.16667.


    *** Constraints ***
    1 <= squares.length <= 5 * 10^4
    squares[i] = [xi, yi, li]
    squares[i].length == 3
    0 <= xi, yi <= 10^9
    1 <= li <= 10^9
    The total area of all the squares will not exceed 1012.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.64% */
/* Space Beats: 52.02% */

/* Time  Complexity: O(N * log(max_y)) */
/* Space Complexity: O(1)              */
class Solution {
public:
    double separateSquares(vector<vector<int>>& squares)
    {
        double total_area = 0.0;

        for (const auto& square : squares)
        {
            double side_len = square[2];

            total_area += side_len * side_len;
        }

        double target_area = total_area / 2.0;

        double min_y =  1e18; // Lowest  'y' point in all squares
        double max_y = -1e18; // Highest 'y' point in all squares

        for (const auto& square : squares)
        {
            double y        = square[1]; // 'y' of the bottom-left point
            double side_len = square[2];

            min_y = min(min_y, y);
            max_y = max(max_y, y + side_len);
        }

        double low  = min_y;
        double high = max_y;

        const double eps = 1e-5;

        while (high - low > eps)
        {
            double mid = low + (high - low) / 2.0;
            double curr_area = area_above_y(squares, mid);

            if (curr_area > target_area)
                low  = mid;
            else
                high = mid;
        }

        return low;
    }

private:
    double area_above_y(const vector<vector<int>>& squares, double y_of_horizontal_line)
    {
        double area = 0.0;

        for (const auto& square : squares)
        {
            double side_len = square[2];

            double y_bottom = square[1];
            double y_top    = y_bottom + side_len;

            if (y_of_horizontal_line >= y_top)
                continue;

            double height = y_top - y_of_horizontal_line;


            /*
               Two possible layouts:


                              ^
                              |
                              |
                              |               side
                              |          <----------->
                 y_top  ----------->     ----------- ^             ^
                              |          |         | |             |
                              |          |         | | side        |
                              |          |         | |             | height
               y_bottom ----------->     ----------- v             |
                              |                                    |
                              |                                    |
   y_of_horizontal_line --------->  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ v ~~~~
                              |
                              |
                              |____________________________________________


                   or 
               
                              ^
                              |
                              |          side
                              |         <--------------------->
                   y_top  -------->     --------------------- ^        ^
                              |         |                   | |        |
                              |         |                   | |        |
                              |         |                   | |        | height
                              |         |                   | | side   |
                              |         |                   | |        |
     y_of_horizontal_line ----->  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~v ~~~~
                              |         |                   | |
                              |         |                   | |
                 y_bottom -------->     --------------------- v
                              |               
                              |____________________________________________
                        


            */
            if (height > side_len)
                height = side_len; // It can be at most "side_len"

            area += side_len * height;
        }

        return area;
    }
};
