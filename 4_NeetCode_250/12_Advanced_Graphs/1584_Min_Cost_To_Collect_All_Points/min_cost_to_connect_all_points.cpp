/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1584) Min Cost to Connect All Points
    ====================================

    ============
    Description:
    ============

    You are given an array points representing integer coordinates of some
    points on a 2D-plane, where points[i] = [xi, yi].

    The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan
    distance between them: |xi - xj| + |yi - yj|, where |val| denotes the
    absolute value of val.

    Return the minimum cost to make all points connected. All points are
    connected if there is exactly one simple path between any two points.

    ================================================================
    FUNCTION: int minCostConnectPoints(vector<vector<int>>& points);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

      ^
 10 __|       X
  9 __|
  8 __|
  7 __|
  6 __|
  5 __|
  4 __|
  3 __|
  2 __|    X        X
  1 __|
      |
      X-|--|--|--|--|--|--X--|--|--|----->
        1  2  3  4  5  6  7  8  9  10
    Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
    Output: 20
    Explanation:

      ^
 10 __|    ## X
  9 __|    #
  8 __|    #
  7 __|    #
  6 __|    #
  5 __|    #
  4 __|    #
  3 __|    #
  2 __#### X ###### X #####
  1 __#                   #
      #                   #
      X-|--|--|--|--|--|--X--|--|--|----->
        1  2  3  4  5  6  7  8  9  10

    We can connect the points as shown above to get the minimum cost of 20.
    Notice that there is a unique path between every pair of points.




    --- Example 2 ---
    Input: points = [[3,12],[-2,5],[-4,1]]
    Output: 18


    *** Constraints ***
    1 <= points.length <= 1000
    -10^6 <= xi, yi <= 10^6
    All pairs (xi, yi) are distinct.

*/

#include <climits>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Consider Example 1:
        points = [[0,0],[2,2],[3,10],[5,2],[7,0]]


    Convert "points" to adj_list:


             Hash Map

        |  Key  :             Values             | // Values = {cost, node}
        +----------------------------------------+
        |   0   :  {4,1}, {13,2},  {7,3},  {7,4} |
        +----------------------------------------+
        |   1   :  {4,0},  {9,2},  {3,3},  {7,4} |
        +----------------------------------------+
        |   2   : {13,0},  {9,1}, {10,3}, {14,4} |
        +----------------------------------------+
        |   3   :  {7,0},  {3,1}, {10,2},  {4,4} |
        +----------------------------------------+
        |   4   :  {7,0},  {7,1}, {14,2},  {4,3} |
        +----------------------------------------+

    After that, do a TEXTBOOK Prims' Algorithm.
    There isn't much explanation other than that.

    The only difference is that the "distance" part(i.e. the first value in
    pair) is the Manhattan distance and not the weight of the edge given
    beforehand.

    If you don't know about Prim's Algorithm, here is an explanation in a
    nutshell:

    We'll have:
        1. An Unordered Set called "visited"
        2. A Min Heap

    The use of an Unordered Set "visited" is to prevent cycles while we connect
    the edges.

    They have explicitly told us:
        "Return the minimum cost to make all points connected. All points are
         connected if there is exactly one simple path between any two points."

    That means that there are NO CYCLES in that one single path.

    No cycles and one path indicates that this will be a:
        MST - Minimum Spanning Tree

    Since this is a Minimum Spanning Tree, we know we can use a Prim's Algo for
    a MST.

    Actually, what is required of us is literally an example of one use-case of
    Prim's Algorithm.

    Prim's Algorithm works as following:
        1. Initially we'll push node 0 with distance 0 in our min_heap.

           Now we begin the main part of Prim's Algorithm

        2. Since pairs are "sorted" in min_heap by the first value(i.e. dist),
           at each iteration, we are popping the top pair from that min_heap
           and we check if the neighbor node it is connectedd to is present in
           Set "visited".

           If it is present, then we don't want to create that edge since we
           are NOT allowed to have cycles. Pop that one out and try with the
           new pair at the top of the min_heap.

           Do that until you find a neighbor node that is NOT preset in
           min_heap.

        3. Insert that neighbor node(i.e. second value from the pair) in our
           "visited" Hash Set.

        4. Add the "dist"(i.e. manhattan distance, i.e. first value from the
           pair) to our final result.

        5. Push all the edges of the neighbor node that are connected will all
           the nodes that are NOT yet visited.

        6. Do steps from [2, 5] inclusively, until we've added N-1 edges.

    Return "result".

