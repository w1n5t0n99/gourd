#include <iostream>
#include <typeinfo>

#include "test.h"
#include "skip_list.h"


void Test(const SkipList<int, 16>& sl)
{
	int level = 0;
	while (level < SkipList<int, 16>::KMax_Height)
	{
		printf("level %d - ", level);
		auto right_of = sl.nodes_[0].next[level];

		while (right_of != SkipList<int, 16>::KTombstone)
		{
			printf(" %d ", sl.nodes_[right_of].data);
			right_of = sl.nodes_[right_of].next[level];
		}
		printf("\n");
		++level;
	}
}


int main()
{
	SkipList<int, 16> skip_list;
	skip_list.Insert(55);
	skip_list.Insert(33);
	skip_list.Insert(4565);
	skip_list.Insert(887);
	skip_list.Insert(6554);
	skip_list.Insert(5466);

	Test(skip_list);
	
	if (skip_list.Find(887))
		printf("Found!\n");
	else
		printf("Not found!\n");



	std::cin.get();
	return 0;
}