#include <iostream>

using namespace std;

struct FileNode {
    string fileName;
    int fileSize; 
    string timestamp; 
    FileNode* next;
};
void insertFile(FileNode*& head, const string& fileName, int fileSize, const string& timestamp) {
    FileNode* newFile = new FileNode{ fileName, fileSize, timestamp, nullptr };
    if (head == nullptr || head->timestamp > timestamp) {
        newFile->next = head;
        head = newFile;
        return;
    }
    FileNode* current = head;
    while (current->next != nullptr && current->next->timestamp <= timestamp) {
        current = current->next;
    }
    newFile->next = current->next;
    current->next = newFile;
}
int calculateTotalSize(FileNode* head) {
    int totalSize = 0;
    FileNode* current = head;
    while (current != nullptr) {
        totalSize += current->fileSize;
        current = current->next;
    }
    return totalSize;
}
void removeSmallestFile(FileNode*& head) {
    if (head == nullptr) return;

    FileNode* smallest = head;
    FileNode* prevSmallest = nullptr;
    FileNode* current = head;
    FileNode* prev = nullptr;

    while (current != nullptr) {
        if (current->fileSize < smallest->fileSize) {
            smallest = current;
            prevSmallest = prev;
        }
        prev = current;
        current = current->next;
    }
    if (prevSmallest == nullptr) {
        head = head->next;
    }
    else {
        prevSmallest->next = smallest->next;
    }
    delete smallest;
}
void fitFilesInUSB(FileNode*& head, int usbSize) {
    int totalSize = calculateTotalSize(head);
    while (totalSize > usbSize) {
        removeSmallestFile(head);
        totalSize = calculateTotalSize(head);
    }
}
void deleteList(FileNode*& head) {
    while (head != nullptr) {
        FileNode* temp = head;
        head = head->next;
        delete temp;
    }
}
void displayFiles(FileNode* head) {
    cout << "Danh sách các file trong thư mục:\n";
    while (head != nullptr) {
        cout << "Tên file: " << head->fileName
            << ", Kích thước: " << head->fileSize << " MB"
            << ", Thời gian: " << head->timestamp << endl;
        head = head->next;
    }
}

int main() {
    FileNode* head = nullptr;
    const int USB_SIZE = 32 * 1024;
    insertFile(head, "1.txt", 500, "2024-11-11 00:00");
    insertFile(head, "2.txt", 200, "2024-11-12 00:00");
    insertFile(head, "3.txt", 700, "2024-11-13 00:00");
    insertFile(head, "4.txt", 100, "2024-11-14 00:00");
    displayFiles(head);
    cout << "\nChèn file mới vào thư mục:\n";
    insertFile(head, "newfile.txt", 300, "2023-11-02 16:00");
    displayFiles(head);
    int totalSize = calculateTotalSize(head);
    cout << "\nTổng kích thước các file: " << totalSize << " MB" << endl;
    if (totalSize > USB_SIZE) {
        fitFilesInUSB(head, USB_SIZE);
        cout << "\nDanh sách các file sau khi loại bỏ file nhỏ nhất để vừa USB:\n";
        displayFiles(head);
    }
    else {
        cout << "\nKhông cần loại bỏ file, tổng kích thước đã nằm trong giới hạn USB.\n";
    }
    deleteList(head);

    return 0;
}