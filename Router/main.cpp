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
		cout << "=======路由器功能实现======" << endl;
		cout << "=     1.添加路由器        =" << endl;
		cout << "=     2.添加通路          =" << endl;
		cout << "=     3.输出路由表        =" << endl;
		cout << "=     4.删除路由器        =" << endl;
		cout << "=     5.删除链路          =" << endl;
		cout << "=     6.退出              =" << endl;
		cin >> x;
		switch (x)
		{
		case'1':
			cout << " 请输入路由器的编号以及路由器的名称" << endl;
			cout << "请输入你需要查询的路由器的编号";
			cout << "(现可供查询的路由器: ";
			g.traverse();
			cin >> Router.numRouter;
			cin >> Router.nameRouter;
			g.insertVertex(Router);
			break;
		case'2':
			cout << "请输入两端路由的编号" << endl;
			cin >> v1 >> v2;
			cout << "请为这条链路分配网络号、子网掩码以及权值" << endl;
			cin >> edge.netNum >> edge.subNum >> edge.cost;
			g.insertEdge(v1, v2, edge);
			break;
		case'3':
			cout << "请输入你需要查询的路由器的编号";
			cout << "(现可供查询的路由器: ";
			g.traverse();
			cout << endl;
			cin >> v1;
			g.ShortestPath(v1);
			break;
		case'4':
			cout << "请输入你要删除的路由器的编号" << endl;
			cout << "(现可供查询的路由器: ";
			g.traverse();
			cout << endl;
			cin >> num;
			g.removeVertex(num);
			break;
		case'5':
			cout << "请输入你要删除的链路两端的路由器编号" << endl;
			cout << "(现可供使用的路由器: ";
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