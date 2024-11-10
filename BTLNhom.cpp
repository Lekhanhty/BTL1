#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Product {
    int id;
    string name;
    float price;
    int quantity;
    string item;
};

typedef struct Node {
    Product data;
    Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    int size;
    List();
    Node* createNode(Product p);
    void addFirst(Product p);
    void addLast(Product p);
    void insert(Product p, int pos);
    void deleteFirst();
    void deleteLast();
    void remove(int pos);
    void print();
    void check(int id);
    void clear();
    void sortByPrice();
    void searchById(int id);
    void inputMultipleProducts(int num);
    void inputProductDetails(Product &p, int id);
    void displayProduct(const Product &p);
} List;

List::List() {
    head = tail = NULL;
    size = 0;
}

Node* List::createNode(Product p) {
    Node *newNode = new Node();
    newNode->data = p;
    newNode->next = NULL;
    return newNode;
}

void List::addFirst(Product p) {
    Node *newNode = createNode(p);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

void List::addLast(Product p) {
    Node *newNode = createNode(p);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void List::insert(Product p, int pos) {
    if (pos < 1 || pos > size + 1) {
        cout << "Vi tri khong hop le\n";
        return;
    }
    
    if (pos == 1) {
        addFirst(p);
        return;
    }
    
    if (pos == size + 1) {
        addLast(p);
        return;
    }
    
    Node *newNode = createNode(p);
    Node *temp = head;
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    size++;
}

void List::deleteFirst() {
    if (head == NULL) {
        cout << "Danh sach trong\n";
    } else {
        head = head->next;
        size--;
    }
}

void List::deleteLast() {
    if (head == NULL) {
        cout << "Danh sach trong\n";
    } else {
        Node *temp = head;
        for (int i = 1; i < size - 1; i++) {
            temp = temp->next;
        }
        temp->next = NULL;
        tail = temp;
        size--;
    }
}

void List::remove(int pos) {
    if (head == NULL) {
        cout << "Danh sach trong\n";
        return;
    }
    
    if (pos == 1) {
        deleteFirst();
        return;
    }

    Node *temp = head;
    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }
    Node *delNode = temp->next;
    temp->next = temp->next->next;
    delete delNode;
    size--;
}

void List::print() {
    for (Node *temp = head; temp != NULL; temp = temp->next) {
        displayProduct(temp->data);
    }
}

void List::check(int id) {
    Node *temp = head;
    while (temp != NULL) {
        if (temp->data.id == id) {
            cout << "Product hien co la: " << temp->data.name << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Product khong co\n";
}

void List::clear() {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;
    size = 0;
}

void List::sortByPrice() {
    if (head == NULL) return;
    for (Node *i = head; i != NULL; i = i->next) {
        for (Node *j = i->next; j != NULL; j = j->next) {
            if (i->data.price > j->data.price) {
                swap(i->data, j->data);
            }
        }
    }
}

void List::searchById(int id) {
    Node *temp = head;
    while (temp != NULL) {
        if (temp->data.id == id) {
            displayProduct(temp->data);
            return;
        }
        temp = temp->next;
    }
    cout << "Product ID khong duoc tim thay : " << id << endl;
}

void List::inputProductDetails(Product &p, int id) {
	cout << "Nhap product ID: ";
    cin >> p.id; 
    cin.ignore();  
    cout << "Nhap product ten: ";
    cin.ignore();  
    getline(cin, p.name);
    cout << "Nhap product gia: ";
    cin >> p.price;
    cout << "Nhap product so luong: ";
    cin >> p.quantity;
    cin.ignore();
    cout << "Nhap loai product : ";
    getline(cin, p.item);
}

void List::displayProduct(const Product &p) {
    cout << left
         << setw(10) << "ID"
         << setw(30) << "Product Name"
         << setw(15) << "Gia"
         << setw(15) << "So luong"
         << setw(30) << "Loai" << endl;

    cout << string(115, '-') << endl;

    cout << setw(10) << p.id
         << setw(30) << p.name
         << setw(15) << fixed << setprecision(2) << p.price
         << setw(15) << p.quantity
         << setw(30) << p.item << endl;
}


void List::inputMultipleProducts(int num) {
    for (int i = 0; i < num; i++) {
        Product p;
        cout << "Thong tin san pham " << (i + 1) << ":\n";
        inputProductDetails(p, i + 1);
        addLast(p);
    }
}

int Menu() {
    int choice;
    cout << "1. Them product \n";  
    cout << "2. Them product vao dau danh sach \n";
    cout << "3. Them product cuoi danh sach\n";
    cout << "4. Them product vao bat ky \n";
    cout << "5. In danh sach product\n";
    cout << "6. Tim kiem product theo ID\n";
    cout << "7. Xoa toan bo products\n";
    cout << "8. Xoa product dau\n";
    cout << "9. Xoa product cuoi\n";
    cout << "10. Xoa product bat ky\n";
    cout << "11. Sap xep product\n";
    cout << "12. Exit\n";  
    cout << "Lua chon la: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

int main() {
    List productList;
    int choice;
    
    while (true) {
        choice = Menu();
        switch (choice) {
            case 1: {
                int numProducts;
                cout << "So luong san pham: ";
                cin >> numProducts;
                productList.inputMultipleProducts(numProducts);
                productList.print();
                break;
            }
            case 2: {
                Product p;
                cout << "Nhap thong tin product:\n";
                productList.inputProductDetails(p, productList.size + 1);
                productList.addFirst(p);
                break;
            }
            case 3: {
                Product p;
                cout << "Nhap thong tin product:\n";
                productList.inputProductDetails(p, productList.size + 1);
                productList.addLast(p);
                break;
            }
            case 4: {
                Product p;
                cout << "Nhap thong tin product:\n";
                productList.inputProductDetails(p, productList.size + 1);
                int position;
                cout << "Vi tri chen: ";
                cin >> position;
                productList.insert(p, position);
                break;
            }
            case 5:
                productList.print();
                break;
            case 6: {
                int id;
                cout << "Nhap ID product: ";
                cin >> id;
                productList.searchById(id);
                break;
            }
            case 7:
                productList.clear();
                cout << "Tat ca da duoc xoa.\n";
                break;
            case 8:
                productList.deleteFirst();
                cout << "Product dau tien da duoc xoa.\n";
                break;
            case 9:
                productList.deleteLast();
                cout << "Product cuoi da duoc xoa.\n";
                break;
            case 10: {
                int pos;
                cout << "Nhap vi tri can xoa: ";
                cin >> pos;
                productList.remove(pos);
                break;
            }
            case 11:
                productList.sortByPrice();
                cout << "Sap xep product theo gia .\n";
                break;
            case 12:
                cout << "Thoat ...\n";
                return 0;
            default:
                cout << "Khong hop le.\n";
        }
    }
}

