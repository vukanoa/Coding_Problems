#include <iostream>
#include <vector>

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
	std::cout << "\n\tSolution is: " << solution(6) << "\n\n";
	// std::cout << "\n\tSolution is: " << solution(10) << "\n\n";
	// std::cout << "\n\tSolution is: " << solution(2) << "\n\n";
	// std::cout << "\n\tSolution is: " << solution(8) << "\n\n";
	// std::cout << "\n\tSolution is: " << solution(9) << "\n\n";
	// std::cout << "\n\tSolution is: " << solution(1) << "\n\n";
	// std::cout << "\n\tSolution is: " << solution(0) << "\n\n";
	// std::cout << "\n\tSolution is: " << solution(1000000000) << "\n\n";

	return 0;
}
