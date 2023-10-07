/*
    Rearrange alternation such that no two odd or even numbers are next to each
    other.

    But you must do it in O(n) Time Complexity and in O(1) Space Complexity.
*/

#include <iostream>
#include <vector>

/*
    ------------
    --- IDEA ---
    ------------

    This one, at worst, is running in O(n) Time Complexity and O(1) Space.
    However, it's written in a much more confusing and unnatural way.

    But it fulfills all the requirements.

    This Solution does maintain the relative order of both odd and even
    numbers.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Messy {
public:
    void solution(std::vector<int>& A)
    {
        int n = A.size();

        if (n <= 2)
            return;

        if (n % 2 != 0) // Even number of elements
        {
            int even = 0;
            int odd  = 0;

            // O(n)
            // Count Even & Odd numbers
            for (const int& num : A)
                num & 1 ? odd++ : even++;

            if (odd > even && A[0] % 2 == 0)
            {
                // O(n)
                for (int i = 1; i < n; i++)
                {
                    if (A[i] % 2 != 0)
                    {
                        std::swap(A[0], A[i]);
                        break;
                    }
                }
            }
            else if (even > odd && A[0] % 2 != 0)
            {
                // O(n)
                for (int i = 1; i < n; i++)
                {
                    if (A[i] % 2 == 0)
                    {
                        std::swap(A[0], A[i]);
                        break;
                    }
                }
            }
        }

        int left  = 1;
        int right = 1;

        // O(n)
        while (right < n)
        {
            // Same parity
            if (A[left - 1] % 2 == A[left] % 2)
            {
                while (right < n)
                {
                    if (A[left] % 2 != A[right] % 2)
                    {
                        std::swap(A[left], A[right]);
                        left++;
                        right = left;
                        break;
                    }

                    right++;
                }

                if (right == n)
                    return;
            }
            else
            {
                left++;
                right++;
            }
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is truly a Solution of O(n) Time Complexity.
    And, of course, a O(1) Space Complexity.

    It uses a simple "Two Pointers" technique and a bit of logical thinking for
    determining which element should be at which index.

    This Solution does NOT maintain the relative order of either odd or even
    numbers.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Concise_and_Efficient {
public:
    void solution(std::vector<int>& A)
    {
        if (A.size() < 2)
            return;

        int odd  = 0;
        int even = 0;

        // O(n)
        for (int& a : A)
            a & 1 ? odd++ : even++;

        int x = even > odd ? 0 : 1;

        int left  = 0;
        int right = A.size() - 1;

        // O(n)
        while (left < right)
        {
            // If at this("left") index there is a correct parity
            if ((left + x) % 2 == A[left] % 2)
            {
                left++;
                continue;
            }

            while (left < right && (left + x) % 2 != A[right] % 2)
                right--;

            // This happens only if the difference between odd and even is > 1
            if (left == right)
                return;

            std::swap(A[left], A[right]);
            left++;
        }

        /*
            For this example:
                [ 7, 5,  3,  2,  4,  9,  8,  6,  1, 12, 14]

            Without this line, we'd end up like this:
                [14, 5, 12,  3,  4,  9,  8,  1,  6,  2,  7]
                                                     ^   ^
                                                     |   |
            These would not be okay ----------------------

            So at the end, check the very last element is at correct index.
            If it's not, then just swap them.

        */
        if (A[A.size() - 1] % 2 != (A.size()-1 + x) % 2)
            std::swap(A[A.size() - 2], A[A.size() - 1]);
    }
};


int
main()
{
    Solution_Messy                 sol_messy;
    Solution_Concise_and_Efficient sol_concise;



    // std::vector<int> A = {6, 4, 3, 1, 5};
    std::vector<int> A = {7, 5, 3, 2, 4, 9, 8, 6, 1, 12, 14};
    // std::vector<int> A = {2};
    // std::vector<int> A = {1, 4};
    // std::vector<int> A = {5, 4, 3, 1, 7, 2, 9, 11, 13, 15, 19};
    // std::vector<int> A = {4, 7, 2, 9, 5, 6, 8, 1, 3, 12, 43, 92, 0};


    // std::vector<int> A = {6, 7, 3, 5, 4, 2, 8};
    // std::vector<int> A = {7, 6, 3, 5, 4, 2, 8};
    // std::vector<int> A = {2, 5, 8, 1, 4, 6, 3};
    // std::vector<int> A = {2, 5, 8, 1, 4, 7, 6, 3, 9};
    // std::vector<int> A = {6, 1, 8, 7, 2, 5, 4, 3};
    // std::vector<int> A = {6, 1, 8, 7, 2, 5, 4, 3, 9};
    // std::vector<int> A = {4, 1, 6, 5, 2, 3};
    // std::vector<int> A = {4, 1, 6, 5, 2, 3, 7};
    // std::vector<int> A = {8, 6, 2, 4, 7, 1, 5, 3};
    // std::vector<int> A = {8, 5, 2, 7, 4, 1, 6, 3, 9};
    // std::vector<int> A = {1, 1, 1, 1, 4, 4, 4, 4};
    // std::vector<int> A = {1, 1, 1, 1, 4, 4, 4, 4, 4};
    // std::vector<int> A = {1, 1, 1, 1, 1, 4, 4, 4, 4};

    /* Write Input */
    std::cout << "\n\tBefore:";
    bool first = true;
    std::cout << "\n\tA: [";
    for (auto x: A)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    /* Solution */
    sol_messy.solution(A);
    // sol_concise.solution(A);


    /* Write Output */
    std::cout << "\n\tAfter:";
    first = true;
    std::cout << "\n\tA: [";
    for (auto x: A)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";

    return 0;
}
