#include <iostream>
#include <iomanip>
using namespace std;
#include "Graphlnk.h"
int main()
{
	Edge<string, int> edge;
	Vertex<string, int> Router;
	char x, c;
	int v1, v2, num;
	Graphlnk<string, int> g;
	g.readtext();
	while (1)
	{
		cout << "=======·��������ʵ��======" << endl;
		cout << "=     1.���·����        =" << endl;
		cout << "=     2.���ͨ·          =" << endl;
		cout << "=     3.���·�ɱ�        =" << endl;
		cout << "=     4.ɾ��·����        =" << endl;
		cout << "=     5.ɾ����·          =" << endl;
		cout << "=     6.�˳�              =" << endl;
		cin >> x;
		switch (x)
		{
		case'1':
			cout << " ������·�����ı���Լ�·����������" << endl;
			cout << "����������Ҫ��ѯ��·�����ı��";
			cout << "(�ֿɹ���ѯ��·����: ";
			g.traverse();
			cin >> Router.numRouter;
			cin >> Router.nameRouter;
			g.insertVertex(Router);
			break;
		case'2':
			cout << "����������·�ɵı��" << endl;
			cin >> v1 >> v2;
			cout << "��Ϊ������·��������š����������Լ�Ȩֵ" << endl;
			cin >> edge.netNum >> edge.subNum >> edge.cost;
			g.insertEdge(v1, v2, edge);
			break;
		case'3':
			cout << "����������Ҫ��ѯ��·�����ı��";
			cout << "(�ֿɹ���ѯ��·����: ";
			g.traverse();
			cout << endl;
			cin >> v1;
			g.ShortestPath(v1);
			break;
		case'4':
			cout << "��������Ҫɾ����·�����ı��" << endl;
			cout << "(�ֿɹ���ѯ��·����: ";
			g.traverse();
			cout << endl;
			cin >> num;
			g.removeVertex(num);
			break;
		case'5':
			cout << "��������Ҫɾ������·���˵�·�������" << endl;
			cout << "(�ֿɹ�ʹ�õ�·����: ";
			g.traverse();
			cout << endl;
			cin >> v1 >> v2;
			g.removeEdge(v1, v2);
			break;
		case'6':
			exit(0);
			break;
		}

	}

	return 0;
}