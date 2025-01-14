/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    2657) Find the Prefix Common Array of Two Arrays
    ================================================

    ============
    Description:
    ============

    You are given two 0-indexed integer permutations A and B of length n.

    A prefix common array of A and B is an array C such that C[i] is equal to
    the count of numbers that are present at or before the index i in both A
    and B.

    Return the prefix common array of A and B.

    A sequence of n integers is called a permutation if it contains all
    integers from 1 to n exactly once.

    ===============================================================================
    FUNCTION: vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: A = [1,3,2,4], B = [3,1,2,4]
    Output: [0,2,3,4]
    Explanation: At i = 0: no number is common, so C[0] = 0.
    At i = 1: 1 and 3 are common in A and B, so C[1] = 2.
    At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.
    At i = 3: 1, 2, 3, and 4 are common in A and B, so C[3] = 4.

    --- Example 2 ---
    Input: A = [2,3,1], B = [3,1,2]
    Output: [0,1,3]
    Explanation: At i = 0: no number is common, so C[0] = 0.
    At i = 1: only 3 is common in A and B, so C[1] = 1.
    At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.


    *** Constraints ***
    1 <= A.length == B.length == n <= 50
    1 <= A[i], B[i] <= n
    It is guaranteed that A and B are both a permutation of n integers

*/

#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First, we go from the back to check how many characters are the same.
    If all are the same, we return {1, 2, ..., N-1}.

    Else, we fill the right amount of same characters from the first index to
    the right of the one where A and B don't have the same element.

    For example:

        A = [3, 1, 4, 5, 2]
        B = [1, 3, 4, 5, 2]
             0  1  2  3  4


        Index 1 is where A and B don't have the same element(coming from the
        right), therefore last: N - idx_where_they_differ(i.e. 1 in this case)
        element will be:

            idx_where_they_differ + 1, incrementally larger by one each time.

        So C would be:

        B = [0, 0, 3, 4, 5]
             0  1  2  3  4


    And after this small optimization, we can go through each of N elements in
    both A and B and if they are the same, then we just increase C[i-1] by one
    and assign it to C[i]. (if i == 0, then we just assign 1 to it)

    Otherwise we go through the HashSet in which we've already put the current
    element and we manually count how many elements are the same.

*/

/* Time  Beats: 17.06% */
/* Space Beats: 19.65% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n)   */
class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B)
    {
        const int N = A.size();
        vector<int> C(N, 0);

        int x = 0;
        for (x = N-1; x >= 0; x--)
        {
            if (A[x] != B[x])
                break;
        }

        if (x == 0)
        {
            iota(C.begin(), C.end(), 1);
            return C;
        }
        else if (x < N-1)
        {
            iota(C.begin() + x + 1, C.end(), x+2);
        }


        unordered_set<int> uset_A;
        unordered_set<int> uset_B;
        for (int i = 0; i < x+1; i++)
        {
            uset_A.insert(A[i]);
            uset_B.insert(B[i]);

            if (A[i] == B[i])
            {
                if (i > 0)
                    C[i] = C[i-1];

                C[i]++;
            }
            else
            {
                auto it_A = uset_A.begin();

                int count = 0;
                while (it_A != uset_A.end())
                {
                    if (uset_B.count(*it_A))
                        count++;

                    it_A++;
                }

                C[i] = count;
            }
        }

        return C;
    }
};
