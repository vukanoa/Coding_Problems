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

/*
   There are 2 Solutions down below.

   1. Prefix Sum approach,          Time: O(n), Space: O(n) // Slowest out of 3
   2. Monotonicly Increasing Stack. Time: O(n), Space: O(n)
   3. Natural, intuitive approach,  Time: O(n), Space: O(1)

*/

#include <stack>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We can either include it in the same chunk as the previous number or create
    a new chunk for it. However, we must consider the limitation that a new
    chunk at index i can only be created if all the numbers in the current and
    previous chunks (the "prefix" of the array) are smaller than all the
    numbers in the following chunks (the "suffix" of the array). This is
    equivalent to checking whether:

        max(prefix[0:i]) < min(suffix[i:n])

    Since we aim to find the largest possible number of chunks, we will choose
    the second option (i.e. create a new chunk) whenever the above condition
    is satisfied. Therefore, the problem reduces to counting how many indices
    in the array satisfy this condition.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  42.82% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Prefix_Sum {
public:
    int maxChunksToSorted(vector<int>& arr)
    {
        const int N = arr.size();
        vector<int> prefix_max = arr;
        vector<int> suffix_min = arr;

        // Fill the prefix_max array
        for (int i = 1; i < N; i++)
            prefix_max[i] = max(prefix_max[i - 1], prefix_max[i]);

        // Fill the suffix_min array in reverse order
        for (int i = N - 2; i >= 0; i--)
            suffix_min[i] = min(suffix_min[i + 1], suffix_min[i]);

        int chunks = 0;
        for (int i = 0; i < N; i++)
        {
            // A new chunk can be created
            if (i == 0 || suffix_min[i] > prefix_max[i - 1])
                chunks++;
        }

        return chunks;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    A bit unusual Monotonicly Increasing Stack approach. However, if you do
    know about it, you'd be able to come up with a Solution given enough time.

    Not too different to other, but it's weird to pop elements, but to "save"
    the top element BEFORe we start popping and then push it after we're done
    popping. That is a bit unusuall, but it's not too bad.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   7.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Monotonic_Stack {
public:
    int maxChunksToSorted(vector<int>& arr)
    {
        const int N = arr.size();
        stack<int> stack; // Monotonicly Increasing stack

        for (int i = 0; i < N; i++)
        {
            // Case 1: Current element is larger, starts a new chunk
            if (stack.empty() || stack.top() < arr[i])
            {
                stack.push(arr[i]);
            }
            else
            {
                // Case 2: Merge chunks
                int max_elem = stack.top();

                while ( ! stack.empty() && stack.top() > arr[i])
                    stack.pop();

                stack.push(max_elem);
            }
        }

        return stack.size();
    }
};




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
class Solution_Efficient {
public:
    int maxChunksToSorted(vector<int>& arr)
    {
        const int N = arr.size();
        int chunks = 0;

        int bound = -1;
        for (int i = 0; i < N; i++)
        {
            if (bound < i)
                chunks++;

            bound = max(bound, arr[i]);
        }

        return chunks;
    }
};
