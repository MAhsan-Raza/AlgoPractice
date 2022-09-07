#pragma once

/*class ListNode {
public:
    int value = 0;
    ListNode* next;

    ListNode(int value, ListNode* next) : value(value), next(next) {}

    ListNode(int val) : ListNode(val, nullptr) {}
};

void PrintSLL(ListNode* head)
{
    while(head)
    {
        cout << head->value << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}*/

ListNode* reverseList(ListNode* crnt, ListNode* prev = nullptr)
{
    if (!crnt)
        return prev;
    ListNode* next = crnt->next;
    crnt->next = prev;
    return reverseList(next, crnt);
}

ListNode* reverseList_ITRITV(ListNode* crnt) {

    ListNode* prev = nullptr;
    ListNode* next = nullptr;

    while (crnt)
    {
        next = crnt->next;
        crnt->next = prev;
        prev = crnt;
        crnt = next;
    }

    return prev;
}

ListNode* reverseBetween(ListNode* head, int left, int right)
{
    int index = 1;
    auto revList = [&](ListNode *&leftHead)->ListNode*
    {
        ListNode *prev = nullptr, *crnt = leftHead;

        while (crnt && index <= right)
        {
            ListNode* tmpNXT = crnt->next;
            crnt->next = prev;
            prev = crnt;
            crnt = tmpNXT;
            ++index;
        }

        leftHead->next = crnt;
        return prev;
    };

    ListNode *crnt1 = head, *prev = nullptr;

    while (crnt1)
    {
        if (index == left)
        {
            ListNode *headRev = revList(crnt1);

            if (prev)
            {
                prev->next = headRev;
                return head;
            }
            else
                return headRev;
        }
        else
        {
            prev = crnt1;
            crnt1 = crnt1->next;
        }
        ++index;
    }

    return head;
}

ListNode* reverseKGroup(ListNode* head, int k) 
{
    /*auto ReverseKNodes = [k](ListNode*& crnt)->ListNode* //Returns newSubHead
    {
        int sk = 0;
        ListNode* subPrev = nullptr;

        while (sk++ < k)
        {
            ListNode* subTmp = crnt->next;
            crnt->next = subPrev;
            subPrev = crnt;
            crnt = subTmp;
        }

        return subPrev;
    };*/

    auto HaveKNodes = [](ListNode* const crnt, const int tk)->bool
    {
        int ik = 0;
        ListNode* tmp = crnt;

        for (; tmp && ik < tk; ik++)
            tmp = tmp->next;

        return ik == tk;
    };

    int ik = 1;
    ListNode* crnt = head, * prev = nullptr, * newSubTail = head, * oldSubTail = nullptr, *newHead = nullptr;

    while (crnt && HaveKNodes(crnt, k - ik + 1))
    {
        if(ik <= k)
        {
            ListNode* tmpNXT = crnt->next;
            crnt->next = prev;
            prev = crnt;

            if (ik == k)
            {
                newHead = (!newHead) ? crnt : newHead;

                if (oldSubTail == nullptr)
                {
                    oldSubTail = newSubTail;
                }
                else
                {
                    oldSubTail->next = crnt;
                    oldSubTail = newSubTail;
                }
                newSubTail = tmpNXT;
                prev = nullptr;
                ik = 0;
            }
            crnt = tmpNXT;
            ++ik;
        }        
    }
    if (oldSubTail) oldSubTail->next = newSubTail;

    return newHead;

    /*while (crnt && HaveKNodes(crnt))
    { 
        newSubTail = crnt;
        ListNode* newSubHead = ReverseKNodes(crnt);

        if (prev)
            prev->next = newSubHead;
        else
            head = newSubHead;

        prev = newSubTail;
    }

    return head;*/
}

ListNode* reverseAlternateKGroup(ListNode* head, int k)
{
    int ik = 1;

    ListNode * crnt = head, * prev = nullptr, * subTail = head, * revSubTail = nullptr;

    while (crnt)
    {
        ListNode* tmpNXT = crnt->next;
        crnt->next = prev;
        prev = crnt;
        crnt = tmpNXT;

        if (ik == k)
        {
            if (subTail == head) 
            {
                head = prev;
                subTail->next = crnt;
            }
            else
            {
                subTail->next = prev;
                revSubTail->next = crnt;
            }

            ik = 0;
            while (crnt && ik++ < k)
            {
                prev = crnt;
                crnt = crnt->next;
            }
            ik = 0;
            subTail = prev;
            revSubTail = crnt;
            prev = nullptr;
        }

        ++ik;
    }
    return head;
}

ListNode* rotateRight(ListNode* head, int k) 
{
    if (!head || !head->next)    return head;

    auto GetLLTailNSize = [](ListNode* crnt, ListNode*& tail)
    {
        int size = 0;
        ListNode* prev = nullptr;
        while (crnt)
        {
            prev = crnt;
            crnt = crnt->next;
            ++size;
        }
        tail = prev;
        return size;
    };

    ListNode* tail = nullptr, * crnt = head;
    int LLSize = GetLLTailNSize(head, tail);

    if (LLSize == k || k == 0)     return head;
    else if (LLSize < k)
    {
        if (k % LLSize == 0)   return head;
        else                k = k % LLSize;
    }

    tail->next = head;

    int nSteps = 0;

    for (int i = 0; i < LLSize - k - 1; i++)
        crnt = crnt->next;

    head = crnt->next;
    crnt->next = nullptr;
    return head;
}

