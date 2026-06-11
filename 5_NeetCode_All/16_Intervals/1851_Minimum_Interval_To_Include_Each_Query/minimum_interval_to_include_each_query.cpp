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

#include <climits>
#include <set>
#include <unordered_map>
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




/*
    ------------
    --- IDEA ---
    ------------


    Here the idea is kind of inverted. We keep all queries sorted inside a
    std::set:

        {queries[j], j}         // (a Red-Black ree)

    Then we iterate through the intervals, which we have previously sorted by
    LENGTH.

    For each interval, we perform a binary search, i.e. a lower_bound, using:

        {start, 0}

    where 0 is a dummy value that allows us to perform lower_bound on pairs.

    Since the queries are stored in a std::set, if lower_bound finds a query
    such that query <= end (this is important for the subsequent checks), we
    can immediately store the length of the current interval as the answer for
    that query. This works because we sorted the intervals from shortest to
    longest.

    After removing the iterator that points to the smallest query contained
    within the current interval, we increment the iterator so that it points to
    the next SMALLEST query that MAY also belong to this interval.

    As long as this condition holds, we keep repeating process--the one
    described in two paragraphs above--inside a while loop.

*/

/* Time  Beats: 39.43% */
/* Space Beats: 35.17% */

/* Time  Complexity: O(N * logN  +  N * logQ  +  Q * logQ) */
/* Space Complexity: O(Q)                                  */
class Solution_Ordered_Set_Greedy {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries)
    {
        const int N = intervals.size();
        const int Q = queries.size();

        vector<int> result(queries.size(), -1);

        /* Sort by SIZE of intervals */
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            return a[1] - a[0] < b[1] - b[0];
        });

        set<pair<int, int>> q_val_and_orig_idx;
        for (int j = 0; j < Q; ++j)
            q_val_and_orig_idx.insert( {queries[j], j} );

        for (int i = 0; i < N; i++)
        {
            const int& start = intervals[i][0];
            const int& end   = intervals[i][1];

            auto iter = q_val_and_orig_idx.lower_bound( {start, 0} );
            // iter->first   <==>  query_value
            // iter->second  <==>  query_orig_idx

            while (iter != q_val_and_orig_idx.end() && iter->first <= end)
            {
                result[iter->second] = end - start + 1;

                q_val_and_orig_idx.erase(iter++);
            }
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

/* Time  Beats: 12.76% */
/* Space Beats: 6.67%  */

/* Time  Complexity: O((N + Q) * logN) */
/* Space Complexity: O(N + Q)          */
class Solution_Line_Sweep {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries)
    {
        const int N = intervals.size();
        const int Q = queries.size();
        vector<int> result(Q, -1);

        vector<vector<int>> events; // {point, type, length, original_idx}

        // Push intervals to "events"
        for (int i = 0; i < N; i++)
        {
            const int& start = intervals[i][0];
            const int& end   = intervals[i][1];

            int interval_len = end - start + 1;

            events.push_back( {start, 0, interval_len, i} );
            events.push_back( {end  , 2, interval_len, i} );
        }

        // Push queries to "events" as well. They will be denoted with a 1.
        for (int j = 0; j < Q; j++)
            events.push_back( {queries[j], 1, 1, j} );

        // Sort by time and type
        sort(events.begin(), events.end(), [](const auto& a, const auto& b) {
            if (a[0] == b[0])
                return a[1] < b[1]; // This sorts by TYPE if starting times
                                    // are equal

            return a[0] < b[0];
        });

        // Min heap [length, orig_idx]
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;

        vector<bool> inactive_intervals(N, false);

        for (const auto& event : events)
        {
            const int& point    = event[0];
            const int& type     = event[1];
            const int& length   = event[2];
            const int& orig_idx = event[3];

            if (type == 0) // Interval start
            {
                min_heap.push( {length, orig_idx} );
            }
            else if (type == 2) // Interval end
            {
                inactive_intervals[orig_idx] = true;
            }
            else // Query
            {
                while ( ! min_heap.empty() && inactive_intervals[min_heap.top().second])
                    min_heap.pop();

                if ( ! min_heap.empty())
                    result[orig_idx] = min_heap.top().first;
                else
                    result[orig_idx] = -1; // Just to be explicit
            }
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

/* Time  Beats:  6.68% */
/* Space Beats: 10.64% */

/* Time  Complexity: O((N + Q) * log(N + Q)) */
/* Space Complexity: O(N + Q)                */
class SegTree {
private:
    int n;
    vector<int> tree;
    vector<int> lazy;

public:
    SegTree(int n)
        : n(n)
    {
        tree.resize(4 * n, INT_MAX);
        lazy.resize(4 * n, INT_MAX);
    }

    void update(int q_L, int q_R, int val)
    {
        update(0, 0, n-1, q_L, q_R, val);
    }

    int RMQ(int q_L, int q_R)
    {
        return RMQ(0, 0, n-1, q_L, q_R);
    }

private:
    void push(int node, int start, int end)
    {
        if (lazy[node] == INT_MAX)
            return;

        tree[node] = min(tree[node], lazy[node]);

        if (start != end)
        {
            int L_child = 2 * node + 1;
            int R_child = 2 * node + 2;

            lazy[L_child] = min(lazy[L_child], lazy[node]);
            lazy[R_child] = min(lazy[R_child], lazy[node]);
        }

        lazy[node] = INT_MAX;
    }

    void update(int node, int start, int end, int q_L, int q_R, int val)
    {
        push(node, start, end);

        if (q_L <= start && end <= q_R) // Total Overlap
        {
            lazy[node] = min(lazy[node], val);
            push(node, start, end);
            return;
        }

        if (q_R < start || end < q_L) // No Overlap
            return;

        int L_child = 2 * node + 1;
        int R_child = 2 * node + 2;

        int mid = start + (end - start) / 2;

        update(L_child, start, mid, q_L, q_R, val);
        update(R_child, mid+1, end, q_L, q_R, val);

        tree[node] = min(tree[L_child], tree[R_child]);
    }

    int RMQ(int node, int start, int end, int q_L, int q_R)
    {
        push(node, start, end);

        if (q_L <= start && end <= q_R) // Total Overlap
            return tree[node];

        if (q_R < start || end < q_L) // No Overlap
            return INT_MAX;

        int L_child = 2 * node + 1;
        int R_child = 2 * node + 2;

        int mid = start + (end - start) / 2;

        return min(RMQ(L_child, start, mid, q_L, q_R),
                   RMQ(R_child, mid+1, end, q_L, q_R));
    }
};

class Solution_Segment_Tree {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries)
    {
        vector<int> result;

        vector<int> points;
        for (const auto& interval : intervals)
        {
            points.push_back(interval[0]);
            points.push_back(interval[1]);
        }

        for (const auto& query : queries)
            points.push_back(query);

        const int POINTS_SIZE = points.size();

        /* Sort in ASCENDING order first by start, then by end */
        sort(points.begin(), points.end());

        points.erase(unique(points.begin(), points.end()), points.end());

        unordered_map<int, int> compressed_idx;
        for (int idx = 0; idx < POINTS_SIZE; idx++)
            compressed_idx[points[idx]] = idx;

        SegTree seg_tree(POINTS_SIZE);

        for (const auto& interval : intervals)
        {
            int start = compressed_idx[interval[0]];
            int end   = compressed_idx[interval[1]];

            int interval_len = interval[1] - interval[0] + 1;

            seg_tree.update(start, end, interval_len);
        }

        for (const auto& query : queries)
        {
            int compressed_query = compressed_idx[query];

            int len = seg_tree.RMQ(compressed_query,
                                   compressed_query);

            result.push_back(len == INT_MAX ? -1 : len);
        }

        return result;
    }
};
