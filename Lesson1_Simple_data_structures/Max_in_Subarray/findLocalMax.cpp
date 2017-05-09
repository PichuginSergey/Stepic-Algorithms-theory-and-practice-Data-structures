#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstddef>

template <typename T>
class StackWithMax
{
public:
	void push(const T& data)
	{
		if (maxData_.empty() || data >= maxData_.top())
			maxData_.push(data);
		data_.push(data);
	}
	void pop()
	{
		if (data_.top() == maxData_.top())
			maxData_.pop();
		data_.pop();
	}
	T max()
	{
		return maxData_.top();
	}
	bool empty() const
	{
		return data_.empty();
	}
private:
	std::stack<T> data_;
	std::stack<T> maxData_;
};

template <typename T>
void findLocalMaxInArray(const std::vector<T>& A, int sizeWindow)
{
	std::stack<T> inStack;
	StackWithMax<T> outStack;
	T inStackMax = std::numeric_limits<T>::min();
	for (std::size_t i = 0; i < sizeWindow; ++i)
	{
		auto elm = A[i];
		if (elm > inStackMax)
			inStackMax = elm;
		inStack.push(elm);
	}
	for (std::size_t i = sizeWindow; i < A.size(); ++i)
	{
		if (outStack.empty())
		{
			for (std::size_t i = 0; i < sizeWindow; ++i)
			{
				outStack.push(inStack.top());
				inStack.pop();
				inStackMax = std::numeric_limits<T>::min();
			}
		}
		std::cout << std::max(outStack.max(), inStackMax) << ' ';
		outStack.pop();
		auto elm = A[i];
		if (elm > inStackMax)
			inStackMax = elm;
		inStack.push(elm);
	}
	if (A.size() >= sizeWindow)
		if (!outStack.empty())
			std::cout << std::max(outStack.max(), inStackMax);
		else
			std::cout << inStackMax;
}

/* Find the maximum in each subarray of size "sizeWindow" in array "A" of size "size" */
int main()
{
	std::size_t size{ 0 };
	std::cin >> size;
	std::vector<int> A(size);
	for (auto& elm : A)
		std::cin >> elm;
	std::size_t sizeWindow{ 0 };
	std::cin >> sizeWindow;
	findLocalMaxInArray(A, sizeWindow);
	return 0;
}