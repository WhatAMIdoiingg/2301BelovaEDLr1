#include <iostream>
#include<time.h>
#define size_secondList 4
#define _CRT_SECURE_NO_WARNINGS


#include <chrono>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
using namespace std;

class Node {   // отдельные элементы связанного списка
public:
	int data;
	Node* prev, * next;
public:
	Node(int data) {//конструктор
		this->data = data;
		this->prev = this->next = NULL;
	}
};

class List { //класс списка
public:
	Node* head, * tail;

public:
	List() {//конструктор
		head = tail = NULL;
	}
	~List() {//деструктор
		while (head != NULL)
		{
			del_front();
		}
	}
	//методы
	Node* push_front(int data) {//добавление в начало списка
		Node* ptr = new Node(data);
		ptr->next = head;
		if (head != NULL)
			head->prev = ptr;
		if (tail == NULL)
			tail = ptr;
		head = ptr;
		return ptr;
	}

	Node* push_back(int data) {//добавление в  конец списка
		Node* ptr = new Node(data);
		ptr->prev = tail;
		if (tail != NULL)
			tail->next = ptr;
		if (head == NULL)
			head = ptr;
		tail = ptr;
		return ptr;
	}

	// Функция для изменения порядка элементов в двусвязном списке на обратный

	void reverseList(Node** head)
	{
		Node* left = *head, * right = *head;

		
		while (right->next != nullptr)
			right = right->next;

		
		while (left != right && left->prev != right) {

			
			swap(left->data, right->data);

			
			left = left->next;

			
			right = right->prev;
		}
	}


	void del_front() { //удаление первого эл-та
		if (head == NULL) return;
		Node* ptr = head->next;
		if (ptr != NULL)
			ptr->prev = NULL;
		else tail = ptr;
		delete head;
		head = ptr;
	}

	void del_back() {// удаление последнего эл-та
		if (tail == NULL) return;
		Node* ptr = tail->prev;
		if (ptr != NULL)
			ptr->next = NULL;
		else head = ptr;
		delete tail;
		tail = ptr;
	}

	Node* get(int index) {// произвольный доступ к элементу списка по индексу
		Node* ptr = head;
		int n = 0;
		
		while (n != index) {
			if (ptr == NULL) return ptr;
			ptr = ptr->next;
			n++;
		}
		return ptr;
	}


	Node* operator[](int index) {
		return get(index);
	}

	Node* insert(int index, int data) {//добавление эл-та в произвольное место по индексу 

		Node* right = get(index);
		if (right == NULL) return push_back(data);
		Node* left = right->prev;
		if (left == NULL) return push_front(data);

		Node* ptr = new Node(data);
		ptr->prev = left;
		ptr->next = right;
		left->next = ptr;
		right->prev = ptr;
		return ptr;
	}



	void delet(int index) { // удаление эл-та по индексу
		Node* ptr = get(index);
		if (ptr == NULL) return;
		if (ptr->prev == NULL) {
			del_front();
			return;
		}
		if (ptr->next == NULL) {
			del_back();
			return;
		}
		Node* left = ptr->prev;
		Node* right = ptr->next;
		left->next = right;
		right->prev = left;
		delete ptr;
	}

	void DeleteEverything() // удаление всего списка
	{
		while (ListEmpty())
		{
			del_front();
		}
	}


	void ChangeTwoElements(List& list, int index1, int index2)
	{
		int k = getLength(head);

		if (index2 >= 0 and index1 >= 0 and k > index1 and k > index2)
		{
			int temp;
			Node* current = head;
			for (int i = 0; i < index1; i++)
			{
				current = current->next;
			}
			Node* ListCurrent = list.head;
			for (int i = 0; i < index2; i++)
			{
				ListCurrent = ListCurrent->next;
			}
			temp = current->data;
			current->data = ListCurrent->data;
			ListCurrent->data = temp;
		}
		else
		{
			cout << "Непотходящие индекс(ы)\n";
		}
	}


	bool ListEmpty() {
		// Проверка списка на пустоту
		Node* ptr = head;

		if (ptr != NULL) {

			return true;
		}
		else
		{

			return false;
		}


	}

	int getLength(Node* head) {// получение длины списка
		int count = 0;
		Node* temp = head;

		while (temp) {
			count++;
			temp = temp->next;
		}
		// cout << count<<endl;
		return count;
	}