*/

/* Time  Beats: 5.01% */
/* Space Beats: 5.01% */

/* Time  Complexity: O(V^2 * logV) */ // V <==> N
/* Space Complexity: O(V^2)        */
class Solution_Lazy_Prim_Algorithm {
public:
    int minCostConnectPoints(vector<vector<int>>& points)
    {
        const int N = points.size();
        int result = 0;

        unordered_map<int, vector<vector<int>>> adj_list;

        for (int i = 0; i < N; i++)
        {
            int xi = points[i][0];
            int yi = points[i][1];

            for (int j = i+1; j < N; j++)
            {
                int xj = points[j][0];
                int yj = points[j][1];

                int distance = abs(xi - xj) + abs(yi - yj);

                adj_list[i].push_back( {j, distance} );
                adj_list[j].push_back( {i, distance} );
            }
        }

        int start_node = 0;

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push( {0, 0} ); // {distance, neighbor_node}

        unordered_set<int> visited;

        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            const int& distance  = top[0];
            const int& curr_node = top[1];

            if (visited.count(curr_node))
                continue;

            visited.insert(curr_node);
            result += distance;

            for (const auto& neighbor : adj_list[curr_node])
            {
                /* Careful with the ordering! */
                const int& neighbor_node = neighbor[0];
                const int& neighbor_dist = neighbor[1];

                if (visited.count(neighbor_node))
                    continue;

                min_heap.push( {neighbor_dist, neighbor_node} );
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    

*/

/* Time  Beats: 99.59% */
/* Space Beats: 94.81% */

/* Time  Complexity: O(V^2) */
/* Space Complexity: O(V)    */
class Solution_On_The_Fly_Prim_Algorithm {
public:
    int minCostConnectPoints(vector<vector<int>>& points)
    {
        const int N = points.size();
        int result = 0;

        vector<int> dist(N, INT_MAX);
        vector<bool> visit(N, false);
        int edges = 0;

        int curr_node = 0;
        while (edges < N - 1) // There are exactly N-1 edges in a MST
        {
            visit[curr_node] = true;

            int xi = points[curr_node][0];
            int yi = points[curr_node][1];

            int next_node = -1;
            for (int j = 0; j < N; j++)
            {
                if (visit[j])
                    continue;

                int xj = points[j][0];
                int yj = points[j][1];

                int distance = abs(xi - xj) + abs(yi - yj);

                dist[j] = min(dist[j], distance);

                if (next_node == -1 || dist[j] < dist[next_node])
                    next_node = j;
            }

            result += dist[next_node];

            curr_node = next_node;
            edges++;
        }

        return result;
    }
};




///////////////////////////
/// Kruskal's Algorithm ///
///////////////////////////

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.05% */
/* Space Beats: 6.65% */

/* Time  Complexity: O(V^2 * log(V^2)) */ // V <==> n
/* Space Complexity: O(V)              */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    DSU (int n)
    {
        rank.reserve(n);
        parent.reserve(n);

        for (int i = 0; i < n; i++)
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Reverse Ackerman function, practically O(1) */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false; // We did NOT perform a UNION

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true; // We have MERGED(unioned) two components
    }
};

class Solution_Kruskal {
public:
    int minCostConnectPoints(vector<vector<int>>& points)
    {
        const int N = points.size();
        int result = 0;

        vector<vector<vector<int>>> edges(N);
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;

        // O(V^2 * log(V^2)) (entire block)
        for (int i = 0; i < N; i++)
        {
            const int xi = points[i][0];
            const int yi = points[i][1];

            for (int j = i+1; j < N; j++)
            {
                const int xj = points[j][0];
                const int yj = points[j][1];

                int distance = abs(xi - xj) + abs(yi - yj);

                min_heap.push( {distance, i, j} ); // O(log(V^2))
            }
        }

        DSU dsu(N);

        /* Kruskal's Algorithm */
        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            const int& distance = top[0];
            const int& i        = top[1];
            const int& j        = top[2];

            if ( ! dsu.union_components(i, j))
                continue;

            result += distance;
        }

        return result;
    }
};
