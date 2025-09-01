/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    1792) Maximum Average Pass Ratio
    ================================

    ============
    Description:
    ============

    There is a school that has classes of students and each class will be
    having a final exam. You are given a 2D integer array classes, where
    classes[i] = [passi, totali]. You know beforehand that in the ith class,
    there are totali total students, but only passi number of students will
    pass the exam.

    You are also given an integer extraStudents. There are another
    extraStudents brilliant students that are guaranteed to pass the exam of
    any class they are assigned to. You want to assign each of the
    extraStudents students to a class in a way that maximizes the average pass
    ratio across all the classes.

    The pass ratio of a class is equal to the number of students of the class
    that will pass the exam divided by the total number of students of the
    class. The average pass ratio is the sum of pass ratios of all the classes
    divided by the number of the classes.

    Return the maximum possible average pass ratio after assigning the
    extraStudents students. Answers within 10-5 of the actual answer will be
    accepted.

    ==================================================================================
    FUNCTION: double maxAverageRatio(vector<vector<int>>& classes, int extraStudents);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
    Output: 0.78333
    Explanation: You can assign the two extra students to the first class. The
                 average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 =
                 0.78333.

    --- Example 2 ---
    Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
    Output: 0.53485


    *** Constraints ***
    1 <= classes.length <= 10^5
    classes[i].length == 2
    1 <= passi <= totali <= 10^5
    1 <= extraStudents <= 10^5

*/

#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Greedy + Heap. Nothing "tricky" here. Maybe the only unintuitive part is
    using the difference between previous and current average, instead of just
    new average.

*/

/* Time  Beats: 91.80% */
/* Space Beats: 81.29% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents)
    {
        const int N = classes.size();
        double result = 0.0;

        priority_queue<pair<double,int>> max_heap; // {ratio_gain, idx};

        for (int idx = 0; idx < N; idx++)
        {
            const double& pass  = classes[idx][0];
            const double& total = classes[idx][1];

            result += 1.0 * pass / total;

            max_heap.push( {gain(pass, total), idx} );
        }

        while (extraStudents > 0)
        {
            auto [avg, idx] = max_heap.top();
            max_heap.pop();

            result -= 1.0 * classes[idx][0] / classes[idx][1];

            classes[idx][0]++;
            classes[idx][1]++;

            result += 1.0 * classes[idx][0] / classes[idx][1];

            max_heap.push( {gain(classes[idx][0], classes[idx][1]), idx} );

            // Decrement
            extraStudents--;
        }

        return result / N;
    }

private:
    double gain(double pass, double total)
    {
        return (pass + 1) / (total + 1) - pass / total;
    }
};
