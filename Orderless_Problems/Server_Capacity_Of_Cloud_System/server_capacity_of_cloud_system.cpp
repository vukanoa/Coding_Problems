/*

    ============
    Description:
    ============

    The developers at Amazon are working on optimising the capacity of their
    cloud system.
    In the system, there are n servers where the memory capacity of the i-th
    server is represented by the array memory[i].

    A system always contains an even number of servers.
    If the system has 2x servers, then x of them will be primary and the other
    x will be backup servers.

    For each primary server P, there exists a backup server B where the memory
    capacity of B ≥ memory capacity of P.
    The system’s memory capacity is the sum of the memory capacity of all the
    primary servers.

    Given n servers and an array memory, find the maximum system memory
    capacity that can be formed using the n servers.


    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, memory = [1, 2, 1, 2]
    Output: 3
    Explanation:
    Here, we have 4 servers [serverA, serverB, serverC, serverD] having memory
    sizes as [1, 2, 1, 2].

    We can choose serverA and serverB as primary servers, and serverC and
    serverD as their respective backup. The conditions hold true since
    memory[serverC] ≥ memory[serverA] and memory[serverD] ≥ memory[serverB].
    Hence, the maximum system memory capacity is 3.


    --- Example 2 ---
    Input: n = 3, memory[1, 2, 1]
    Output: 1
    Explanation:
    Here, we have 3 servers [serverA, serverB, serverC] having memory sizes as
    [1, 2, 1].

    We can choose serverA as a primary server, and serverB as its respective
    backup server. The conditions hold true since
    memory[serverB] >= memory[serverA]. Hence, the maximum system memory
    capacity is 1.


    --- Example 3 ---
    Input: n = 4, memory = [2, 4, 3, 1, 2]
    Output: 5


    *** Constraints ***
    2 <= n <= 2*10^5
    1 <= size[i] <= 10^9

*/

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long maximumCapacity(int n, vector<int>& memory)
    {
        long long result = 0LL;

        /* Sort */
        sort(memory.begin(), memory.end());

        priority_queue<int> max_heap;
        max_heap.push(memory.back());

        for (int i = n-1; i >= 0; i--)
        {
            if (max_heap.top() >= memory[i])
            {
                result += memory[i];
                max_heap.pop();
            }
            else
                max_heap.push(memory[i]);
        }

        return 0LL;
    }
};
