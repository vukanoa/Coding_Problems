/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    621) Task Scheduler
    ===========================

    ============
    Description:
    ============

    Given a characters array tasks, representing the tasks a CPU needs to do,
    where each letter represents a different task. Tasks could be done in any
    order. Each task is done in one unit of time. For each unit of time, the
    CPU could complete either one task or just be idle.

    However, there is a non-negative integer n that represents the cooldown
    period between two same tasks (the same letter in the array), that is that
    there must be at least n units of time between any two same tasks.

    Return the least number of units of times that the CPU will take to finish
    all the given tasks.

    ========================================================
    FUNCTION: int leastInterval(vector<char>& tasks, int n);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tasks = ["A","A","A","B","B","B"], n = 2
    Output: 8
    Explanation:
    A -> B -> idle -> A -> B -> idle -> A -> B
    There is at least 2 units of time between any two same tasks.

    --- Example 2 ---
    Input: tasks = ["A","A","A","B","B","B"], n = 0
    Output: 6
    Explanation: On this case any permutation of size 6 would work since n = 0.
    ["A","A","A","B","B","B"]
    ["A","B","A","B","A","B"]
    ["B","B","B","A","A","A"]
    ...
    And so on.

    --- Example 3 ---
    Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
    Output: 16
    Explanation:
    One possible solution is
    A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> idle -> idle -> A -> idle
    -> idle -> A


    *** Constraints ***
    1 <= task.length <= 10^4
    tasks[i] is upper-case English letter.
    The integer n is in the range [0, 100].

*/

#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.43% */
/* Space Beats: 42.44% */

/* Time  Complexity: O(SIZE * log26) --> O(SIZE * 1) --> O(SIZE) */
/* Space Complexity: O(26) ----------------------------> O(1)    */
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n)
    {
        const int SIZE = tasks.size();

        if (n == 0) // Then we can process them in any order, it doesn't matter
            return SIZE;

        int frequency[26] = {0}; // On the STACK

        priority_queue<pair<int, char>, vector<pair<int, char>>> max_heap;
        queue<tuple<int, int, char>> used;

        // O(SIZE)
        for (const char& task_chr : tasks)
            frequency[task_chr - 'A']++;

        // Fill the Heap in O(26 * log26) --> O(1)
        for (int task_id = 0; task_id < 26; task_id++)
        {
            if (frequency[task_id] > 0)
                max_heap.push( {frequency[task_id], task_id + 'A'} ); // O(log26) --> O(1)
        }

        int curr_cycle = 0;
        while ( ! max_heap.empty() || ! used.empty()) // O(SIZE) in total
        {
            if ( ! used.empty() && get<0>(used.front()) == curr_cycle)
            {
                auto [prev_cycle, freq, task_chr] = used.front(); // O(1)
                used.pop(); // O(1)

                max_heap.push( {freq, task_chr} ); // O(log26) --> O(1)
            }

            if ( ! max_heap.empty())
            {
                auto [freq, task_chr] = max_heap.top(); // O(1)
                max_heap.pop(); // O(log26) --> O(1)

                freq--;

                if (freq > 0)
                    used.push( {curr_cycle + n + 1, freq, task_chr} ); // O(1)
                //               ~~~~~~~~~~~~~~~~~~
                //                      ^
                //                      |
                //                      |
                // Can be used again from
            }

            curr_cycle++;
        }

        return curr_cycle;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.43% */

/* Time  Complexity: O(SIZE) */
/* Space Complexity: O(1)    */
class Solution_Greedy {
public:
    int leastInterval(vector<char>& tasks, int n)
    {
        const int SIZE = tasks.size();

        int frequency[26] = {0}; // On the STACK
        for (const char& task_chr : tasks) // O(SIZE)
            frequency[task_chr - 'A']++;

        /* Sort in ASCENDING order */
        sort(begin(frequency), end(frequency)); // O(26 * log 26) --> O(1)

        int max_freq = frequency[25];
        int idle_gaps = (max_freq - 1) * n;

        // O(25) --> O(1)
        for (int i = 24; i >= 0; i--)
            idle_gaps -= min(max_freq - 1, frequency[i]);

        return max(0, idle_gaps) + SIZE;
    }
};
