#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    283) Move Zeroes
    ===========================

    ============
    Description:
    ============

    Given an integer array "nums", move all 0's to the end of it while
    maintaining the relative order of the non-zero elements.

    =====
    Node: that you must do this in-place without making a copy of the array.
    =====

    Follow up: Could you minimize the total number of operations done?

    =============================================
    FUNCTION: void moveZeroes(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [0, 1, 0, 3, 12]
    Output: [1, 3, 12, 0, 0]

    --- Example 2 ---
    Input:  nums = [0]
    Output: [0]

    *** Constraints ***
    1 <= nums.length <= 10^4
    -2^31 <= nums[i] <= 2^31 -1

*/





/*
    ------------
    --- IDEA ---
    ------------

    Sort of like Bubble Sort, but a bit optimized. Not very much though.
    We start from the second element form the back since if we start
    from the last element and:
        if it is not 0
            continue
        else
            it's in the right spot, hence - Do nothing

    So we don't have to start from the very last element, but a 2nd from the
    back.

    Each time we find a zero we swap with the previous. We do that until the
    very next, right, element of our current moving zero is 0 or until our
    zero is less than n - 1st position.

    We do that for every zero. If we were to go from the very left, we would've
    had much more operations. So that's a tiny optimization, though this is
    still very inefficient. It's just an interesting approach.

    It passes all the tests, though it beats only 5%.
*/

/* Time  Beats:  5.10% */
/* Space Beats: 81.93% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution_inefficient {
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int n = nums.size();

        for (int i = n - 2; i >= 0; i--)
        {
            if (nums[i] == 0)
            {
                int x = i;
                int prev = x + 1;

                while (prev < n && nums[prev] != 0)
                {
                    std::swap(nums[x], nums[prev]);
                    x++;
                    prev = x + 1;
                }
            }
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This question comes under a broad category of "Array Transformation". This
    category is the meat of tech interviews. Mostly because arrays are such a
    simple and easy to use data structure. Traversal or representation doesn't
    require any boilerplate code and most of your code will look like the
    Pseudo code itself.

    The 2 requirements of the question are:
        1. Move all the 0's to the end of array.
        2. All the non-zero elements must retain their original order.

    It's good to realize here that both the requirements are mutually exclusive
    i.e you can solve the individual sub-problems and then combine them for the
    final solution.

    If asked in an interview, this approach would be a good start. You can
    explain the interviewer(not code) the above and build your base for the
    next Optimal Solution.
*/

/* Time  Beats: 76.14% */
/* Space Beats:  5.19% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Space_Inefficient{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int n = nums.size();

        // Count the zeroes
        int num_zeroes = 0;
        for (int i = 0; i < n; i++)
            num_zeroes += (nums[i] == 0);

        // Make all the non-zero elelments retain their original order.
        std::vector<int> help_vec;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] != 0)
                help_vec.push_back(nums[i]);
        }

        // Move all zeroes to the end
        while (num_zeroes--)
            help_vec.push_back(0);

        // Overwrite original vector "nums"
        for (int i = 0; i < n; i++)
            nums[i] = help_vec[i];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This approach works the same way as above, i.e., first fulfills one
    requirement and then another. The catch? It does it in a clever way. The
    above problem can also be stated in alternate way - "Bring all the non 0
    elements to the front of array keeping their relative order same".

    This is a 2 pointer approach. The fast pointer which is denoted by variable
    "curr" does the job of processing new elements. If the newly found element
    is not a 0, we record it just after the last found non-0 element. The
    position of last found non-0 element is denoted by the slow pointer
    "lastNonZeroFoundAt" variable. As we keep finding new non-0 elements, we
    just overwrite them at the "lastNonZeroFoundAt + 1" 'th index. This
    overwrite will not result in any loss of data because we already processed
    what was there(if it were non-0, it already is now written at it's
    corresponding index, or if it were 0 it will be handled later in time).

    After the "curr" index reaches the end of array, we now know that all the
    non-0 elements have been moved to beginning of array in their original
    order. Now comes the time to fulfill other requirement. "Move all 0's to
    the end". We now simply need to fill all the indexes after the
    "lastNonZeroFoundAt" index with 0.
*/

/* Time  Beats: 92.16% */
/* Space Beats: 51.63% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient_1{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int lastNonZeroFoundAt = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != 0)
                nums[lastNonZeroFoundAt++] = nums[i];
        }

        for (int i = lastNonZeroFoundAt; i < nums.size(); i++)
            nums[i] = 0;
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    Approach #3 (Optimal)
    The total number of operations of the previous approach is sub-optimal.
    For example, the array which has all (except last) leading zeroes:
        [0, 0, 0, 0, ..., 1]

    How many write operations to the array? For the previous approach, it's
    0's n - 1 times, which is not necessary. We could have instead written just
    once. How? ... By only fixing the non-0 element, i.e., once.

    The optimal approach is again a subtle extension of the above solution. A
    simple realization is if the current element is non-0, its correct position
    can at best be its current position or a position earlier.

    If it's the latter, the current position will be eventually occupied by a
    non-0, or a 0, which lies at a index greater than "cur" index.
    We fill the current position by 0 right away, so that unlike the previous
    solution, we don't need to come back here in next iteration.

    In other words, the code will maintain the following invariant:
        1. All elements before the slow pointer (lastNonZeroFoundAt) are
           non-zeroes.

        2. All elements between the current and slow pointer are zeroes.

    Therefore, when we encounter a non-zero element, we need to swap elements
    pointed by current and slow pointer, then advance both pointers. If it's
    zero element, we just advance current pointer.

    With this invariant in-place, it's easy to see that the algorithm will work

    ==================
    === Simulation === (N = non_zero, Z = zero)
    ==================

     Z
     N
    [13, 0, 0, 5, 1, 0, 3, 12, 0, 7, 0]
     0   1  2  3  4  5  6  7   8  9  10


    nums[N] != 0
         ~~~~~~ Swap ~~~~~~ and then Increment both Z and N.
         (Nothing happens)


         Z
         N
    [13, 0, 0, 5, 1, 0, 3, 12, 0, 7, 0]
     0   1  2  3  4  5  6  7   8  9  10


    nums[N] == 0, so Increment N only;


         Z  N
    [13, 0, 0, 5, 1, 0, 3, 12, 0, 7, 0]
     0   1  2  3  4  5  6  7   8  9  10


    nums[N] == 0, so Increment N only;


         Z     N
    [13, 5, 0, 0, 1, 0, 3, 12, 0, 7, 0]
     0   1  2  3  4  5  6  7   8  9  10


    nums[N] == 0, so Increment N only;


            Z     N
    [13, 5, 0, 0, 1, 0, 3, 12, 0, 7, 0]
     0   1  2  3  4  5  6  7   8  9  10


    nums[N] != 0
         ~~~~~~ Swap ~~~~~~ and then Increment both Z and N.


               Z     N
    [13, 5, 1, 0, 0, 0, 3, 12, 0, 7, 0]
     0   1  2  3  4  5  6  7   8  9  10


    nums[N] == 0, so Increment N only;


               Z        N
    [13, 5, 1, 0, 0, 0, 3, 12, 0, 7, 0]
     0   1  2  3  4  5  6  7   8  9  10


    nums[N] != 0
         ~~~~~~ Swap ~~~~~~ and then Increment both Z and N.


                  Z        N
    [13, 5, 1, 3, 0, 0, 0, 12, 0, 7, 0]
     0   1  2  3  4  5  6  7   8  9  10


    nums[N] != 0
         ~~~~~~ Swap ~~~~~~ and then Increment both Z and N.


                      Z        N
    [13, 5, 1, 3, 12, 0, 0, 0, 0, 7, 0]
     0   1  2  3  4   5  6  7  8  9  10


    nums[N] == 0, so Increment N only;


                      Z           N
    [13, 5, 1, 3, 12, 0, 0, 0, 0, 7, 0]
     0   1  2  3  4   5  6  7  8  9  10


    nums[N] != 0
         ~~~~~~ Swap ~~~~~~ and then Increment both Z and N.


                         Z           N
    [13, 5, 1, 3, 12, 7, 0, 0, 0, 0, 0]
     0   1  2  3  4   5  6  7  8  9  10


    nums[N] == 0, so Increment N only;


                         Z              N <--- Out of Bounds
    [13, 5, 1, 3, 12, 7, 0, 0, 0, 0, 0]
     0   1  2  3  4   5  6  7  8  9  10


*/

/* Time  Beats: 95.77% */
/* Space Beats: 51.63% */
/*
    Time  Complexity: O(n)
    However, the total number of operations are optimal. The total operations
    (array writes) that code does is Number of non-0 elements. This gives us a
    much better best-case (when most of the elements are 0) complexity than
    last solution.
    However, the worst-case (when all elements are non-0) complexity for both
    the algorithms is same.
*/
/*
    Space Complexity: O(1)
*/
class Solution_Efficient_2{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int left_zero = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != 0)
                std::swap(nums[left_zero++], nums[i]);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above.
    Implementation is more in the spirit of Two Pointers technique.

*/

/* Time  Beats: 89.22% */
/* Space Beats: 30.33% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient_In_Spirit_Of_Two_Pointers {
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int left  = 0; // zero
        int right = 0; // non-zero

        while (right < nums.size())
        {
            if (nums[right]) // If nums[right] is indeed a non-zero
                std::swap(nums[left++], nums[right]);
            
            right++; // Increment everytime, even if we didn't swap anything
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The idea is that we go through the array and gather all zeros on our road.

    Let's take our example:
    The first step - we meet 0.
    Okay, just remember that now the size of our snowball is 1. Go further.
    ('#' will denote snowball. Number of characters is the size of snowball)

    [0, 1, 0, 3, 12]
     # // Size 1

    Next step - We encounter 1. Swap the most left 0 of our snowball with
    element 1.

         ----
         |  |
         |  v
        [0, 1, 0, 3, 12]
         #  |
         ^  |
         |__|


    Next step - We encounter 0 again! (Our ball gets bigger, now its size = 2)
    [1, 0, 0, 3, 12]
        #  #

    Next Step - 3. Swap again with the most left zero.

            -------
            |     |
            |     v
        [1, 0, 0, 3, 12]
            #  #  |
            ^     |
            |_____|

    Looks like our zeros roll all the time


    [1, 3, 0, 0, 12]
           #  #

    Next Step - 12. Swap again.

               --------
               |      |
               |      v
        [1, 3, 0, 0, 12]
               #  #   |
               ^      |
               |______|


    We reach the end:

        [1, 3, 12, 0, 0]

*/

/* Time  Beats: 85.64% */
/* Space Beats: 81.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Snowball{
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int snowball_size = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
                snowball_size++;
            else if (snowball_size > 0)
                std::swap(nums[i], nums[i - snowball_size]);
        }
    }
};


int
main()
{
    Solution_inefficient                          sol_ineff;
    Solution_Space_Inefficient                    sol_space;
    Solution_Efficient_1                          sol_eff_1;
    Solution_Efficient_2                          sol_eff_2;
    Solution_Efficient_In_Spirit_Of_Two_Pointers  sol_two_p;
    Solution_Snowball                             sol_snowball;


    /* Example 1 */
    // std::vector<int> nums = {0, 1, 0, 3, 12};

    /* Example 2 */
    // std::vector<int> nums = {0};

    /* Example 3 */
    // std::vector<int> nums = {0, 1};

    /* Example 4 */
    std::vector<int> nums = {13, 0, 0, 5, 1, 0, 3, 12, 0, 7, 0};


    std::cout << "\n\t===================";
    std::cout << "\n\t=== MOVE ZEROES ===";
    std::cout << "\n\t===================\n\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tNums: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    /* Solution */
    // sol_ineff.moveZeroes(nums);
    // sol_space.moveZeroes(nums);
    // sol_eff_1.moveZeroes(nums);
    // sol_eff_2.moveZeroes(nums);
    // sol_two_p.moveZeroes(nums);
    sol_snowball.moveZeroes(nums);

    std::cout << "\t\t*** MOVE ZEROES ***\n";


    /* Write Output */
    first = true;
    std::cout << "\n\tNums: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
