/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    4001) Aggregate Two Time Series
    ===============================

    ============
    Description:
    ============

    You are given two 2D integer arrays series1 and series2.

    Each element in both series is of the form [timestamp, value], where:

        + timestamp is an integer representing the time.
        + value is an integer representing the value at that timestamp.

    Each array is sorted in strictly increasing order of timestamp.

    For any timestamp not present in a series, its value is taken from the next
    available timestamp in the same series if one exists. Otherwise, its value
    is considered 0.

    The aggregated series is formed by summing the corresponding values from
    both series at every timestamp that appears in either series.

    Return the aggregated series as a 2D integer array of [timestamp,
    summedValue] pairs, sorted in strictly increasing order of timestamp.

    ==============================================================================================================
    FUNCTION: vector<vector<int>> aggregateTimeSeries(vector<vector<int>>& series1, vector<vector<int>>& series2);
    ==============================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: series1 = [[1,3],[4,1]], series2 = [[2,2],[5,2]]
    Output: [[1,5],[2,3],[4,3],[5,2]]
    Explanation:
    Timestamp    series1    series2    summedValue
       1            3          2          5
       2            1          2          3
       4            1          2          3
       5            0          2          2

    Thus, the aggregated series is [[1, 5], [2, 3], [4, 3], [5, 2]].


    --- Example 2 ---
    Input: series1 = [[1,5],[3,1]], series2 = [[2,2]]
    Output: [[1,7],[2,3],[3,1]]
    Explanation:
    Timestamp    series1    series2    summedValue
        1           5          2           7
        2           1          2           3
        3           1          0           1

    Thus, the aggregated series is [[1, 7], [2, 3], [3, 1]].


    --- Example 3 ---
    Input: series1 = [[1,5]], series2 = [[1000000000,2]]
    Output: [[1,7],[1000000000,2]]
    Explanation:
    At timestamp 1, the next available value in series2 is 2 at timestamp
    1000000000. At timestamp 1000000000, there is no later timestamp in
    series1, so its value is 0. Only timestamps that appear in at least one of
    the two series are included.


    *** Constraints ***
    1 <= series1.length, series2.length <= 10^5
    series1[i].length == series2[i].length == 2
    1 <= series1[i][0], series2[i][0] <= 10^9
    1 <= series1[i][1], series2[i][1] <= 10^9
    Each series is sorted in strictly increasing order of timestamp.

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;


/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N + M) */
class Solution {
public:
    vector<vector<int>> aggregateTimeSeries(vector<vector<int>>& series1, vector<vector<int>>& series2)
    {
        const int N = series1.size();
        const int M = series2.size();

        vector<vector<int>> result;
        result.reserve(N + M); // To prevent repeated reallocations

        int value1 = 0;
        int value2 = 0;

        while ( ! series1.empty() ||  ! series2.empty())
        {
            int timestamp = max(series1.empty() ? INT_MIN : series1.back()[0],
                                series2.empty() ? INT_MIN : series2.back()[0]);

            if ( ! series1.empty() && series1.back()[0] == timestamp)
            {
                value1 = series1.back()[1];
                series1.pop_back();
            }

            if ( ! series2.empty() && series2.back()[0] == timestamp)
            {
                value2 = series2.back()[1];
                series2.pop_back();
            }

            result.push_back( {timestamp, value1 + value2} );
        }

        /* Reverse */
        reverse(result.begin(), result.end());

        return result;
    }
};




/* Time  Complexity: O((N + M) * (logN + logM)) */
/* Space Complexity: O(N + M)                   */
class Solution_2 {
public:
    vector<vector<int>> aggregateTimeSeries(vector<vector<int>>& series1, vector<vector<int>>& series2)
    {
        const int N = series1.size();
        const int M = series2.size();

        vector<vector<int>> result;
        result.reserve(N + M); // To prevent repeated reallocations

        int left  = 0;
        int right = 0;

        while (left < N || right < M)
        {
            vector<int> dummy_vec = {INT_MAX, INT_MAX};
            
            vector<int> one = left  < N ? series1[left]  : dummy_vec;
            vector<int> two = right < M ? series2[right] : dummy_vec;

            if (one[0] == two[0])
            {
                result.push_back( {one[0], one[1] + two[1]} );
                
                ++left;
                ++right;
                continue;
            }

            if (one[0] < two[0])
            {
                auto it = lower_bound(series2.begin(), series2.end(), vector<int>{one[0], INT_MIN},
                    [](const vector<int>& a, const vector<int>& b) {
                        return a[0] < b[0];
                    });

                result.push_back( {one[0], one[1] + (it != series2.end() ? (*it)[1] : 0)} );

                ++left;
            }
            else
            {
                 auto it = lower_bound(series1.begin(), series1.end(), vector<int>{one[0], INT_MIN},
                    [](const vector<int>& a, const vector<int>& b) {
                        return a[0] < b[0];
                    });

                result.push_back( {two[0], (it != series1.end() ? (*it)[1] : 0) + two[1]} );
                
                ++right;
            }
        }

        return result;
    }
};


class Solution_3 {
private:
    static vector<vector<int>> result;

public:
    vector<vector<int>> aggregateTimeSeries(vector<vector<int>>& series1, vector<vector<int>>& series2)
    {
        const int N = series1.size();
        const int M = series2.size();
        int idx = 0;

        /* Add a "sentinel" value */
        series1.push_back( {1 << 30, 0} );
        series2.push_back( {1 << 30, 0} );

        int left  = 0;
        int right = 0;


        while (left < N || right < M)
        {
            int timestamp = min(series1[left][0], series2[right][0]);

            result[idx][0] = timestamp;
            result[idx][1] = series1[left][1] + series2[right][1];

            if (series1[left][0] == timestamp)
                ++left;

            if (series2[right][0] == timestamp)
                ++right;

            // Increment
            ++idx;
        }

        return vector<vector<int>>(result.begin(), result.begin() + idx);
    }
};


