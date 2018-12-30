#include <iostream>
#include <string>
#include <vector>
using namespace std;

class List{ 
	friend ostream& operator<<(ostream& os, const List& rhs) {
		Node* curr = rhs.getHead();
		while(curr != rhs.sentinel) {
			os << *curr << ' ';
			curr = curr->next;
		}
		return os;
	}
	struct Node {
		friend ostream& operator<<(ostream& os, const Node& rhs) {
			os << rhs.data;
			return os;
		}
		Node(int data = 0, Node* next = nullptr, Node* prev = nullptr) : data(data),
			next(next), prev(prev) {}
		int data;
		Node* next;
		Node* prev;
	};
	
	public:
	List(){sentinel = new Node;}

	void push_back(int data) {
		Node* nodeToAdd = new Node(data);
		if(sentinel->next == nullptr) {
			sentinel->next = nodeToAdd;
			nodeToAdd->next = sentinel;
			nodeToAdd->prev = sentinel;
			sentinel->prev = nodeToAdd;
			++listSize;
			return;
		}
		sentinel->prev->next = nodeToAdd;
		nodeToAdd->prev = sentinel->prev;
		sentinel->prev = nodeToAdd;
		nodeToAdd->next = sentinel;
		++listSize;
		return;
	}

	int pop_back() {
		Node* last = sentinel->prev;
		int val = last->data; 
		last->prev->next = sentinel;
		sentinel->prev = last->prev;
		--listSize;
		delete last;
		return val;
	}

	void push_front(int data) {
		if(listSize == 0) {push_back(data);}
		else {
		Node* nodeToAdd = new Node(data);
		Node* prevHead = sentinel->next;
		sentinel->next = nodeToAdd;
		nodeToAdd->prev = sentinel;
		nodeToAdd->next = prevHead;
		prevHead->prev = nodeToAdd;
		}
		++listSize;
		return;
	}

	void pop_front() {
		Node* tmp = sentinel->next;
		sentinel->next = sentinel->next->next;
		sentinel->next->next->prev = sentinel;
		--listSize;
		delete tmp;
	}

	Node* getHead() const {
		return sentinel->next;
	}

	Node* getLast() const {
		if(sentinel->prev == nullptr) {return sentinel;}
		return sentinel->prev;
	}

	int size() const {return listSize;}

	int front() {
		return sentinel->next->data;
	}

	int back() {
		return sentinel->prev->data;
	}

	void display() const {
		Node* head = getHead();
		while(head != sentinel) {
			cout << head->data << endl;
			head = head->next;
		}
	}

	void clear() {
		Node* headPtr = getHead();
		while(headPtr != sentinel) {
			pop_front();
			headPtr = headPtr->next;
		}
		listSize = 0;
	}

	int& operator[](size_t ind) {
		Node* curr = getHead();
		for(size_t i = 0; i < ind; ++i) {
			curr = curr->next;
		}
		return curr->data;
	}

	class Iterator {
		friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
			return lhs.currNode == rhs.currNode;
		}
		friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
			return !(lhs.currNode == rhs.currNode);
		}
		friend List;
		public:
		Iterator (Node* nPtr) {currNode = nPtr;} 

		Iterator& operator++() {
			currNode = currNode->next;
			return *(this);
		}
		Iterator& operator--() {
			currNode = currNode->prev;
			return *(this);
		}
		int operator*() {return currNode->data;}
		private:
		Node* currNode;
	};

	Iterator begin() const {return Iterator(getHead());}

	Iterator end() const {return Iterator(sentinel);}

	Iterator insert(const Iterator& iterInd, int data) {
		Node* nodeToAdd = new Node(data);
		Node* tmpCpy = iterInd.currNode;
		iterInd.currNode->prev->next = nodeToAdd;
		nodeToAdd->prev = iterInd.currNode->prev;
		nodeToAdd->next = tmpCpy;
		tmpCpy->prev = nodeToAdd;
		++listSize;
		return Iterator(nodeToAdd);
	}

	Iterator erase(const Iterator& iterInd) {
		Node* tmp = iterInd.currNode;
		iterInd.currNode->prev->next = iterInd.currNode->next;
		iterInd.currNode->next->prev = iterInd.currNode->prev;
		--listSize;
		delete iterInd.currNode;
		return Iterator(tmp->next);
	}
	private:
	Node* sentinel;//"first" node
	int listSize = 0;

	Node* getLastNode() const {
		if(sentinel->next == nullptr) {return sentinel;}
		return sentinel->prev;	
	}
};

class Polynomial {
public:
	Polynomial(const vector<int>& initV) {
		for(int n: initV) {
			coeffs.push_front(n);
		}
	}
	void display() const {
		cout << coeffs << endl;
	}

	Polynomial& operator+=(Polynomial& rhs) {
		if(coeffs.size() > rhs.coeffs.size()) {
			rhs.equalize(coeffs.size() - rhs.coeffs.size());
		}
		if(rhs.coeffs.size() > coeffs.size()) {
			equalize(rhs.coeffs.size() - coeffs.size());
		}
		for(int i = 0; i < coeffs.size(); ++i) {
			coeffs[i] += rhs.coeffs[i];
		}
		return *this;

	}
private:
	List coeffs;
	int degree;

	void equalize(int n) {
		cout << n << endl;
		for(int i = 0; i < n; ++i) {
			coeffs.push_back(0);
		}
		return;
	}
};

int main() {
	Polynomial p1({17});                 // 17
	p1.display();
	Polynomial p2({1, 2});               // x + 2
	p2.display();
	Polynomial p3({-1, 5});              // -1x + 5
	p3.display();
	Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
	p4.display();
	Polynomial has_a_zero({4, 0, 1, 7});
	p4+=p3;
	p4.display();
}

