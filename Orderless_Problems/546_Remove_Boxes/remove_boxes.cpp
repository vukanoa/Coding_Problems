/*
    ============
    === HARD ===
    ============

    ===========================
    546) Remove Boxes
    ===========================

    ============
    Description:
    ============

    You are given several boxes with different colors represented by different
    positive numbers.

    You may experience several rounds to remove boxes until there is no box
    left. Each time you can choose some continuous boxes with the same color
    (i.e., composed of k boxes, k >= 1), remove them and get k * k points.

    Return the maximum points you can get.

    ==============================================
    FUNCTION: int removeBoxes(vector<int>& boxes);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: boxes = [1,3,2,2,2,3,4,3,1]
    Output: 23
    Explanation:
    [1, 3, 2, 2, 2, 3, 4, 3, 1] 
    ----> [1, 3, 3, 4, 3, 1] (3*3=9 points) 
    ----> [1, 3, 3, 3, 1] (1*1=1 points) 
    ----> [1, 1] (3*3=9 points) 
    ----> [] (2*2=4 points)

    --- Example 2 ---
    Input: boxes = [1,1,1]
    Output: 9

    --- Example 3 ---
    Input: boxes = [1]
    Output: 1


    *** Constraints ***
    1 <= boxes.length <= 100
    1 <= boxes[i] <= 100

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 77.81% */
/* Space Beats: 70.42% */

/* Time  Complexity: O(N^4) */
/* Space Complexity: O(N^3) */
class Solution {
private:
    int memo[101][101][101];

public:
    int removeBoxes(vector<int> & boxes)
    {
        memset(memo, -1, sizeof(memo));

        int total_boxes = static_cast<int>(boxes.size());
        return solve(0, total_boxes - 1, boxes, 0);
    }

private:
    int solve(int left_idx, int right_idx, vector<int>& boxes, int same_color_on_left)
    {
        if (left_idx > right_idx)
            return 0;

        int original_left_idx   = left_idx;
        int original_same_color = same_color_on_left;

        if (memo[left_idx][right_idx][same_color_on_left] != -1)
            return memo[left_idx][right_idx][same_color_on_left];

        while (left_idx + 1 <= right_idx &&
               boxes[left_idx] == boxes[left_idx + 1])
        {
            ++left_idx;
            ++same_color_on_left;
        }

        /*
            TAKE case:

            remove current group (boxes[left_idx] plus same_color_on_left)
            immediately, then solve the rest independently
        */
        int best_score = (same_color_on_left + 1) * (same_color_on_left + 1) + solve(left_idx + 1, right_idx, boxes, 0);

        /*
            SKIP case:

            try to keep boxes[left_idx] and merge it later with the same color
            appearing at position merge_idx
        */
        for (int merge_idx = left_idx + 1; merge_idx <= right_idx; ++merge_idx)
        {
            if (boxes[merge_idx] == boxes[left_idx])
            {
                best_score = max(best_score, solve(left_idx + 1, merge_idx - 1, boxes,                      0) +
                                             solve(merge_idx   , right_idx    , boxes, same_color_on_left + 1));
            }
        }

        return memo[original_left_idx][right_idx][original_same_color] = best_score;
    }
};
