#include <iostream>
#include <typeinfo>

#include "test.h"
#include "skip_list.h"


void Test(const TestSkipList& sl)
{
	int level = 0;
	while (level < TestSkipList::KMax_Height)
	{
		printf("level %d - ", level);
		auto right_of = sl.nodes_[0].next[level];

		while (right_of != TestSkipList::KTombstone)
		{
			printf(" %d ", sl.values_[right_of]);
			right_of = sl.nodes_[right_of].next[level];
		}
		printf("\n");
		++level;
	}
}


int main()
{
	TestSkipList skip_list;
	skip_list.Insert(55);
	skip_list.Insert(33);
	skip_list.Insert(4565);
	skip_list.Insert(887);
	skip_list.Insert(6554);
	skip_list.Insert(5466);

	Test(skip_list);

	std::cin.get();
	return 0;
}