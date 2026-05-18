/*
    ============
    === HARD ===
    ============

    ===========================
    1345) Jump Game IV
    ===========================

    ============
    Description:
    ============

    Given an array of integers arr, you are initially positioned at the first
    index of the array.

    In one step you can jump from index i to index:

        i + 1 where: i + 1 < arr.length.
        i - 1 where: i - 1 >= 0.
        j where: arr[i] == arr[j] and i != j.

    Return the minimum number of steps to reach the last index of the array.

    =====
    Note: that you can not jump outside of the array at any time. 
    =====

    =========================================
    FUNCTION: int minJumps(vector<int>& arr);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
    Output: 3
    Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that
                 index 9 is the last index of the array.

    --- Example 2 ---
    Input: arr = [7]
    Output: 0
    Explanation: Start index is the last index. You do not need to jump.

    --- Example 3 ---
    Input: arr = [7,6,9,6,9,6,9,7]
    Output: 1
    Explanation: You can jump directly from index 0 to index 7 which is last
                 index of the array.


    *** Constraints ***
    1 <= arr.length <= 5 * 10^4
    -10^8 <= arr[i] <= 10^8

*/

#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 83.76% */
/* Space Beats: 97.55% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int minJumps(vector<int>& arr)
    {
        const int N = arr.size();

        vector<bool> visited(N,false);
        unordered_map<int,vector<int>> indices_of_value;

        for (int idx = 0; idx < N; idx++)
            indices_of_value[arr[idx]].push_back(idx);

        queue<int> queue;
        queue.push(0);

        int jumps = 0;

        while ( ! queue.empty())
        {
            int size = queue.size();

            while (size-- > 0)
            {
                int idx = queue.front();
                queue.pop();

                if (idx == N - 1)
                    return jumps;

                if (idx - 1 >= 0 && ! visited[idx - 1]) { queue.push(idx-1); visited[idx-1] = true; }
                if (idx + 1 <  N && ! visited[idx + 1]) { queue.push(idx+1); visited[idx+1] = true; }
                
                for (const auto& matching_value_idx : indices_of_value[arr[idx]])
                {
                    if ( ! visited[matching_value_idx])
                    {
                        queue.push(matching_value_idx);
                        visited[matching_value_idx] = true;
                    }
                }
                
                indices_of_value[arr[idx]].clear();
            }

            jumps++;
        }

        return -1;
    }
};
