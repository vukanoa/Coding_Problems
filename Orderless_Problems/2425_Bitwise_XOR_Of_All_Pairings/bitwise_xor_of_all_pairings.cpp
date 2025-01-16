/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2425) Bitwise XOR of All Pairings
    =================================

    ============
    Description:
    ============

    You are given two 0-indexed arrays, nums1 and nums2, consisting of
    non-negative integers. There exists another array, nums3, which contains
    the bitwise XOR of all pairings of integers between nums1 and nums2 (every
    integer in nums1 is paired with every integer in nums2 exactly once).

    Return the bitwise XOR of all integers in nums3.

    =================================================================
    FUNCTION: int xorAllNums(vector<int>& nums1, vector<int>& nums2);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
    Output: 13
    Explanation:
    A possible nums3 array is [8,0,7,2,11,3,4,1,9,1,6,3].
    The bitwise XOR of all these numbers is 13, so we return 13.

    --- Example 2 ---
    Input: nums1 = [1,2], nums2 = [3,4]
    Output: 0
    Explanation:
    All possible pairs of bitwise XORs are nums1[0] ^ nums2[0], nums1[0] ^ nums2[1], nums1[1] ^ nums2[0],
    and nums1[1] ^ nums2[1].
    Thus, one possible nums3 array is [2,5,1,6].
    2 ^ 5 ^ 1 ^ 6 = 0, so we return 0.


    *** Constraints ***
    1 <= nums1.length, nums2.length <= 10^5
    0 <= nums1[i], nums2[j] <= 10^9

*/

#include <iostream>
#include <vector>
using namespace std;



