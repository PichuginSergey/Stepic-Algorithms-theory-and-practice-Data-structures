/* You need to determine the height of the tree. 
The tree is specified as an array, each element of which stores the number of its parent. 
The root node stores the number itself.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstddef>
 
struct Link 
{
	Link(int data, Link* next = nullptr) : data_(data), next_(next){}
	int data_;
	Link* next_;
};

class Tree
{
public:
	Tree(std::size_t size) : root_(INVALID_ROOT_IDX), tree_(size, nullptr) {}
	~Tree() 
	{
		std::for_each(tree_.begin(), tree_.end(), DeleteList());
	}
	void addBranch(std::size_t nodeParent, int nodeChild)
	{
		tree_[nodeParent] = new Link(nodeChild, tree_[nodeParent]);
	}
	void setRoot(int root) 
	{
		root_ = root;
	}
	std::size_t getHeight() const;
	static const int ROOT_MARKER;
	static const int INVALID_ROOT_IDX;
private:
	struct DeleteList
	{
		void operator()(const Link* node)
		{
			while(node != nullptr)
			{
				const Link* tmp {node};
				node = node->next_;
				delete tmp;
			}
		}
	};
	int root_;
	std::vector<Link*> tree_;
};

std::size_t Tree::getHeight() const
{
	using std::pair<int, int> = Elm;
	if (root_ == INVALID_ROOT_IDX) 
		return 0;
	std::stack<Elm> s;
	s.push(std::make_pair(root_, 1));
	int height {1};
	while(!s.empty())
	{
		auto idx = s.top(); s.pop();
		if (idx.second > height)
			height = idx.second;
		for (Link* tmp = tree_[idx.first]; tmp != nullptr; tmp = tmp->next_)
			s.push(std::make_pair(tmp->data_, idx.second + 1));
	}
	return height;
}
const int Tree::ROOT_MARKER = -1;
const int Tree::INVALID_ROOT_IDX = -1;

int main()
{
	std::size_t treeSize {0};
	std::cin >> treeSize;
	Tree tree(treeSize);
	std::size_t rootIdx {0};
	for (int idx = 0; idx < treeSize; ++idx)
	{
		int parentIdx {0};
		std::cin >> parentIdx;
		if (parentIdx != Tree::ROOT_MARKER)
			tree.addBranch(parentIdx, i);
		else
			tree.setRoot(i);
	}
	std::cout << tree.getHeight();
	return 0;
}