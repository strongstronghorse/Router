#ifndef GRAPHLNK_H
#define GRAPHLNK_H
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
const int DefaultNumOfPort = 8;
const int DefaultVertices = 8;
const int MaxVertices = 100;	//ͼ�е���󶥵���Ŀ
const int maxValue = 10000;	//������Ȩֵ
const string invalidN = "0.0.0.0";//��Ч�����
const string invalidS = "255.255.255.255";//��Ч��������
template<class T, class E>
struct Edge
{
	int dest;
	string netNum;          //�����
	E cost;                 //Ȩֵ
	Edge<T, E> *link;
	string subNum;          //��������
	Edge(int i_dest, string s_netNum, string subNum_mask, E i_cost)
	{
		dest = i_dest;
		netNum = s_netNum;
		cost = i_cost;
		subNum = subNum_mask;
	}
	Edge() { cost = maxValue; }
	bool operator != (Edge<T, E>& R)const
	{
		return (dest != R.dest) ? true : false;
	}
};
struct port {
	int num;		//�˿ں�
	string netNum;  //�˿����������
};
template<class T, class E>
struct Vertex
{
	int numRouter;				 //·�ɱ��
	T nameRouter;				 //·��������
	string borderNetNum;		//�߽�·���������
	string subNumber;			 //��������
	port *por;					 //�ӿ�����
	int numofports;				 //��ǰ�ӿ���
	Edge<T, E> *adj;			 //�������ͷָ��
	Vertex() {
		por = new port[DefaultNumOfPort];
		numofports = 0;
	}
};
template<class T, class E>
class Graphlnk
{
public:
	Graphlnk(int sz = MaxVertices);
	~Graphlnk();
	T getValue(int i)					//ȡλ��Ϊi�Ķ����е�ֵ
	{
		return (i >= 0 && i< numVertices) ? NodeTable[i].nameRouter : 0;
	}
	E getWeight(int v1, int v2);			//���ر�(v1,v2)��Ȩֵ
	bool insertVertex(const Vertex<T, E> vertex);
	bool removeVertex(int v);
	bool insertEdge(int v1, int v2, const Edge<T, E> edge);
	bool removeEdge(int v1, int v2);
	string merge(string net, string subnet);
	void readtext();
	int NumberOfVertices()
	{
		return this->numVertices;
	}
	void getNetMeg(int v1, int v2, string &x, string &y) {						//�����Ͳ���,�õ�����ź���������
		if (v1 != -1 && v2 != -1)
		{
			Edge<T, E> *p = NodeTable[v1].adj;
			while (p != NULL && p->dest != v2)
			{
				p = p->link;
			}
			if (p != NULL)
			{
				x = p->netNum;
				y = p->subNum;
			}
			else {
				x = invalidN;
				y = invalidS;
			}
		}

	}
	int getPort(int v1, int v2) {					//�õ��ӿں�
		if (v1 != -1 && v2 != -1)
		{
			Edge<T, E> *p = NodeTable[v1].adj;
			while (p != NULL && p->dest != v2)
			{
				p = p->link;
			}
			if (p != NULL)
				for (int i = 0; i < 20; i++)
				{
					if (NodeTable[v1].por[i].netNum == p->netNum)
						return i;
				}
			else return -1;
		}
	}
	int getVertexPos(const int num)
	{
		for (int i = 0; i< numVertices; i++)
			if (NodeTable[i].numRouter == num)
				return i;
		return -1;
	}
	void ShortestPath(int v);
	void printRouTable(int v, E dist[], int path[]);
	void traverse() {
		for (int i = NumberOfVertices() - 1; i >= 0; i--)
			cout << " " << NodeTable[i].numRouter;
	}
private:
	Vertex<T, E> * NodeTable;
	int maxVertices;
	int numEdges;
	int numVertices;
};
template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz /* = DeafultVertices */)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = NULL;

	try
	{
		NodeTable = new Vertex<T, E>[maxVertices];
	}
	catch (bad_alloc & memExp)
	{
		cerr << memExp.what() << endl;
	}
	for (int i = 0; i<maxVertices; i++)
	{
		NodeTable[i].adj = NULL;
	}
}
template<class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
	for (int i = 0; i<maxVertices; i++)
	{
		Edge<T, E> * p = NodeTable[i].adj;
		while (p != NULL)
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[] NodeTable;
}
template<class T, class E>
void Graphlnk<T, E>::ShortestPath(int v1)
{//Graph��һ����Ȩ����ͼ�����㷨����һ�����飬dist[j],0<=j<n;�ǵ�ǰ�󵽵ĴӶ���v������j�����·�����ȣ�ͬʱ������path����󵽵����·��
	int	v = getVertexPos(v1);				//�õ����v1�Ķ���λ��
	int n = numVertices;
	E *dist = new E[n];
	int *path = new int[n];
	bool *S = new bool[n];
	int i, j, k;
	E w, min;
	for (i = 0; i<n; i++)
	{
		dist[i] = getWeight(v, i);
		S[i] = false;
		if (i != v && dist[i] <maxValue)
			path[i] = v;
		else
		{
			path[i] = -1;
		}
	}
	S[v] = true;
	dist[v] = 0;
	for (i = 0; i<n - 1; i++)
	{
		min = maxValue;
		int u = v;
		for (j = 0; j<n; j++)
		{
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;
		for (k = 0; k<n; k++)
		{
			w = getWeight(u, k);
			if (S[k] == false && w <maxValue && dist[u] + w<dist[k])
			{
				dist[k] = dist[u] + w;
				path[k] = u;
			}
		}
	}
	printRouTable(v, dist, path);
}
template<class T, class E>
void Graphlnk<T, E>::printRouTable(int v, E dist[], int path[])		//vΪnodetaλ��
{//���path�����д洢��ͼG�Ӷ���v������������·���;���
	cout << "·�ɱ�" << getValue(v) << "��·�ɱ�Ϊ:" << endl;
	int i, j, k, n = numVertices;
	int m = 0;
	string netN, subN;
	cout << "Ŀ �� �� ��  �� �� �� ��      ��һ��               | �� ��" << endl;
	int * d = new int[n];						//�������·��
	for (i = 0; i<n; i++)
	{
		if (i != v)
		{
			j = i;
			k = 0;
			while (j != v)
			{
				d[k++] = j;					//d[k]����Ǳ��
				j = path[j];
			}
			k--;
			netN = NodeTable[i].borderNetNum;
			subN = NodeTable[i].subNumber;
			if (k == 0)
			{
				m = getPort(v, d[k]);				//�õ��Ľӿں�
				cout << netN << " |" << subN << " |" << "  ֱ�ӽ����ӿ�" << NodeTable[v].por[m].num << "    |    " << dist[i] << endl;
			}
			else if (k >= 1)
			{
				cout << netN << " |" << subN << " |" << "     " << getValue(d[k]) << "      |    " << dist[i] << endl;

			}
		}
	}
	delete[] d;
}

template<class T, class E>
void Graphlnk<T, E>::readtext() {
	ifstream vfile, efile;
	Edge<string, int> edge;
	Vertex<string, int> Router;
	int v1, v2;
	vfile.open("routers.txt");
	if (!vfile) {
		cout << "�޷����ļ�" << endl;
		exit(1);
	}
	while (vfile.eof() != 1)
	{
		vfile >> Router.numRouter >> Router.nameRouter >> Router.borderNetNum >> Router.subNumber;
		insertVertex(Router);
	}
	efile.open("edges.txt");
	if (!efile) {
		cout << "�޷����ļ�" << endl;
		exit(1);
	}
	while (efile.eof() != 1)
	{
		efile >> edge.netNum >> edge.subNum >> v1 >> v2 >> edge.cost;
		insertEdge(v1, v2, edge);
	}

}
template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E> *p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL)
			return p->cost;
		else return maxValue;
	}
}
template<class T, class E>
bool Graphlnk<T, E>::insertVertex(const Vertex<T, E> vertex)
{
	if (numVertices == maxVertices) return false;
	NodeTable[numVertices].nameRouter = vertex.nameRouter;
	NodeTable[numVertices].numRouter = vertex.numRouter;
	NodeTable[numVertices].borderNetNum = vertex.borderNetNum;
	NodeTable[numVertices].subNumber = vertex.subNumber;
	numVertices++;
	return true;
}
template<class T, class E>
bool Graphlnk<T, E>::removeVertex(int v)		//ͬʱɾ����������йصı�
{
	int n = 0;
	v = getVertexPos(v);				//�õ����v1�Ķ���λ��
	if (numVertices == 1 || v<0 || v >= numVertices)return false;
	Edge<T, E> *p, *s, *t;
	int i, k;
	while (NodeTable[v].adj != NULL)			//���ɾ�������ڽӵĵ��Ӧ��v
	{
		p = NodeTable[v].adj;
		k = p->dest;
		s = NodeTable[k].adj;					//�ҵ���������ڽӵĵ㲢ɾ����Ӧ��
		t = NULL;
		while (s != NULL && s->dest != v)
		{
			t = s;                           //tΪs����һ����
			s = s->link;					 //�ҵ��Ǹ���
		}									 //sָ����һ����Ϊv
		if (s != NULL)
		{
			if (t == NULL) NodeTable[k].adj = s->link;  //��ζ��s->dest==v��һ����
			else t->link = s->link;						//ǰһ����ͺ�һ����������
			delete s;
		}
		NodeTable[v].adj = p->link;				//��������һ��λ��
		delete p;
		numEdges--;								//ÿ��ɾ������һ��
	}
	numVertices--;
	NodeTable[v].numRouter = NodeTable[numVertices].numRouter;				//��ɾ�������Ϣ����Ϊ���һ�������Ϣ�����0��ʼ
	NodeTable[v].nameRouter = NodeTable[numVertices].nameRouter;
	NodeTable[v].numofports = NodeTable[numVertices].numofports;
	n = NodeTable[numVertices].numofports;											//�ӿ���Ϊ���һ������ӿ���
	for (int i = 0; i < n; i++)
	{
		NodeTable[v].por[i].num = NodeTable[numVertices].por[i].num;							//���ν���ӿ�
		NodeTable[v].por[i].netNum = NodeTable[numVertices].por[i].netNum;				//������Ŵ��뵽�ӿڵ������
	}
	p = NodeTable[v].adj = NodeTable[numVertices].adj;						//�����ظ���Ϣ
	while (p != NULL)
	{
		k = p->dest;
		s = NodeTable[k].adj;
		while (s != NULL) {
			if (s->dest == numVertices) {								 //ɾ���ظ����һ���㶥��λ�ö�Ӧ�ı�ʹ��ָ�����¸��ڽӵ㣬���������ɾ��
				s->dest = v;
				break;
			}
			else s = s->link;
		}
		p = p->link;									//��������һ���ڽӵ�
	}
	cout << "ɾ���ɹ�" << endl;
	cout << "(�ֿɹ�ʹ�õ�·����: ";
	traverse();
	cout << endl;
	return true;
}
template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, const Edge<T, E> edge)
{
	v1 = getVertexPos(v1);										//��·�ɱ���ת��Ϊ�ڽӱ��ж���λ��
	v2 = getVertexPos(v2);
	int n;
	if (v1 >= 0 && v1< numVertices && v2 >= 0 && v2<numVertices)
	{
		Edge<T, E> *q, *p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
		{
			p = p->link;
		}
		if (p != NULL) return false;
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = edge.cost;
		p->link = NodeTable[v1].adj;
		p->netNum = edge.netNum;								//������Ÿ����
		p->subNum = edge.subNum;								//���������븳����
		n = NodeTable[v1].numofports;
		NodeTable[v1].por[n].num = n;							//���ν���ӿ�
		NodeTable[v1].por[n].netNum = edge.netNum;				//������Ŵ��뵽�ӿڵ������
		NodeTable[v1].numofports++;
		NodeTable[v1].adj = p;
		q->dest = v1;
		q->cost = edge.cost;
		q->netNum = edge.netNum;
		q->subNum = edge.subNum;
		n = NodeTable[v2].numofports;
		NodeTable[v2].por[n].num = n;							//���ν���ӿ�
		NodeTable[v2].por[n].netNum = edge.netNum;				//������Ŵ��뵽�ӿڵ������
		NodeTable[v2].numofports++;								//��ǰ�ӿ���Ŀ��һ
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return false;
}

template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
	v1 = getVertexPos(v1);										//��·�ɱ���ת��Ϊ�ڽӱ��ж���λ��
	v2 = getVertexPos(v2);
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E> *p = NodeTable[v1].adj, *q = NULL, *s = p;
		while (p != NULL && p->dest != v2)						//�ҵ���Ӧ�����ڽӱ��λ��
		{
			q = p;
			p = p->link;
		}
		if (p != NULL)
		{
			if (p == s)											//v1��һ���ڽӵ�Ϊv2
				NodeTable[v1].adj = p->link;
			else
			{
				q->link = p->link;
			}
			delete p;
		}
		else
		{
			return false;
		}
		p = NodeTable[v2].adj;
		q = NULL;
		s = p;
		while (p->dest != v1)
		{
			q = p;
			p = p->link;
		}
		if (p == s)
			NodeTable[v2].adj = p->link;
		else
		{
			q->link = p->link;
		}
		delete p;
		numEdges--;
		cout << " ɾ���ɹ�" << endl;

		return true;
	}
	cout << "ɾ��ʧ��" << endl;
	return false;
}
template<class T, class E>
string Graphlnk<T, E>::merge(string net, string subnet)
{
	string a;
	int length = net.length() - 1;
	int sublength = subnet.length() - 1;
	int part[4] = { 0,0,0,0 };
	int spart[4] = { 0,0,0,0 };
	int fpart[4] = { 0,0,0,0 };
	int tag = 1;
	int t = 0;
	int temp = 0;
	for (int i = length; i >= 0; i--)
	{
		if (net[i] != '.')
		{
			temp = (net[i] - 48) * tag;
			part[t] += temp;
			tag *= 10;

		}
		else {
			t++;
			tag = 1;
		}
	}
	tag = 1;
	t = 0;
	temp = 0;
	for (int i = sublength; i >= 0; i--)
	{
		if (subnet[i] != '.')
		{
			temp = (subnet[i] - 48) * tag;
			spart[t] += temp;
			tag *= 10;

		}
		else {
			t++;
			tag = 1;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		fpart[i] = spart[i] & part[i];
	}
	a = to_string(fpart[3]) + '.' + to_string(fpart[2]) + '.' + to_string(fpart[1]) + '.' + to_string(fpart[0]);
	return  a;
}
#endif