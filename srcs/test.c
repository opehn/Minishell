#include "parsing.h"

int main()
{
	t_node a;
	a.type = CHAR_NODE;
	a.data.value = 'a';

	t_node b;
	b.type = CHAR_NODE;
	b.data.value = 'b';

	Node p;
	p.type = PAIR_NODE;
	p.data.pair.left = &a;
	p.data.pair.right = &b;
}

