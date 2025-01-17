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

#include <numeric>
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

/* Time  Beats: 10.28% */
/* Space Beats:  5.61% */

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

        bool check_for_zero = (original[0] == original[N]);

        original = {1};

        for (int i = 0; i < derived.size(); i++)
            original.push_back((derived[i] ^ original[i]));

        bool check_for_one = (original[0] == original[N]);

        return check_for_zero | check_for_one;
    }
};

/*
    ------------
    --- IDEA ---
    ------------


    Observe the following equations that represent the relationship between the
    elements of the derived and original arrays:

        derived[0] = original[0] XOR original[1]
        derived[1] = original[1] XOR original[2]
        derived[2] = original[2] XOR original[3]
        derived[3] = original[3] XOR original[4]

        ...

        derived[n-1] = original[n-1] XOR original[0]


    Each element in original appears exactly twice in the equations: once as
    original[i] and once as original[i+1]. For example:

        original[0] first appears in derived[0]   (original[0]   XOR original[1])
        original[0] also  appears in derived[n-1] (original[n-1] XOR original[0])

    Since XOR is both commutative and associative, the order doesn’t matter.
    When all occurrences of original[i] are XORed together, they cancel each
    other out:
        original[0] XOR original[0] XOR original[1] XOR original[1] ... = 0

    If the derived array is valid (i.e., it was generated from some original),
    then the XOR of all elements in derived must be 0. This is because all
    elements of original cancel out when XOR-ed.

    Initialize a variable XOR to 0. This will store the cumulative XOR of
    elements in the derived array.

        Iterate through each element in the derived array:

            For each element, compute the XOR with the current value of XOR and
            update XOR.

    After the loop, check the value of XOR:

        If XOR == 0, return true (indicating the array is valid).

    Otherwise, return false.

*/

/* Time  Beats: 31.78% */
/* Space Beats: 23.83% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Cumulative_XOR {
public:
    bool doesValidArrayExist(vector<int>& derived)
    {
        int result = 0;

        for (const int& element : derived)
            result = result ^ element;

        return result == 0;
    }
};

/*
    ------------
    --- IDEA ---
    ------------


    Similar to the previous approach, we can rely on the properties of XOR.
    However, this time, we focus on the parity (even or odd nature) of the
    numbers involved.

    The XOR of two binary numbers produces a result based on their bits.
    Specifically:

        0 XOR 0 = 0
        1 XOR 1 = 0
        0 XOR 1 = 1
        1 XOR 0 = 1

    Notice that when two identical numbers are XOR-ed, the result is 0.

    For an XOR operation to result in a balanced and valid sequence, the total
    number of 1s in the derived array (which represents mismatched bits) must
    be even. This is because each 1 in derived corresponds to a mismatch
    between adjacent elements in the original array, and mismatches can only be
    resolved in pairs.

    The sum of the elements in derived gives the total count of 1s in the array

    If the sum is even, it means that the mismatches can be paired and
    resolved, allowing us to construct a valid original array. If the sum is
    odd, it’s impossible to resolve the mismatches, and no valid original array
    can exist.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.19% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sum_Parity {
public:
    bool doesValidArrayExist(vector<int>& derived)
    {
        int sum = accumulate(derived.begin(), derived.end(), 0);
        return sum % 2 == 0;
    }
};
