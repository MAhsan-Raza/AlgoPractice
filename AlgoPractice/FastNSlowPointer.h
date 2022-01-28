#pragma once

using LLNode = struct _LLNode {

	int data;
	_LLNode* next;

	_LLNode(int data, _LLNode* next) : data(data), next(next) {}
	_LLNode(int data) : _LLNode(data, nullptr) {}
	_LLNode() : _LLNode(0, nullptr) {}
};

bool IsCyclicLinkedList(LLNode* head)
{
	LLNode* slow = head;
	LLNode* fast = head;

	while(fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast)
			return true;
	}

	return false;
}

int LLLoopLength(LLNode* head)
{
	int len = 0;
	LLNode* slow = head;
	LLNode* fast = head;
	bool LoopDetected = false;

	while (fast && fast->next)
	{
		slow = slow->next;

		if (LoopDetected)	++len;
		else				fast = fast->next->next;

		if (slow == fast)
		{
			if(LoopDetected)	return len;
			else				LoopDetected = true;
		}
	}

	return len;
}

LLNode* LLLoopStart(LLNode* head)
{
	int len = LLLoopLength(head);

	if (len == 0)
		return nullptr;

	LLNode* inLoopNode = head;
	while (len--)	inLoopNode = inLoopNode->next;

	while (head != inLoopNode)
	{
		head = head->next;
		inLoopNode = inLoopNode->next;
	}

	return head;
}

void BreakLLLoop(LLNode*& head, LLNode* loopStart)
{
	if (!head || !loopStart)		return;

	bool inLoop = false;
	LLNode* current = head;
	while (true)
	{
		if(current->next == loopStart)
		{
			if (inLoop)
			{
				current->next = nullptr;
			}
			else
			{
				inLoop = true;
			}
		}

		current = current->next;
	}
}

int MiddleOfLL(LLNode* head)
{
	_ASSERT(head);
	LLNode* slow = head;
	LLNode* fast = head;

	while (fast && fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow->data;
}

using Point = pair<int, int>;

void GetNextPositions(const string& cmd, int& index, char& direction, Point& currentPos)
{
	if (cmd[index] == 'G')
	{
		if (direction == 'N')
		{
			++currentPos.second;
		}
		else if (direction == 'W')
		{
			--currentPos.first;
		}
		else if (direction == 'E')
		{
			++currentPos.first;
		}
		else //'S'
		{
			--currentPos.second;
		}
	}
	++index;
}

void SetDirection(const string& cmd, int& index, char& direction)
{
	while(cmd[index] != 'G')
	{
		if (cmd[index] == 'L')
		{
			switch (direction)
			{
			case 'N':	direction = 'W'; break;
			case 'W':	direction = 'S'; break;
			case 'S':	direction = 'E'; break;
			case 'E':	direction = 'N'; break;
			}
		}
		else if (cmd[index] == 'R')
		{
			switch (direction)
			{
			case 'N':	direction = 'E'; break;
			case 'W':	direction = 'N'; break;
			case 'S':	direction = 'W'; break;
			case 'E':	direction = 'S'; break;
			}
		}
		index = ++index >= cmd.size() ? index - cmd.size() : index;
	}
}

bool RobotInCircle(const string& instrs)
{
	Point slowP = make_pair(0, 0);
	char slowD = 'N';
	int slowI = 0;
	Point fastP = make_pair(0, 0);
	char fastD = 'N';
	int fastI = 0;

	for (int i = 0; i < instrs.size() * 10; i++)
	{
		SetDirection(instrs, slowI, slowD);
		GetNextPositions(instrs, slowI, slowD, slowP);

		SetDirection(instrs, fastI, fastD);
		GetNextPositions(instrs, fastI, fastD, fastP);
		SetDirection(instrs, fastI, fastD);
		GetNextPositions(instrs, fastI, fastD, fastP);

		cout << "Slow:- " << slowP.first << "," 
			<< slowP.second << "   " << slowD << endl << "Fast:- " 
			<< fastP.first << "," << fastP.second << "   " << fastD << endl << endl;

		if (slowP == fastP && slowD == fastD)
			return true;
	}

	return false;
}

inline vector<int> GetDigits(int num)
{
	vector<int> res;

	int mr = 10;
	while (num)
	{
		res.push_back(num % mr);
		num /= mr;
		mr * 10;
	}
	return res;
}

inline int HappyCalc(const int num)
{
	int happy = 0;

	for (auto x : GetDigits(num))
		happy += pow(x, 2);

	return happy;
}

bool IsHappyNumber(const int num)
{
	int fast = num;
	int slow = num;

	while ( fast != 1)
	{ 
		slow = HappyCalc(slow);
		fast = HappyCalc(HappyCalc(fast));

		if (slow == fast)
			return false;
	}

	return true;
}

void testFastSlowPointers()
{
	//IsCyclicLinkedList(new LLNode(1, new LLNode(2, new LLNode(3))));
	LLNode* tmp = nullptr;
	LLNode* head = new LLNode(1, new LLNode(2, tmp = new LLNode(3, new LLNode(4, new LLNode(5, nullptr)))));
	//head->next->next->next->next->next = tmp;
	//IsCyclicLinkedList(head);
	//LLLoopLength(head);
	//auto x = LLLoopStart(head);
	//MiddleOfLL(head);
	/*RobotInCircle("GGLLGG");
	RobotInCircle("GG");
	RobotInCircle("GGL");
	RobotInCircle("GGLRL");
	RobotInCircle("GGLR");
	RobotInCircle("GGLLR");
	IsHappyNumber(19);*/
}