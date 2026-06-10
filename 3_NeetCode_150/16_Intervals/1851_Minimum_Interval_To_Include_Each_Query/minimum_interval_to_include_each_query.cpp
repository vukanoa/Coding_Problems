/*
    ============
    === HARD ===
    ============

    ============================================
    1851) Minimum Interval to Include Each Query
    ============================================

    ============
    Description:
    ============

    You are given a 2D integer array intervals, where intervals[i] = [lefti,
    righti] describes the ith interval starting at lefti and ending at righti
    (inclusive). The size of an interval is defined as the number of integers
    it contains, or more formally righti - lefti + 1.

    You are also given an integer array queries. The answer to the jth query is
    the size of the smallest interval i such that lefti <= queries[j] <=
    righti. If no such interval exists, the answer is -1.

    Return an array containing the answers to the queries.

    ========================================================================================
    FUNCTION: vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries);
    ========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
    Output: [3,3,1,4]
    Explanation: The queries are processed as follows:
    - Query = 2: The interval [2,4] is the smallest interval containing 2. The answer is 4 - 2 + 1 = 3.
    - Query = 3: The interval [2,4] is the smallest interval containing 3. The answer is 4 - 2 + 1 = 3.
    - Query = 4: The interval [4,4] is the smallest interval containing 4. The answer is 4 - 4 + 1 = 1.
    - Query = 5: The interval [3,6] is the smallest interval containing 5. The answer is 6 - 3 + 1 = 4.


    --- Example 2 ---
    Input: intervals = [[2,3],[2,5],[1,8],[20,25]], queries = [2,19,5,22]
    Output: [2,-1,4,6]
    Explanation: The queries are processed as follows:
    - Query = 2: The interval [2,3] is the smallest interval containing 2. The answer is 3 - 2 + 1 = 2.
    - Query = 19: None of the intervals contain 19. The answer is -1.
    - Query = 5: The interval [2,5] is the smallest interval containing 5. The answer is 5 - 2 + 1 = 4.
    - Query = 22: The interval [20,25] is the smallest interval containing 22. The answer is 25 - 20 + 1 = 6.


    *** Constraints ***
    1 <= intervals.length <= 10^5
    1 <= queries.length <= 10^5
    intervals[i].length == 2
    1 <= lefti <= righti <= 10^7
    1 <= queries[j] <= 10^7

*/

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 50.23% */
/* Space Beats: 91.38% */

/* Time  Complexity: O(N * logN  +  Q * logQ) */
/* Space Complexity: O(N         +  Q      )  */
class Solution_Min_Heap {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries)
    {
        const int N = intervals.size();
        const int Q = queries.size();

        vector<int> result(Q, -1);

        /* Sort by start_time in ASCENDING order */
        sort(intervals.begin(), intervals.end()); // O(N * logN)

        vector<pair<int,int>> q_val_and_orig_idx;
        q_val_and_orig_idx.reserve(Q); // To prevent Reallocations

        for (int j = 0; j < Q; j++)
            q_val_and_orig_idx.push_back( {queries[j], j} );

        /* Sort in ASCENDING order */
        sort(q_val_and_orig_idx.begin(), q_val_and_orig_idx.end()); // O(Q * logQ)



        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;

        int i = 0;
        for (const auto& [query_val, query_orig_idx] : q_val_and_orig_idx)
        {
            while (i < N && intervals[i][0] <= query_val)
            {
                const int& start = intervals[i][0];
                const int& end   = intervals[i][1];

                int interval_size = end - start + 1;

                min_heap.push( {interval_size, end} ); // O(logN)

                // Increment
                i++;
            }

            // Pop all the intervals that end STRICTLY BEFORE the query_val
            while ( ! min_heap.empty() && min_heap.top().second < query_val)
                min_heap.pop();

            if ( ! min_heap.empty())
                result[query_orig_idx] = min_heap.top().first;
            else
                result[query_orig_idx] = -1; // Just to be explicit
        }

        return result;
    }
};
