#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    1899) Merge Triplets to Form Target Triplet
    ===========================================

    ============
    Description:
    ============

    A triplet is an array of three integers. You are given a 2D integer array
    triplets, where triplets[i] = [ai, bi, ci] describes the ith triplet. You
    are also given an integer array target = [x, y, z] that describes the
    triplet you want to obtain.

    To obtain target, you may apply the following operation on triplets any
    number of times (possibly zero):

        Choose two indices (0-indexed) i and j (i != j) and update triplets[j]
        to become [max(ai, aj), max(bi, bj), max(ci, cj)].  For example, if
        triplets[i] = [2, 5, 3] and triplets[j] = [1, 7, 5], triplets[j] will
        be updated to [max(2, 1), max(5, 7), max(3, 5)] = [2, 7, 5].

    Return true if it is possible to obtain the target triplet [x, y, z] as an
    element of triplets, or false otherwise.

    =================================================================================
    FUNCTION: bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: triplets = [[2,5,3],[1,8,4],[1,7,5]], target = [2,7,5]
    Output: true
    Explanation: Perform the following operations:
    - Choose the first and last triplets [[2,5,3],[1,8,4],[1,7,5]]. Update the
      last triplet to be [max(2,1), max(5,7), max(3,5)] = [2,7,5]. triplets =
      [[2,5,3],[1,8,4],[2,7,5]] The target triplet [2,7,5] is now an element of
      triplets.


    --- Example 2 ---
    Input: triplets = [[3,4,5],[4,5,6]], target = [3,2,5]
    Output: false
    Explanation: It is impossible to have [3,2,5] as an element because there
    is no 2 in any of the triplets.


    --- Example 3 ---
    Input: triplets = [[2,5,3],[2,3,4],[1,2,5],[5,2,3]], target = [5,5,5]
    Output: true Explanation: Perform the following operations:
    - Choose the first and third triplets [[2,5,3],[2,3,4],[1,2,5],[5,2,3]].
      Update the third triplet to be [max(2,1), max(5,2), max(3,5)] = [2,5,5].
      triplets = [[2,5,3],[2,3,4],[2,5,5],[5,2,3]].
    - Choose the third and fourth triplets [[2,5,3],[2,3,4],[2,5,5],[5,2,3]].
      Update the fourth triplet to be [max(2,5), max(5,2), max(5,3)] = [5,5,5].
      triplets = [[2,5,3],[2,3,4],[2,5,5],[5,5,5]].  The target triplet [5,5,5]
      is now an element of triplets.

    *** Constraints ***
    1 <= triplets.length <= 105
    triplets[i].length == target.length == 3
    1 <= ai, bi, ci, x, y, z <= 1000

*/


/* Time  Beats: 13.61% */
/* Space Beats: 25.16% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
private:
    struct HashFunction{
        std::size_t operator() (const std::vector<int>& triplet) const
        {
            int h1 = std::hash<int>() (triplet[0]);
            int h2 = std::hash<int>() (triplet[1]);
            int h3 = std::hash<int>() (triplet[2]);

            return h1 ^ (h2 << 1) & (h3 << 4);
        }
    };

public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target)
    {
        std::unordered_set<std::vector<int>, HashFunction> good_triplets;

        for (auto& t : triplets)
        {
            if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2])
                continue;

            good_triplets.insert(t);
        }

        int count = 0;
        for (int i = 0; i < 3; i++)
        {
            for (auto& triplet : good_triplets)
            {
                if (triplet[i] == target[i])
                {
                    count++;
                    break;
                }
            }
        }

        return count == 3 ? true : false;
    }
};




/* Time  Beats: 86.64% */
/* Space Beats: 40.66% */

/*
    Time  Complexity: O(n)
*/
/*
    Space Complexity: O(1)

    Set "good_triplets" is, at worst(if the result is "true") going to have
    only 3 elements, therefore, since it's a constant, we can say that the
    overall Space Complexity is O(1).
*/
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target)
    {
        std::unordered_set<int> good_triplets;

        for (auto& t : triplets)
        {
            if (t[0] > target[0] || t[1] > target[1] || t[2] > target[2])
                continue;

            for (int i = 0; i < 3; i++)
            {
                if (t[i] == target[i])
                    good_triplets.insert(i);
            }
        }

        return good_triplets.size() == 3 ? true : false;
    }
};
