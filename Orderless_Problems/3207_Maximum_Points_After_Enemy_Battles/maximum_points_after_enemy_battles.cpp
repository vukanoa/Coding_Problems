/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    3207) Maximum Points After Enemy Battles
    ========================================

    ============
    Description:
    ============

    You are given an integer array enemyEnergies denoting the energy values of
    various enemies.

    You are also given an integer currentEnergy denoting the amount of energy
    you have initially.

    You start with 0 points, and all the enemies are unmarked initially.

    You can perform either of the following operations zero or multiple times
    to gain points:

        + Choose an unmarked enemy, i, such that
          currentEnergy >= enemyEnergies[i]. By choosing this option:

            + You gain 1 point.

            + Your energy is reduced by the enemy's energy,
              i.e. currentEnergy = currentEnergy - enemyEnergies[i].


        If you have at least 1 point, you can choose an unmarked enemy, i.
        By choosing this option:
            + Your energy increases by the enemy's energy,
              i.e. currentEnergy = currentEnergy + enemyEnergies[i].

            + The enemy i is marked.


    Return an integer denoting the maximum points you can get in the end by
    optimally performing operations.

    =================================================================================
    FUNCTION: long long maximumPoints(vector<int>& enemyEnergies, int currentEnergy);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: enemyEnergies = [3,2,2], currentEnergy = 2
    Output: 3
    Explanation:
    The following operations can be performed to get 3 points, which is the maximum:
        First operation on enemy 1: points increases by 1, and currentEnergy
        decreases by 2. So, points = 1, and currentEnergy = 0.

        Second operation on enemy 0: currentEnergy increases by 3, and enemy 0
        is marked. So, points = 1, currentEnergy = 3, and marked enemies = [0].

        First operation on enemy 2: points increases by 1, and currentEnergy
        decreases by 2. So, points = 2, currentEnergy = 1, and marked
        enemies = [0].

        Second operation on enemy 2: currentEnergy increases by 2, and enemy 2
        is marked. So, points = 2, currentEnergy = 3, and marked
        enemies = [0, 2].

        First operation on enemy 1: points increases by 1, and currentEnergy
        decreases by 2. So, points = 3, currentEnergy = 1, and marked
        enemies = [0, 2].



    --- Example 2 ---
    Input: enemyEnergies = [2], currentEnergy = 10
    Output: 5
    Explanation: Performing the first operation 5 times on enemy 0 results in
                 the maximum number of points.



    *** Constraints ***
    1 <= enemyEnergies.length <= 10^5
    1 <= enemyEnergies[i] <= 10^9
    0 <= currentEnergy <= 10^9

*/

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    It's more or less a Greedy approach, even if we're used a Heap.

    First or all if the MINIMUM energy from "enemyEnergies" is GREATER than our
    currentEnergy, we should immediately return 0.

    Why?
    Because first step MUST ALWAYS BE to choose an unmarked enemy where:

        currentEnergy >= enemyEnergies[i]

    and by doing that, we gain 1 point.

    This MUST be the first step because we're NOT allowed to perform 2nd option
    UNLESS we had AT LEAST 1 point.

    Therefore, if we're unable to perform the first option at all, we
    immediately quit and return 0.

    If we've successfully passed this first part, then we will create two Heaps
    where one is min_heap and the other is max_heap.

    However our Heaps will be Heaps of pair<int,int> of {val, index} and they
    are going to be "sorted" by "val".

    We need both index and value because we need a quick way to check if some
    enemyEnergy is MARKED or not. We can't do that with only "val" because
    there can be multiple instances of the same "val" within "enemyEnergies".

    Now once we've constructed our two Heaps, we can begin.

    Also it's good to explicitly say this, even if it is written:

        When you're gaining 1 point by subtracting the energy of an unmarked
        enemyEnergy, you DON'T mark it by doing so.

        In other words, you can keep gaining points FROM THE SAME ENERGY by
        subtracting the value of its energy.

        ONLY THE 2ND OPTION ACTUALLY MARKS an enemyEnergy!

    Therefore, we want to take MINIMAL enemyEnergy that is UNMARKED and we want
    to gain as much points as we can before needing to choose 2nd option.

    That's where this line comes in:

                currentEnergy += max_heap.top().first;

    Now, once we are forced to choose a 2nd option, i.e. MINIMAL enemyEnergy
    that is UNMARKED is currently GREATER than our currentEnergy.

    Therefore we must choose 2nd option to regain energy.

    Which enemyEnergy are we going to mark to gain points?
    Of course, the biggest one!

    But by doing so, we MUST somehow mark it. To mark it we're going to use a
    HashSet. And we pop it from max_heap.

    Now that we CERTAINLY have enough energy to gain points again, we choose
    1st option once again.

    However, maybe this minimal enemyEnergy from min_heap is now marked,
    therefore we must check. If it is marked, i.e. it is present in our HashSet
    "marked", we should pop from min_heap and try the next one.

    As long as the minimum from min_heap is MARKED, we are popping.

    That way, we're being essentially being greedy and that's the entire
    solution.

*/

/* Time  Beats: 6.12% */
/* Space Beats: 4.96% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long maximumPoints(vector<int>& enemyEnergies, int currentEnergy)
    {
        const int N = enemyEnergies.size();
        long long result = 0;

        // Edge case
        if (*min_element(enemyEnergies.begin(), enemyEnergies.end()) > currentEnergy)
            return 0;

        unordered_set<int> marked;


        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> min_heap;

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>> max_heap;

        // O(N * logN)
        for (int i = 0; i < N; i++)
        {
            min_heap.push( {enemyEnergies[i], i} );
            max_heap.push( {enemyEnergies[i], i} );
        }

        // Initial
        result++;
        currentEnergy -= min_heap.top().first;

        while ( ! min_heap.empty() && ! max_heap.empty())
        {
            if (min_heap.top().first > currentEnergy)
            {
                currentEnergy += max_heap.top().first;
                marked.insert(max_heap.top().second);

                max_heap.pop();
            }
            else
            {
                while ( ! min_heap.empty() && marked.count(min_heap.top().second))
                    min_heap.pop();

                if (min_heap.empty())
                    break;

                result += currentEnergy / min_heap.top().first;
                currentEnergy = currentEnergy % min_heap.top().first;
            }
        }

        return result;
    }
};
