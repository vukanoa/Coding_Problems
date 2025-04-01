/*
    ============
    === EASY ===
    ============

    ===================================
    3162) Find the Number of Good Pairs
    ===================================

    ============
    Description:
    ============

    You are given 2 integer arrays nums1 and nums2 of lengths n and m
    respectively. You are also given a positive integer k.

    A pair (i, j) is called good if nums1[i] is divisible by nums2[j] * k
    (0 <= i <= n - 1, 0 <= j <= m - 1).

    Return the total number of good pairs.

    ===========================================================================
    FUNCTION: int numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,3,4], nums2 = [1,3,4], k = 1
    Output: 5
    Explanation:
    The 5 good pairs are (0, 0), (1, 0), (1, 1), (2, 0), and (2, 2).

    --- Example 2 ---
    Input: nums1 = [1,2,4,12], nums2 = [2,4], k = 3
    Output: 2
    Explanation:
    The 2 good pairs are (3, 0) and (3, 1).

    *** Constraints ***
    1 <= n, m <= 50
    1 <= nums1[i], nums2[j] <= 50
    1 <= k <= 50

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Because of the extremely small Constraints, we're allowed to perform a
    Brute-Force.

    However, the proper way to do this is found in the 2nd Solution below.

*/

/* Time  Beats: 18.30% */
/* Space Beats: 45.00% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(1)     */
class Solution_Brute_Force {
public:
    int numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k)
    {
        const int N = nums1.size();
        const int M = nums2.size();

        int result = 0;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (nums1[i] % (nums2[j] * k) == 0)
                    result++;
            }
        }
        

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    (This is the Solution of the 2nd(II) version of this problem. The only
     difference is the Constraints. Check out: LeetCode 3164)

    Very first thing we need to do is: Get the factors of each number in nums1.

    How do we get all the factors of a number?

        Loop from 1 to sqrt(number).

    Why?
    Because if you were to loop from 1 to number, for each number, you'd get a
    TLE.

    Constraints say that:
        1. nums1[i] are from 1 to 10^6, and
        2. nums1.size() is 10^5

    Therefore, that would be 10^11, which is even bigger than O(N * M) which
    also gives TLE.

    (If 10^10 gives TLE, then 10^11 would as well)

    Also, that's not the only reason. You'll see that we DON'T NEED to go past
    sqrt(number).

    Let's explain why.

    lets say we have number = 12. These are all the factors of it:

         1  * 12 = 12
         2  *  6 = 12
         3  *  4 = 12
         4  *  3 = 12
         6  *  2 = 12
        12  *  1 = 12

        factors = [1, 2, 3, 4, 6, 12]

    Do you notice a REPEATING pattern?
    After 3 * 4, factors are REPEATING(since multiplication is commutative)

    We had pairs:

        (1, 12)
        (2,  6)
        (3,  4)

    And now after pair (3, 4) if you observe carefully, we'll have ALL OF THE
    SAME PAIRS, but in reveresed order. However since multiplication is
    commutative, that means it's the same.

    In other words:   3 * 4  <==> 4 * 3

    Therefore, we say it's repeating.


    Now, we're going to iterate through each number in nums1 and we'll get all
    of the factors of each number and we'll count the frequency of each factor.

    To be more precise, if we had:

        nums1 = [4, 8]

    Both 6 and 9 have a factor of 3, right?
    Therefore, in our HashMap, we'll have:

             Hash Map
         (factor)  (freq)
        |  Key  :  Value |
        +----------------+
        |   3   :    2   |
        +----------------+


    And then the last step is to simply iterate through nums2 and if th current
    number in nums2 is present in our HashMap of factors, then add its freq to
    result.



    Let's look at one example:

        nums1 = [10,20,30]
        nums2 = [5,15]
        k = 2


    Get all of the factors of each number in nums1:

        10 -> 1, 2, 5, 10
        20 -> 1, 2, 5, 10, 20
        30 -> 1, 3, 5, 10, 15, 30


    Store in our HashMap
             Hash Map
         (factor)  (freq)
        |  Key  :  Value |
        +----------------+
        |   1   :    3   |
        +----------------+
        |   2   :    2   |
        +----------------+
        |   3   :    1   |
        +----------------+
        |   5   :    3   |
        +----------------+
        |  10   :    3   |
        +----------------+
        |  15   :    1   |
        +----------------+
        |  20   :    1   |
        +----------------+
        |  30   :    1   |
        +----------------+


    Now loop through nums2 = [5,15]:

        j=0) nums2[0] = 5

             Factor 5 appears as a factor in 3 numbers(Look at the freq of HashMap)
             Therefore: result += 3



        j=1) nums2[1] = 15

            Factor 15 appears as a factor in 1 number(Look at the freq of Hashmap)
            Therefore: result += 1



    Result: 3 + 1 = 4

    That's it.

*/

/* Time  Beats: 34.31% */
/* Space Beats: 48.54% */

/* Time  Complexity: O(N * sqrt(M) + M) */
/* Space Complexity: O(M)               */
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k)
    {
        const int N = nums1.size();
        const int M = nums2.size();
        long long result = 0;

        unordered_map<int,int> umap;

        for (const auto& number : nums1)
        {
            for(int f = 1; f * f <= number; f++)
            {
                if (f * f == number)
                {
                    umap[f]++;
                }
                else if (number % f == 0)
                {
                    umap[f]++;
                    umap[number / f]++;
                }
            }

        }

        for (int j = 0; j < M; j++)
        {
            long long num = nums2[j] * k;

            if (umap[nums2[j] * k] > 0)
                result += umap[num];
        }

        return result;
    }
};
