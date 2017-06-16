#include <iostream>
#include <cstddef>
#include <functional> 

template <typename T, typename Comp = std::greater<T>>
class Heap
{
public:
	Heap(int size) : heap(new T[size]), maxSize(size), curSize(0) {}
	~Heap() { delete[] heap; }
	void insert(const T& elm);
	T getMax() { return heap[curSize]; }
	T remove();
	int size() { return curSize; }

private:
	void up(int idx);
	void down(int idx);
	T* heap;
	int maxSize;
	int curSize;
};

template <typename T, typename Comp>
void Heap<T, Comp>::insert(const T& elm)
{
	heap[curSize] = elm;
	up(curSize++);
}

template <typename T, typename Comp>
T Heap<T, Comp>::remove()
{
	const T tmp = heap[0];
	heap[0] = heap[--curSize];
	down(0);
	return tmp;
}

template <typename T, typename Comp>
void Heap<T, Comp>::up(int idx)
{
	T tmp = heap[idx];
	while (idx > 0)
	{
		int parent = (idx - 1) / 2;
		if (Comp()(heap[parent], tmp))
			break;
		heap[idx] = heap[parent];
		idx = parent;
	}
	heap[idx] = tmp;
}

template <typename T, typename Comp>
void Heap<T, Comp>::down(int idx)
{
	T tmp = heap[idx];
	while (idx < curSize / 2)
	{
		int left = 2 * idx + 1;
		int right = left + 1;
		int maximum = 0;
		if (right < curSize && Comp()(heap[right], heap[left]))
			maximum = right;
		else
			maximum = left;
		if (Comp()(heap[maximum], tmp))
			heap[idx] = heap[maximum];
		else
			break;
		idx = maximum;
	}
	heap[idx] = tmp;
}

template <typename T1, typename T2>
struct Task
{
	T1 timeEnd;
	T2 numProce;
	Task(T1 time = 0, T2 num = 0) : timeEnd(time), numProce(num) {}
	bool operator<(const Task& rhs) const
	{
		if (timeEnd == rhs.timeEnd)
			return (numProce < rhs.numProce);
		else
			return timeEnd < rhs.timeEnd;
	}
};

int main()
{
	uint32_t numProc{ 0 }, numTasks{ 0 };
	std::cin >> numProc >> numTasks;
	using LongTask = Task<uint64_t, uint32_t>;
	Heap<LongTask, std::less<LongTask>> processing(numProc);
	for (std::size_t idx = 0; idx < numProc; ++idx)
		processing.insert(LongTask(0, idx));
	for (std::size_t idx = 0; idx < numTasks; ++idx)
	{
		uint64_t time{ 0 };
		std::cin >> time;
		LongTask task = processing.remove();
		std::cout << task.numProce << ' ' << task.timeEnd << '\n';
		processing.insert(LongTask(task.timeEnd + time, task.numProce));
	}

	return 0;
}
