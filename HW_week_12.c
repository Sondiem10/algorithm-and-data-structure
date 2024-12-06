#include <stdio.h>
#include <stdlib.h>

#define MAXLENGTH 100
#define NIL -1
typedef struct Node {
    char* data;             
    struct Node* left;        
    struct Node* right;       
} Node;
Node* createNode(char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void NLR(Node* root) {
    if (root == NULL) return;
    printf("%s ", root->data);
    NLR(root->left);
    NLR(root->right);
}
void LNR(Node* root) {
    if (root == NULL) return;
    LNR(root->left);
    printf("%s ", root->data);
    LNR(root->right);
}
void LRN(Node* root) {
    if (root == NULL) return;
    LRN(root->left);
    LRN(root->right);
    printf("%s ", root->data);
}
Node* buildExpressionTree() {
    Node* eNode = createNode("e");
    Node* expNode = createNode("^");
    expNode->left = eNode;
    expNode->right = createNode("1/2");
    Node* dNode = createNode("d");
    Node* mulDE = createNode("*");
    mulDE->left = dNode;
    mulDE->right = expNode;
    Node* fiveNode = createNode("5");
    Node* bNode = createNode("b");
    Node* cNode = createNode("c");
    Node* mulBC = createNode("*");
    mulBC->left = fiveNode;
    mulBC->right = bNode;
    Node* divBC = createNode("/");
    divBC->left = mulBC;
    divBC->right = cNode;
    Node* cNode2 = createNode("c");
    Node* expC8 = createNode("^");
    expC8->left = cNode2;
    expC8->right = createNode("8");
    Node* aNode = createNode("a");
    Node* addAB = createNode("+");
    addAB->left = aNode;
    addAB->right = divBC;
    Node* subABC = createNode("-");
    subABC->left = addAB;
    subABC->right = expC8;
    Node* addFinal = createNode("+");
    addFinal->left = subABC;
    addFinal->right = mulDE;
    return addFinal;
}

int main() {
    Node* root = buildExpressionTree();
    printf("Tien to (NLR): ");
    NLR(root);
    printf("\n");
    printf("Trung to (LNR): ");
    LNR(root);
    printf("\n");
    printf("Hau to (LRN): ");
    LRN(root);
    printf("\n");
    return 0;
}