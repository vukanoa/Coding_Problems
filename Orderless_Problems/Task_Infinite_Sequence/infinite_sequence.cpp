#include <iostream>
#include <vector>

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


/*
	0 1 1 2 3 5 8 13 12 7 10 8 9, ...
*/

int
sum_digits(int n)
{
	int sum = 0;
	while (n != 0)
	{
		sum = sum + n % 10;
		n = n / 10;
	}

	return sum;
}


/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N) */
int
solution (int N)
{
	if (N < 0)
		return -1;

	if (N > 1000000000)
		return -1;

	if (N == 0)
		return 0;

	if (N == 1)
		return 1;

	// Initial elements
	std::vector<int> vect;
	vect.push_back(0);
	vect.push_back(1);

	/*
		It's not as efficient to call a function every time within this
		for loop, so unless a compiler optimizes this function (which it probably will)
		in the place we call it (sum_digits), then it would've been more
		efficient to write "hard coded" version of this function inside this
		for loop since it's called twice in every iteration.
	*/

	// But for purposes of readability I will leave this the way it is.
	int sum = 0;
	unsigned N_unsigned = (unsigned) N;
	for (unsigned i = 2; vect.size() <= N_unsigned; i++)
	{
		sum = sum_digits(vect[i-1]) + sum_digits(vect[i-2]);
		vect.push_back(sum);
	}


	return vect[N];
}

int
main()
{
	std::cout << "\n\t\t\tUsing function\n";
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

	// 9609ms
	std::cout << "\n\tSolution (100 000 000)  : " << solution(100000000) << "\n\n";

sw.tock();
std::cout << "This took " << sw.report_ms() << "ms.\n";

	return 0;
}
