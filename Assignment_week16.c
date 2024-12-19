#include <stdio.h>

#define MAX_CHILDREN 10
#define MAX_TITLE_LENGTH 100
#define MAX_NODES 100

typedef struct TreeNode {
    char title[MAX_TITLE_LENGTH];
    int pageCount; 
    struct TreeNode* children[MAX_CHILDREN]; 
    int childCount; 
} TreeNode;

TreeNode nodePool[MAX_NODES];
int nodeCount = 0;
TreeNode* createNode(const char* title, int pageCount) {
    if (nodeCount >= MAX_NODES) {
        printf("Không đủ bộ nhớ.\n");
        return NULL;
    }
    TreeNode* node = &nodePool[nodeCount++];
    int i = 0;
    while (title[i] != '\0' && i < MAX_TITLE_LENGTH - 1) {
        node->title[i] = title[i];
        i++;
    }
    node->title[i] = '\0';
    node->pageCount = pageCount;
    node->childCount = 0;
    return node;
}
void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->childCount < MAX_CHILDREN) {
        parent->children[parent->childCount++] = child;
    }
    else {
        printf("Không thể thêm mục con, đã đạt giới hạn.\n");
    }
}
int stringCompare(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return 0;
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}
int countChapters(TreeNode* root) {
    if (!root) return 0;
    int count = 1; 
    for (int i = 0; i < root->childCount; i++) {
        count += countChapters(root->children[i]);
    }
    return count;
}
TreeNode* findLongestChapter(TreeNode* root) {
    if (!root) return NULL;
    TreeNode* longest = root;
    for (int i = 0; i < root->childCount; i++) {
        TreeNode* childLongest = findLongestChapter(root->children[i]);
        if (childLongest && childLongest->pageCount > longest->pageCount) {
            longest = childLongest;
        }
    }
    return longest;
}
int findAndDelete(TreeNode* root, const char* title) {
    if (!root) return 0;
    for (int i = 0; i < root->childCount; i++) {
        if (stringCompare(root->children[i]->title, title)) {
            for (int j = i; j < root->childCount - 1; j++) {
                root->children[j] = root->children[j + 1];
            }
            root->childCount--;
            return 1;
        }
        if (findAndDelete(root->children[i], title)) {
            return 1;
        }
    }
    return 0;
}
void printTree(TreeNode* root, int level) {
    if (!root) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s (%d trang)\n", root->title, root->pageCount);
    for (int i = 0; i < root->childCount; i++) {
        printTree(root->children[i], level + 1);
    }
}

int main() {
    TreeNode* book = createNode("Điện tử số", 0);
    TreeNode* chapter1 = createNode("Chương 1: Giới thiệu", 10);
    addChild(book, chapter1);
    TreeNode* section1 = createNode("Mục 1.1: Cổng Logic ", 15);
    TreeNode* section2 = createNode("Mục 1.2: K-map", 10);
    addChild(chapter1, section1);
    addChild(chapter1, section2);
    printf("Cây mục lục:\n");
    printTree(book, 0);
    printf("\nTổng số chương: %d\n", countChapters(book));
    TreeNode* longest = findLongestChapter(book);
    if (longest) {
        printf("Chương dài nhất: %s (%d trang)\n", longest->title, longest->pageCount);
    }
    printf("\nXóa mục 'Mục 3.1: Hàm'\n");
    if (findAndDelete(book, "Mục 3.1: Hàm")) {
        printf("Đã xóa thành công.\n");
    }
    else {
        printf("Không tìm thấy mục để xóa.\n");
    }
    printf("\nCây mục lục sau khi xóa:\n");
    printTree(book, 0);
    return 0;
}