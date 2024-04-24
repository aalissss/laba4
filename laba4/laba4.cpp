#include <iostream>
#include <string>
using namespace std;

//структура информации для узла
struct Information {
	string city = "";
	string region = "";
	int population = 0;
};

//структура узла
template <typename T>
struct NodeCity {
	T Information;
	NodeCity* next = nullptr;
	NodeCity* prev = nullptr;
};

//структура списка
template <typename T>
struct List{
    T information;
	NodeCity<T>* first = nullptr;
	NodeCity<T>* last = nullptr;
    NodeCity<T>* now = nullptr;
	int cnt = 0;
    int position = 0;

    //доступ к индексу
    void toIndex(int index) {
        if (abs(index - position) > (cnt - 1 - index)) {
            now = last;
            position = cnt - 1;
        }
        if (abs(index - position) > index) {
            now = first;
            position = 0;
        }
        if (index > position) {
            for (int i = 0; i < index - position; i++) {
                now = now->next;
            }
        }
        else {
            for (int i = 0; i < position - index; i++) {
                now = now->prev; 
            } 
        }
        position = index;
    }

	//добавление элемента в конец списка
	void add(T information) {
        NodeCity<T>* newNode = new NodeCity <T>;
        newNode->Information = information;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        if (first == nullptr) {
            first = newNode;
            last = newNode;
            now = newNode;
        }
        else {
            newNode->prev = last;
            last->next = newNode;
            last = newNode;
        }
        cnt++;
	}

	//вставка по индексу
	void insert(int index, T information) {
        if (index < 0 || index > cnt) {
            throw 0;
        }
        if (index == cnt) {
            add(information);
            return;
        }   
        toIndex(index);
        NodeCity<T>* newNode = new NodeCity<T>();
        newNode->Information = information;
        newNode->prev = now->prev;
        now->prev = newNode;
        if (newNode->prev != nullptr) {
            newNode->prev = newNode;
        }
        else {
            first = newNode;
        }
        cnt++;
        position++;
	}

	//удаление по индексу
	void removeAt(int index) {
        if (index < 0 || index >= cnt) {
            return;
        }
        NodeCity<T>* temp = first;
        toIndex(index);
        if (index == 0) {
            first = first->next;
            if (first != nullptr) {
                first->prev = nullptr;
            }
            else {
                last = nullptr;
            }
            delete temp;
            now = first;
            cnt--;
            position--;
        }
        else {
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            NodeCity<T>* current = temp->next;
            temp->next = temp->next->next;
            if (temp->next != nullptr) {
                temp->next->prev = temp;
            }
            else {
                last = temp;
            }
            delete current;
            cnt--;
            position--;
        }
	}

	//доступ к информационной части элемента в заданной позиции
	T elementAt(int index) {
        if (index < 0 || index >= cnt) {
            throw 0;
        }
        toIndex(index);
        return now->Information;
	}

	//количество элементов в коллекции
	int count() {
		return cnt;
	}

	//удаление всех элементов
	void clear() {
        int kol = cnt;
        for (int i = 0; i < kol; i++) {
            NodeCity<T>* temp = first;
            first = first->next;
            delete temp;
            cnt--;
        }
        first = nullptr;
        last = nullptr;
        now = nullptr;
        cnt = 0;
        position = 0;
	}
};

//удаление узлов с заданным регионом
void removeRegion(string region, List<Information> &list) {
    for (int i = 0; i < list.count(); i++) {
        if (list.elementAt(i).region == region) {
            list.removeAt(i);
            i--;
        }
    }
}

//вывод регионов отсортированных по населению
void sortRegions(List<Information> list) {
    List<Information> regions;
    for (int i = 0; i < list.count(); i++) {
        bool isIn = false;
        for (int j = 0; j < regions.count(); j++) {
            if (regions.elementAt(j).region == list.elementAt(i).region) {
                regions.now->Information.population += list.elementAt(i).population;
                isIn = true;
                break;
            }
        }
        if (!isIn) {
            regions.add(list.elementAt(i));
        }
    }
    for (int i = 0; i < regions.count(); i++) {
        for (int j = 0; j < regions.count() - 1; j++) {
            if (regions.elementAt(j).population < regions.elementAt(j + 1).population) {
                swap(regions.now->prev->Information, regions.now->Information);
            }
        }
    }
    for (int i = 0; i < regions.count(); i++) {
        cout << regions.elementAt(i).region << endl;
    }
}

//ввод элементов
Information input() {
    Information information;
    cout << "Введите город: ";
    cin >> information.city;
    cout << "Введите регион: ";
    cin >> information.region;
    cout << "Введите население: ";
    cin >> information.population;
    return information;
}

int main()
{
    system("chcp 1251>NULL");
    List<Information> List;
    string region = "";

	setlocale(LC_ALL, "Russian");

    cout << "Введите число для:" << endl;
    cout << "1. добавления элементов в конец списка" << endl << "2. вставки элемента в заданную позицию" << endl;
    cout << "3. удаления элемента  из заданной позиции" << endl << "4. доступа к информационной части элемента в заданной позиции" << endl;
    cout << "5. подсчета количества элементов в коллекции " << endl << "6. удаления всех элементов коллекции" << endl;
    cout << "7. вывода наименования регионов в упорядоченном по убыванию суммарной численности городского населения" << endl;
    cout << "8. удаления узлов, хранящих информацию о городах указанного региона" << endl;
    cout << "9. завершения работы программы" << endl;

    while (true) {
        try {
            int numb;
            cin >> numb;
            switch (numb) {
            case 1:
                List.add(input());
                break;
            case 2:
                int index;
                cout << "На какую позицию вставить элемент?" << endl;
                cin >> index;
                List.insert(index, input());
                break;
            case 3:
                int index1;
                cout << "Введите индекс элемента для удаления" << endl;
                cin >> index1;
                List.removeAt(index1);
                break;
            case 4:
                int index2;
                cout << "Введите индекс элемента для вывода" << endl;
                cin >> index2;
                cout << "На этом месте находится элемент: " << List.elementAt(index2).city << " " << List.elementAt(index2).region << " " << List.elementAt(index2).population << endl;
                break;
            case 5:
                cout << "Количество элементов в коллекции: " << List.count() << endl;
                break;
            case 6:
                List.clear();
                cout << "Список пуст!" << endl;
                break;
            case 7:
                sortRegions(List);
                break;
            case 8:
                cout << "Введите регион для удаления: ";
                cin >> region;
                removeRegion(region, List);
                break;
            case 9:
                return 0;
            default:
                cout << "Ошибка!!! Введите корректный номер команды!";
                break;
            }
        }
        catch (int error) {
            if (error == 0) {
                cout << "Введен некорректный индекс!" << endl;
            }
        }
    }
}