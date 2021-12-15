#include <vector>
#include <random>
#include <iostream>
#include <time.h>

using namespace std;

template <class T>
struct Node {
public:
	T key;
	Node<T>* next;
	Node<T>* prev;
	Node<T>* up;
	Node<T>* down;

	Node(const T& key) {
		this->key = key;
		this->next = nullptr;
		this->prev = nullptr;
		this->up = nullptr;
		this->down = nullptr;
	}

	void print() {
		if (key < INFINITY && key 
		> -INFINITY) cout << key << " ";
	}
};

template <class T>
class SkipList {
public:
	SkipList();
	
	void Insert(T N);
	
	Node<T>* InsertToLevel
	(T N, int level, Node<T>* down);

	void PrintData();

	Node<T>* Seartch(T key);

	void Delete(T N);

	void DeleteNode(Node<T>* N);

	vector<Node<T>*> Heads;

	int Levels;
};

template <class T>
SkipList<T> ::SkipList() {
	srand(static_cast<unsigned int>
	(time(NULL)));
	Node<T>* Head = new Node<T>(-INFINITY);
	Node<T>* Tail = new Node<T>(INFINITY);

	Head->next = Tail;
	Tail->prev = Head; 

	Heads.push_back(Head);
}


template<class T>
Node<T>* SkipList<T> ::InsertToLevel
(T data, int level, Node<T>* Down) {

	Node<T>* N = new Node<T>(data);
	N->down = Down;
	Node<T>* pt = new Node<T>(INFINITY);

	pt = Heads[level];

	while (pt->next != nullptr
		&& data > pt->next->key)
	{
		pt = pt->next;
	}

	N->prev = pt;
	N->next = pt->next;
	pt->next = N;
	return N;
}

template<class T>
void SkipList<T> ::Insert(T data) {
	int i = 0;

	Node<T>* Down =
		InsertToLevel(data, i, nullptr);

	int coinToss = rand() % 2;
	while (coinToss == 0)
	{
		i++;
		if (Levels < i)
		{
			Levels += 1;
			Node<T>* NewHead = new Node <T>(-INFINITY);
			Node<T>* NewTail = new Node <T>(INFINITY);
			NewHead->next = NewTail;
			NewTail->prev = NewHead;

			Heads[i - 1]->up = NewHead;
			Heads.push_back(NewHead);
		}
		Node <T>* N = InsertToLevel(data, i, Down);
		Down->up = N;
		Down = N;
		coinToss = rand() % 2;
	}
	return;
}


template<class T>
Node<T>* SkipList<T> ::Seartch(T key) {
	Node <T>* toplevel;
	toplevel = Heads[Heads.size() - 1];
	Node<T>* pt = new Node<T>(-INFINITY); 
	pt = toplevel;

	while (pt != nullptr)
	{
		if (pt->key == key) {
			break;
		}
		else if (key > pt->key && key >= pt->next->key) {
			pt = pt->next;
		}
		else if (key > pt->key && key < pt->next->key) {
			pt = pt->down;
		}
	}
	return pt;
}


template<class T>
void SkipList<T> ::DeleteNode(Node<T>* N) {
	if (N->down != nullptr)
		N->down->up = nullptr;
	if (N->up != nullptr)
		N->up->down = nullptr;

	Node<T>* Next = N->next;
	Node<T>* Prev = N->prev;

	Prev->next = Next;
	delete(N);
	Next->prev = Prev;
}

template<class T>
void SkipList<T> ::Delete(T N) {
	Node<T>* pt = Seartch(N);

	while ( pt != nullptr)
	{
		Node<T>* temp = pt->down;
		DeleteNode(pt);
		pt = temp;
	}
}


template <class T>
void SkipList<T>::PrintData() {
	for (int i = 0; i != Heads.size(); i++) {
		cout << " Level : " << i << endl;
		Node<T>* pt = new Node<T>(-INFINITY);
		pt = Heads[i];
		while (pt != nullptr) {
			pt->print();
			pt = pt->next;
		}
		cout << endl;
	}
}



int main() {
	SkipList<int>* mySL = new SkipList<int>();

	cout << "SKIP LIST DATA : " << endl;
	mySL->Insert(4);
	mySL->Insert(5);
	mySL->Insert(6);
	mySL->Insert(2);
	mySL->Insert(3);
	mySL->Insert(7);
	mySL->Insert(10);
	mySL->Insert(311);
	mySL->Insert(0);
	mySL->Insert(8);
	mySL->Insert(9);
	mySL->Insert(11);
	mySL->PrintData();

	mySL->Delete(4);
	cout << endl<< endl<< endl;
	mySL->PrintData();

	cout << endl;


	return 0;
}