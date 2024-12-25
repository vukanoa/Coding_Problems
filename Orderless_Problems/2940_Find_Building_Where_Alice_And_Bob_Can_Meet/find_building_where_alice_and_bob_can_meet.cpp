/*
    ============
    === HARD ===
    ============

    ================================================
    2940) Find Building Where Alice and Bob Can Meet
    ================================================

    ============
    Description:
    ============

    You are given a 0-indexed array heights of positive integers, where
    heights[i] represents the height of the ith building.

    If a person is in building i, they can move to any other building j if and
    only if i < j and heights[i] < heights[j].

    You are also given another array queries where queries[i] = [ai, bi]. On
    the ith query, Alice is in building ai while Bob is in building bi.

    Return an array ans where ans[i] is the index of the leftmost building
    where Alice and Bob can meet on the ith query. If Alice and Bob cannot move
    to a common building on query i, set ans[i] to -1.

    ==================================================================================================
    FUNCTION: vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries);
    ==================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
    Output: [2,5,-1,5,2]
    Explanation: In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2]. 
    In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5]. 
    In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
    In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
    In the fifth query, Alice and Bob are already in the same building.  
    For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
    For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.

    --- Example 2 ---
    Input: heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
    Output: [7,6,-1,4,6]
    Explanation: In the first query, Alice can directly move to Bob's building since heights[0] < heights[7].
    In the second query, Alice and Bob can move to building 6 since heights[3] < heights[6] and heights[5] < heights[6].
    In the third query, Alice cannot meet Bob since Bob cannot move to any other building.
    In the fourth query, Alice and Bob can move to building 4 since heights[3] < heights[4] and heights[0] < heights[4].
    In the fifth query, Alice can directly move to Bob's building since heights[1] < heights[6].
    For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
    For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.


    *** Constraints ***
    1 <= heights.length <= 5 * 10^4
    1 <= heights[i] <= 10^9
    1 <= queries.length <= 5 * 10^4
    queries[i] = [ai, bi]
    0 <= ai, bi <= heights.length - 1

*/

#include <queue>
#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.62% */
/* Space Beats: 70.70% */

/* Time  Complexity: O(M * logM) */
/* Space Complexity: O(N + M)    */
class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries)
    {
        vector<int> monotonic;
        vector<int> answer(queries.size(), -1);

        vector<vector<pair<int, int>>> new_queries(heights.size());

        for (int i = 0; i < queries.size(); i++)
        {
            int a = queries[i][0]; // Left  query index
            int b = queries[i][1]; // Right query index

            if (a > b)
                swap(a, b); // Left one should ALWAYS be smaller

            if (a == b || heights[b] > heights[a])
                answer[i] = b;
            else
                new_queries[b].push_back( {heights[a], i} ); // So that we can
                                                             // sort by heights[left]
        }

        for (int i = heights.size()-1; i >= 0; i--)
        {
            int monotonic_size = monotonic.size();

            for (auto& [a, query_idx] : new_queries[i])
            {

                int position = search(a, heights, monotonic);

                if (position >= 0 && position < monotonic_size)
                    answer[query_idx] = monotonic[position];
            }

            while ( ! monotonic.empty() && heights[monotonic.back()] <= heights[i])
                monotonic.pop_back();

            monotonic.push_back(i);
        }

        return answer;
    }

private:
    int search(int curr_height, vector<int>& heights, vector<int>& monotonic)
    {
        int left = 0;
        int right = monotonic.size() - 1;

        int position = -1;
        while (left <= right)
        {
            int mid = (left + right) / 2;

            if (curr_height < heights[monotonic[mid]])
            {
                position = max(position, mid);
                left = mid + 1;
            }
            else
                right = mid - 1;
        }

        return position;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 52.87% */
/* Space Beats: 28.03% */

/* Time  Complexity: O(M * logM) */
/* Space Complexity: O(N + M)    */
class Solution_2 {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries)
    {
        vector<int> answer(queries.size(), -1);

        vector<vector<vector<int>>> store_queries(heights.size());
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> max_index;


        // Store the mappings for all queries in storeQueries.
        for (int curr_query = 0; curr_query < queries.size(); curr_query++)
        {
            int a = queries[curr_query][0];
            int b = queries[curr_query][1];

            if (a < b && heights[a] < heights[b])
            {
                answer[curr_query] = b;
            }
            else if (a > b && heights[a] > heights[b])
            {
                answer[curr_query] = a;
            }
            else if (a == b)
            {
                answer[curr_query] = a;
            }
            else
            {
                store_queries[max(a, b)].push_back( {max(heights[a], heights[b]), curr_query} );
            }
        }

        for (int i = 0; i < heights.size(); i++)
        {
            // If the priority queue's minimum pair value is less than the
            // current index of height, it is an answer to the query.
            while ( ! max_index.empty() && max_index.top()[0] < heights[i])
            {
                answer[max_index.top()[1]] = i;
                max_index.pop();
            }

            // Push the with their maximum index as the current index in the
            // priority queue.
            for (auto& element : store_queries[i])
                max_index.push(element);
        }

        return answer;
    }
};