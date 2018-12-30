#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Polynomial {
	friend ostream& operator<<(ostream& os, const Polynomial& rhs) {
		vector<int> test;
		Node* iter = rhs.polynomial;
		while(iter->next != nullptr) {
			test.insert(test.begin(), iter->data);
			iter = iter->next;
		}
			test.insert(test.begin(), iter->data);
		int pwr = rhs.degree;
		for(size_t i = 0; i < test.size() - 1; ++i) {
			os << test[i] << "x^" << pwr << '+';
			--pwr;
		}
		os << test[test.size() - 1];
		return os;
	}
	struct Node {
		Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
		int data;
		Node* next;
	};
public:
	Polynomial(const vector<int> lst) {
		polynomial = new Node(lst[0]);
		for(size_t i = 1; i < lst.size(); ++i) {
			listAddHead(lst[i]);
			++degree;
			++size;
		}
	}

	Polynomial(const Polynomial& rhs) {
		listClear();
		polynomial = rhs.listDuplicate();
		degree = rhs.degree;
		size = rhs.size;
	}

	~Polynomial() {
		listClear();
	}

	Polynomial& operator=(Polynomial& rhs) {
		if(&rhs != this) {
			listClear();
		polynomial = rhs.listDuplicate();
		degree = rhs.degree;
		size = rhs.size;
		}
		return *this;
	}

	void listDisplay() {
		const Node* p = polynomial;
		while (p != nullptr) {
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}

	Polynomial& operator+=(Polynomial& rhs) {
		if(size > rhs.size) {
			rhs.equalize(size - rhs.size);
		}
		if(rhs.size > size) {
			equalize(rhs.size - size);
		}
		Node* p1 = polynomial;
		Node* p2 = rhs.polynomial;
		for(int i = 0; i < size; ++i) {
			p1->data += p2->data;
			p1 = p1->next;
			p2 = p2->next;
		}
		return *this;
	}

	bool operator==(const Polynomial& rhs) const {
		if(degree != rhs.degree) {return false;}
		Node* p1 = polynomial;
		Node* p2 = rhs.polynomial;

		for(size_t i = 0; i < size; ++i) {
			if(p1->data != p2->data) {
				return false;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		return true;
	}

	int pwrcalc(int base, int exp) {//faster to use loop than pow when working with ints
		if(exp == 0) {return 1;}
		else  {
			return base * pwrcalc(base, exp-1);
		}
	}

	int evaluate(int n) {
		int tot = 0;
		int val = 0;
		Node* iter = polynomial;
		for(size_t i = 0; i < size; ++i) {
			tot += (iter->data * pwrcalc(n, i));
			val += tot;
		}
		return val;
	}

	private:
	Node* polynomial;
	int degree = 0;
	int size = 1;

	void equalize(int n) {
		for(int i = 0; i < n; ++i) {
			listAddLast(0);
		}		
	}

	bool listRemoveHead() {
		if (polynomial != nullptr) {
			Node* target = polynomial;
			// 1. make the head pointer point to the second node
			polynomial = polynomial->next;
			// 2. get rid of old head
			delete target;
			return true;
		}
		return false;
	}

	void listClear() {
		while (polynomial != nullptr) {
			listRemoveHead();
		}
	}

	Node* listDuplicate() const {
		if (polynomial == nullptr) return nullptr;
		Node* rest = listDuplicate();
		return new Node(polynomial->data, rest);
	}



	int listLength()  {
		const Node* p = polynomial;
		int count = 0;
		while (p != nullptr) {
			++count;
			p = p->next;
		}
		return count;
	}

	//void listAddHead
	void listAddHead(int data) {
		// // 1. create a node for the data
		Node* p = new Node(data);
		// // 3. make the new node point to the old head node
		p->next = polynomial;
		// Node* p = new Node(data, headPtr);
		// // 2. make the head pointer point to the new node
		polynomial = p;
	}

	void listAddLast(int data) {
		Node* holder = polynomial;
			while(holder->next != nullptr) {
				holder = holder->next;
			}
			holder->next = new Node(data);
			++size;
		}

	void listRemove(Node* prior) {
		Node* nodeAfter = prior->next->next;
		delete prior->next;
		prior->next = nodeAfter;
	}
};

Polynomial operator+(Polynomial& lhs, Polynomial& rhs) {
	Polynomial result = lhs;
	result += rhs;
	return result;
}

bool operator!=(const Polynomial& rhs, const Polynomial& lhs) {
	return !(rhs == lhs);
}


int main() {
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial p5({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
	cout << p4.evaluate(1);
}






















