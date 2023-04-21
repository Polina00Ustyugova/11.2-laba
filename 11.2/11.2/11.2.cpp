#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
struct point // узел
{
	string key; // Информация в узле
	point* prev, * next; // Указатели на предыдущий и на следующий элементы
};

point* make_list() // Создание и заполнение списка
{
	int n;
	setlocale(LC_ALL, "ru");
	cout << "Введите размер списка: " << endl;
	cin >> n;
	cout << "Введите информацию, которую хотите записать: " << endl;
	string s;
	getline(cin, s);
	getline(cin, s);

	point* p, * r, * van;
	p = new (point);
	p->key = s;
	p->prev = nullptr;
	p->next = nullptr; // Делает введённый пользователем элемент последним
	van = p;

	for (int i = 1; i < n; i++) //добавить элементы в конец списка
	{
		r = new(point);
		cout << "Введите информацию, которую хотите записать:" << endl;
		string s;
		getline(cin, s);

		r->key = s;
		p->next = r;
		r->prev = p;
		r->next = nullptr;
		p = r;
	}
	return van;
}

void print_list(point* van) // Вывод списка на консоль
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (van == 0) //если список пустой
	{
		cout << "Список пустой\n" << endl;
		return;
	}
	point* p = van;
	int i = 1;
	cout << "Ваш список:" << endl;
	while (p != nullptr) //пока не конец списка
	{
		cout << i << ". " << p->key << endl; // Вывод информации, содержащейся в узле
		p = p->next; //перейти на следующий элемент
		i++;
	}
	cout << "\n";
}

point* del_point(point* van, int k) // Удаление узлов (элементов списка)
{
	k--;
	point* p = van;
	if (k == 0) {
		van = van->next;
		if (van == nullptr) return nullptr;
		van->prev = nullptr;
		delete p;
		return van;
	}
	for (int i = 0; i < k - 1 && p != nullptr; i++, p = p->next);
	if (p == nullptr || p->next == nullptr) return van;
	point* r = p->next; //встать на удаляемый элемент
	p->next = r->next; //изменить указатель
	delete r;
	r = p->next; //встать на следующий
	if (r) r->prev = p;
	return van;
}

point* add_point(point* ctrl, int k) // Добавить узел
{
	setlocale(LC_ALL, "ru");
	k--;
	point* p;
	p = new(point);
	cout << "Введите новую информацию: " << endl; // Заполнение нового нового узла информацией
	string s;
	getline(cin, s);
	getline(cin, s);
	p->key = s;
	if (k == 0)
	{
		p->next = ctrl;
		p->prev = nullptr; //обнулить адрес предыдущего
		//связать список с добавленным элементом
		ctrl->prev = p;
		ctrl = p;
		return ctrl;
	}
	point* r = ctrl; //встать на начало списка
	for (int i = 0; i < k - 1 && r->next != nullptr; i++, r = r->next);
	p->next = r->next; //связать р с концом списка
	//если элемент не последний, то связать конец списка с р
	if (r->next == nullptr)  r->next->prev = p;
	p->prev = r; //связать р и r
	r->next = p;
	return ctrl;
}

int find_key_index(point* van) // Находит индекс элемента по информации, хранящейся в нём
{
	setlocale(LC_ALL, "ru");
	cout << "Введите ключ: " << endl;
	string key_word;
	getline(cin, key_word);
	getline(cin, key_word);
	point* r = van;
	int counter = 1;
	while (r)
	{
		if (r->key == key_word) return counter;
		r = r->next;
		counter++;
	}
	cout << "Такой элемент не был найден!" << endl;
	return 0;
}
point* delete_list(point* van) // Удалить список
{
	point* p = van;
	int counter = 1; // Количество элементов в списке
	while (p->next != nullptr) {
		p = p->next;
		counter++;
	}
	for (int i = counter; i > 0; i--) {
		van = del_point(van, i);
	}
	return van;
}

void printINfile(point* van, string path) // Запись списка в файл
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fout;
	fout.open(path);
	if (!fout.is_open())  cout << "Ошибка открытия файла!" << endl; 
	else {
		point* p = van;
		while (p != nullptr) {
			fout << p->key;
			fout << endl;
			p = p->next;
		}
	}
	cout << "Информация была внесена в файл" << endl;
	fout.close();
}

point* ReadFromFile(string path) // Восстановление информации из файла
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin;
	fin.open(path);
	point* van = new(point);
	if (!fin.is_open()) { cout << "Ошибка открытия файла!" << endl; }
	else {
		cout << "Информация была восстановлена!" << endl;
		string word;
		point* p, * r;
		p = new (point);
		fin >> word;
		p->key = word;
		p->prev = nullptr;
		p->next = nullptr;
		van = p;

		while (!fin.eof())
		{
			word = "";
			fin >> word;
			r = new(point);
			r->key = word;
			p->prev = nullptr;
			p->next = r;
			r->prev = p;
			r->next = nullptr;
			p = r;
		}
		p = p->prev;
		p->next = nullptr;
	}
	fin.close();
	return van;
}
void menu(int a, point* first)
{
	setlocale(LC_ALL, "ru");
	int num;
	string path = "myFile.txt";
	point* second;
	switch (a)
	{
	case 0:
		exit(777);
	case 1:
		first = make_list();
		print_list(first);
		break;
	case 2:
		cout << "Введите позицию элемента, который вы хотите удалить: " << endl;
		int n;
		cin >> n;
		first = del_point(first, n);
		print_list(first);
		break;
	case 3:
		num = find_key_index(first);
		if (num != 0)
		{
			cout << "Введите количество элементов k, которое хотите добавить" << endl;
			int k;
			cin >> k;
			for (int i = 0; i < k; i++) {
				first = add_point(first, num + i);
			}
			num += k;
			for (int i = 0; i < k; i++)
			{
				first = add_point(first, num + i + 1);
			}
			print_list(first);
		}
		break;
	case 4:
		first = delete_list(first);
		print_list(first);
		break;
	case 5:
		printINfile(first, path);
		break;
	case 6:
		first = ReadFromFile(path);
		print_list(first);
		break;
	default:
		cout << "Пожалуйста, введите номер операции верно" << endl;
		break;
	}
	system("pause");
	system("cls");
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int a = 1;
	cout << "Для работы с программой требуется создать список." << endl;
	point* first = make_list();
	while (true)
	{
		system("pause");
		system("cls");
		cout << "0. Выход" << endl;
		cout << "1. Создать список." << endl;
		cout << "2. Удалить элемент списка. " << endl;
		cout << "3. Добавить k элементов справа и слева от выбранного элемента." << endl;
		cout << "4. Удалить список." << endl;
		cout << "5. Записать список в файл." << endl;
		cout << "6. Восстановить список." << endl;
		cout << "Выберите действие: ";
		cin >> a;
		system("cls");
		menu(a, first);
	}
	return 0;
}