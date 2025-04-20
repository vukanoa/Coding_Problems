/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    781) Rabbits in Forest
    ===========================

    ============
    Description:
    ============

    There is a forest with an unknown number of rabbits. We asked n rabbits
    "How many rabbits have the same color as you?" and collected the answers in
    an integer array answers where answers[i] is the answer of the ith rabbit.

    Given the array answers, return the minimum number of rabbits that could be
    in the forest.

    ===============================================
    FUNCTION: int numRabbits(vector<int>& answers);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: answers = [1,1,2]
    Output: 5
    Explanation:
    The two rabbits that answered "1" could both be the same color, say red.
    The rabbit that answered "2" can't be red or the answers would be
    inconsistent.
    Say the rabbit that answered "2" was blue. Then there should be 2 other
    blue rabbits in the forest that didn't answer into the array. The smallest
    possible number of rabbits in the forest is therefore 5: 3 that answered
    plus 2 that didn't.


    --- Example 2 ---
    Input: answers = [10,10,10]
    Output: 11


    *** Constraints ***
    1 <= answers.length <= 1000
    0 <= answers[i] < 1000

*/

#include <cmath>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The idea is faitly simple.

    Rabbits that say:"There are X other rabbits that have the same color as me"
    can be grouped together.

    We are assuming rabbits are not lying. Therefore, if two rabbits say that
    there are different number of other rabbits like them in forest, then it's
    safe to assume they are of different colors because otherwise it would mean
    rabbits are lying, which is unreasonable since this is a coding problem.

    However there's one more caveat. Consider this example:

        answers[1,3,2,4,1,1]

    There are three rabbits that say:"There is 1 more like me", meaning them
    and one more.

    Since THREE of them are claiming that then, assuming they're not lying,
    minimum amount of rabbits is 4 then.

    How?

    Three rabbits are saying:"There is 1 more like me". Let's say that the
    first two rabbits are referencing EACH OTHER, that's 2.

    However, we have one more rabbit say:"There is 1 more like me" which is of
    DIFFERENT color than the previous grouped two, and that's another 2.

    Therefore there are 4.

    We should do this for every unique claim.

        "There  is 1 more like me"  : 3
        "There are 3 more like me"  : 1
        "There are 2 more like me"  : 1
        "There are 4 more like me"  : 1


    We create a HashMap:

             Hash Map
          (color)  (freq)
        |  Key  :  Value |
        +----------------+
        |   1   :    3   |
        +----------------+
        |   3   :    1   |
        +----------------+
        |   2   :    1   |
        +----------------+
        |   4   :    1   |
        +----------------+


    But what is the formula?

    It's fairly simple. When some rabbits claims:"There are X more like me",
    that means there are X+1 of them.

    However, if more than X+1 of them claim "There are X more like me", then
    there are more than X+1 of them.

    As we've seen before, if three rabbits claim:"There is 1 more like me",
    there can't be 1+1 one them, because three are claiming that.

    If we assume that first two rabbits that claim:"THere is 1 more like me"
    are referencing each other, then the third one must be in OTHER group, i.e.
    of other color.

    Therefore, the formula is:

        ceil[(how_many_rabbits_claim / (X + 1))] * (X + 1)

    or, more visually:
       ___                     ___
       | how_many_rabbits_claim  |
       | ----------------------  | * (X + 1)
       |       (X + 1)           |


    This ensure that we group as many rabbit as possible as if they were
    referencing each other(the ones that made THE SAME CLAIMS).

    This formula calculates it nicely.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  42.46% */
/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int numRabbits(vector<int>& answers)
    {
        const int N = answers.size();
        int result = 0;

        unordered_map<int,int> umap;
        for (int i = 0; i < N; i++)
            umap[answers[i]]++;

        for (const auto& [color, freq] : umap)
            result += ceil(1.0 * freq / (color + 1)) * (color + 1);

        return result;
    }
};
