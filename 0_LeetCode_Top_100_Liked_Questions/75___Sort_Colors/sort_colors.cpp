#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    75) Sort Colors
    ===========================

    ============
    Description:
    ============

    Given an array "nums" with 'n' objects colored red, white or blue, sort
    them in-place so that objects of the same color are adjacent, with the
    colors in the order red, white and blue.

    We will use the integers 0, 1 and 2 to represent the color red, white and
    blue, respectively.

    You must solve this problem without using the library's sort function.

    =============================================
    FUNCTION: void sortColors(vector<int>& nums);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [2, 0, 2, 1, 1, 0]
    Output: nums = [0, 0, 1, 1, 2, 2]

    --- Example 2 ---
    Input:  nums = [2, 0, 1]
    Output: [0, 1, 2]

    --- Example 3 ---
    Input:  nums = [2, 0, 1, 2, 0, 2, 2, 1, 2, 1, 1, 2, 0]
    Output: [0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]

    *** Constraints ***
    n == nums.length
    1 <= n <= 300
    nums[i] is either 0, 1 or 2.

*/

/*
    Beats 100%

    Legend:
        ^ -> i
        # -> j
        @ -> one

    [2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
     ^                                      #

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
     ^                                   #

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
     ^                                   #

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
        ^                                #

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           ^                             #

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           ^                             #

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           ^                          #

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2] one = 11
           ^                          #
                                      @

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           ^                       #  @

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           ^                    #     @

    [0, 0, 2, 2, 0, 2, 2, 1, 0, 1, 1, 1, 2, 2]
           ^                 #        @

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 1, 1, 2, 2, 2]
           ^                 #     @

    [0, 0, 0, 2, 0, 2, 2, 1, 1, 1, 1, 2, 2, 2]
           ^              #        @

    [0, 0, 0, 2, 0, 2, 2, 1, 1, 1, 1, 2, 2, 2]
              ^           #        @

    [0, 0, 0, 1, 0, 2, 2, 1, 1, 1, 2, 2, 2, 2]
              ^           #     @

    [0, 0, 0, 1, 0, 2, 2, 1, 1, 1, 2, 2, 2, 2]
              ^        #        @

    [0, 0, 0, 2, 0, 2, 1, 1, 1, 1, 2, 2, 2, 2]
              ^     #           @

    [0, 0, 0, 1, 0, 2, 1, 1, 1, 2, 2, 2, 2, 2]
              ^     #        @

    [0, 0, 0, 2, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2]
              ^  #           @

    [0, 0, 0, 1, 0, 1, 1, 1, 2, 2, 2, 2, 2, 2]
              ^  #        @

    [0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
              ^           @
              #

    [0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
              #  ^        @
*/



/*
    ------------
    --- IDEA ---
    ------------

    The above example should illustrate how the algorithm works.

    We have two pointers(three to be exact):
        'i' and 'j'. (and "one")

    Whenever 'i' == 0, just increment 'i' since that is the position '0'(color
    red) should be at.

    At the beginning, pointer "one" is -1("unititialized" yet).
    Why?

    The idea is that we need to find the very first value 1 from the right
    border. Once we find it, we will use that position to swap with a value 2
    at position 'i'.

    There is one special case:
        'i' == 1 and 'j' == 1

    What do we do then?
    Just decrement 'j'
    & if "one" if it's still -1(Initialize it with
    a position of our first value of 1(color white) from the right border)

    If 'i' == 2 and 'j' == 2
        decrement j

    if 'i' == 2 and we have found a value of(color white) from the right then
    swap value of 2 with the most right value of 1(color white) and decrement
    the position of "one" to point at the current right most value of 1.

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************


    [2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
     i                                      j


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
     i                                   j


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
     i                                   j


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
        i                                j


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           i                             j


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           i                             j


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           i                          j


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2] one = 11 // Denoted as O
           i                          j
                                      O

    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           i                       j  O


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
           i                    j     O


    [0, 0, 2, 2, 0, 2, 2, 1, 0, 1, 1, 1, 2, 2]
           i                 j        O


    [0, 0, 1, 2, 0, 2, 2, 1, 0, 1, 1, 2, 2, 2]
           i                 j     O


    [0, 0, 0, 2, 0, 2, 2, 1, 1, 1, 1, 2, 2, 2]
           i              j        O


    [0, 0, 0, 2, 0, 2, 2, 1, 1, 1, 1, 2, 2, 2]
              i           j        O


    [0, 0, 0, 1, 0, 2, 2, 1, 1, 1, 2, 2, 2, 2]
              i           j     O


    [0, 0, 0, 1, 0, 2, 2, 1, 1, 1, 2, 2, 2, 2]
              i        j        O


    [0, 0, 0, 2, 0, 2, 1, 1, 1, 1, 2, 2, 2, 2]
              i     j           O


    [0, 0, 0, 1, 0, 2, 1, 1, 1, 2, 2, 2, 2, 2]
              i     j        O


    [0, 0, 0, 2, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2]
              i  j           O


    [0, 0, 0, 1, 0, 1, 1, 1, 2, 2, 2, 2, 2, 2]
              i  j        O


    [0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
              i           O
              j


    [0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
              j  i        O

-------------------------------------------------------------------------------

*/

