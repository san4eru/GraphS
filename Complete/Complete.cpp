#include "pch.h"
#include <stdio.h>
#include <conio.h>  
#include <string.h>    
#include <string>
#include <process.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Edge
{
private:
	int u, v;
public:
	Edge(int u, int v)
	{
		this->u = u;
		this->v = v;
	}
	
	int U() {
		return u;
	}
	int V() {
		return v;
	}

	bool operator == (const Edge &other) {
		return this->u == other.u && this->v == other.v;
	}
};

class Graph {
private:
	bool Find(vector<int> &list, int x)
	{
		if (list.empty())
			return false;
		else
		{
			for (int i = 0; i < list.size(); i++)
			{
				if (list[i] == x)
					return true;
			}
		}
		return false;
	}

	bool Compare(vector<int> &L1, vector<int> &L2)
	{
		if (L1.size() == L2.size())
		{
			for (int i = 0; i < L1.size(); i++)
			{
				if (L1[i] != L2[i])
					return false;
			}
		}
		else
			return false;
		return true;
	}

	void AddWay(vector<int> &list, vector<vector<int>> &listWays)
	{
		int i = 0;
		bool temp = true;
		while (i < listWays.size() && temp)
		{
			if (Compare(list, listWays[i]))
				temp = false;
			else
				i++;
		}
		if (temp || i == listWays.size())
		{
			listWays.push_back(vector<int>());
			for (int j = 0; j < list.size(); j++)
			{
				listWays[listWays.size() - 1].push_back(list[j]);
			}
		}
	}

public:
	void Ways(vector<Edge*> &edges, int numberEdge, vector<int> &list, vector<vector<int>> &listWays, int b)
	{
		for (int i = 0; i < edges.size(); i++)
		{
			Edge* edge = edges[i];
			if (!Find(list, numberEdge))
			{
				if (edge->U() == numberEdge)
				{
					list.push_back(numberEdge);

					if (!Find(list, edge->V()))
					{
						Ways(edges, edge->V(), list, listWays, b);
					}
					else
					{
						if (edge->U() == b)
							AddWay(list, listWays);
					}
					list.erase(remove(list.begin(), list.end(), numberEdge), list.end());
				}
				else if (edge->U() == numberEdge)
				{
					list.push_back(numberEdge);

					if (!Find(list, edge->U()))
						Ways(edges, edge->U(), list, listWays, b);
					else
					{
						if (edge->V() == b)
							AddWay(list, listWays);
					}
					list.erase(remove(list.begin(), list.end(), numberEdge), list.end());
				}
			}
		}
	}
	void Print(vector<vector<int>> &list)
	{
		int j = 1;
		for (vector<vector<int>>::iterator ITER = list.begin(); ITER != list.end(); ITER++) {
			cout << "[" << j << "] ";
			for (const auto &i : *ITER) 
				cout << i << " -> ";
			cout << endl;
			j++;
		}
	}
	void Print(vector<Edge*> &edges)
	{
		for (vector<Edge*>::iterator ITER = edges.begin(); ITER != edges.end(); ITER++)
			cout << (*ITER)->U() << " - " << (*ITER)->V() << endl;
	}
};

class MainMenu {
private:
	bool flag;
public:
	Graph graph;
	void menu()
	{
		cout << " ______________________________________________" << endl;
		cout << "|                                              |" << endl;
		cout << "|                  GRAPH SOLVER                |" << endl;
		cout << "|______________________________________________|" << endl;
		cout << "|                                              |" << endl;
		cout << "|          (!!!)ВЫБЕРИТЕ ДЕЙСТВИЕ(!!!)         |" << endl;
		cout << "|______________________________________________|" << endl;
		cout << "|                                              |" << endl;
		cout << "|  (1) -Загрузить новый граф                    |" << endl;
		cout << "|  (2) Вывести                                 |" << endl;
		cout << "|  (3) -Добавить вершину/путь                   |" << endl;
		cout << "|  (4) Найти все простые пути от A до B        |" << endl;
		cout << "|  (5) -Сохранить текущий граф                  |" << endl;
		cout << "|  (6) -Выйти из программы                      |" << endl;
		cout << "|______________________________________________|" << endl;
	}
	void user_input(vector<Edge*> edges, vector<vector<int>> listWays, vector<int> Paph)
	{
		menu();
		this->flag = true;
		int num;
		cout << "[*]Введите номер => ";
		cin >> num;
		if ((num <= 0) || (num > 6)) cout << "[-]Введен неправильный код задачи. Повторите ввод!" << endl;
		if (num == 1)
		{
			this->flag = true;
			cout << "Записал!";
			system("pause"); system("cls");
			user_input(edges, listWays, Paph);
		}
		if (num == 2)
		{
			if (this->flag == true) graph.Print(edges);
			else cout << "[-]Не найдено загруженного файла. Сначала необходимо его загрузить!" << endl; system("pause"); system("cls");
			user_input(edges, listWays, Paph);
		}
		if (num == 4)
		{
			if (this->flag) {
				cout << "Введите путь от A до B (через пробел): ";
				int a, b;
				cin >> a >> b;
				graph.Ways(edges, a, Paph, listWays, b);
				graph.Print(listWays);
			}
			else cout << "[-]Не найдено загруженного файла. Сначала необходимо его загрузить!" << endl; system("pause"); system("cls");
			user_input(edges, listWays, Paph);
		}
		if (num == 5) {
			user_input(edges, listWays, Paph);
		}
		if (num == 6) 
			exit(0);
	}
};


void main()
	{
		vector<Edge*> edges;
		vector<vector<int>> listWays;
		vector<int> Paph;
		Edge tempVar(1, 2);
		edges.push_back(&tempVar);
		Edge tempVar2(1, 5);
		edges.push_back(&tempVar2);
		Edge tempVar3(2, 5);
		edges.push_back(&tempVar3);
		Edge tempVar4(5, 4);
		edges.push_back(&tempVar4);
		Edge tempVar5(2, 3);
		edges.push_back(&tempVar5);
		Edge tempVar6(3, 4);
		edges.push_back(&tempVar6);
		Edge tempVar7(4, 6);
		edges.push_back(&tempVar7);

		Edge tempVar8(2, 1);
		edges.push_back(&tempVar8);
		Edge tempVar9(5, 1);
		edges.push_back(&tempVar9);
		Edge tempVar10(5, 2);
		edges.push_back(&tempVar10);
		Edge tempVar11(4, 5);
		edges.push_back(&tempVar11);
		Edge tempVar12(3, 2);
		edges.push_back(&tempVar12);
		Edge tempVar13(4, 3);
		edges.push_back(&tempVar13);
		Edge tempVar14(6, 4);
		edges.push_back(&tempVar14);

		setlocale(LC_ALL, "RUS");
		MainMenu manager;
		manager.user_input(edges, listWays, Paph);
		system("pause");
}