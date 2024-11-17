#include <stdio.h>

typedef struct FileNode {
    char name[50];     
    int size;          
    int created_time;  
    struct FileNode* next; 
} FileNode;

FileNode* createNode(const char* name, int size, int created_time) {
    FileNode* newNode = (FileNode*)malloc(sizeof(FileNode));
    strcpy(newNode->name, name);
    newNode->size = size;
    newNode->created_time = created_time;
    newNode->next = NULL;
    return newNode;
}
void addFile(FileNode** head, const char* name, int size, int created_time) {
    FileNode* newNode = createNode(name, size, created_time);
    if (*head == NULL || (*head)->size > size) { 
        newNode->next = *head;
        *head = newNode;
    }
    else { 
        FileNode* current = *head;
        while (current->next != NULL && current->next->size <= size) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
void deleteHead(FileNode** head) {
    if (*head != NULL) {
        FileNode* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
void deleteTail(FileNode** head) {
    if (*head == NULL) return; 
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    FileNode* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}
void deleteAfter(FileNode* prevNode) {
    if (prevNode != NULL && prevNode->next != NULL) {
        FileNode* temp = prevNode->next;
        prevNode->next = temp->next;
        free(temp);
    }
}
void deleteSmallestOldest(FileNode** head) {
    if (*head == NULL) return;
    int min_size = (*head)->size;
    FileNode* current = *head, * min_time_node = *head, * min_time_prev = NULL;
    FileNode* prev = NULL;
    while (current != NULL && current->size == min_size) {
        if (current->created_time < min_time_node->created_time) {
            min_time_node = current;
            min_time_prev = prev;
        }
        prev = current;
        current = current->next;
    }
    if (min_time_prev == NULL) { 
        *head = min_time_node->next;
    }
    else { 
        min_time_prev->next = min_time_node->next;
    }
    free(min_time_node);
}
void display(FileNode* head) {
    FileNode* current = head;
    while (current != NULL) {
        printf("File: %s, kich_thuoc: %d bytes, Thoi gian tao ra: %d\n", current->name, current->size, current->created_time);
        current = current->next;
    }
}
int main() {
    FileNode* folder = NULL;
    addFile(&folder, "file_1.txt", 500, 19990101);
    addFile(&folder, "file_2.txt", 200, 20240105);
    addFile(&folder, "file_3.txt", 200, 20241225);
    addFile(&folder, "file_4.txt", 300, 20230201);
    printf("Danh sach ban dau:\n");
    display(folder);
    deleteSmallestOldest(&folder);
    printf("\nDanh sach sau khi xoa file nho nhat và cu nhat:\n");
    display(folder);
    deleteHead(&folder);
    printf("\nDanh sach sau khi xoa dau danh sach:\n");
    display(folder);
    deleteTail(&folder);
    printf("\nDanh sach sau khi xoa cuoi danh sach:\n");
    display(folder);
    return 0;
}
