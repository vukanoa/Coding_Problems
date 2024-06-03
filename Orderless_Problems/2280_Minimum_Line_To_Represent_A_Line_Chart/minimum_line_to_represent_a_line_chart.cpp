#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2280) Minimum Line to Represent a Line Chart
    ============================================

    ============
    Description:
    ============

    You are given a 2D integer array stockPrices where stockPrices[i] = [dayi,
    pricei] indicates the price of the stock on day dayi is pricei. A line
    chart is created from the array by plotting the points on an XY plane with
    the X-axis representing the day and the Y-axis representing the price and
    connecting adjacent points. One such example is shown below:

        PICTURE

    (Make sure to go on the website and look at the picture. It is impossible
    for me to draw it in ASCII)

    =============================================================
    FUNCTION: int minimumLines(vector<vector<int>>& stockPrices);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stockPrices = [[1,7],[2,6],[3,5],[4,4],[5,4],[6,3],[7,2],[8,1]]
    Output: 3
    Explanation:
    The diagram above represents the input, with the X-axis representing the
    day and Y-axis representing the price.
    The following 3 lines can be drawn to represent the line chart:
    - Line 1 (in red) from (1,7) to (4,4) passing through (1,7), (2,6), (3,5),
      and (4,4).
    - Line 2 (in blue) from (4,4) to (5,4).
    - Line 3 (in green) from (5,4) to (8,1) passing through (5,4), (6,3),
      (7,2), and (8,1).

    It can be shown that it is not possible to represent the line chart using
    less than 3 lines.



    --- Example 2 ---
    Input: stockPrices = [[3,4],[1,2],[7,8],[2,3]]
    Output: 1
    Explanation:
    As shown in the diagram above, the line chart can be represented with a
    single line.



    *** Constraints ***
    1 <= stockPrices.length <= 10^5
    stockPrices[i].length == 2
    1 <= dayi, pricei <= 10^9
    All dayi are distinct.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.24% */
/* Space Beats: 90.14% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution {
public:
    int minimumLines(vector<vector<int>>& stockPrices)
    {
        const int N = stockPrices.size();

        if (N <= 1)
            return 0;

        /* Sorting the input */
        std::sort (stockPrices.begin(), stockPrices.end());

        int count = 1;
        for(int i = 2; i < N; i++)
        {
            long x1 = stockPrices[i-2][0];
            long y1 = stockPrices[i-2][1];

            long x2 = stockPrices[i-1][0];
            long y2 = stockPrices[i-1][1];

            long x3 = stockPrices[i][0];
            long y3 = stockPrices[i][1];

            if((y3-y2) * (x2-x1) != (y2-y1) * (x3-x2))
                count++;
        }

        return count;
    }
};
