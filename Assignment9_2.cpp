#include <iostream>

using namespace std;

struct Node {
    string word;
    int count;
    Node* next;
};

void addWord(Node*& head, const string& word) {
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->word == word) {
            current->count++;
            return;
        }
        prev = current;
        current = current->next;
    }
    Node* newNode = new Node{ word, 1, nullptr };
    if (prev == nullptr) {
        head = newNode;
    }
    else {
        prev->next = newNode;
    }
}


string findMostFrequent(Node* head) {
    Node* current = head;
    string mostFrequentWord;
    int maxCount = 0;

    while (current != nullptr) {
        if (current->count > maxCount) {
            maxCount = current->count;
            mostFrequentWord = current->word;
        }
        current = current->next;
    }

    return mostFrequentWord;
}

void removeRedundantWords(Node*& head) {
    Node* current = head;

    while (current != nullptr && current->next != nullptr) {
        if (current->word == current->next->word) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else {
            current = current->next;
        }
    }
}

int countDistinctWords(Node* head) {
    int distinctCount = 0;
    Node* current = head;

    while (current != nullptr) {
        distinctCount++;
        current = current->next;
    }

    return distinctCount;
}

void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head = nullptr;
    char sentence[100];
    cout << "Nhập câu tiếng Việt: ";
    cin.getline(sentence,100);
    string word;
    for (char c : sentence) {
        if (c == ' ') {
            if (!word.empty()) {
                addWord(head, word);
                word.clear();
            }
        }
        else {
            word += c;
        }
    }
    if (!word.empty()) {
        addWord(head, word);
    }
    string mostFrequent = findMostFrequent(head);
    cout << "Từ xuất hiện nhiều nhất: " << mostFrequent << endl;

    removeRedundantWords(head);
    int distinctCount = countDistinctWords(head);
    cout << "Số từ khác nhau trong câu sau khi loại bỏ: " << distinctCount << endl;
    deleteList(head);
    return 0;
}

