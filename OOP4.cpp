// Тестова зміна коду для перевірки Git
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ostream& outsetup(ostream& ofs) {
    ofs.setf(ios::hex | ios::showbase);
    ofs << setw(8) << setfill(' ');
    return ofs;
}

istream& insetup(istream& ifs) {
    ifs.setf(ios::hex | ios::skipws);
    return ifs;
}

struct Node {
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class Lqueue {
private:
    Node* pbeg;
    Node* pend;
    int count;

public:
    Lqueue() {
        pbeg = nullptr;
        pend = nullptr;
        count = 0;
    }

    ~Lqueue() {
        while (!isempty()) {
            pop();
        }
    }

    Lqueue(const Lqueue& other) {
        pbeg = nullptr;
        pend = nullptr;
        count = 0;

        Node* current = other.pbeg;
        while (current != nullptr) {
            add(current->data);
            current = current->next;
        }
    }

    void add(int value) {
        Node* newNode = new Node(value);
        if (isempty()) {
            pbeg = pend = newNode;
        }
        else {
            pend->next = newNode;
            pend = newNode;
        }
        count++;
    }

    int pop() {
        if (isempty()) {
            throw "Помилка: черга порожня!";
        }

        Node* temp = pbeg;
        int value = temp->data;

        pbeg = pbeg->next;
        if (pbeg == nullptr) {
            pend = nullptr;
        }

        delete temp;
        count--;

        return value;
    }

    void print() const {
        if (isempty()) {
            cout << "Черга порожня" << endl;
            return;
        }

        Node* current = pbeg;
        cout << "Черга: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    int num() const {
        return count;
    }

    bool isempty() const {
        return pbeg == nullptr;
    }

    void toFile(const string& filename) {
        ofstream ofs(filename);
        if (!ofs.is_open()) {
            cout << "Помилка відкриття файлу для запису!" << endl;
            return;
        }

        ofs << count << endl;

        Node* current = pbeg;
        while (current != nullptr) {
            ofs << outsetup << current->data;
            current = current->next;
        }

        ofs.close();
        cout << "Дані успішно збережено у файл " << filename << endl;
    }

    void fromFile(const string& filename) {
        ifstream ifs(filename);
        if (!ifs.is_open()) {
            cout << "Помилка відкриття файлу для читання!" << endl;
            return;
        }

        while (!isempty()) {
            pop();
        }

        int n;
        ifs >> n;

        for (int i = 0; i < n; i++) {
            int val;
            ifs >> insetup >> val;
            add(val);
        }

        ifs.close();
        cout << "Дані успішно завантажено з файлу " << filename << endl;
    }
};

int main() {
    Lqueue queue;
    int choice;
    int value;
    string filename = "queue_data.txt";

    cout << "--- Меню Черги ---" << endl;
    cout << "1. Додати (add)" << endl;
    cout << "2. Вилучити (pop)" << endl;
    cout << "3. Друк (print)" << endl;
    cout << "4. Кількість (num)" << endl;
    cout << "5. Чи порожня (isempty)" << endl;
    cout << "6. Копія" << endl;
    cout << "7. Зберегти у файл (toFile)" << endl;
    cout << "8. Завантажити з файлу (fromFile)" << endl;
    cout << "0. Вихід" << endl;

    do {
        cout << "\nВибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введіть число: ";
            cin >> value;
            queue.add(value);
            cout << "Додано: " << value << endl;
            break;
        case 2:
            try {
                value = queue.pop();
                cout << "Вилучено: " << value << endl;
            }
            catch (const char* msg) {
                cerr << msg << endl;
            }
            break;
        case 3:
            queue.print();
            break;
        case 4:
            cout << "Кількість: " << queue.num() << endl;
            break;
        case 5:
            if (queue.isempty()) cout << "Черга порожня" << endl;
            else cout << "Черга не порожня" << endl;
            break;
        case 6: {
            cout << "Копіювання..." << endl;
            Lqueue copiedQueue = queue;
            cout << "Оригінал: ";
            queue.print();
            cout << "Копія:    ";
            copiedQueue.print();
            break;
        }
        case 7:
            queue.toFile(filename);
            break;
        case 8:
            queue.fromFile(filename);
            break;
        case 0:
            cout << "Вихід." << endl;
            break;
        default:
            cout << "Помилка вводу." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}