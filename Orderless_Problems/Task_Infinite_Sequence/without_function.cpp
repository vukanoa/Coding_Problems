#include<iostream>
#include<vector>

#include <chrono>
#include <ctime>

template <typename T> class basic_stopwatch
{
    typedef T clock;
    typename clock::time_point p;
    typename clock::duration   d;

public:
    void tick()  { p  = clock::now();            }
    void tock()  { d += clock::now() - p;        }
    void reset() { d  = clock::duration::zero(); }

    template <typename S> unsigned long long int report() const
    {
        return std::chrono::duration_cast<S>(d).count();
    }

    unsigned long long int report_ms() const
    {
        return report<std::chrono::milliseconds>();
    }

    basic_stopwatch() : p(), d() { }
};

struct c_clock
{
    typedef std::clock_t time_point;
    typedef std::clock_t duration;
    static time_point now() { return std::clock(); }
};

template <> unsigned long long int basic_stopwatch<c_clock>::report_ms() const
{
	return 1000. * double(d) / double(CLOCKS_PER_SEC);
}

typedef basic_stopwatch<std::chrono::high_resolution_clock> stopwatch;
typedef basic_stopwatch<c_clock> cstopwatch;



/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N) */
int solution(int N)
{
	if (N == 0)
		return 0;

	if (N == 1)
		return 1;

	// Initialize vector with first two elements
	std::vector<int> sequence = {0, 1};

	// Generate remaining elements using dynamic programming
	for (int i = 2; i <= N; i++)
	{
		// Compute sum of separate digits of previous two elements
		int a = sequence[i - 1];
		int b = sequence[i - 2];
		int digits_sum = 0;

		while (a > 0)
		{
			digits_sum += a % 10;
			a /= 10;
		}

		while (b > 0)
		{
			digits_sum += b % 10;
			b /= 10;
		}

		// Add new elements to sequence
		sequence.push_back(digits_sum);
	}

	// Return N-th element
	return sequence[N];
}


int
main()
{
	std::cout << "\n\t\t\tWithout function\n";
	// std::cout << "\n\tSolution (6) : " << solution(6) << "\n\n";
	// std::cout << "\n\tSolution (10): " << solution(10) << "\n\n";
	// std::cout << "\n\tSolution (2) : " << solution(2) << "\n\n";
	// std::cout << "\n\tSolution (8) : " << solution(8) << "\n\n";
	// std::cout << "\n\tSolution (9) : " << solution(9) << "\n\n";
	// std::cout << "\n\tSolution (1) : " << solution(1) << "\n\n";
	// std::cout << "\n\tSolution (0) : " << solution(0) << "\n\n";

	// std::cout << "\n\tSolution (1 000 000)    : " << solution (1000000) << "\n\n";
	// std::cout << "\n\tSolution (10 000 000) : " << solution(10000000) << "\n\n";
	// std::cout << "\n\tSolution (100 000 000)  : " << solution(100000000) << "\n\n";
	// std::cout << "\n\tSolution (1000 000 000) : " << solution(1000000000) << "\n\n";

stopwatch sw;
sw.tick();

	// 7605ms
	std::cout << "\n\tSolution (100 000 000)  : " << solution(100000000) << "\n\n";

sw.tock();
std::cout << "This took " << sw.report_ms() << "ms.\n";



	return 0;
}

