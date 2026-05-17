/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1306) Jump Game III
    ===========================

    ============
    Description:
    ============

    Given an array of non-negative integers arr, you are initially positioned
    at start index of the array. When you are at index i, you can jump to i +
    arr[i] or i - arr[i], check if you can reach any index with value 0.

    =====
    Note: that you can not jump outside of the array at any time. 
    =====

    =====================================================
    FUNCTION: bool canReach(vector<int>& arr, int start);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [4,2,3,0,3,1,2], start = 5
    Output: true
    Explanation: 
    All possible ways to reach at index 3 with value 0 are: 
    index 5 -> index 4 -> index 1 -> index 3 
    index 5 -> index 6 -> index 4 -> index 1 -> index 3 

    --- Example 2 ---
    Input: arr = [4,2,3,0,3,1,2], start = 0
    Output: true 
    Explanation: 
    One possible way to reach at index 3 with value 0 is: 
    index 0 -> index 4 -> index 1 -> index 3

    --- Example 3 ---
    Input: arr = [3,0,2,1,2], start = 2
    Output: false
    Explanation: There is no way to reach at index 1 with value 0.


    *** Constraints ***
    1 <= arr.length <= 5 * 10^4
    0 <= arr[i] < arr.length
    0 <= start < arr.length

*/

#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple BFS. However "Solution_BFS_2" in this file is a cleaner
    implementation. You shoul look at both in order to appreciate the 2nd one.

*/

/* Time  Beats: 14.73% */
/* Space Beats: 37.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS_1 {
public:
    bool canReach(vector<int>& arr, int start)
    {
        const int N = arr.size();

        if (arr[start] == 0)
            return true;

        queue<int> queue;
        queue.push(start);

        unordered_set<int> visited;
        visited.insert(start);

        while ( ! queue.empty())
        {
            int idx = queue.front();
            queue.pop();


            if (idx + arr[idx] < N && ! visited.count(idx + arr[idx]))
            {
                if (arr[idx + arr[idx]] == 0)
                    return true;

                queue.push(idx + arr[idx]);
                visited.insert(idx + arr[idx]);
            }

            if (idx - arr[idx] >= 0 && ! visited.count(idx - arr[idx]))
            {
                if (arr[idx - arr[idx]] == 0)
                    return true;

                queue.push(idx - arr[idx]);
                visited.insert(idx - arr[idx]);
            }
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  68.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS_2 {
public:
    bool canReach(vector<int>& arr, int start)
    {
        const int N = arr.size();

        queue<int> queue;
        queue.push(start);

        vector<bool> visited(N, false);

        while ( ! queue.empty())
        {
            int i = queue.front();
            queue.pop();

            if (i < 0 || i >= N || visited[i])
                continue;

            if (arr[i] == 0)
                return true;

            visited[i] = true;

            queue.push(i + arr[i]); // Forward
            queue.push(i - arr[i]); // Backward
        }

        return false;
    }
};
