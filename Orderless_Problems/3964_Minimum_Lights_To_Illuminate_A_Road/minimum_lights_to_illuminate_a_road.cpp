/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3964) Minimum Lights to Illuminate a Road
    =========================================

    ============
    Description:
    ============

    You are given an integer array lights of length n, representing positions 0
    through n - 1 on a road.

    For each position i:

        + If lights[i] = v, where v > 0, there is a working bulb at position i
          that illuminates every position from max(0, i - v) to min(n - 1, i +
          v), inclusive.

        + If lights[i] = 0, there is no working bulb at position i.

    A position is visible if it is illuminated by at least one working bulb.

    You may install additional bulbs at any positions. Each additional bulb
    installed at position j illuminates positions from max(0, j - 1) to min(n -
    1, j + 1), inclusive.

    Return the minimum number of additional bulbs required to make every
    position on the road visible.

    =============================================
    FUNCTION: int minLights(vector<int>& lights);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: lights = [0,0,0,0]
    Output: 2
    Explanation:
    One optimal placement is:
        Install an additional bulb at position 1, illuminating positions [0, 1, 2].
        Install an additional bulb at position 3, illuminating positions [2, 3].

    Therefore, the minimum number of additional bulbs required is 2.


    --- Example 2 ---
    Input: lights = [0,0,0,2,0]
    Output: 1
    Explanation:
        Since lights[3] = 2, the working bulb at position 3 illuminates positions [1, 2, 3, 4].
        Installing an additional bulb at position 1 illuminates positions [0, 1, 2], making every position visible.
        Therefore, the minimum number of additional bulbs required is 1.


    *** Constraints ***
    1 <= n == lights.length <= 10^5
    0 <= lights[i] <= n

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Line Sweep + Greedy coverage of lightbulbs in the dark.

*/

/* Time  Beats: 91.30% */
/* Space Beats: 94.48% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minLights(vector<int>& lights)
    {
        const int N = lights.size();
        static constexpr int MAX_SIZE = 1e5;
        int result = 0;

        int line_sweep[MAX_SIZE + 1] = {0};
        for (int i = 0; i < N; i++)
        {
            int& v = lights[i];

            if (v == 0)
                continue;

            int left  = max(0,   i - v);
            int right = min(N-1, i + v);

            ++line_sweep[left];
            --line_sweep[right+1];
        }

        vector<int> in_dark;
        in_dark.reserve(N); // To prevent reallocations

        int illuminated_by = 0;
        for (int i = 0; i < N; i++)
        {
            illuminated_by += line_sweep[i];

            if (illuminated_by == 0)
                in_dark.push_back(i);
        }

        int i = 0;
        const int SIZE = in_dark.size();
        while (i < SIZE)
        {
            int last_idx = i + 2;

            while (last_idx >= SIZE || (in_dark[i] + 2) < in_dark[last_idx])
                last_idx--;

            result++;

            // Move to the next in_dark lightbulb:
            i = last_idx + 1;
        }
        
        return result;
    }
};
