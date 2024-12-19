/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    769) Max Chunks To Make Sorted
    ==============================

    ============
    Description:
    ============

    You are given an integer array arr of length n that represents a
    permutation of the integers in the range [0, n - 1].

    We split arr into some number of chunks (i.e., partitions), and
    individually sort each chunk. After concatenating them, the result should
    equal the sorted array.

    Return the largest number of chunks we can make to sort the array.

    ==================================================
    FUNCTION: int maxChunksToSorted(vector<int>& arr);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [4,3,2,1,0]
    Output: 1
    Explanation:
    Splitting into two or more chunks will not return the required result.
    For example, splitting into [4, 3], [2, 1, 0] will result in [3, 4, 0, 1, 2], which isn't sorted.

    --- Example 2 ---

    Input: arr = [1,0,2,3,4]
    Output: 4
    Explanation:
    We can split into two chunks, such as [1, 0], [2, 3, 4].
    However, splitting into [1, 0], [2], [3], [4] is the highest number of chunks possible.

    *** Constraints ***
    n == arr.length
    1 <= n <= 10
    0 <= arr[i] < n
    All the elements of arr are unique.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is pretty simple if you take a little bit of time to think about
    it.

    Have a variable "bound" set to -1 at the beginning. Each time check:

        if (bound < i)

    Why?
    Because if that happened, we need to start a new chunk, "bound" is
    essentially a way to say: "From the beginning of this current chunk, last
    element should be at index BEFORE 'i', therefore change "bound" to current
    element and increment number of found chunks(i.e. result).

    However, now matter if (bound < i), we ALWAYS have to take the maximum of
    current element and current "bound" value.

    Consider this example:
        arr = {1, 2, 0, 4, 3]
               0  1  2  3  4

    First "bound" is -1.

        i=0) bound = -1
            bound is indeed smaller than i=0, therefore: bound = arr[i] // 1
            result++; // Start of the new "chunk"

        i=1) bound = 1
            bound is NOT smaller than i=1(it's equal to 'i'), so do nothing.

        i=2) bound = 1
            bound is indeed smaller than i=2, therefore: bound = arr[i] // 0
            result++; // Start of the new "chunk"

        i=3) bound = 0
            bound is indeed smaller than i=3, therefore: bound = arr[i] // 4
            result++; // Start of the new "chunk"

        i=4) bound = 4
            bound is NOT smaller than i=4, therefore do nothing.


        The result would be 3, but that is NOT correct.
        That answer should be 2.

        Why?

        Because the first window chunk should be first THREE elements, not
        first TWO elements.

        Where did we make a mistake?
        We made a mistake at i=1. "bound" wasn't smaler than i, however within
        this VALID chunk there appeared to be a BIGGER element, i.e. new bound.
        We have NOT updated it and therefore we ended up return incorrect
        result.

        This is how it should've been:

    First "bound" is -1.

        i=0) bound = -1
            bound is indeed smaller than i=0, therefore: bound = arr[i] // 1
            result++; // Start of the new "chunk"

        i=1) bound = 1
            bound is NOT smaller than i=1(it's equal to 'i'), so do nothing.
            bound = max(bound, arr[i]); // We have a new, bigger, value in this
                                        // VALID chunk

        i=2) bound = 2
            bound is NOT smaller than i=1(it's equal to 'i'), so do nothing.
            result++; // Start of the new "chunk"

        i=3) bound = 2
            bound is indeed smaller than i=3, therefore: bound = arr[i] // 4
            result++; // Start of the new "chunk"

        i=4) bound = 4
            bound is NOT smaller than i=4, therefore do nothing.


    Now we have the correct result = 2.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  35.22% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr)
    {
        const int N = arr.size();
        int result = 0;

        int bound = -1;
        for (int i = 0; i < N; i++)
        {
            if (bound < i)
            {
                result++;
                bound = arr[i]; // This could be omitted
            }

            bound = max(bound, arr[i]);
        }

        return result;
    }
};
