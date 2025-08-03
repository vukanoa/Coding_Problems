/*
    ============
    === HARD ===
    ============

    ====================================================
    2106) Maximum Fruits Harvested After at Most K Steps
    ====================================================

    ============
    Description:
    ============

    Fruits are available at some positions on an infinite x-axis. You are given
    a 2D integer array fruits where fruits[i] = [positioni, amounti] depicts
    amounti fruits at the position positioni. fruits is already sorted by
    positioni in ascending order, and each positioni is unique.

    You are also given an integer startPos and an integer k. Initially, you are
    at the position startPos. From any position, you can either walk to the
    left or right. It takes one step to move one unit on the x-axis, and you
    can walk at most k steps in total. For every position you reach, you
    harvest all the fruits at that position, and the fruits will disappear from
    that position.

    Return the maximum total number of fruits you can harvest.

    ===============================================================================
    FUNCTION: int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
    Output: 9
    Explanation:
    The optimal way is to:
    - Move right to position 6 and harvest 3 fruits
    - Move right to position 8 and harvest 6 fruits
    You moved 3 steps and harvested 3 + 6 = 9 fruits in total.

    --- Example 2 ---
    Input: fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
    Output: 14
    Explanation:
    You can move at most k = 4 steps, so you cannot reach position 0 nor 10.
    The optimal way is to:
    - Harvest the 7 fruits at the starting position 5
    - Move left to position 4 and harvest 1 fruit
    - Move right to position 6 and harvest 2 fruits
    - Move right to position 7 and harvest 4 fruits
    You moved 1 + 3 = 4 steps and harvested 7 + 1 + 2 + 4 = 14 fruits in total.

    --- Example 3 ---
    Input: fruits = [[0,3],[6,4],[8,5]], startPos = 3, k = 2
    Output: 0
    Explanation:
    You can move at most k = 2 steps and cannot reach any position with fruits.


    *** Constraints ***
    1 <= fruits.length <= 10^5
    fruits[i].length == 2
    0 <= startPos, positioni <= 2 * 10^5
    positioni-1 < positioni for any i > 0 (0-indexed)
    1 <= amounti <= 10^4
    0 <= k <= 2 * 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.94% */
/* Space Beats: 51.06% */

/* Time  Complexity: O(N + k * logN) */
/* Space Complexity: O(N)            */
class Solution_Prefix_Sum_Plus_Binary_Search {
private:
    struct CompareFirstElementWithTarget
    {
        bool operator()(const vector<int>& vec, int target) const
        {
            return vec[0] < target;
        }
    };

public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k)
    {
        const int N = fruits.size();
        int result = 0;

        vector<int> prefix_sum(N + 1);
        for (int i = 0; i < N; i++)
        {
            prefix_sum[i + 1]  = prefix_sum[i] + fruits[i][1];
        }

        for (int step = 0; step <= k / 2; step++)
        {
            ///////////////////////////////////////////////////////////////
            // Move left (step) steps, then move right (k - step) steps ///
            ///////////////////////////////////////////////////////////////
            int remaining_steps = k - 2 * step;

            int leftmost_pos  = startPos - step;
            int rightmost_pos = startPos + remaining_steps;

            auto iter_start = lower_bound(fruits.begin(), fruits.end(), leftmost_pos,  CompareFirstElementWithTarget());
            auto iter_end   = upper_bound(fruits.begin(), fruits.end(), rightmost_pos, CompareFirstElementWithTarget());

            int start_idx = distance(fruits.begin(), iter_start);
            int end_idx   = distance(fruits.begin(), iter_end);

            result = max(result, prefix_sum[end_idx] - prefix_sum[start_idx]);


            //////////////////////////////////////////////////////////////
            // Move right (step) steps, then move left (k - step) steps //
            //////////////////////////////////////////////////////////////
            remaining_steps = k - 2 * step;

            leftmost_pos  = startPos - remaining_steps;
            rightmost_pos = startPos + step;


            iter_start = lower_bound(fruits.begin(), fruits.end(), leftmost_pos,  CompareFirstElementWithTarget());
            iter_end   = upper_bound(fruits.begin(), fruits.end(), rightmost_pos, CompareFirstElementWithTarget());

            start_idx = distance(fruits.begin(), iter_start);
            end_idx   = distance(fruits.begin(), iter_end);

            result = max(result, prefix_sum[end_idx] - prefix_sum[start_idx]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar idea to the one above, however this one does NOT use Binary Search.
    It is redundant.

    TODO

*/

/* Time  Beats: 37.45% */
/* Space Beats: 23.83% */

/* Time  Complexity: O(N + k + max_position) */
/* Space Complexity: O(max_position)         */
class Solution_Only_Prefix_Sum {
public:
    int MaxTotalFruits(vector<vector<int>>& fruits, int startPos, int k)
    {
        const int N = fruits.size();
        int result = 0;

        int max_position = max(fruits.back()[0], startPos + k) + 2;

        vector<int> prefix_sum(max_position, 0);
        for (const vector<int>& fruit : fruits)
        {
            int position = fruit[0];
            int amount   = fruit[1];

            prefix_sum[position + 1] += amount;
        }

        for (int i = 1; i < max_position; ++i)
        {
            prefix_sum[i] += prefix_sum[i - 1];
        }


        // First to the left
        for (int steps_left = 0; steps_left <= k; steps_left++)
        {
            int left_limit  = max(startPos - steps_left, 0);
            int right_limit = max(startPos + (k - 2 * steps_left), 0);

            result = max(result, prefix_sum[right_limit + 1] - prefix_sum[left_limit]);
        }

        // First to the right
        for (int steps_right = 0; steps_right <= k; steps_right++)
        {
            int right_limit = startPos + steps_right;
            int left_limit  = max(startPos - (k - 2 * steps_right), 0);

            result = max(result, prefix_sum[right_limit + 1] - prefix_sum[left_limit]);
        }

        return result;
    }
};
