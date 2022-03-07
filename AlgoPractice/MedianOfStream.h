#pragma once
#include<conio.h>


/*
* callc CalcMedian
* if val is smaller or equal to Median
*	choose lower q
* if val is greator than Median
*	choose higher q
*
* if middle present
*	push the val to the selected queue
*	push middle to the other queue
* else
*	push the val to selected queue
*	remove top of SELQ & mmake it middle
*/
class StreamMedian
{
public:

	StreamMedian() : IsMiddlePresent(false)
	{
	}

	virtual ~StreamMedian() = default;

	double AddElement(const int val)
	{
		return this->InsertElement(val);
	}

	double GetMedian() const 
	{
		return this->GetMedian();
	}

protected:

	virtual double InsertElement(const int val)
	{
		double crntMedian = this->CalcMedian();
		bool IsLowerQSeld = val > crntMedian ? false : true;

		if (this->IsMiddlePresent)
		{
			this->PushToQ(val, IsLowerQSeld, false);
			this->PushToQ(this->MiddleVal, IsLowerQSeld, true);
			this->IsMiddlePresent = false;
		}
		else
		{
			this->PushToQ(val, IsLowerQSeld, false);
			this->IsMiddlePresent = true;
			this->MiddleVal = PopFromSelectedQ(IsLowerQSeld);
		}

		return this->CalcMedian();
	}

	virtual double CalcMedian() const
	{
		if (!IsMiddlePresent & LowerQueue.empty() && HigherQueue.empty())
			return 0;

		if (this->IsMiddlePresent)
			return MiddleVal;

		return (LowerQueue.top() + HigherQueue.top()) / 2.0;
	}

	virtual void PushToQ(const int val, const bool IsLowerQSeld, const bool PushToOther)
	{
		if (PushToOther)
		{
			if (IsLowerQSeld)
				this->HigherQueue.push(val);
			else
				this->LowerQueue.push(val);
		}
		else
		{
			if (IsLowerQSeld)
				this->LowerQueue.push(val);
			else
				this->HigherQueue.push(val);
		}
	}

	virtual int PopFromSelectedQ(const bool IsLowerQSeld)
	{
		int tmp = 0;
		if (IsLowerQSeld)
		{
			tmp = this->LowerQueue.top();
			this->LowerQueue.pop();
		}
		else
		{
			tmp = this->HigherQueue.top();
			this->HigherQueue.pop();
		}
		return tmp;
	}

private:

	int MiddleVal;
	bool IsMiddlePresent;

	priority_queue<int> LowerQueue;								//Max Queue
	priority_queue<int, vector<int>, std::greater<int>> HigherQueue;			//Min Queue 
};

void GeneratNPrintSM(vector<int>& tmp, StreamMedian& sm, const int n)
{
	tmp.push_back(n);
	std::sort(tmp.begin(), tmp.end());
	//cout << endl;
	for_each(tmp.begin(), tmp.end(), [](const int x) {cout << x << " "; });
	cout /* << endl */ << ",   Median:- ";
	cout << sm.AddElement(n);
	cout << endl;
}

void testStreamMedian()
{
	srand(time(NULL));
	vector<int> tmp;
	StreamMedian sm;

	/*while (_getch() != 'x')
	{
		GeneratNPrintSM(tmp, sm, rand() % 10 + 1);
	}*/

	for (size_t i = 0; i < 20; i++)
	{
		GeneratNPrintSM(tmp, sm, rand() % 100 + 1);
	}
}