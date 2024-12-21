#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    =============================================================
    1964) Find the Longest Valid Obstacle Course at Each Position
    =============================================================

    ============
    Description:
    ============

    You want to build some obstacle courses. You are given a 0-indexed integer
    array obstacles of length n, where obstacles[i] describes the height of the
    ith obstacle.

    For every index i between 0 and n - 1 (inclusive), find the length of the
    longest obstacle course in obstacles such that:

        + You choose any number of obstacles between 0 and i inclusive.

        + You must include the ith obstacle in the course.

        + You must put the chosen obstacles in the same order as they appear in
          obstacles.

        + Every obstacle (except the first) is taller than or the same height
          as the obstacle immediately before it.

    Return an array ans of length n, where ans[i] is the length of the longest
    obstacle course for index i as described above.

    ==================================================================================
    FUNCTION: vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: obstacles = [1,2,3,2]
    Output: [1,2,3,3]
    Explanation: The longest valid obstacle course at each position is:
    - i = 0: [1], [1] has length 1.
    - i = 1: [1,2], [1,2] has length 2.
    - i = 2: [1,2,3], [1,2,3] has length 3.
    - i = 3: [1,2,3,2], [1,2,2] has length 3.


    --- Example 2 ---
    Input: obstacles = [2,2,1]
    Output: [1,2,1]
    Explanation: The longest valid obstacle course at each position is:
    - i = 0: [2], [2] has length 1.
    - i = 1: [2,2], [2,2] has length 2.
    - i = 2: [2,2,1], [1] has length 1.


    --- Example 3 ---
    Input: obstacles = [3,1,5,6,4,2]
    Output: [1,1,2,3,2,2]
    Explanation: The longest valid obstacle course at each position is:
    - i = 0: [3], [3] has length 1.
    - i = 1: [3,1], [1] has length 1.
    - i = 2: [3,1,5], [3,5] has length 2. [1,5] is also valid.
    - i = 3: [3,1,5,6], [3,5,6] has length 3. [1,5,6] is also valid.
    - i = 4: [3,1,5,6,4], [3,4] has length 2. [1,4] is also valid.
    - i = 5: [3,1,5,6,4,2], [1,2] has length 2.


    *** Constraints ***
    n == obstacles.length
    1 <= n <= 10^5
    1 <= obstacles[i] <= 10^7

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.41% */
/* Space Beats: 96.85% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles)
    {
        const int n = obstacles.size();

        vector<int> result(n);
        vector<int> LIS;

        for (int i = 0; i < n; i++)
        {
            int low = 0;
            int high = LIS.size() - 1;

            while (low <= high)
            {
                int mid = low + (high - low) / 2;

                if (LIS[mid] <= obstacles[i])
                    low  = mid + 1;
                else
                    high = mid - 1;
            }

            if (low == LIS.size())
                LIS.emplace_back(obstacles[i]);
            else
                LIS[low] = obstacles[i];

            result[i] = low + 1;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 74.87% */
/* Space Beats: 10.07% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles)
    {
        const int n = obstacles.size();

        vector<int> LIS;
        vector<int> result;

        for (int i = 0; i < n; i++)
        {
            int target = obstacles[i];

            auto it = upper_bound(LIS.begin(), LIS.end(), target);

            if (it == LIS.end())
            {
                LIS.push_back(target);
                result.push_back(LIS.size());
            }
            else
            {
                *it = target;
                result.push_back(it - LIS.begin() + 1);
            }
        }

        return result;
    }
};
