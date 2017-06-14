/* See problem 2.3 "processing network packets" */
#include <cstddef>
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Queue {

public:
	Queue(size_t max_size) : m_max_size(max_size), num_elm(0), front(-1), end(-1), m_elm(NULL) {
		m_elm = new T[m_max_size];
	}
	~Queue() { delete[] m_elm; }
	void push(const T& elm);
	T pop();
	T& peek() const;
	bool empty() const { return num_elm == 0; }
	bool full() const { return num_elm == m_max_size; }
private:
	const size_t m_max_size;
	size_t num_elm;
	int front;
	int end;
	T* m_elm;
};

template <typename T>
void Queue<T>::push(const T& elm)
{
	++num_elm;
	end = (++end) % m_max_size;
	m_elm[end] = elm;
}

template <typename T>
T& Queue<T>::peek() const {
	return m_elm[(front + 1) % m_max_size];
}

template <typename T>
T Queue<T>::pop() {
	--num_elm;
	front = (++front) % m_max_size;
	return m_elm[front];
}

int main()
{
	std::size_t size{ 0 };
	std::cin >> size;
	Queue<int> buffer(size);
	std::size_t num_query;
	std::cin >> num_query;
	int cutTime{ 0 };
	std::vector<int> log;
	while (num_query > 0)
	{
		int arrive{ 0 }, duration{ 0 };
		std::cin >> arrive >> duration;
		if (buffer.empty())
		{
			cutTime = std::max(cutTime, arrive);
			log.push_back(cutTime);
			cutTime = cutTime + duration;
			buffer.push(cutTime);
		}
		else
		{
			while (!buffer.empty() && buffer.peek() <= arrive)
				buffer.pop();
			if (buffer.full())
				log.push_back(-1);
			else
			{
				cutTime = std::max(cutTime, arrive);
				log.push_back(cutTime);
				cutTime = cutTime + duration;
				buffer.push(cutTime);
			}
		}
		--num_query;
	}

	for (auto elm : log)
		std::cout << elm << '\n';
}