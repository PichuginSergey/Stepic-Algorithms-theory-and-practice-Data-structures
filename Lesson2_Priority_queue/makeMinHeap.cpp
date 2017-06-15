/* Make min Heap from input array */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstddef>

template <typename T>
void makeminHeap(std::vector<T>& data)
{
	const auto size = data.size();
	if (size < 2)
		return;
	std::vector<std::pair<int, int>> log;
	for (int idx = size / 2; idx >= 0; --idx)
	{
		int curIdx{ idx };
		const T curElm{ data[idx] };
		while (curIdx < size / 2)
		{
			int left = 2 * curIdx + 1;
			int right = left + 1;
			int small = left;
			if (right < size && data[left] > data[right])
				small = right;
			if (data[small] < curElm)
			{
				log.push_back(std::make_pair(curIdx, small));
				data[curIdx] = data[small];
				curIdx = small;
			}
			else
				break;
		}
		data[curIdx] = curElm;
	}
	if (!log.empty())
	{
		std::cout << log.size() << '\n';
		for (const auto& elm : log)
			std::cout << elm.first << ' ' << elm.second << '\n';
	}
    else
        std::cout << 0;
}

int main(int argc, char* argv[])
{
	std::size_t size{ 0 };
	std::cin >> size;
	std::vector<int> data;
	data.reserve(size);
	std::copy(std::istream_iterator<int>(std::cin),
				std::istream_iterator<int>(),
				std::back_inserter(data));
	makeminHeap(data);
	return 0;
}