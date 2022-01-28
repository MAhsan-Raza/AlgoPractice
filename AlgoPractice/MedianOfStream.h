#pragma once


class StreamMedian
{
public:

	void AddElement(const int val)
	{
		this->InsertElement(val);
	}

	double GetMedian() const 
	{
		return this->GetMedian();
	}

protected:

	virtual void InsertElement(const int val)
	{
		/*
		* callc CalcMedian
		* if val is smaller or equal to Median
		*	choose lower q 
		* if val is greator than Median
		*	choose higher q 
		*/
	}

	virtual double CalcMedian() const
	{
		if (this->IsMiddlePresent)
			return MiddleVal;

		return (LowwerQueue.top() + HigherQueue.top()) / 2;
	}

private:

	int MiddleVal;
	bool IsMiddlePresent;

	priority_queue<int, vector<int>> LowwerQueue;
	priority_queue<int, vector<int>> HigherQueue;
};

void testStreamMedian(){}