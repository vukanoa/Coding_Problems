/*
    ============
    === HARD ===
    ============

    ==============================================
    3538) Merge Operations for Minimum Travel Time
    ==============================================

    ============
    Description:
    ============

    You are given a straight road of length l km, an integer n, an integer k,
    and two integer arrays, position and time, each of length n.

    The array position lists the positions (in km) of signs in strictly
    increasing order (with position[0] = 0 and position[n - 1] = l).

    Each time[i] represents the time (in minutes) required to travel 1 km
    between position[i] and position[i + 1].

    You must perform exactly k merge operations. In one merge, you can choose
    any two adjacent signs at indices i and i + 1 (with i > 0 and i + 1 < n) and:

        + Update the sign at index i + 1 so that its time becomes time[i] + time[i + 1].

        + Remove the sign at index i.

    Return the minimum total travel time (in minutes) to travel from 0 to l
    after exactly k merges.

    ===========================================================================================
    FUNCTION: int minTravelTime(int l, int n, int k, vector<int> &position, vector<int> &time);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: l = 10, n = 4, k = 1, position = [0,3,8,10], time = [5,8,3,6]
    Output: 62
    Explanation:
        Merge the signs at indices 1 and 2. Remove the sign at index 1, and change the time at index 2 to 8 + 3 = 11.
        After the merge:
            position array: [0, 8, 10]
            time array: [5, 11, 6]

    Segment    Distance (km)    Time per km (min)    Segment Travel Time (min)
    0 → 8         8                  5                    8 × 5 = 40
    8 → 10        2                 11                    2 × 11 = 22

    Total Travel Time: 40 + 22 = 62, which is the minimum possible time after
    exactly 1 merge.


    --- Example 2 ---
    Input: l = 5, n = 5, k = 1, position = [0,1,2,3,5], time = [8,3,9,3,3]
    Output: 34
    Explanation:
        Merge the signs at indices 1 and 2. Remove the sign at index 1, and
        change the time at index 2 to 3 + 9 = 12.
        After the merge:
            position array: [0, 2, 3, 5]
            time array: [8, 12, 3, 3]

    Segment    Distance (km)    Time per km (min)    Segment Travel Time (min)
    0 → 2         2                   8                  2 × 8  = 16
    2 → 3         1                   12                 1 × 12 = 12
    3 → 5         2                   3                  2 × 3  = 6

    Total Travel Time: 16 + 12 + 6 = 34, which is the minimum possible time
    after exactly 1 merge.


    *** Constraints ***
    1 <= l <= 10^5
    2 <= n <= min(l + 1, 50)
    0 <= k <= min(n - 2, 10)
    position.length == n
    position[0] = 0 and position[n - 1] = l
    position is sorted in strictly increasing order.
    time.length == n
    1 <= time[i] <= 100
    1 <= sum(time) <= 100

*/

#include <climits>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.49% */
/* Space Beats: 38.22% */

/* Time  Complexity: O(n * k * sum(time)) */
/* Space Complexity: O(n * k * sum(time)) */
class Solution {
private:
    vector<vector<vector<int>>> memo;
    vector<int> position;
    vector<int> time;

public:
    int minTravelTime(int l, int n, int k, vector<int> &position, vector<int> &time)
    {
        int total_time = accumulate(time.begin(), time.end(), 0);

        this->position = position;
        this->time = time;

        memo.assign(n, vector<vector<int>>(k + 1, vector<int>(total_time + 1, -1)));

        return solve(0, k, time[0]);
    }

private:
    int solve(int idx, int skips_left, int curr_time)
    {
        int n = position.size();

        if (idx == n - 1)
        {
            // Reached the end, cannot skip further
            return skips_left > 0 ? INT_MAX : 0;
        }

        if (memo[idx][skips_left][curr_time] != -1)
        {
            return memo[idx][skips_left][curr_time];
        }

        int min_cost = INT_MAX;

        // === Option 1: Take
        int cost_to_next = solve(idx + 1, skips_left, time[idx + 1]);

        if (cost_to_next != INT_MAX)
        {
            int distance = position[idx + 1] - position[idx];
            min_cost = min(min_cost, distance * curr_time + cost_to_next);
        }

        // === Option 2: Skip one or more points ===
        int accumulated_time = time[idx + 1];
        for (int j = idx + 2; j < n && j - idx - 1 <= skips_left; ++j)
        {
            accumulated_time += time[j];
            int used_skips = j - idx - 1;

            int skip_cost = solve(j, skips_left - used_skips, accumulated_time);

            if (skip_cost != INT_MAX)
            {
                int distance = position[j] - position[idx];
                min_cost = min(min_cost, distance * curr_time + skip_cost);
            }
        }

        return memo[idx][skips_left][curr_time] = min_cost;
    }
};
