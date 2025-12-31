/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2039) The time when the Network becomes Idle
    ============================================

    ============
    Description:
    ============

    There is a network of n servers, labeled from 0 to n - 1. You are given a
    2D integer array edges, where edges[i] = [ui, vi] indicates there is a
    message channel between servers ui and vi, and they can pass any number of
    messages to each other directly in one second. You are also given a
    0-indexed integer array patience of length n.

    All servers are connected, i.e., a message can be passed from one server to
    any other server(s) directly or indirectly through the message channels.

    The server labeled 0 is the master server. The rest are data servers. Each
    data server needs to send its message to the master server for processing
    and wait for a reply. Messages move between servers optimally, so every
    message takes the least amount of time to arrive at the master server. The
    master server will process all newly arrived messages instantly and send a
    reply to the originating server via the reversed path the message had gone
    through.

    At the beginning of second 0, each data server sends its message to be
    processed. Starting from second 1, at the beginning of every second, each
    data server will check if it has received a reply to the message it sent
    (including any newly arrived replies) from the master server:

    If it has not, it will resend the message periodically. The data server i
    will resend the message every patience[i] second(s), i.e., the data server
    i will resend the message if patience[i] second(s) have elapsed since the
    last time the message was sent from this server. Otherwise, no more
    resending will occur from this server.

    The network becomes idle when there are no messages passing between servers
    or arriving at servers.

    Return the earliest second starting from which the network becomes idle.

    ====================================================================================
    FUNCTION: int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[0,1],[1,2]], patience = [0,2,1]
    Output: 8
    Explanation:
    At (the beginning of) second 0,
    - Data server 1 sends its message (denoted 1A) to the master server.
    - Data server 2 sends its message (denoted 2A) to the master server.

    At second 1,
    - Message 1A arrives at the master server. Master server processes message 1A instantly and sends a reply 1A back.
    - Server 1 has not received any reply. 1 second (1 < patience[1] = 2) elapsed since this server has sent the message, therefore it does not resend the message.
    - Server 2 has not received any reply. 1 second (1 == patience[2] = 1) elapsed since this server has sent the message, therefore it resends the message (denoted 2B).

    At second 2,
    - The reply 1A arrives at server 1. No more resending will occur from server 1.
    - Message 2A arrives at the master server. Master server processes message 2A instantly and sends a reply 2A back.
    - Server 2 resends the message (denoted 2C).
    ...
    At second 4,
    - The reply 2A arrives at server 2. No more resending will occur from server 2.
    ...
    At second 7, reply 2D arrives at server 2.

    Starting from the beginning of the second 8, there are no messages passing between servers or arriving at servers.
    This is the time when the network becomes idle.


    --- Example 2 ---
    Input: edges = [[0,1],[0,2],[1,2]], patience = [0,10,10]
    Output: 3
    Explanation: Data servers 1 and 2 receive a reply back at the beginning of second 2.
    From the beginning of the second 3, the network becomes idle.


    *** Constraints ***
    n == patience.length
    2 <= n <= 10^5
    patience[0] == 0
    1 <= patience[i] <= 10^5 for 1 <= i < n
    1 <= edges.length <= min(10^5, n * (n - 1) / 2)
    edges[i].length == 2
    0 <= ui, vi < n
    ui != vi
    There are no duplicate edges.
    Each server can directly or indirectly reach another server.

*/

#include <climits>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.25% */
/* Space Beats: 76.67% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience)
    {
        const int N = patience.size();

        vector<int> shortest_distance(N, INT_MAX);
        vector<vector<int>> adj_list(N);

        // Build an Adjacency List
        for (auto& edge : edges)
        {
            int server_u = edge[0];
            int server_v = edge[1];

            adj_list[server_u].push_back(server_v);
            adj_list[server_v].push_back(server_u);
        }

        // BFS to find shortest path from master server (0) to all servers
        queue<int> queue;
        queue.push(0);

        vector<bool> visited(N, false);
        visited[0] = true;

        int distance = 0;
        /* BFS */
        while ( ! queue.empty())
        {
            int level_size = queue.size();
            for (int i = 0; i < level_size; i++)
            {
                int curr_server = queue.front();
                queue.pop();

                shortest_distance[curr_server] = distance;

                for (auto neighbor_server : adj_list[curr_server])
                {
                    if ( ! visited[neighbor_server])
                    {
                        queue.push(neighbor_server);
                        visited[neighbor_server] = true;
                    }
                }
            }
            distance++;
        }

        // Find the slowest completion time
        int slowest_completion_time = 0;
        for (int server_id = 1; server_id < N; server_id++)
        {
            int round_trip_time = shortest_distance[server_id] * 2; // To master and back
            int last_send_time  = round_trip_time - 1;

            int num_resends = last_send_time / patience[server_id];
            int completion_time = round_trip_time + num_resends * patience[server_id];
            slowest_completion_time = max(slowest_completion_time, completion_time);
        }

        return slowest_completion_time + 1;
    }
};
