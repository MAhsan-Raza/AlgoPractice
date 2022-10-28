// AlgoPractice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<string>
#include<vector>
#include<functional>
#include<algorithm>
#include<map>
#include<stack>
#include<set>
#include<queue>
#include<unordered_set>
#include<queue>
#include<unordered_map>
#include<chrono>
using namespace std::chrono;

using namespace std;

#include "Helpers.h"

/*#include "SlidingWindow.h"
#include "Sorting.h"
#include "TwoPointers.h"
#include "FastNSlowPointer.h"
#include "NumberTheory.h"
#include "IntervalsScheduling.h"
#include "InplaceLinkListReversal.h"
#include "BTreeDFS.h"
#include "BTreeLevelOrderTrv-BFS.h"
#include "CyclicSort.h"*/
/*#include "MedianOfStream.h"
#include "CombsAndPermuts.h"
#include "Subsets.h"
#include "MISC.h"*/
/*#include "BSearch.h"
#include "TopKNums_Heap.h"
#include "KSortedLists.h"
#include "DivideAndConquer.h"
#include "BSearchTree.h"*/
#include "Knapsack.h"
#include "Fibonacci.h"
#include "PalindromeSubseq.h"

#include "LongestCommonSubString.h"
#include "GreedyAlgos.h"
#include "GraphTheory.h"
#include "BSearchTree.h"

int main()
{
    /*testSlidingWindow();
    testSorting();
    testTwoPointers();
    testFastSlowPointers();
    testNumberTheory();
    testIntervalScheduling();
    testInplaceLinkedListReversal();
    testBTree();
    BTreeLevelOrderTrv_BFS();
    testCyclicSort();*/
    /*testStreamMedian();
    CombsAndPermuts();
    testSubsets();
    testMISC();*/
    /*testBSearch();
    testTopKNums_Heap();
    testKSortedLists();
    testDivideAndConquer();*/

    testKnapsack();
    testFib_DynoPro();
    testPalindromeSubseq();
    testLongestCommonSubString();
    testGreedyAlgos();
    testGraphTheory();
    testBSearchTree();

    /*
        https://leetcode.com/problems/smallest-number-in-infinite-set/
        https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/
        https://leetcode.com/problems/append-k-integers-with-minimal-sum/
        https://leetcode.com/problems/find-unique-binary-string/

    */

    return 0;
}
