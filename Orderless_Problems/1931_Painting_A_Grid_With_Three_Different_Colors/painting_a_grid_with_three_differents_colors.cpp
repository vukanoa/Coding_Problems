/*
    ============
    === HARD ===
    ============

    =================================================
    1931) Painting a Grid With Three Different Colors
    =================================================

    ============
    Description:
    ============

    You are given two integers m and n. Consider an m x n grid where each cell
    is initially white. You can paint each cell red, green, or blue. All cells
    must be painted.

    Return the number of ways to color the grid with no two adjacent cells
    having the same color. Since the answer can be very large, return it
    modulo 10^9 + 7.

    =========================================
    FUNCTION: int colorTheGrid(int m, int n);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 1, n = 1
    Output: 3
    Explanation: The three possible colorings are shown in the image above.

    --- Example 2 ---
    Input: m = 1, n = 2
    Output: 6
    Explanation: The six possible colorings are shown in the image above.

    --- Example 3 ---
    Input: m = 5, n = 5
    Output: 580986


    *** Constraints ***
    1 <= m <= 5
    1 <= n <= 1000

*/

#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.86% */
/* Space Beats: 35.06% */

/* Time  Complexity: O(3^(2m) * n) */
/* Space Complexity: O(3^(2m))     */
class Solution {
private:
    static constexpr int mod = 1000000007;

public:
    int colorTheGrid(int m, int n)
    {
        unordered_map<int, vector<int>> valid_color_schemes;

        // Enumerate masks that meet the requirements within the range [0, 3^m)
        int mask_limit = pow(3, m);
        for (int mask = 0; mask < mask_limit; mask++)
        {
            vector<int> color_scheme;
            int curr_mask = mask;

            for (int i = 0; i < m; i++)
            {
                color_scheme.push_back(curr_mask % 3);
                curr_mask /= 3;
            }

            bool is_valid_scheme = true;
            for (int i = 0; i < m - 1; i++)
            {
                if (color_scheme[i] == color_scheme[i + 1])
                {
                    is_valid_scheme = false;
                    break;
                }
            }

            if (is_valid_scheme)
                valid_color_schemes[mask] = std::move(color_scheme);
        }

        unordered_map<int, vector<int>> adjacent_schemes;
        for (const auto& [mask1, color1] : valid_color_schemes)
        {
            for (const auto& [mask2, color2] : valid_color_schemes)
            {
                bool are_adjacent = true;
                for (int row = 0; row < m; ++row)
                {
                    if (color1[row] == color2[row])
                    {
                        are_adjacent = false;
                        break;
                    }
                }

                if (are_adjacent)
                    adjacent_schemes[mask1].push_back(mask2);
            }
        }

        vector<int> dp_previous(mask_limit);
        for (const auto& [mask, _] : valid_color_schemes)
            dp_previous[mask] = 1;

        for (int i = 1; i < n; i++)
        {
            vector<int> dp_current(mask_limit);
            for (const auto& [mask2, _] : valid_color_schemes)
            {
                for (int mask1 : adjacent_schemes[mask2])
                {
                    dp_current[mask2] += dp_previous[mask1];

                    if (dp_current[mask2] >= mod)
                        dp_current[mask2] -= mod;
                }
            }

            dp_previous = std::move(dp_current);
        }

        int total_schemes = 0;
        for (int num : dp_previous)
        {
            total_schemes += num;

            if (total_schemes >= mod)
                total_schemes -= mod;
        }

        return total_schemes;
    }
};
