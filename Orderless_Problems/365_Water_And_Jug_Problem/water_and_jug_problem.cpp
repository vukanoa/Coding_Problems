/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    365) Water and Jug Problem
    ===========================

    ============
    Description:
    ============


    You are given two jugs with capacities x liters and y liters. You have an
    infinite water supply. Return whether the total amount of water in both
    jugs may reach target using the following operations:

        + Fill either jug completely with water.

        + Completely empty either jug.

        + Pour water from one jug into another until the receiving jug is full,
          or the transferring jug is empty.

    =========================================================
    FUNCTION: bool canMeasureWater(int x, int y, int target);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: x = 3, y = 5, target = 4
    Output: true
    Explanation:
    Follow these steps to reach a total of 4 liters:
        Fill the 5-liter jug (0, 5).
        Pour from the 5-liter jug into the 3-liter jug, leaving 2 liters (3, 2).
        Empty the 3-liter jug (0, 2).
        Transfer the 2 liters from the 5-liter jug to the 3-liter jug (2, 0).
        Fill the 5-liter jug again (2, 5).
        Pour from the 5-liter jug into the 3-liter jug until the 3-liter jug is full.
        This leaves 4 liters in the 5-liter jug (3, 4).
        Empty the 3-liter jug. Now, you have exactly 4 liters in the 5-liter jug (0, 4).


    --- Example 2 ---
    Input: x = 2, y = 6, target = 5
    Output: false


    --- Example 3 ---
    Input: x = 1, y = 2, target = 3
    Output: true
    Explanation: Fill both jugs. The total amount of water in both jugs is
                 equal to 3 now.


    *** Constraints ***
    1 <= x, y, target <= 10^3

*/

#include <stack>
#include <unordered_set>
#include <utility>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  8.65% */
/* Space Beats: 10.25% */

/* Time  Complexity: O(x * y) */
/* Space Complexity: O(x * y) */
class Solution {
public:
    bool CanMeasureWater(int x, int y, int target)
    {
        if (target > x + y)
            return false;

        stack<pair<int, int>> state_stack;
        state_stack.push({0, 0});

        unordered_set<long long> visited;

        while ( ! state_stack.empty())
        {
            auto [a, b] = state_stack.top();
            state_stack.pop();

            if (a + b == target)
                return true;

            long long state_id = static_cast<long long>(a) << 32 | b;
            if (visited.count(state_id))
                continue;

            visited.insert(state_id);

            state_stack.push({x, b});  // Fill jug x
            state_stack.push({a, y});  // Fill jug y
            state_stack.push({0, b});  // Empty jug x
            state_stack.push({a, 0});  // Empty jug y

            int pour = min(a, y - b);
            state_stack.push({a - pour, b + pour}); // Pour x → y

            pour = min(b, x - a);
            state_stack.push({a + pour, b - pour}); // Pour y → x
        }

        return false;
    }
};