/*
    ------------
    --- IDEA ---
    ------------

    If you don't know much abbout Bit Manipulation, I highly suggest you, at
    least, read a bit about it on Wikipedia.

    However, I'll explain this as if you don't know anything.

    Bitwise XOR is an operation CPU does when it wants to add/subtract/multiply
    elements. Bitwise operations are all CPUs are doing.

    XOR-ing (designated as '^') means that the output is 1 ONLY if the two bits
    differ.

    In other words:
        1 xor 0 = 1
        0 xor 1 = 1

    That's why same bits give 0:
        1 xor 1 = 0
        0 xor 0 = 0


    After you know the absolute basics, now it's handy to know these as well.
    But first, remember this:

        XOR is both COMMUTATIVE and ASSOCIATIVE

    That means that these are the same:

             a ^ b  <==> b ^ a         // Commutative

        a ^ (b ^ c) <==> (a ^ b) ^ c   // Associative

    This property of XOR operation is VERY important.


    Also, it's handy to know these:

        a ^ a = 0      // Any number XORed by itself gives 0

        a ^ 0 = a      // Any number XORed by 0 gives itself

        a ^ a ^ a = a  // Any number XORed with itself ODD number of times
                       // gives ITSELF



    Now that you know this, it won't be that bad, but it's not hyper-intuitive
    at a first glance.

    However, you can realize that there must be some XOR "trick" you didn't
    consider since Constraints for both N and M are 10^5, meaning, if you were
    to do a basic Brute-Force it would be O(n^2) Time Complexity which is most
    certainly inefficient and won't pass all LeetCode tests. It will give you
    a TLE(Time Limit Exceeded).


    So, how can we do it better than O(n^2)?

    Let's revisit our "tricks" from the above and try to see if we can somehow
    use them to our advantage.

    Let's consider only "small" example:

        nums1 = [1, 2, 3]       nums2 = [3, 4]

        We need to XOR 1 with 3, then 1 with 4
        We need to XOR 2 with 3, then 2 with 4
        We need to XOR 3 with 3, then 3 with 4

        Then we need to XOR all of those values together and that is our result


    This is the key observation:

        Since we need to XOR both 3 and 4 with 1, isn't it the same to xor 1
        with the XORed 3 and 4?

         ---------------------
         |                   |
         |  1 ^ 3 = 2 --------
         |  1 ^ 4 = 5 ---
         |              |
         |      ---------
         |      |
         |      v
         -> 2 ^ 5 = 7




            3 ^ 4 = 7   // XORed nums2
                    | 
                -----
                |
                v
            1 ^ 7 = 6


    It seems not. However, we've missed a VERY important point:

        We need to XOR 1 with each element in nums1.

    What happens if there are ODD and what happens when there are EVEN number
    of elements in nums2?

    If there are EVEN number of elements, we can't do what we just did, but
    what if we had ODD number of elements in nums2?

    If we had EVEN number of elements in nums2, as in the above example, then
    of course we won't get the same result.

    But why?
    Because we need to XOR each element in nums2 with 1(and with other elements
    but focus on 1 for now).

    That means we have to do this:

        1 ^ 3 = X
        1 ^ 4 = Y

        then: X ^ Y

    But that's THE SAME as this:

        0 ^ (3 ^ 4)
        ^
        |
     This represents M 1s that are XORed. Remember:     a ^ a = 0
                                                    a ^ a ^ a = a

    Since there are EVEN number of 1s we have to use in our XOR, then we can
    treat it as 0. In that case the total reslut is just all of the nums2
    elements XORed, which is 7.

         ---------------------
         |                   |
         |  1 ^ 3 = 2 --------
         |  1 ^ 4 = 5 ---
         |              |
         |      ---------
         |      |
         |      v
         -> 2 ^ 5 = 7 ----------------------------------------
                                                             |
                                                             |
                                                             v
                                                            SAME
                                                             ^
                                                             |
                                                             |
                                                             |
            3 ^ 4 = 7   // XORed nums2                       |
                    |                                        |
                -----                                        |
                |                                            |
                v                                            |
            0 ^ 7 = 7 ----------------------------------------




    However, what happens if we had ODD number of elements in nums2?
    Then our FIRST approach WORKS! Look at it:

    (Let's try with modified number of elements in M)

                                           we added 5
                                               |
                                               v
        nums1 = [1, 2, 3]       nums2 = [3, 4, 5]
                                         ~~~~~~~~
                                            ^
                                            |
                                          M = 3
    

        Now this is the same:

          ----------------------------
          |                          |
          |  ---------------------   |
          |  |                   |   |
          |  |  1 ^ 3 = 2 --------   |
          |  |  1 ^ 4 = 5 ------------
          |  |  1 ^ 5 = 4 ---
          |  |              |
          |  |          -----
          |  |          |
          |  |          v
          |  -> 2 ^ 5 ^ 4 = 3 ---------------------------------
          |         ^                                         |
          |         |                                         |
          -----------                                         |
                                                              v
                                                            SAME
        As this:                                              ^
                                                              |
            3 ^ 4 ^ 5 = 2  // XORed nums2                     |
                        |                                     |
                ---------                                     |
                |                                             |
                v                                             |
            1 ^ 2 = 3 -----------------------------------------
            ^ 
            |
        We can use only a single '1' because, remember:

            a ^ a ^ a = a
            ~~~~~~~~~
             ODD number of a's XORed together give a

        That's why we don't have to go through EACH element of nums2 and xor it
        with 1. We can just XOR 1 with the totally XORed nums2.

        Now we do this for every element in nums1, while we are XOR-ing it with
        result.


    In the second way(below "As this" comment) it took us only O(M + N),
    whereas the first approach took O(M * N) which is MUCH MUCH slower,
    especially for the given Constraints.


    Now read the Implementation and I'm sure you'll get it. If you don't, then
    read, slowly, this explanation and read the code.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   7.72% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(1)     */
class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        const int N = nums1.size();
        const int M = nums2.size();

        int result = 0;

        int xor_nums2 = 0;
        for (int i = 0; i < M; i++)
            xor_nums2 ^= nums2[i];

        if (M % 2 == 0)
        {
            for (int i = 0; i < N; i++)
                result ^= xor_nums2;
        }
        else
        {
            for (int i = 0; i < N; i++)
                result ^= nums1[i] ^ xor_nums2;
        }

        return result;
    }
};
