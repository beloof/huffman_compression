#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

struct Node {
	int value;
	char letter;
	Node* left;
	Node* right;
};

struct Compare {
	bool operator()(Node* a, Node* b) {
		return a->value > b->value;
	}
};

//extracts letter codes from a given tree
unordered_map<char, string> extract(Node* node, string path) {

	unordered_map<char, string> codes;
	if (node->left == nullptr) {
		codes[node->letter] = path;
		return codes;
	}

	unordered_map<char, string> rightcodes = extract(node->right, path + '0');
	unordered_map<char, string> leftcodes = extract(node->left, path + '1');

	codes.insert(rightcodes.begin(), rightcodes.end());
	codes.insert(leftcodes.begin(), leftcodes.end());

	return codes;
}
//extracts letter codes from a given text
unordered_map<char, string> huffman(string text) {
	unordered_map<char, int> letter_frequency;
	for (const auto& ch : text) {
		letter_frequency[ch]++;
	}

	priority_queue<Node*, vector<Node*>, Compare> pq;

	for (const auto& freq : letter_frequency) {
		Node* node = new Node;
		node->value = freq.second;
		node->letter = freq.first;
		node->left = nullptr;
		node->right = nullptr;
		pq.push(node);
	}


	while (pq.size() > 1) {
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top(); pq.pop();
		Node* node = new Node;
		node->letter = '\0';
		node->value = left->value + right->value;
		node->left = left;
		node->right = right;
		pq.push(node);
	}

	unordered_map<char, string> codes = extract(pq.top(), "");
	return codes;


}



int main() {

	string text;
	cout << "text to compress please" << endl;
	cin >> text;

	unordered_map<char, string> codes = huffman(text);

	cout << "these are your codes   " << endl;

	for (const auto& obj : codes) {
		cout << obj.first << ":" << obj.second << endl;
	}

	string code;

	for (const auto& letter : text) {
		code += codes[letter];
	}

	cout << "this is your compressed text   " << code << endl;
}