/* Time  Beats: 100% */
/* Space Beats: 31.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Complicated_Messy {
public:
    void sortColors(std::vector<int>& nums)
    {
        int n = nums.size();

        if (n == 1)
            return;

        int one = -1; // Not found yet
        int i = 0;
        int j = n - 1;

        while (i <= j)
        {
            if (nums[i] == 2)
            {
                if (one > 0)
                {
                    std::swap(nums[i], nums[one]);
                    one--;
                }
                else
                {
                    if (nums[j] < 2)
                        std::swap(nums[i], nums[j]);

                    if (nums[j] == 1)
                        one = j;

                    j--;
                }
            }
            else if (nums[i] == 1)
            {
                if (nums[j] == 0 || (nums[j] == 2 && one > 0))
                    std::swap(nums[i], nums[j]);

                if (nums[j] == 1 && one < 0)
                    one = j;

                j--;
            }
            else
                i++;
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Simple Solution, though implemented using 2 passes.

*/

/* Time  Beats:   100% */
/* Space Beats: 20.18% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Simple_Two_passes {
public:
    void sortColors(std::vector<int>& nums)
    {
        int n = nums.size();
        int x = n-1;

        for (int i = n-1; i >= 0; i--)
        {
            if (nums[i] == 2)
                std::swap(nums[i], nums[x--]);
        }

        for (int i = x; i >= 0; i--)
        {
            if (nums[i] == 1)
                std::swap(nums[i], nums[x--]);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Different IDEA than the first one above that also uses a single pass. This
    one is much more clean and concise.

    Instead of putting 0's at the right place and the 1's in second loop, we
    can do both at the same time.

    However, there are some cases where simple:
        if (nums[i] == 0)
            std::swap(nums[i], nums[left++]);

        if (nums[i] == 2)
            std::swap(nums[i], nums[right--]);

    Won't be enough.


    Examples where it wouldn't work:

        1. nums = [1, 2, 0]
        2. nums = [2, 1, 2]

    In the 1. example it wouldn't work because once we put 2 all the way to the
    right, we're left with a 0 in the middle of the array, therefore we must
    move 0 as well, if it was swapped during the placement of 2 all the way to
    the right.

    For the 1. example it would work to use:

        if (nums[i] == 0)
            std::swap(nums[i], nums[left++]);

        if (nums[i] == 2 && i <= right)              // If statement
        {
            std::swap(nums[i], nums[right--]);

            if (nums[i] == 0)
                std::swap(nums[i], nums[left++]);
        }


    However, for the 2. example it WOULD NOT!
    Therefore, we must use a "while loop" instead. (Because of that we, also,
    must use an additional condition "i <= right" since those two can move past
    each other)

    Now we have:

        if (nums[i] == 0)
            std::swap(nums[i], nums[left++]);

        while (nums[i] == 2 && i <= right)
        {
            std::swap(nums[i], nums[right--]);

            if (nums[i] == 0)
                std::swap(nums[i], nums[left++]);
        }

    That part is IN the outer "for loop". That DOES NOT mean it's an O(n^2)
    Solution, it's still O(n).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  35.81% */

/* Time  Complexity: O(n) */ // SINGLE PASS!
/* Space Complexity: O(1) */
class Solution_Simple_Elegant_Single_Pass {
public:
    void sortColors(std::vector<int>& nums)
    {
        int left  = 0;
        int right = nums.size()-1;

        for (int i = 0; i <= right; i++)
        {
            if (nums[i] == 0)
                std::swap(nums[i], nums[left++]);

            while (nums[i] == 2 && i <= right)
            {
                std::swap(nums[i], nums[right--]);

                if (nums[i] == 0)
                    std::swap(nums[i], nums[left++]);
            }
        }
    }
};


int
main()
{
    Solution_Complicated_Messy            sol_mess;
    Solution_Simple_Two_passes            sol_two_pass;
    Solution_Simple_Elegant_Single_Pass   sol_eleg_one_pass;

    /* Example 1 */
    // std::vector<int> nums = {2, 0, 2, 1, 1, 0};

    /* Example 2 */
    // std::vector<int> nums = {2, 0, 1};

    /* Example 3 */
    // std::vector<int> nums = {2, 0, 1, 2, 0, 2, 2, 1, 2, 1, 1, 2, 0};

    /* Example 4 */
    // std::vector<int> nums = {1, 2, 0};

    /* Example 5 */
    // std::vector<int> nums = {1, 2, 1};

    /* Example 6 */
    std::vector<int> nums = {2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0};

    std::cout << "\n\t===================";
    std::cout << "\n\t=== SORT COLORS ===";
    std::cout << "\n\t===================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tArray:  [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";



    /* Solution */
    // sol_mess.sortColors(nums);
    // sol_two_pass.sortColors(nums);
    sol_eleg_one_pass.sortColors(nums);


    /* Write Output */
    first = true;
    std::cout << "\n\tSorted: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";
    std::cout << "\n\n";

    return 0;
}
