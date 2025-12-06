/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    1093) Statistics from a Large Scale
    ===================================

    ============
    Description:
    ============

    You are given a large sample of integers in the range [0, 255]. Since the
    sample is so large, it is represented by an array count where count[k] is
    the number of times that k appears in the sample.

    Calculate the following statistics:

        + minimum: The minimum element in the sample.

        + maximum: The maximum element in the sample.

        + mean: The average of the sample, calculated as the total sum of all
                elements divided by the total number of elements.

        + median:
            + If the sample has an odd number of elements, then the median is
              the middle element once the sample is sorted.

            + If the sample has an even number of elements, then the median is
              the average of the two middle elements once the sample is sorted.

        + mode: The number that appears the most in the sample. It is
                guaranteed to be unique.

    Return the statistics of the sample as an array of floating-point numbers
    [minimum, maximum, mean, median, mode]. Answers within 10-5 of the actual
    answer will be accepted.

    =========================================================
    FUNCTION: vector<double> sampleStats(vector<int>& count);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: count =
    [0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0]

    Output: [1.00000,3.00000,2.37500,2.50000,3.00000]
    Explanation: The sample represented by count is [1,2,2,2,3,3,3,3].
    The minimum and maximum are 1 and 3 respectively.
    The mean is (1+2+2+2+3+3+3+3) / 8 = 19 / 8 = 2.375.
    Since the size of the sample is even, the median is the average of the two
    middle elements 2 and 3, which is 2.5. The mode is 3 as it appears the most
    in the sample.


    *** Constraints ***
    count.length == 256
    0 <= count[i] <= 10^9
    1 <= sum(count) <= 10^9
    The mode of the sample that count represents is unique.

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

/* Time  Beats: 100.00% */
/* Space Beats:  20.67% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<double> sampleStats(vector<int>& counts)
    {
        double result[5] = {255, 0, 0, 0, 0};

        int total_count = accumulate(counts.begin(), counts.end(), 0);
        int max_count = 0;

        int median_pos1 = (total_count + 1) / 2;
        int median_pos2 = median_pos1 + (total_count % 2 == 0 ? 1 : 0);

        int prefix_sum = 0;

        for (int value = 0; value < static_cast<int>(counts.size()); value++)
        {
            int count_at_value = counts[value];

            if (count_at_value > 0)
            {
                result[0] = min((int)result[0], value);
                result[1] = value;
            }

            result[2] += (double)value * count_at_value / total_count;

            if (prefix_sum < median_pos1 && prefix_sum + count_at_value >= median_pos1)
                result[3] += 1.0 * value / 2;

            if (prefix_sum < median_pos2 && prefix_sum + count_at_value >= median_pos2)
                result[3] += 1.0 * value / 2;

            if (count_at_value > max_count)
            {
                max_count = count_at_value;
                result[4] = value;
            }

            prefix_sum += count_at_value;
        }

        return vector<double>(result, result + 5);
    }
};
