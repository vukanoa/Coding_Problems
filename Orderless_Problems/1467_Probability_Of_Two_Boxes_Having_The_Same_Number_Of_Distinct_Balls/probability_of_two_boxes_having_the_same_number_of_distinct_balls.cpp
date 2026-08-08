/*
    ============
    === HARD ===
    ============

    =========================================================================
    1467) Probability of a Two Boxes Having The Same Number of Distinct Balls
    =========================================================================

    ============
    Description:
    ============

    Given 2n balls of k distinct colors. You will be given an integer array
    balls of size k where balls[i] is the number of balls of color i.

    All the balls will be shuffled uniformly at random, then we will distribute
    the first n balls to the first box and the remaining n balls to the other
    box (Please read the explanation of the second example carefully).

    Please note that the two boxes are considered different. For example, if we
    have two balls of colors a and b, and two boxes [] and (), then the
    distribution [a] (b) is considered different than the distribution [b] (a)
    (Please read the explanation of the first example carefully).

    Return the probability that the two boxes have the same number of distinct
    balls. Answers within 10-5 of the actual value will be accepted as correct.

    ====================================================
    FUNCTION: double getProbability(vector<int>& balls);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: balls = [1,1]
    Output: 1.00000
    Explanation: Only 2 ways to divide the balls equally:
    - A ball of color 1 to box 1 and a ball of color 2 to box 2
    - A ball of color 2 to box 1 and a ball of color 1 to box 2
    In both ways, the number of distinct colors in each box is equal. The
    probability is 2/2 = 1

    --- Example 2 ---
    Input: balls = [2,1,1]
    Output: 0.66667
    Explanation: We have the set of balls [1, 1, 2, 3]
    This set of balls will be shuffled randomly and we may have one of the 12
    distinct shuffles with equal probability (i.e. 1/12): [1,1 / 2,3], [1,1 /
    3,2], [1,2 / 1,3], [1,2 / 3,1], [1,3 / 1,2], [1,3 / 2,1], [2,1 / 1,3], [2,1
    / 3,1], [2,3 / 1,1], [3,1 / 1,2], [3,1 / 2,1], [3,2 / 1,1] After that, we
    add the first two balls to the first box and the second two balls to the
    second box. We can see that 8 of these 12 possible random distributions
    have the same number of distinct colors of balls in each box. Probability
    is 8/12 = 0.66667

    --- Example 3 ---
    Input: balls = [1,2,1,2]
    Output: 0.60000
    Explanation: The set of balls is [1, 2, 2, 3, 4, 4]. It is hard to display
    all the 180 possible random shuffles of this set but it is easy to check
    that 108 of them will have the same number of distinct colors in each box.
    Probability = 108 / 180 = 0.6

    *** Constraints ***
    1 <= balls.length <= 8
    1 <= balls[i] <= 6
    sum(balls) is even.

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 23.01% */
/* Space Beats: 61.95% */

/* Time  Complexity: O(3^N * N) */
/* Space Complexity: O(N)       */
class Solution {
private:
    int total_balls = 0;

public:
    double getProbability(vector<int>& balls)
    {
        total_balls = accumulate(begin(balls), end(balls), 0);

        vector<int> first_box(balls.size());
        vector<int> second_box(balls.size());

        return dfs(0, 0, 0, balls, first_box, second_box) / calculate_permutations(balls);
    }

private:
    double calculate_permutations(vector<int>& balls)
    {
        const int N = balls.size();

        double permutations = 1;
        for (int color = 0, current_ball = 1; color < N; color++)
        {
            for (int ball = 1; ball <= balls[color]; ball++, current_ball++)
                permutations = permutations * current_ball / ball;
        }

        return permutations;
    }

    double dfs(int color,
               int first_box_balls,
               int second_box_balls,
               vector<int>& balls,
               vector<int>& first_box,
               vector<int>& second_box)
    {
        if (first_box_balls > total_balls / 2 || second_box_balls > total_balls / 2)
            return 0;

        if (color == balls.size())
        {
            int first_box_colors = 0;
            int second_box_colors = 0;

            for (int current_color = 0; current_color < balls.size(); current_color++)
                first_box_colors += first_box[current_color] > 0;

            for (int current_color = 0; current_color < balls.size(); current_color++)
                second_box_colors += second_box[current_color] > 0;

            if (first_box_colors != second_box_colors)
                return 0;

            return calculate_permutations(first_box) * calculate_permutations(second_box);
        }

        double probability = 0;

        for (int first_box_count = 0; first_box_count <= balls[color]; first_box_count++)
        {
            first_box[color]  = first_box_count;
            second_box[color] = balls[color] - first_box_count;

            probability += dfs(color + 1,
                               first_box_balls + first_box[color],
                               second_box_balls + second_box[color],
                               balls,
                               first_box,
                               second_box);
        }

        return probability;
    }
};
