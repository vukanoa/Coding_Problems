/*
    ============
    === HARD ===
    ============

    ================================================
    3414) Maximum Score of Non-Overlapping Intervals
    ================================================

    ============
    Description:
    ============

    You are given a 2D integer array intervals, where intervals[i] = [li, ri,
    weighti]. Interval i starts at position li and ends at ri, and has a weight
    of weighti. You can choose up to 4 non-overlapping intervals. The score of
    the chosen intervals is defined as the total sum of their weights.

    Return the array of at most 4 indices from intervals with maximum score,
    representing your choice of non-overlapping intervals.

    Two intervals are said to be non-overlapping if they do not share any
    points. In particular, intervals sharing a left or right boundary are
    considered overlapping.

    ====================================================================
    FUNCTION: vector<int> maximumWeight(vector<vector<int>>& intervals);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
    Output: [2,3]
    Explanation:
    You can choose the intervals with indices 2, and 3 with respective weights
    of 5, and 3.

    --- Example 2 ---
    Input: intervals = [[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]
    Output: [1,3,5,6]
    Explanation:
    You can choose the intervals with indices 1, 3, 5, and 6 with respective
    weights of 7, 6, 3, and 5.


    *** Constraints ***
    1 <= intevals.length <= 5 * 10^4
    intervals[i].length == 3
    intervals[i] = [li, ri, weighti]
    1 <= li <= ri <= 10^9
    1 <= weighti <= 10^9

*/

#include <algorithm>
#include <map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.35% */
/* Space Beats: 71.74% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();
        long long result = 0LL;
        long long dp_idx = -1;
        long long dp_use = -1;

        int last_end = -1;

        /* Add index (0-based) at the end of each interval */
        for (int i = 0; i < N; i++)
        {
            intervals[i].push_back(i);

            last_end = max(last_end, intervals[i][1]);
        }



        /* Sort */
        sort(intervals.begin(), intervals.end(),
        [](const vector<int>& a, const vector<int>& b)
        {
            if (a[0] == b[0])
                return a[3] < b[3];

            return a[0] < b[0];
        });


        map<int, vector<pair<long long,vector<int>>>> dp;
        dp.insert( {last_end + 1, {{0, {}},
                                   {0, {}},
                                   {0, {}},
                                   {0, {}},
                                   {0, {}}}   } );


        for (int i = N-1; i >= 0; i--)
        {
            const int& start  = intervals[i][0];
            const int& end    = intervals[i][1];
            const int& weight = intervals[i][2];
            const int& index  = intervals[i][3];

            if ( ! dp.count(start))
                dp[start] = {{0, {}}, {0, {}}, {0, {}}, {0, {}}, {0, {}}};

            for (int used = 1; used <= 4; used++)
            {
                auto it = dp.lower_bound(end + 1);
                int next_start = it->first;

                long long candidate = dp[next_start][used - 1].first + weight;

                vector<int> candidate_indices = dp[next_start][used - 1].second;
                candidate_indices.push_back(index);

                /* Sort so LEXICOGRAPHIC comparisons are on INDEX arrays */
                sort(candidate_indices.begin(), candidate_indices.end()); // O(4 * log4) --> O(1)

                if (candidate > dp[start][used].first)
                {
                    dp[start][used].first  = candidate;
                    dp[start][used].second = candidate_indices;
                }
                else if (candidate == dp[start][used].first
                         &&
                         candidate_indices < dp[start][used].second) // Lexicographically smaller
                {
                    dp[start][used].second = candidate_indices;
                }


                if (result < dp[start][used].first
                        ||
                    (result == dp[start][used].first
                     &&
                     dp[start][used].second < dp[dp_idx][dp_use].second))
                {
                    result = dp[start][used].first;

                    dp_idx = start;
                    dp_use = used;
                }
            }

            /* Best solution starting strictly AFTER "start" */
            auto it_skip = dp.upper_bound(start);

            for (int used = 1; used <= 4; used++)
            {
                if (it_skip->second[used].first > dp[start][used].first
                        ||
                    (it_skip->second[used].first == dp[start][used].first
                     &&
                     it_skip->second[used].second < dp[start][used].second))
                {
                    dp[start][used] = it_skip->second[used];
                }
            }
        }

        /* Restore original "intervals" */
        for (int i = 0; i < N; i++)
            intervals[i].pop_back();


        vector<int> result_array = dp[dp_idx][dp_use].second;

        return result_array;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    I'm leaving both Solutions here because it's always nice to see why one
    Solution is better.

    A common "trick" in Interval problems is to try and "Sort by end times".

    If we do exactl that here, then the Solution because many times more
    elegant than the one above. Although both Solutions have the same BigO Time
    and Space Complexities, however the above one is much LESS elegant and has
    more constant facts that are sloving it down unnecessarily.

    Also, since here we're sorting by the "End times", the Solution kind of
    becomes reverse.

    Instead of:
        "best solution starting at/after interval i",

    now it's:
        "the best solution using only the first i intervals"

