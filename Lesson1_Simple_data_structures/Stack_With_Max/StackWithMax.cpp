#include <iostream>
#include <stack>
#include <string>
class StackWithMax
{
public:
	void push(int data)
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
	void max()
	{
		if (!maxData_.empty())
			std::cout << maxData_.top() << '\n';
	}
private:
	std::stack<int> data_;
	std::stack<int> maxData_;
};

int main()
{
	int num_cmd = 0;
	StackWithMax stackWithMax;
	std::cin >> num_cmd;
	while (num_cmd > 0)
	{
		std::string cmd;
		std::cin >> cmd;
		if (cmd == "push")
		{
			int data;
			std::cin >> data;
			stackWithMax.push(data);
		}
		else if (cmd == "pop")
			stackWithMax.pop();
		else if (cmd == "max")
			stackWithMax.max();
		--num_cmd;
	}
	return 0;
}