/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    134) Gas Station
    ===========================

    ============
    Description:
    ============

    There are 'n' gas stations along a circular route, where the amount of gas
    at the i-th is "gas[i]".

    You have a car with an unlimited gas tank and it costs "cost[i]" of gas to
    travel from the i-th station to its next (i + 1)-th station. You begin the
    journey with an empty tank at one of the gas stations.

    Given two integers arrays "gas" and "cost", return the starting gas
    station's index if you can travel around the circuit once in the clockwise
    direction, otherwise return "-1". If there exists a solution, it is
    guaranteed to be unique.

    ======================================================================
    FUNCTION: int canCompleteCircuit(vector<int>& gas, vector<int>& cost);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  gas = [1, 2, 3, 4, 5], cost = [3, 4, 5, 1, 2]
    Output: 3
    Explanation:
    Start at station 3(index 3) and fill up with 4 units of gas.
    Your tank = 0 + 4 = 4;
    Travel to station 4. Your tank = 4 - 1 + 5 = 8
    Travel to station 0. Your tank = 8 - 2 + 1 = 7
    Travel to station 1. Your tank = 7 - 3 + 2 = 6
    Travel to station 2. Your tank = 6 - 4 + 3 = 5
    Travel to station 3. The cost is 5. Your gas is just enough to travel back
    to station 3.
    Therefore, return 3 as the starting index.

    --- Example 2 ---
    Input:  gas = [2, 3, 4], cost = [3, 4, 3]
    Output: -1
    Explanation:
    You can't start at station 0 or 1, as there is not enough gas to travel to
    the next station. Let's start at station 2 and fill up with 4 unit of gas.
    Your tank = 0 + 4 = 4
    Travel to station 0. Your tank = 4 - 3 + 2 = 3
    Travel to station 1. Your tank = 3 - 3 + 3 = 3
    You cannot travel back to station 2, as it requires 4 unit of gas but you
    only have 3.
    Therefore, you can't travel around the circuit once no matter where you
    start.

    *** Constraints ***
    n == gas.length == cost.length
    1 <= n <= 10^5
    0 <= gas[i], cost[i] = 10^4

*/