	Node* pushListBack(Node* head, List& list)
	{
		int k = list.getLength(list.head);
		Node* current = list.head;
		for (int i = 0; i < k; i++)
		{
			Node* sd = push_back(current->data);
			current = current->next;
		}
		return head; //// 
	}
	Node* pushListFront(Node* head, List& list) {
		Node* current = list.head;
		int k = list.getLength(list.head);
		for (int i = 0; i < k; i++)
		{
			insert(i, current->data);
			current = current->next;
		}
		return head; ////
	}
	Node* pushListINDEX(Node* head, List& list, int index)
	{
		int k = list.getLength(list.head);
		Node* current = list.head;
		for (int i = index; i < k + index; i++)
		{
			insert(i, current->data);
			current = current->next;
		}
		return head; ////???????????????????
	}
	void ReplaceElem(int index, int data)
	{
		//ищется узел по индексу и замеяется его инф. часть
		if (getLength(head) > index and index >= 0)
		{
			Node* current = head;
			for (int i = 0; i < index; i++)
			{
				current = current->next;
			}
			current->data = data;
		}
		else
		{
			cout << "Недопустимый индекс элемента\n";
		}
	}


	bool Search(List& list)

	{
		int currIndex = -1;
		int q;
		
		bool NotEmpty = list.ListEmpty();
		if (NotEmpty)
		{
				
				Node* current = head;
				Node* ListCurrent = list.head;
				while (current != nullptr and ListCurrent != nullptr)
				{

					if (current->data == ListCurrent->data)
					{

						if (currIndex == -1)
						{
							currIndex = 1;

						}
						ListCurrent = ListCurrent->next;

					}
					else {
						ListCurrent = list.head;
						currIndex = -1;
					}

					current = current->next;
					
				}
				if (currIndex = 1 && ListCurrent == NULL) { return 1; }
				else { return -1; };
			
		}
		return -1;
	}


	int FirstEntry(List& List)
	{
		int currIndex = -1;
		bool NotEmpty = List.ListEmpty();
		int i = 0; //счетчик нынешней позиции
		if (NotEmpty)
		{
			Node* current = head;
			Node* ListCurrent = List.head;
			while (current != nullptr and ListCurrent != nullptr)
			{
				
				if (current->data == ListCurrent->data)
				{
					
					
						
					if (currIndex == -1)
					{
						currIndex = i;

					}
						ListCurrent = ListCurrent->next;

				}
				else {
					ListCurrent = List.head;
					currIndex = -1;
				}
				
				current = current->next;
				i++;
			}
			if (currIndex != -1 && ListCurrent == NULL) { return currIndex; }
			else { return -1; };
		}
		return -1 ;
	}

	int LastEntry(List& List)
	{
		
		int currIndex = -1;
		bool NotEmpty = List.ListEmpty();
		int i = getLength(head) - 1; //счетчик нынешней позиции
		if (NotEmpty)
		{
			Node* current = tail;
			Node* ListCurrent = List.tail;
			while (current != nullptr and ListCurrent != nullptr)
			{

				if (current->data == ListCurrent->data)
				{


					if (currIndex == -1)
					{
						currIndex = i;

					}
					ListCurrent = ListCurrent->prev;

				}
				else {
					ListCurrent = List.tail;
					currIndex = -1;
				}

				current = current->prev;
				i--;
			}
			if (currIndex != -1 && ListCurrent == NULL) { return currIndex; }
			else { return -1; };
		}
		
		
		return -1;
	}

};


