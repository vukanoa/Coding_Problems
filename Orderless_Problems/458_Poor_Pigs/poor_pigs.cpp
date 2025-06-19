/*
    ============
    === HARD ===
    ============

    ===========================
    458) Poor Pigs
    ===========================

    ============
    Description:
    ============

    There are buckets buckets of liquid, where exactly one of the buckets is
    poisonous. To figure out which one is poisonous, you feed some number of
    (poor) pigs the liquid to see whether they will die or not. Unfortunately,
    you only have minutesToTest minutes to determine which bucket is poisonous.

    You can feed the pigs according to these steps:

        + Choose some live pigs to feed.

        + For each pig, choose which buckets to feed it. The pig will consume
          all the chosen buckets simultaneously and will take no time. Each pig
          can feed from any number of buckets, and each bucket can be fed from
          by any number of pigs.

        + Wait for minutesToDie minutes. You may not feed any other pigs during
          this time.

        + After minutesToDie minutes have passed, any pigs that have been fed
          the poisonous bucket will die, and all others will survive.

        + Repeat this process until you run out of time.

    Given buckets, minutesToDie, and minutesToTest, return the minimum number
    of pigs needed to figure out which bucket is poisonous within the allotted
    time.

    =========================================================================
    FUNCTION: int poorPigs(int buckets, int minutesToDie, int minutesToTest);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: buckets = 4, minutesToDie = 15, minutesToTest = 15
    Output: 2
    Explanation: We can determine the poisonous bucket as follows:
    At time 0, feed the first pig buckets 1 and 2, and feed the second pig buckets 2 and 3.
    At time 15, there are 4 possible outcomes:
    - If only the first pig dies, then bucket 1 must be poisonous.
    - If only the second pig dies, then bucket 3 must be poisonous.
    - If both pigs die, then bucket 2 must be poisonous.
    - If neither pig dies, then bucket 4 must be poisonous.

    --- Example 2 ---
    Input: buckets = 4, minutesToDie = 15, minutesToTest = 30
    Output: 2
    Explanation: We can determine the poisonous bucket as follows:
    At time 0, feed the first pig bucket 1, and feed the second pig bucket 2.
    At time 15, there are 2 possible outcomes:
    - If either pig dies, then the poisonous bucket is the one it was fed.
    - If neither pig dies, then feed the first pig bucket 3, and feed the second pig bucket 4.
    At time 30, one of the two pigs must die, and the poisonous bucket is the one it was fed.


    *** Constraints ***
    1 <= buckets <= 1000
    1 <= minutesToDie <= minutesToTest <= 100

*/

#include <cmath>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    With 2 pigs, poison killing in 15 minutes, and having 60 minutes, we can
    find the poison in up to 25 buckets in the following way. Arrange the
    buckets in a 5×5 square:

         1  2  3  4  5
         6  7  8  9 10
        11 12 13 14 15
        16 17 18 19 20
        21 22 23 24 25

    Now use one pig to find the row (make it drink from buckets 1, 2, 3, 4, 5,
    wait 15 minutes, make it drink from buckets 6, 7, 8, 9, 10, wait 15
    minutes, etc). Use the second pig to find the column (make it drink
    1, 6, 11, 16, 21, then 2, 7, 12, 17, 22, etc).

    Having 60 minutes and tests taking 15 minutes means we can run four tests.
    If the row pig dies in the third test, the poison is in the third row. If
    the column pig doesn't die at all, the poison is in the fifth column (this
    is why we can cover five rows/columns even though we can only run four
    tests).

    With 3 pigs, we can similarly use a 5×5×5 cube instead of a 5×5 square and
    again use one pig to determine the coordinate of one dimension (one pig
    drinks layers from top to bottom, one drinks layers from left to right, one
    drinks layers from front to back). So 3 pigs can solve up to 125 buckets.

    In general, we can solve up to (⌊minutesToTest / minutesToDie⌋ + 1) pigs
    buckets this way, so just find the smallest sufficient number of pigs.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.35% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int poorPigs(int buckets, int minutes_to_die, int minutes_to_test)
    {
        int pigs = 0;
        int attempts = minutes_to_test / minutes_to_die + 1;

        while (power(attempts, pigs) < buckets)
            pigs++;

        return pigs;
    }

private:
    int power(int base, int exponent)
    {
        int result = 1;

        for (int i = 0; i < exponent; i++)
            result *= base;

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This question can also be done as a combinatorial problem.

    Let us assume that we have p pigs, and our goal is to determine whether
    they can help identify the poisoned bucket with 100% accuracy.

    Now, consider the number of test rounds we are allowed to perform. Each pig
    can be tested every minutesToDie minutes. If the total time available for
    all testing is minutesToTest, then the number of full tests we can
    conduct is:

        T = minutesToTest / minutesToDie



    In each test round, a pig can either die or survive. But since a pig may
    die in the 1st, 2nd, ..., or T-th round--or survive all T rounds--there
    are a total of T + 1 possible outcomes for each pig.

    Therefore, for p pigs, the total number of outcome combinations is:

        (T + 1) * (T + 1) * ... * (T + 1)  [p times] = (T + 1)^p

    Each unique combination of pig outcomes allows us to identify one unique
    bucket. Thus, to be able to distinguish between all N buckets, the number
    of combinations must be at least N. Hence, the condition is:


        (T + 1)^p >= N

    To solve for the minimum number of pigs p, we take the logarithm of both
    sides:

        p >= log(N) / log(T + 1)

    Since p must be an integer (you can't have a fraction of a pig), we take
    the ceiling of the result:

        p = ceil(log(N) / log(T + 1))

    This gives us the minimum number of pigs required to determine the poisoned
    bucket within the given time constraints.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  26.86% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution_Math {
public:
    int poorPigs(int buckets, int poisonTime, int totalTime)
    {
        return ceil(log2(buckets) / log2(totalTime / poisonTime + 1));
    }
};
