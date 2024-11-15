#include <iostream>
#define MAX 100
using namespace std;

struct Go {
    char loaiGo[100];
    int kichThuoc;
    int tuoiGo;
};
struct Stack {
    Go data[MAX];
    int top;
};
void initStack(Stack* s) {
    s->top = -1;
}
int isEmpty(Stack* s) {
    return s->top == -1;
}
int isFull(Stack* s) {
    return s->top == MAX - 1;
}
void push(Stack* s, Go go) {
    if (isFull(s)) {
        printf("Stack đã đầy!\n");
        return;
    }
    s->data[++(s->top)] = go;
}
Go pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack rỗng!\n");
    }
    return s->data[(s->top)--];
}
int countSameAge(Stack*s, int tuoiGo) {
    int count = 0;
    for (int i = 0; i <= s->top; i++) {
        if (s->data[i].tuoiGo == tuoiGo) {
            count++;
        }
    }
    return count;
}
void display(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack rỗng!\n");
        return;
    }
    printf("Danh sách gỗ trong kho:\n");
    for (int i = 0; i <= s->top; i++) {
        printf("Loại gỗ: %s, Kích thước: %s, Tuổi gỗ: %d\n",
            s->data[i].loaiGo, s->data[i].kichThuoc, s->data[i].tuoiGo);
    }
}
int main() {
    Stack s;
    initStack(&s);
    int in = 0;
    int out = 0;
    cout << "Nhập số gỗ muốn thêm";
    cin >> in;
    for (int i = 0; i < in; i++) {
        Go go;
        cout << "Nhập loại gỗ: ";
        cin.getline(go.loaiGo, 100);
        cout << "Nhập kích thước: ";
        cin >> go.kichThuoc;
        cout << "Nhập tuổi gỗ: ";
        cin >> go.tuoiGo;
        push(&s, go);
    }
    cout << "Nhập số gỗ muốn bỏ";
    cin >> out;
    for (int i = 0; i < in; i++) {
        pop(&s);
    }
    display(&s);
    int tuoi;
    cout << "Nhập tuổi gỗ cần đếm: ";
    cin >> tuoi;
    int count = countSameAge(&s,tuoi);
    cout << "Số lượng gỗ có tuổi " << tuoi << " là: " << count << "\n";
    return 0;
}