#include <vector>
#include <numeric> // for accumulate
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First, in order to know whether a solution even exists, we must check
    whether the total amount of gas is greater than the total cost.

    If a solution exists, we are told that it is unique.

    In that case--i.e. if a solution exists--we only need to find the "idx" of
    the first station from which we NEVER drop below 0 until the end of the
    array.

    Why and how is this sufficient?

    If we know that a solution exists, that means that at least 1 index from
    [0, N-1] is a valid solution.

    At every station we refill gas[i] and subtract(consume) cost[i].

    Since we know that at least 1 index from [0, N-1] is a solution, we start
    from index 0.

    We assume that the potential solution, i.e. "starting_idx", is equal to 0
    and begin.

    Also, initially the "tank"(i.e. current amount of gas) is 0.

    Now we start from station "starting_idx" = 0.

    At every station we always first refill gas[i], and then subtract(consume)
    cost[i], i.e.:

        tank += gas[i] - cost[i];

    If--and this is now EXTREMELY important--at ANY moment "tank" becomes < 0,
    that means that CERTAINLY none of the stations BEFORE the current one, nor
    the current one itself, are a solution.

    Formally: no station in the range [0, i] (inclusive), is a solution.

    How do we know that? How can we be certain?

    Let's look at this example:

        gas = [1, 4, 2, 3, 5]
       cost = [2, 3, 4, 1, 1]
               0  1  2  3  4

    First, we immediately see that index 0 is not a solution because the "tank"
    after refilling gas[i] and consuming cost[i] becomes smaller than 0.

    In other words, if we start from station 0, we will not even be able to
    reach station 1.

    Because of that, we reset "tank" back to 0 and set the new potential
    solution:

        starting_idx = 1

    and continue with i = 1.

    When we are at station idx = 1, the current state of "tank" is 0.

    We refill gas[1] and subtract cost[1]:

        tank += gas[1] - cost[1]
        tank += 4      - 3

    Since "tank" >= 0, that means we can reach station idx = 2.

    Now we are at station idx = 2 with "tank" = 1 (this is VERY important)

    We refill gas[2] and subtract cost[2].

        tank += gas[2] - cost[1]
        tank +=  2     -   4
        tank += (-2)

    Since "tank" when entering the station was 1, and after refilling gas[2]
    and subtracting cost[2] the tank is:

        tank = tank + (-2)
        tank =  1   + (-2)
        tank = -1

    This now is the core idea:

    Since tank < 0, that means that if we start from starting_idx=1, we will
    not even be able to reach station idx=3, let alone complete the whole
    circle.

    However, how exactly do we know that not only starting_idx = 1 is not a
    solution, but also that none of the indices [0, i] are solutions?

    First, we know that stations [0, starting_idx - 1] are not solutions
    because we already established that earlier(that is why "starting_idx" is
    where it is)

    However, we also established that station idx = 1 is not a solution because
    "tank" dropped below 0 BEFORE reaching the end of the array.

    But how do we know that some station from:

        [starting_idx + 1, i]

    is not a solution?

    If we start from some station--i.e. if starting_idx is equal to that
    station--then our "tank" is 0.

    However, if we did not START from some station, but instead ARRIVED at it
    by starting from some earlier station, that means that we arrived at this
    station with -- in the WORST case -- "tank" equal to 0.

    In other words, in the WORST case it is as if we started from this station.

    If even then we cannot reach the end of the array, then we know that:

        [starting_idx + 1, i]

    certainly are not stations from which we should start in order to complete
    the whole circle.

    However, we still did not answer why it is sufficient to check only whether
    we can reach the end of the array in order to conclude that it is possible
    to complete the whole circle starting from "starting_idx".

    The reason is very simple. Suppose we had:

         gas = [1, 1, 1, 1, 17]
        cost = [2, 3, 2, 4, 5 ]
                0  1  2  3  4

    At the beginning we established that a solution exists because the total
    amount of gas is greater than the total amount of cost.

    That means at least one station from the range:

        [0, N-1]

    IS a solution. Visually, we can immediately conclude that stations:

        {0, 1, 2, 3}

    are not solutions because starting from any of these stations, we cannot
    even reach the next station, let alone complete the whole circle.

    Since {0, 1, 2, 3} are not solutions, and from station idx=4 we can reach
    the end of the array, and since we know that a solution exists and must
    belong to the set [0, N-1], we conclude that idx=4 IS a solution.

    However, what would happen if we had this example:

         gas = [1, 1, 1, 1, 8, 4, 5]
        cost = [2, 3, 2, 4, 1, 2, 3]

    Again we see that a solution exists because the total "gas" is greater than
    the total cost, and we see that stations {0, 1, 2, 3} are not solutions. If
    we start from station idx = 4, we can reach the end of the array and
    therefore conclude that it is the solution.

    However, how EXACTLY can we claim that idx=4 is the solution, and not some
    later station, e.g. idx=5 or idx=6?

    Mathematically:

    If we have already established that stations:

        [0, idx-1]

    are not solutions, and we see that starting from idx=4 we can reach the end
    of the array, then we can conclude that idx=4 is a solution because later
    stations CERTAINLY cannot reach the end of the array with MORE gas than
    when starting from idx=4.

    How do we know that?

    If we start from "i" we can reach some station "j"(where i < j):

        + either with tank >  0
        + or with tank == 0

    If we start from some station "j", then tank is ALWAYS == 0, which means
    that if we managed to reach the end of the array(starting from "i"), i.e.
    station 0, then maybe some station "j" (j from [i+1, N-1]) could also be a
    solution, but it can CERTAINLY reach station 0 with LESS gas, and at the
    same time we already know that stations [0, i-1] are not solutions,
    therefore if from "i" we managed to reach station 0--We know that it is
    the solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  23.28% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
    {
        const int N = gas.size();

        int gas_sum  = accumulate(gas.begin(),  gas.end(), 0);
        int cost_sum = accumulate(cost.begin(), cost.end(), 0);

        if (gas_sum < cost_sum) // There is NO Solution
            return -1;

        /* There is CERTAINLY a Solution */
        int starting_idx = 0;
        int tank         = 0;

        for (int i = 0; i < N; i++)
        {
            tank += gas[i] - cost[i];

            if (tank < 0)
            {
                tank = 0;
                starting_idx = i + 1;
            }
        }

        return starting_idx;
    }
};
