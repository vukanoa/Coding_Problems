#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1029) Two City Scheduling
    ===========================

    ============
    Description:
    ============

    A company is planning to interview 2n people. Given the array costs where
    costs[i] = [aCosti, bCosti], the cost of flying the ith person to city a is
    aCosti, and the cost of flying the ith person to city b is bCosti.

    Return the minimum cost to fly every person to a city such that exactly n
    people arrive in each city.

    ===========================================================
    FUNCTION: int twoCitySchedCost(vector<vector<int>>& costs);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: costs = [[10,20],[30,200],[400,50],[30,20]]
    Output: 110
    Explanation:
    The first person goes to city A for a cost of 10.
    The second person goes to city A for a cost of 30.
    The third person goes to city B for a cost of 50.
    The fourth person goes to city B for a cost of 20.

    The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people
    interviewing in each city.




    --- Example 2 ---
    Input: costs = [[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]
    Output: 1859



    --- Example 3 ---
    Input: costs = [[515,563],[451,713],[537,709],[343,819],[855,779],[457,60],
                    [650,359],[631,42]]
    Output: 3086


    *** Constraints ***
    2 * n == costs.length
    2 <= costs.length <= 100
    costs.length is even.
    1 <= aCosti, bCosti <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    The crux of this Problem is that we must notice that when the absolute
    difference between price A and price B represents the importance of taking
    the lesser price for that person.

    In other words, if, say, John have a BIG difference in price between taking
    the flight A and taking the flight B and, say, Luke has a SMALL difference
    in price between taking the flight A and taking the flight B, then we
    should, obivously, take the preffered one for John, and let Luke have what
    is left since it doesn't matter that much.

    For each person, taking the "correct" flight matters as much as the
    difference in prices between flight A and flight B.

    John had a BIG disparity in prices so it matters a lot to take the cheaper
    one.

    Luke, on the other hand, did not have such a big disparit, therefore he
    should let John pick his cheaper flight and then he can pick the remaining
    one.

    Let's look at an example.

    Example 2:

        [[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]
           511,       394,     259,       45,      722,      108  // abs(A - B)

        Push differences to a Heap alongside with both values A and B.

        It will be a pair of int : pairs

           {difference : {A, B}}

        The the cost where the disparity in price is the biggest and push
        smaller of the two prices.

        Each time you take a price for either A or B, increment A or B,
        respectively.  That way if we find ourselves "done" with all the B
        flights, then all the remaining flights must be assigned to flight A
        cost.

        The max_heap will be ordered by the difference between two prices:

            n = 3
            A = 0, B = 0

            722   B: 118     // A = 0, B = 1
            511   A: 259     // A = 1, B = 1
            394   B: 54      // A = 1, B = 2
            259   B: 667     // A = 1, B = 3  Now we have reached limit for B
            108   A: 577     // A = 2, B = 3  B == n, hence we must use A cost
            45    A: 184     // A = 3, B = 3  B == n, hence We must use A cost
                      ^
                      |
                      |
                      ----------------
                                     |
                                     |
                                     |
        And now just add all these prices together for a total of 1859.

*/

/* Time  Beats:   100% */
/* Space Beats: 28.72% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs)
    {
        std::vector<std::pair<int, std::pair<int, int>>> vec;

        for (auto& cost : costs)
        {
            int A_cost = cost[0];
            int B_cost = cost[1];

            vec.push_back( {std::abs(A_cost - B_cost), {A_cost, B_cost}} );
        }

        std::priority_queue<std::pair<int, std::pair<int, int>>> max_heap(vec.begin(), vec.end());

        int n = costs.size() / 2;
        int A = 0;
        int B = 0;

        int total = 0;

        while (!max_heap.empty())
        {
            auto pair = max_heap.top();
            max_heap.pop();

            int A_cost = pair.second.first;
            int B_cost = pair.second.second;

            if (A < n && B < n)
            {
                total += std::min(A_cost, B_cost);
                A_cost <= B_cost ? A++ : B++;
            }
            else if (A == n)
                total += B_cost;
            else if (B == n)
                total += A_cost;
        }

        return total;
    }
};