ListNode* swapPairs(ListNode* head)
{
    auto revPair = [](ListNode* crnt, ListNode*& grpHead, ListNode*& grpTail) -> ListNode*
    {
        if (!crnt->next)
        {
            grpHead = crnt;
            return nullptr;
        }

        ListNode* grpNxt = crnt->next->next;

        grpTail = crnt;
        grpHead = crnt->next;

        crnt->next = nullptr;
        grpHead->next = crnt;

        return grpNxt;
    };

    ListNode* crnt = head, * prevTail = nullptr, * grpHead = nullptr, * grpTail = nullptr;

    while (crnt)
    {
        crnt = revPair(crnt, grpHead, grpTail);

        if (nullptr == prevTail)     head = grpHead;
        else                        prevTail->next = grpHead;

        prevTail = grpTail;
    }

    return head;
}

void testInplaceLinkedListReversal()
{
    /*ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    PrintLL(head);
    PrintLL(reverseList(head));

    PrintLL(CreateLL({ 1,2,3,4,5 }));
    PrintLL(reverseBetween(CreateLL({ 1,2,3,4,5 }), 2, 4));
    PrintLL(CreateLL({ 5 }));
    PrintLL(reverseBetween(CreateLL({ 5 }), 1, 1));
    PrintLL(CreateLL({ 3,5 }));
    PrintLL(reverseBetween(CreateLL({ 3,5 }), 2, 2));
    PrintLL(CreateLL({ 1,2,3,4,5 }));
    PrintLL(reverseBetween(CreateLL({ 1,2,3,4,5 }), 1, 3));
    PrintLL(CreateLL({ 4,5 }));
    PrintLL(reverseBetween(CreateLL({ 4,5 }), 1, 2));
    PrintLL(CreateLL({ 10,20,30,40,50 }));
    PrintLL(reverseBetween(CreateLL({ 10,20,30,40,50 }), 4, 5));


    PrintLL(CreateLL({ 1,2,3,4,5 }));
    PrintLL(reverseKGroup(CreateLL({ 1,2,3,4,5 }), 2));

    PrintLL(CreateLL({ 1,2,3,4,5 }));
    PrintLL(reverseKGroup(CreateLL({ 1,2,3,4,5 }), 3));

    PrintLL(CreateLL({ 1,2,3,4,5,6,7,8,9,10 }));
    PrintLL(reverseKGroup(CreateLL({ 1,2,3,4,5,6,7,8,9,10 }), 4));


    PrintLL(CreateLL({ 1,2,3,4,5,6 }));
    PrintLL(reverseAlternateKGroup(CreateLL({ 1,2,3,4,5,6 }), 2));

    PrintLL(CreateLL({ 1,2,3 }));
    PrintLL(reverseAlternateKGroup(CreateLL({ 1,2,3 }), 3));

    PrintLL(CreateLL({ 1,2,3,4,5,6,7,8 }));
    PrintLL(reverseAlternateKGroup(CreateLL({ 1,2,3,4,5,6,7,8 }), 2));

    PrintLL(CreateLL({1,2,3,4,5,6}));
    PrintLL(rotateRight(CreateLL({ 1,2,3,4,5,6 }), 2)); cout << endl;

    PrintLL(CreateLL({ 1,2,3,4,5,6 }));
    PrintLL(rotateRight(CreateLL({ 1,2,3,4,5,6 }), 3)); cout << endl;

    PrintLL(CreateLL({ 1,2,3,4,5,6 }));
    PrintLL(rotateRight(CreateLL({ 1,2,3,4,5,6 }), 4)); cout << endl;

    PrintLL(CreateLL({ 1,2,3,4,5,6 }));
    PrintLL(rotateRight(CreateLL({ 1,2,3,4,5,6 }), 6)); cout << endl;

    PrintLL(CreateLL({ 1,2,3 }));
    PrintLL(rotateRight(CreateLL({ 1,2,3 }), 1)); cout << endl;

    PrintLL(CreateLL({ 1,2,3 }));
    PrintLL(rotateRight(CreateLL({ 1,2,3 }), 2)); cout << endl;

    PrintLL(CreateLL({ 1,2,3 }));
    PrintLL(rotateRight(CreateLL({ 1,2,3 }), 3)); cout << endl;

    PrintLL(CreateLL({ 1,2,3 }));
    PrintLL(rotateRight(CreateLL({ 1,2,3 }), 4)); cout << endl;

    PrintLL(CreateLL({ 1,2,3 }));
    PrintLL(rotateRight(CreateLL({ 1,2,3 }), 5)); cout << endl;*/


    /*
    * https://leetcode.com/problems/binary-tree-upside-down/
    * https://leetcode.com/problems/reverse-nodes-in-even-length-groups/
    * https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/
    * https://leetcode.com/problems/swapping-nodes-in-a-linked-list/
    * https://leetcode.com/problems/plus-one-linked-list/
    * https://leetcode.com/problems/add-two-polynomials-represented-as-linked-lists/
    * https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list/
    */
}