int main()
{
	setlocale(LC_ALL, "rus");
	List list;

	////////////////////////

		list.push_back(5);
		list.push_back(6);
		list.push_back(7);
		list.push_back(8);

	

	List SecondList;
	for (int size = 0; size < size_secondList; size++)
	{
		SecondList.push_back(1);
	}
	

	int choice = 1;
	int choice_input = 1;
	int Data;
	int INDEX, INDEX2;
	while (choice != 0)
	{
	     choice_input = 1;
		 cout << "Список: " << endl;
		 for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)//вывод списка
		 {

			 cout << ptr->data << " ";

		 }
		cout << endl;
		cout << endl << "1.Добавление элемента в список" << endl
			<< "2.Удаление элемента из списка" << endl
			<< "3.Получение элемента по индексу" << endl
			<< "4.Получение размера списка" << endl
			<< "5.Замена элемента по индексу на передаваемый элемент" << endl
			<< "6.Проверка на пустоту списка" << endl
			<< "7.Замена порядока элементов в списке на обратный" << endl
			<< "8.Обмен двух элементов списка по индексу" << endl
			<< "9.Вставка списка в список" << endl
			<< "10.Проверка на содержание списка в списке" << endl
			<< "Для выхода из меню нажмите 0" << endl;
		cout << "Ваш выбор: ";
		cin >> choice;
		switch (choice)
		{
		case 1:

			while (choice_input != 0)

			{
				cout << endl << "1. Добавление в начало списка" << endl
					<< "2. Добавление в конец списка" << endl
					<< "3. Добавление элемента по индексу" << endl <<
					"4. Замена по индексу на передаваемый элемент" << endl << "Для выхода из меню нажмите 0" << endl;
				cin >> choice_input;
				switch (choice_input)
				{
				case 1:  cout << "Введите значение элемента" << endl;
					cin >> Data;
					list.push_front(Data);  break;
				case 2:  cout << "Введите значение элемента" << endl;
					cin >> Data;
					list.push_back(Data);  break;
				case 3:  cout << "Введите значение элемента затем индекс" << endl;
					cin >> Data >> INDEX;
						list.insert(INDEX,Data );
					break;
				case 4: cout << "Введите значение элемента затем индекс" << endl;
					cin >> Data >> INDEX; list.ReplaceElem(INDEX, Data); break;
				default:
					break;
				}

			} break;
		case 2:

			cout << endl << "1. Удаление из начала списка" << endl
				<< "2. Удаление с конеца списка" << endl
				<< "3. Удаление элемента по индексу" << endl
				<< "4. Удаление всего списка" << endl
				<< "Для выхода из меню нажмите 0" << endl;
			cin >> choice_input;
			switch (choice_input)
			{
			case 1:
				list.del_front(); break;
			case 2: list.del_back(); break;
			case 3:  cout << "Введите значение индексa" << endl;
				cin >> INDEX;
				list.delet(INDEX);
				break;
			case 4: list.DeleteEverything();

			default:
				break;
			}

			break;
		case 3: cout << "Введите индекс элемента" << endl;
			cin >> INDEX;
			cout << "Элемент: " << list[INDEX]->data << endl;  break;
		case 4: cout << "Размер списка: " << list.getLength(list.head) << endl; break;
		case 5:   cout << "Введите значение элемента на который хотите заменить, затем индекс заменяемого эл-та" << endl;
			cin >> Data >> INDEX;
			list.ReplaceElem(INDEX, Data); break;
		case 6: if (list.ListEmpty()) cout << "Список не пустой\n"; else cout << "Список пустой\n"; break;
		case 7: list.reverseList(&list.head); break;
		case 8: cout << "Введите первый, затем второй индекс ";
			cin >> INDEX >> INDEX2;
			list.ChangeTwoElements(list,INDEX, INDEX2); break;

		case 9:
			while (choice_input != 0)
			{
				cout << endl << "1. Добавление в начало списка" << endl
					<< "2. Добавление в конец списка" << endl
					<< "3. Добавление списка по индексу" << endl
					<< "Для выхода из меню нажмите 0" << endl;

				cin >> choice_input;
				switch (choice_input)
				{
				case 1:
					list.pushListFront(list.head, SecondList);  break;
				case 2:
					list.pushListBack(list.head, SecondList);  break;
				case 3:  cout << "Введите индекс" << endl;
					cin >> INDEX;
					list.pushListINDEX(list.head, SecondList, INDEX);  break;


				}

			} break;

		case 10:
			cout << endl << "1. Проверка наличия списка в списке " << endl
				<< "2. Индекс первого вхождения списка в списов" << endl
				<< "3. Индекс последнего вхождения списка в список" << endl;

			cin >> choice_input;
			switch (choice_input)
			{
			case 1:
				
				if (list.Search(SecondList)) cout << "Список есть в списке" << endl;
				else cout << "Списка нет в списке" << endl;
				
				break;
			case 2:
				if (list.FirstEntry(SecondList)>-1) cout << list.FirstEntry(SecondList)<<endl;
				else cout << "Списка нет в списке" << endl; break;
			case 3:
				if (list.LastEntry(SecondList) > -1)cout << list.LastEntry(SecondList) << endl;
				else cout << "Списка нет в списке" << endl; break;

			default:
				break;
			}

		default:
			break;

		}
	};
}

