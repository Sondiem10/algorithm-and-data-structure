#include <iostream>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    int maSV;
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien SV;
    Node* link;
};

struct ListSV {
    Node* first;
    Node* last;
};

void List_Add(ListSV* list, SinhVien SV) {
    Node* newnode = new Node;
    newnode->SV = SV;
    newnode->link = nullptr; 
    if (list->first == nullptr) { 
        list->first = newnode;
        list->last = newnode;
    }
    else {
        newnode->link = list->first;
        list->first = newnode; 
    }
}
int List_Length(ListSV* list) {
    Node* node = list->first;
    int i = 0;
    while (node != nullptr) { 
        i++;
        node = node->link; 
    }
    return i;
}
void PrintList(ListSV* list) {
    Node* node = list->first;
    while (node != nullptr) {
        cout << node->SV.maSV << "\n";
        cout << node->SV.hoTen << "\n";
        cout << node->SV.gioiTinh << "\n";
        cout << node->SV.ngaySinh.ngay << "/" << node->SV.ngaySinh.thang << "/" << node->SV.ngaySinh.nam << "\n";
        cout << node->SV.diaChi;
        cout << node->SV.lop;
        cout << node->SV.khoa;
        node = node->link;
    }
}

void BubbleSort(ListSV* list) {
    if (list->first == nullptr) return; 

    bool swapped;
    do {
        swapped = false;
        Node* current = list->first;
        Node* nextNode = current->link;
        while (nextNode != nullptr) {
            if (current->SV.maSV > nextNode->SV.maSV) {
                SinhVien temp = current->SV;
                current->SV = nextNode->SV;
                nextNode->SV = temp;
                swapped = true;
            }
            current = nextNode;
            nextNode = nextNode->link;
        }
    } while (swapped); 
}
void PrintSameBirthday(ListSV* list) {

    Node* current = list->first;
    while (current != nullptr) {
        Node* comparer = current->link;
        cout << "hoc sinh cung ngay sinh la " << current->SV.hoTen << " ("
            << current->SV.ngaySinh.ngay << "/" << current->SV.ngaySinh.thang << "/"
            << current->SV.ngaySinh.nam << "):\n";

        bool found = false;
        while (comparer != nullptr) {
            if (comparer->SV.ngaySinh.ngay == current->SV.ngaySinh.ngay &&
                comparer->SV.ngaySinh.thang == current->SV.ngaySinh.thang &&
                comparer->SV.ngaySinh.nam == current->SV.ngaySinh.nam) {
                cout << "- " << comparer->SV.hoTen << "\n";
                found = true;
            }
            comparer = comparer->link;
        }
        if (!found) {
            cout << "khong thay sinh vien cung ngay sinh\n";
        }
        current = current->link;
        cout << endl;
    }
}
void RemoveSameBirthday(ListSV* list) {
    if (list->first == nullptr) return;
    Node* current = list->first;
    while (current != nullptr) {
        Node* prev = current;
        Node* next = current->link;
        while (next != nullptr) {
            if (current->SV.ngaySinh.ngay == next->SV.ngaySinh.ngay &&
                current->SV.ngaySinh.thang == next->SV.ngaySinh.thang &&
                current->SV.ngaySinh.nam == next->SV.ngaySinh.nam) {
                prev->link = next->link;
                delete next;
                next = prev->link;
            }
            else {
                prev = next;
                next = next->link;
            }
        }

        current = current->link;
    }
}