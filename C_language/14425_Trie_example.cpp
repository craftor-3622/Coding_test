#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAX_ALPHABET 26

struct TrieNode {
	bool isFinished;
	int next[MAX_ALPHABET];

	// 생성자
	TrieNode() {
		memset(next, -1, sizeof(next));
		isFinished = false;
	}
};

struct Trie {
	// 각 노드 별로, child에 다음 노드 고유 번호가 저장됩니다.
	vector<TrieNode> nodes;

	// Trie 생성 시, 루트 노드 생성하여 nodes에 저장
	// 이 때, emplace_back은 객체 복사 없이 내부에서 직접 생성합니다.
	Trie() { nodes.emplace_back(); }

	// 문자열 삽입
	void insert(const string& str) {
		int node_id = 0;
		for (const auto& c : str) {
			int idx = c - 'a';		// a에서 얼마만큼 떨어져 있는가
			// child 에 해당 노드가 없는 경우, 노드를 생성하고 고유 번호 부여
			if (nodes[node_id].next[idx] == -1) {
				nodes[node_id].next[idx] = nodes.size();
				nodes.emplace_back();
			}
			node_id = nodes[node_id].next[idx];		// 남은 문자가 있다면, 포인터 이동
		}

		// 문자열이 끝났다고 표시하기
		nodes[node_id].isFinished = true;
	}

	// 문자열 탐색
	bool search(const string& str) const {
		int node_id = 0;
		for (const auto& c : str) {
			int idx = c - 'a';
			
			// 자식 노드가 없는 경우 false
			if (nodes[node_id].next[idx] == -1) {
				return false;
			}
			node_id = nodes[node_id].next[idx];
		}

		// 실제 단어를 가지고 있다면 isFinished가 true
		// 하지만 접두어로만 기능하는 경우 isFinished는 false
		return nodes[node_id].isFinished;
	}
};

int main() {
	freopen("input.txt", "r", stdin);

	int N, M;
	cin >> N >> M;
	
	Trie words;
	int answer = 0;

	for (int i = 0; i < N; i++)	{
		string new_word;
		cin >> new_word;
		words.insert(new_word);
	}

	for (int i = 0; i < M; i++)	{
		string target;
		cin >> target;
		if (words.search(target)) answer++;
	}

	cout << answer;

	return 0;
}
