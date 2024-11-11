#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    2601) Prime Subtraction Operation
    =================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums of length n.

    You can perform the following operation as many times as you want:

        Pick an index i that you haven’t picked before, and pick a prime p
        strictly less than nums[i], then subtract p from nums[i].

    Return true if you can make nums a strictly increasing array using the
    above operation and false otherwise.

    A strictly increasing array is an array whose each element is strictly
    greater than its preceding element.

    ====================================================
    FUNCTION: bool primeSubOperation(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,9,6,10]
    Output: true
    Explanation: In the first operation: Pick i = 0 and p = 3, and then
                 subtract 3 from nums[0], so that nums becomes [1,9,6,10]. In
                 the second operation: i = 1, p = 7, subtract 7 from nums[1],
                 so nums becomes equal to [1,2,6,10]. After the second
                 operation, nums is sorted in strictly increasing order, so the
                 answer is true.

    --- Example 2 ---
    Input: nums = [6,8,11,12]
    Output: true
    Explanation: Initially nums is sorted in strictly increasing order, so we
                 don't need to make any operations.

    --- Example 3 ---
    Input: nums = [5,8,3]
    Output: false
    Explanation: It can be proven that there is no way to perform operations to
                 make nums sorted in strictly increasing order, so the answer
                 is false.


    *** Constraints ***
    1 <= nums.length <= 1000
    1 <= nums[i] <= 1000
    nums.length == n

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.36% */

/* Time  Complexity: O(n * nums[i] * sqrt(nums[i])) */
/* Space Complexity: O(1)                           */
class Solution {
public:
    bool primeSubOperation(vector<int>& nums)
    {
        int prev = 0;
        for (const int& num : nums)
        {
            int upper_bound = num - prev; // Non-inclusive

            int largest_prime = 0;
            for (int i = upper_bound - 1; i >= 2; i--)
            {
                if (is_prime(i))
                {
                    largest_prime = i;
                    break;
                }
            }

            if (num - largest_prime <= prev)
                return false; // It's impossible to make the array sorted

            prev = num - largest_prime;
        }

        return true;
    }

private:
    bool is_prime(int& num)
    {
        for (int factor = 2; factor <= std::sqrt(num); factor++)
        {
            if (num % factor == 0)
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

    This Solution is MORE efficient in terms of Big O Complexity, however
    LeetCode, for some reason, rates it as LESS efficient.

    Anyway, the optimization is not trivial as we've prevented the repetitive
    work.

*/

/* Time  Beats: 46.63% */
/* Space Beats: 80.19% */

/* Time  Complexity: O(n * nums[i] + nums[i] * sqrt(nums[i])) */
/* Space Complexity: O(1)                                     */
class Solution_Optimization_1 {
public:
    bool primeSubOperation(vector<int>& nums)
    {
        int max_elem = *max_element(nums.begin(), nums.end());

        /*
           Pre-compute prime numbers
           Optimization 1: primes[i] == true, if i == prime
        */
        vector<bool> primes;
        primes.push_back(true); // Idx = 0;
        primes.push_back(true); // Idx = 1;

        for (int i = 2; i < max_elem; i++)
        {
            if (is_prime(i))
                primes.push_back(true);
            else
                primes.push_back(false);
        }


        int prev = 0;
        for (const int& num : nums)
        {
            int upper_bound = num - prev; // Non-inclusive

            int largest_prime = 0;
            for (int i = upper_bound - 1; i >= 2; i--)
            {
                if (is_prime(i))
                {
                    largest_prime = i;
                    break;
                }
            }

            if (num - largest_prime <= prev)
                return false; // It's impossible to make the array sorted

            prev = num - largest_prime;
        }

        return true;
    }

private:
    bool is_prime(int& num)
    {
        for (int factor = 2; factor <= std::sqrt(num); factor++)
        {
            if (num % factor == 0)
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

    For some reason I cannot get this to work, even if it's the natural
    optimization of the above Solution, but I'll leave it here anyways.

    However, I'll try to write this one in another way below this failed
    attempt.

*/

/* Time  Complexity: O(n + nums[i] * sqrt(nums[i])) */
/* Space Complexity: O(1)                           */
class Solution_Optimization_2 {
public:
    bool primeSubOperation(vector<int>& nums)
    {
        int max_elem = *max_element(nums.begin(), nums.end());

        /*
           Pre-compute prime numbers
           Optimization 2: primes[i] --> largest prime <= i
        */
        vector<int> primes;
        primes.push_back(0); // Idx = 0;
        primes.push_back(0); // Idx = 1;
        primes.push_back(2); // Idx = 2;

        // It's going to be something like this: (No, it's NOT Fibonacci)
        // [0, 0, 2, 3, 3, 5, 5, 7, ...]


        for (int i = 2; i < max_elem + 1; i++)
        {
            if (is_prime(i))
                primes.push_back(i);
            else
                primes.push_back(primes[i - 1]);
        }


        int prev = 0;
        for (const int& num : nums)
        {
            int upper_bound = num - prev; // Non-inclusive

            /*
                Optimization 2:

                We took out the for-loop and now the total Time Complexity is:
                    O(n + nums[i] * sqrt(nums[i]))

            */
            int largest_prime = primes[upper_bound - 1];

            if (num - largest_prime <= prev)
                return false; // It's impossible to make the array sorted

            prev = num - largest_prime;
        }

        return true;
    }

private:
    bool is_prime(int& num)
    {
        for (int factor = 2; factor <= std::sqrt(num); factor++)
        {
            if (num % factor == 0)
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Sieve of Eratosthenes)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  81.15% */

/* Time  Complexity: O(n * sqrt(m)) */
/* Space Complexity: O(m)           */
class Solution_Sieve_Of_Eratosthenes {
class Solution {
public:
    bool primeSubOperation(vector<int>& nums)
    {
        int max_elem = *max_element(nums.begin(), nums.end());

        // Create Sieve of Eratosthenes array to identify prime numbers
        vector<bool> sieve(max_elem + 1, true);
        sieve[1] = false;

        for (int i = 2; i <= std::sqrt(max_elem + 1); i++)
        {
            if (sieve[i]) // If it's a prime number
            {
                for (int j = i * i; j <= max_elem; j += i)
                    sieve[j] = false;
            }
        }

        // Check if array can be made strictly increasing by subtracting prime numbers
        int curr_val = 1;
        int i = 0;
        while (i < nums.size())
        {
            int upper_bound = nums[i] - curr_val;

            // Return false if current number is already smaller than required value
            if (upper_bound < 0)
                return false;

            // Move to next number if upper_bound is prime or zero
            if (sieve[upper_bound] == true || upper_bound == 0)
            {
                i++;
                curr_val++;
            }
            else
                curr_val++;
        }

        return true;
    }
};
