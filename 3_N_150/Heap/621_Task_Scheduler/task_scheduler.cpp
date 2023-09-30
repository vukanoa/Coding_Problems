#include <iostream>
#include <vector>
#include <queue>

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

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    We don't need the pair {occurences[i], i + 'A'}, but I think it's a bit
    easier to understand what's going on.

    We could just use occurrences[i] in max_heap and pair<int, int> in queue.

    I'll leave it this way, because it's easier to grasp every though C++'s
    syntax makes declarations a bit messy.

*/

/* Time  Beats: 56.43% */
/* Space Beats: 38.58% */

/*
    Time  Complexity: O(tasks.size() * n)

    It's actually O(tasks.size() * n) where 'n' is the "cooldown". However for
    this problerm, since n, at worst, is going to be 100, which is a lot
    smaller than n, we could say that the overall Time Complexity is:
        O(tasks.size()).

    When will this "idle time" worsen our Complexity?
    Imagine that we had this:
    tasks = ['A', 'A', 'A', 'A', 'A', ..., 'A']; and n = 90

    Let's say that there are 10 A's.

    We would, then, process one 'A' and then wait for 90 units, then process
    'A' again and wait another 90(cooldown) and we will continue to repeat this
    until all 10 A's are processed.

    The least amount of time we need to process all the A's is:
        tasks.size() + (n * (tasks.size() - 1));
                       ^                      ^
                       |                      |
                       ------------------------
                              |
    We don't need these parentheses, but it's easier to read.

    Imagine that we had 3 A's and n = 90.

    Process the first A in 1 Unit of time.
    Wait 90 Units of time.
    Process the second A in 1 Unit of time.
    Wait 90 Units of time.
    Process the last A in 1 Unit of time.

    So it's: tasks.size() plus (cooldown multiplied by (tasks.size() - 1))

*/
/*
    Space Complexity: O(1)
    Space is, at worst, going to be O(26) which is a constant time, hence: O(1)
*/
class Solution {
public:
    int leastInterval(std::vector<char>& tasks, int n)
    {
        if (n == 0) // Then we can process them in any order, it doesn't matter
            return tasks.size();

        std::vector<int> occurrences(26, 0);
        std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>> max_heap;
        std::queue<std::pair<int, std::pair<int, char>>> queue;

        // Fill Hash Map of occurrences in O(tasks.size())
        for (char& task : tasks)
            occurrences[task - 'A']++;

        // Fill the Heap in O(26 * log26) --> O(1)
        for (int i = 0; i < 26; i++)
        {
            if (occurrences[i] > 0)
                max_heap.push({occurrences[i], i + 'A'}); // O(log26) --> O(1)
        }

        int time = 0;
        while (!max_heap.empty() || !queue.empty())
        {
            if (!queue.empty() && queue.front().first == time)
            {
                std::pair<int, std::pair<int, char>> queue_pair = queue.front(); // O(1)
                queue.pop(); // O(1)

                max_heap.push(queue_pair.second); // O(log26) --> O(1)
            }

            if (!max_heap.empty())
            {
                std::pair<int, char> heap_pair = max_heap.top(); // O(1)
                max_heap.pop(); // O(log26) --> O(1)

                heap_pair.first--;

                if (heap_pair.first > 0)
                    queue.push({n + time + 1, heap_pair}); // O(1)
            }

            time++;
        }

        return time;
    }
};
