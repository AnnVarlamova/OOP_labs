#include "tlinkedlist.h"

tT
LT::TLinkedList() : beginning(nullptr), end(nullptr) {}

tT
LT::TLinkedList(const TLinkedList &other)
{
    beginning = other.beginning;
    end = other.end;
}

tT
sT LT::First()
{
    if (beginning == nullptr) {
        std::cout << "The list is empty" << std::endl;
        exit(1);
    }
    return beginning->GetOctagon();
}

tT
sT LT::Last()
{
    if (end == nullptr) {
        std::cout << "The list is empty" << std::endl;
        exit(1);
    }
    return end->GetOctagon();
}

tT
sT LT::GetItem(size_t position)
{
    size_t n = this->Length();
    if (beginning == nullptr) {
        std::cout << "The list is empty" << std::endl;
        exit(1);
    }
    if (position > n) {
        std::cout << "The is no such position" << std::endl;
        exit(1);
    }
    if (position == 1) {
        return beginning->GetOctagon();
    }
    if (position == n) {
        return end->GetOctagon();
    }
    sIT node = beginning;
    for (size_t i = 1; i < position; ++i) {
        node = node->Right();
    }
    return node->GetOctagon();
}

tT
bool LT::Empty()
{
    return (beginning == nullptr);
}

tT
size_t LT::Length()
{
    size_t size = 0;
    for (sIT i = beginning; i != nullptr; i = i->Right()) {
        ++size;
    }
    return size;
}

tT
void LT::InsertFirst(sT octagon)
{
    sIT node(new IT(octagon));
    if (beginning == nullptr) {
        beginning = (end = node);
        return;
    }
    node->ToLeft(nullptr);
    node->ToRight(beginning);
    beginning->ToLeft(node);
    beginning = node;
}

tT
void LT::InsertLast(sT octagon)
{
    sIT node(new IT(octagon));
    if (beginning == nullptr) {
        beginning = (end = node);
        return;
    }
    node->ToLeft(end);
    node->ToRight(nullptr);
    end->ToRight(node);
    end = node;
}

tT
void LT::Insert(sT octagon, size_t position)
{
    size_t n = this->Length();
    if (position > n + 1) {
        std::cout << "The is no such position" << std::endl;
        return;
    }
    if (position == 1) {
        InsertFirst(octagon);
        return;
    }
    if (position == n + 1) {
        InsertLast(octagon);
        return;
    }
    sIT node(new IT(octagon));
    sIT now = beginning;
    for (size_t i = 1; i < position; ++i) {
        now = now->Right();
    }
    sIT before = now->Left();
    before->ToRight(node);
    now->ToLeft(node);
    node->ToLeft(before);
    node->ToRight(now);
}

tT
void LT::RemoveFirst()
{
    if (beginning == nullptr) {
        std::cout << "The list is empty" << std::endl;
        return;
    }
    if (end == beginning) {
        beginning = (end = nullptr);
        return;
    }
    sIT node = beginning;
    beginning = beginning->Right();
    beginning->ToLeft(nullptr);
}

tT
void LT::RemoveLast()
{
    if (end == nullptr) {
        std::cout << "The list is empty" << std::endl;
        return;
    }
    if (end == beginning) {
        beginning = (end = nullptr);
        return;
    }
    sIT node = end;
    end = end->Left();
    end->ToRight(nullptr);
}

tT
void LT::Remove(size_t position)
{
    size_t n = this->Length();
    if (beginning == nullptr) {
        std::cout << "The list is empty" << std::endl;
        return;
    }
    if (position > n) {
        std::cout << "The is no such position" << std::endl;
        return;
    }
    if (position == 1) {
        RemoveFirst();
        return;
    }
    if (position == n) {
        RemoveLast();
        return;
    }
    sIT node = beginning;
    for (size_t i = 1; i < position; ++i) {
        node = node->Right();
    }
    sIT node_left = node->Left();
    sIT node_right = node->Right();
    node_left->ToRight(node_right);
    node_right->ToLeft(node_left);
}

tT
std::ostream &operator<<(std::ostream &os, const LT &list)
{
    if (list.beginning == nullptr) {
        os << "List is empty" << std::endl;
        return os;
    }
    for (sIT i = list.beginning; i != nullptr; i = i->Right()) {
        if (i->Right() != nullptr)
            os << i->GetOctagon()->Area() << " -> ";
        else
            os << i->GetOctagon()->Area();
    }
    return os;
}

tT
void LT::Clear()
{
    while (beginning != nullptr) {
        RemoveFirst();
    }
}

tT
LT::~TLinkedList()
{
    while (beginning != nullptr) {
        RemoveFirst();
    }
}

template class TLinkedList<Octagon>;
template std::ostream& operator<<(std::ostream& os, const TLinkedList<Octagon>& list);