/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    2683) Neighboring Bitwise XOR
    =============================

    ============
    Description:
    ============


    A 0-indexed array derived with length n is derived by computing the bitwise
    XOR (⊕) of adjacent values in a binary array original of length n.

    Specifically, for each index i in the range [0, n - 1]:

        + If i = n - 1, then derived[i] = original[i] ⊕ original[0].

        + Otherwise, derived[i] = original[i] ⊕ original[i + 1].

    Given an array derived, your task is to determine whether there exists a
    valid binary array original that could have formed derived.

    Return true if such an array exists or false otherwise.

        A binary array is an array containing only 0's and 1's

    =========================================================
    FUNCTION: bool doesValidArrayExist(vector<int>& derived);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: derived = [1,1,0]
    Output: true
    Explanation: A valid original array that gives derived is [0,1,0].
    derived[0] = original[0] ⊕ original[1] = 0 ⊕ 1 = 1
    derived[1] = original[1] ⊕ original[2] = 1 ⊕ 0 = 1
    derived[2] = original[2] ⊕ original[0] = 0 ⊕ 0 = 0

    --- Example 2 ---
    Input: derived = [1,1]
    Output: true
    Explanation: A valid original array that gives derived is [0,1].
    derived[0] = original[0] ⊕ original[1] = 1
    derived[1] = original[1] ⊕ original[0] = 1

    --- Example 3 ---
    Input: derived = [1,0]
    Output: false
    Explanation: There is no valid original array that gives derived.


    *** Constraints ***
    n == derived.length
    1 <= n <= 10^5
    The values in derived are either 0's or 1's

*/

#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Well since EVERY bit in original must give a correct XOR-ed bit, then we
    really have two possibilities only.

    1. If derived is 0, then original[0] and original[1] must both be either 0
       or 1.

       Otherwise, we wouldn't be able to get even past this first bit.

       That's why we'll have two options.

       After that we are trying to construct the original based on "derived".
       It will certainly be possible to construct N-1 derived's bits, however
       the very last one is where we'll see if it's possible to create an
       original or not.

       That's why we have two options.


    2. If derived is 1, then original[0] and original[1] have to either be:
       0 and 1, or
       1 and 0

       respecitvely.

       The "after" part is the same. Only at the very last element, i.e. N-1
       we'll know if this original could truly be an original of derived.


    It's a "long code", but it's very easy.

*/

/* Time  Beats: 17.29% */
/* Space Beats: 14.49% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool doesValidArrayExist(vector<int>& derived)
    {
        const int N = derived.size();

        if (N == 1)
            return derived[0] == 0;

        vector<int> original_1(N, 0);
        vector<int> original_2(N, 0);


        if (derived[0] == 0)
        {
            original_1[0] = 1;
            original_1[1] = 1;
            if (dfs(derived, original_1, 1))
                return true;

            original_2[0] = 0;
            original_2[1] = 0;
            if (dfs(derived, original_2, 1))
                return true;
        }
        else
        {
            original_1[0] = 0;
            original_1[1] = 1;
            if (dfs(derived, original_1, 1))
                return true;

            original_2[0] = 1;
            original_2[1] = 0;
            if (dfs(derived, original_2, 1))
                return true;
        }

        return false;
    }

private:
    bool dfs(vector<int>& derived, vector<int>& original, int start)
    {
        const int N = derived.size();
        for (int i = start; i < N; i++)
        {
            if (i == N-1)
            {
                if (derived[N-1] == 0)
                {
                    return (original[N-1] == 0 && original[0] == 0) ||
                           (original[N-1] == 1 && original[0] == 1);
                }
                else
                {
                    return (original[N-1] == 1 && original[0] == 0) ||
                           (original[N-1] == 0 && original[0] == 1);
                }
            }
            else
            {
                if (derived[i] == 0)
                {
                    if (original[i] == 0)
                    {
                        original[i+1] = 0;
                    }
                    else
                    {
                        original[i+1] = 1;
                    }
                }
                else
                {
                    if (original[i] == 0)
                    {
                        original[i+1] = 1;
                    }
                    else
                    {
                        original[i+1] = 0;
                    }
                }
            }
        }

        return false; // Unreachable
    }
};




/*
    ------------
    --- IDEA ---
    ------------


    Similar to the above approach, but written in a much more elegant way.

    To determine whether a valid original array can be constructed from the
    given derived array, we can carefully simulate how the original array would
    be built.

    From the problem, we know:

     derived[i] = original[i] XOR original[i+1]


    Using the inversion property of XOR, we can rewrite this as:

        original[i+1] = derived[i] XOR original[i]

    This means that if we know the value of the original[i], we can calculate
    the next element, original[i+1], using the corresponding value from derived.

    The first element of original, original[0], can be either 0 or 1 (since
    it’s binary).

        + If we assume original[0] = 0, we can calculate the rest of the array.

        + Similarly, we can repeat the process assuming original[0] = 1.

    Once we compute all the elements of the original for both starting points,
    we need to check if they satisfy the circular condition:

        derived[N-1] = original[N-1] XOR original[0]


    This ensures that the last element in derived matches the XOR of the first
    and last elements of original.

    If the circular condition is satisfied for either of the two cases
    (original[0] = 0 or original[0] = 1), then a valid original array exists,
    and we return true. Otherwise, we return false.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    bool doesValidArrayExist(vector<int>& derived)
    {
        const int N = derived.size();
        vector<int> original = {0};

        for (int i = 0; i < N; i++)
            original.push_back((derived[i] ^ original[i]));

        bool check_for_zero = (original[0] == original[N-1]);

        original = {1};

        for (int i = 0; i < derived.size(); i++)
            original.push_back((derived[i] ^ original[i]));

        bool check_for_one = (original[0] == original[N-1]);

        return check_for_zero | check_for_one;
    }
};