*/

/* Time  Beats: 60.87% */
/* Space Beats: 71.74% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Sorting_by_End {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();

        /* Add indices to "intervals" */
        for (int i = 0; i < N; i++)
            intervals[i].push_back(i);

        /* Sort */
        sort(intervals.begin(), intervals.end(),
        [](const vector<int>& a, const vector<int>& b)
        {
            return a[1] < b[1];
        });

        vector<int> interval_ends(N);
        for (int i = 0; i < N; i++)
            interval_ends[i] = intervals[i][1];

        vector<pair<long long, vector<int>>> dp(N + 1, {0, {}});
        for (int used = 0; used < 4; used++)
        {
            vector<pair<long long, vector<int>>> new_dp(N + 1, {0, {}});

            for (int i = 1; i <= N; i++)
            {
                const int& start  = intervals[i - 1][0];
                const int& end    = intervals[i - 1][1];
                const int& weight = intervals[i - 1][2];
                const int& index  = intervals[i - 1][3];

                auto it      = lower_bound(interval_ends.begin(), interval_ends.end(), start);
                int prev_idx = it - interval_ends.begin();

                auto take = dp[prev_idx];

                take.first -= weight;
                take.second.insert( upper_bound(take.second.begin(), take.second.end(), index), index);

                new_dp[i] = min(take, new_dp[i - 1]);
            }

            dp = std::move(new_dp);
        }

        /* Restore original "intervals" */
        for (int i = 0; i < N; i++)
            intervals[i].pop_back();

        return dp[N].second;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Elegant as above, but actually matches the first Solution in this file much
    more since it sorts by START as well.

    I wanted to first include the one with "sort by end" since that is a common
    theme in "interval" problems.

*/

/* Time  Beats: 66.30% */
/* Space Beats: 71.74% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Sorting_by_Start {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals)
    {
        const int N = intervals.size();

        /* Add indices to "intervals" */
        for (int i = 0; i < N; i++)
            intervals[i].push_back(i);

        /* Sort */
        sort(intervals.begin(), intervals.end(),
        [](const vector<int>& a, const vector<int>& b)
        {
            return a[0] < b[0];
        });

        vector<int> interval_starts(N);
        for (int i = 0; i < N; i++)
            interval_starts[i] = intervals[i][0];

        vector<pair<long long, vector<int>>> dp(N + 1, {0, {}});
        for (int used = 0; used < 4; used++)
        {
            vector<pair<long long, vector<int>>> new_dp(N + 1, {0, {}});

            for (int i = N - 1; i >= 0; i--)
            {
                const int& start  = intervals[i][0];
                const int& end    = intervals[i][1];
                const int& weight = intervals[i][2];
                const int& index  = intervals[i][3];

                auto it = upper_bound(interval_starts.begin(), interval_starts.end(), end);
                int next_idx = it - interval_starts.begin();

                auto take = dp[next_idx];

                take.first -= weight;
                take.second.insert( upper_bound(take.second.begin(), take.second.end(), index), index);

                new_dp[i] = min(take, new_dp[i + 1]);
            }

            dp = std::move(new_dp);
        }

        /* Restore original "intervals" */
        for (int i = 0; i < N; i++)
            intervals[i].pop_back();

        return dp[0].second;
    }
};
