#include "Node.h"
class Compare
{
public:
	bool operator() (Node* a, Node* b) {
		return a->frequency > b->frequency;
	}
};