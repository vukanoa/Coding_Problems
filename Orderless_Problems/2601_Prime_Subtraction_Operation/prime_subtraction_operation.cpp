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

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

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

    1   2   3   4   5   6
    7   8   9  10  11  12
    13 14  15  16  17  18
    19 20  21  22  23  24
    25 26  27  28  29  30
    31 32  33  34  35  36
    37 38  39  40  41  42
    43 44  45  46  47  48
    49 50  51  52  53  54
    55 56  57  58  59  60
    61 62  63  64  65  66
    67 68  69  70  71  72
    73 74  75  76  77  78
    79 80  81  82  83  84
    85 86  87  88  89  90
    91 92  93  94  95  96
    97 98  99 100


    1) Cross out 1

    2) Cross out first non-crossed out number and cross out all of the numbers
       it divides

    3) Repeat step 2 up until SQRT(final_num)   // final_num=100 in our case






*/

/* Time  Beats: 100.00% */
/* Space Beats:  81.15% */

/* Time  Complexity: O(n * sqrt(m)) */
/* Space Complexity: O(m)           */
class Solution_Sieve_Of_Eratosthenes {
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  67.65% */

/* Time  Complexity: O(n * logp) */ // p -> is the number of primes up to 1000
/* Space Complexity: O(p)        */
class Solution_Write_Primes_For_First_Thousand_Numbers {
public:
    // Since in the Constraints it is stated that: 1 <= nums[i] <= 1000
    // We can write all the primes in the first 1000 numbers.
    vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
        149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
        227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
        307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383,
        389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
        467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569,
        571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647,
        653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743,
        751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839,
        853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
        947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021
    };

    bool primeSubOperation(vector<int>& nums)
    {
        int prev = 0;
        for (int num : nums)
        {
            if (num <= prev)
                return false;

            auto it = lower_bound(primes.begin(), primes.end(), num - prev);
            int i = it - primes.begin() - 1;

            if (i != -1)
                num -= primes[i];

            prev = num;
        }
        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 55.96% */
/* Space Beats: 80.07% */

/* Time  Complexity: O(n + m * log(logm)) */
/* Space Complexity: O(m)                 */
class Solution_Sieve_Of_Atkin {
public:
    bool primeSubOperation(vector<int>& nums)
    {
        int max_elem = *max_element(nums.begin(), nums.end());
        
        // Sieve of Atkin
        vector<bool> sieve(max_elem + 1, false);

        if (max_elem > 2)
            sieve[2] = true;

        if (max_elem > 3)
            sieve[3] = true;
        
        for (int x = 1; x*x <= max_elem; x++)
        {
            for (int y = 1; y*y <= max_elem; y++)
            {
                int n = (4 * x*x) + (y*y);
                if (n <= max_elem && (n % 12 == 1 || n % 12 == 5))
                    sieve[n] = !sieve[n];
                
                n = (3 * x*x) + (y*y);
                if (n <= max_elem && n % 12 == 7)
                    sieve[n] = !sieve[n];
                
                n = (3 * x*x) - (y*y);
                if (x > y && n <= max_elem && n % 12 == 11)
                    sieve[n] = !sieve[n];
            }
        }
        
        for (int i = 5; i*i <= max_elem; i++)
        {
            if (sieve[i])
            {
                for (int j = i*i; j <= max_elem; j += i*i)
                    sieve[j] = false;
            }
        }
        
        int curr_val = 1;
        int i = 0;
        while (i < nums.size())
        {
            int upper_bound = nums[i] - curr_val;
            
            if (upper_bound < 0)
                return false;
            
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
