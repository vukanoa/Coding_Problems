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




/*
    ------------
    --- IDEA ---
    ------------

    We don't actually need a HashSet and then iterate through the elements of
    it and check if it's present in the other HashSet, we can simply increment
    the count of each number, since there are a total of 2 occurrences of each
    number between two vectors.

    Therefore, once we find out that the counter of some number is 2, it
    indicates that the number with that count has appeared at thix index or
    before in BOTH vectors, therefore we can increment C[i] and include that
    number as well.

    If it's NOT 2, then we "add 0", i.e. do nothing.

*/

/* Time  Beats: 69.55% */
/* Space Beats: 69.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Efficient {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B)
    {
        const int N = A.size();
        vector<int> C(N, 0);

        vector<int> counter(N+1, 0);
        for (int i = 0; i < N; i++)
        {
            counter[A[i]]++;
            counter[B[i]]++;

            if (i > 0)
                C[i] = C[i-1];

            if (A[i] == B[i])
                C[i] += 1;
            else
            {
                C[i] += counter[A[i]] == 2 ? 1 : 0;
                C[i] += counter[B[i]] == 2 ? 1 : 0;
            }
        }

        return C;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is another way of implementing the above Efficient, Linear, Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.89% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Efficient_2 {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B)
    {
        const int N = A.size();
        vector<int> C(N);

        vector<int> frequency(N + 1, 0);

        int count = 0;
        for (int i = 0; i < N; ++i)
        {
            if (++frequency[A[i]] == 2)
                count++;

            if (++frequency[B[i]] == 2)
                count++;

            C[i] = count;
        }

        return C;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is another way of implementing the Efficient Solution. Choose to your
    liking, but it's always useful to see different possible ways of thinking
    and approaching the implementation.

*/

/* Time  Beats: 75.81% */
/* Space Beats: 41.68% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Efficient_3 {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B)
    {
        const int N = A.size();
        vector<int> C;

        unordered_set<int> uset;
        for (int i = 0; i < A.size(); i++)
        {
            uset.insert(A[i]);
            uset.insert(B[i]);

            C.push_back(2 * (i + 1) - uset.size());
        }

        return C;
    }
};
