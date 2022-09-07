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

/*inline vector<int> GetDigits(int num)
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
*/
bool IsHappyNum_Labmda(int num)
{
	auto happyStep = [](int i)->int 
	{
		int res = 0;

		while (i > 0)
		{
			int digi = i % 10;
			res += pow(digi, 2);
			i /= 10;
		}

		return res;
	};

	int slowStep = num, fastStep = num;

	while (1 != fastStep)
	{
		slowStep = happyStep(slowStep);
		fastStep = happyStep(happyStep(fastStep));

		if (1 != fastStep && slowStep == fastStep)
			return false;
	}

	return true;
}


inline LLNode* deleteMiddle(LLNode* head)
{
	auto slow = head, fast = head;
	LLNode* prev = slow;

	while (fast && fast->next)
	{
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}

	if (prev == head && head->next == nullptr)
		return nullptr;
	else if (prev == head && head->next->next == nullptr)
		head->next = nullptr;
	else
		prev->next = slow->next;

	return head;
}

// Fast&Slow Pointer W/ list manipulation -> O(1) space & O(N) time
inline bool isPalindrome(ListNode* head)
{
	auto GetMidNode = [&head]()->ListNode*
	{
		ListNode* slow = head, * fast = head;

		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}

		return slow;
	};

	auto ReverseLL = [](ListNode* crnt)->ListNode*
	{
		ListNode* prev = nullptr;

		while (crnt)
		{
			ListNode* tmpNxt = crnt->next;
			crnt->next = prev;
			prev = crnt;
			crnt = tmpNxt;
		}

		return prev;
	};

	auto CompareTwoLL = [](ListNode* h1, ListNode* h2)->bool
	{
		while (h2)
		{
			if (h1->val != h2->val)
				return false;
			h1 = h1->next;
			h2 = h2->next;
		}

		return true;
	};

	ListNode* h2 = ReverseLL(GetMidNode());

	return CompareTwoLL(head, h2);
}

inline void reorderList(ListNode* head)
{
	if (!head || !head->next || !head->next->next)	return;

	auto SplitAndRevOthr = [&head]()->ListNode*
	{
		ListNode* slow = head, * fast = head, * prev = nullptr;

		while (fast && fast->next)
		{
			prev = slow;
			slow = slow->next;
			fast = fast->next->next;
		}

		if (prev) prev->next = nullptr;

		prev = nullptr;
		while (slow)
		{
			ListNode* nx = slow->next;
			slow->next = prev;
			prev = slow;
			slow = nx;
		}
		return prev;
	};

	auto MergeTwo = [&head](ListNode* h2)
	{
		ListNode* crH1 = head;
		while (crH1)
		{
			ListNode* nxH1 = crH1->next;
			ListNode* nxH2 = h2->next;

			crH1->next = h2;
			h2->next = nxH1;

			if (!nxH1)
				crH1->next->next = nxH2;
			
			crH1 = nxH1;
			h2 = nxH2;			
		}
	};

	MergeTwo(SplitAndRevOthr());
}

bool circularArrayLoop(const vector<int>& nums)
{
	if (nums.empty() || nums.size() == 1)	return false;

	auto GetIndexCircular = [&nums](int relindx)->int
	{
		while (relindx >= (int)nums.size())
			relindx -= nums.size();

		while (relindx < 0)
			relindx += nums.size();

		if (relindx < 0 || relindx >= nums.size())
			throw exception();

		return relindx;
	};

	auto JumpToIndx = [&](int ofstIndx)->int
	{
		return GetIndexCircular(nums[ofstIndx] + ofstIndx);
	};

	auto GetInLoop = [&](const int start)->int
	{
		int slow = start, fast = start;

		while (true)
		{
			slow = JumpToIndx(slow);
			fast = JumpToIndx(JumpToIndx(fast));

			if (slow == fast)
				return slow;
		}
	};

	auto CheckLoop = [&](const int indxInLoop)->bool
	{
		bool SignIsPositv = nums[indxInLoop] > 0 ? true : false;
		int crnt = indxInLoop;
		int count = 0;

		do
		{
			if (SignIsPositv && nums[crnt] < 0)
				return false;

			if (SignIsPositv == false && nums[crnt] > 0)
				return false;

			++count;
			crnt = JumpToIndx(crnt);

		} while (crnt != indxInLoop);

		return count == 1 ? false : true;
	};

	for (int i = 0; i < nums.size(); i++)
	{
		int indxInLop = GetInLoop(i);

		if (CheckLoop(indxInLop))
			return true;
	}
	return false;	
}

void testFastSlowPointers()
{
	/*IsCyclicLinkedList(new LLNode(1, new LLNode(2, new LLNode(3))));
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
	IsHappyNumber(19);

	IsHappyNum_Labmda(10);
	IsHappyNum_Labmda(2);
	IsHappyNum_Labmda(19);
	IsHappyNum_Labmda(23);
	IsHappyNum_Labmda(12);
	IsHappyNum_Labmda(20);

	isPalindrome(CreateLL({ 1,2,2,1 }));
	isPalindrome(CreateLL({ 1,2 }));
	isPalindrome(CreateLL({ 1 }));
	isPalindrome(CreateLL({  }));
	isPalindrome(CreateLL({ 1,2,2,5 }));


	PrintCompareLL(CreateLL({ 1,2,3,4 }), reorderList);
	PrintCompareLL(CreateLL({ 1,2,3,4,5 }), reorderList);
	PrintCompareLL(CreateLL({ 1 }), reorderList);
	PrintCompareLL(CreateLL({ }), reorderList);*/

	circularArrayLoop({ 3,1,2 });
	circularArrayLoop({ 2,-1,1,2,2 });
	circularArrayLoop({ -1,2 });
	circularArrayLoop({ -2,1,-1,-2,-2 });
	circularArrayLoop({ 2,-1,1,2,2 });
	circularArrayLoop({ 1, 2, -1, 2, 2 });
	circularArrayLoop({ 2, 2, -1, 2 });
	circularArrayLoop({ 2, 1, -1, -2 });
	circularArrayLoop({ -1 });
	circularArrayLoop({ -9 });
	circularArrayLoop({  });
}