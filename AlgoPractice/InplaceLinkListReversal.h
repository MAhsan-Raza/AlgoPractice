#pragma once

class ListNode {
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
}

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

void testInplaceLinkedListReversal()
{
    ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    PrintSLL(head);
    PrintSLL(reverseList(head));
}