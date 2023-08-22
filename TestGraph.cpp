#include"testGraph.h"
template<typename T>
void ContainerPrintOneDimension(T values)
{
	for (auto value : values)
	{
		cout << value << " ";

	}
	cout << endl;

}//输出一维数组
template<typename T>
void ContainerPrintTwoDimension(T values)
{
	for (auto con : values)
	{
		for (auto value : con)
		{
			cout << value << " ";
		}
		cout << endl;
	}

}//输出二维数组
vector<vector<int>> RandomMatrix(int n)
{
	srand(time(NULL)); // 设置随机种子
	vector<vector<int>> matrix(n, vector<int>(n, 0));

	//随机生成矩阵
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				matrix[i][j] = 0; // 对角线上的元素为 0
			}
			else {
				matrix[i][j] = rand() % 10 + 1; // 随机生成 1~10 之间的整数
				if (matrix[i][j] == 1) { // 避免出现环路
					matrix[i][j] = INF;
				}
			}
		}
	}
	return matrix;
}//生产随机数组
void Print(auto& p)
{
	for (auto c : p)
	{
		cout << c->value << endl;
	}
}//输出数组
void PrintEdge(auto& values)//输出边的权重
{
	for (auto& val : values)
	{
		cout << format("weight:{},from node{},to node{}", val->weight, val->from->value, val->to->value) << endl;
	}
	cout << endl;
}

void init1(Graph<int>& g, graphTable<int>& gt)
{
	for (int i = 1; i < 10; ++i)
	{
		g.InsertNode(gt, i);
	}
	g.AddEdge(gt, 1, 2, 6);
	g.AddEdge(gt, 2, 5, 1);
	g.AddEdge(gt, 5, 7, 9);
	g.AddEdge(gt, 7, 9, 2);

	g.AddEdge(gt, 1, 3, 4);
	g.AddEdge(gt, 3, 5, 1);
	g.AddEdge(gt, 5, 8, 7);
	g.AddEdge(gt, 8, 9, 4);

	g.AddEdge(gt, 1, 4, 5);
	g.AddEdge(gt, 4, 6, 2);
	g.AddEdge(gt, 6, 8, 4);
}
void init2(Graph<int>& g, graphTable<int>& gt)
{
	for (int i = 1; i < 7; ++i)
	{
		g.InsertNode(gt, i);
	}
	g.AddEdge(gt, 1, 2, 6);
	g.AddEdge(gt, 1, 3, 1);
	g.AddEdge(gt, 1, 4, 5);

	g.AddEdge(gt, 2, 3, 5);
	g.AddEdge(gt, 2, 1, 6);
	g.AddEdge(gt, 2, 5, 3);

	g.AddEdge(gt, 3, 1, 1);
	g.AddEdge(gt, 3, 2, 5);
	g.AddEdge(gt, 3, 4, 5);
	g.AddEdge(gt, 3, 5, 6);
	g.AddEdge(gt, 3, 6, 4);

	g.AddEdge(gt, 4, 3, 5);
	g.AddEdge(gt, 4, 1, 5);
	g.AddEdge(gt, 4, 6, 2);

	g.AddEdge(gt, 5, 2, 3);
	g.AddEdge(gt, 5, 3, 6);
	g.AddEdge(gt, 5, 6, 6);

	g.AddEdge(gt, 6, 3, 4);
	g.AddEdge(gt, 6, 4, 2);
	g.AddEdge(gt, 6, 5, 6);

}
void Init3(Graph<int>& g, graphTable<int>& gt)
{
	for (int i = 0; i < 3; ++i)
	{
		g.InsertNode(gt, i);
	}
	g.AddEdge(gt, 0, 1, 7);
	g.AddEdge(gt, 0, 2, 5);

	g.AddEdge(gt, 1, 2, -5);

	/*g.AddEdge(gt, 0, 2, 10);
	g.AddEdge(gt, 1, 5, 5);

	g.AddEdge(gt, 2, 5, 2);
	g.AddEdge(gt, 2, 3, 1);

	g.AddEdge(gt, 3, 4, 4);

	g.AddEdge(gt, 4, 1, 7);
	g.AddEdge(gt, 4, 3, 6);

	g.AddEdge(gt, 5, 2, 3);
	g.AddEdge(gt, 5, 3, 9);
	g.AddEdge(gt, 5, 4, 2);*/
}
void TestGraph()
{
	graphTable<int> gt1,gt2,gt3;
	vector<vector<int>> arrays{
		{INT_MAX, 5, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
		{ INT_MAX,INT_MAX,4,INT_MAX,INT_MAX,INT_MAX },
		{ 8,INT_MAX,INT_MAX,INT_MAX,INT_MAX,9 },
		{ INT_MAX,INT_MAX,5,INT_MAX,INT_MAX,6 },
		{ INT_MAX,INT_MAX,INT_MAX,5,INT_MAX,INT_MAX },
		{ 3,INT_MAX,INT_MAX,INT_MAX,1,INT_MAX }
	};
	vector<vector<int>> arrays1{
		{0, 1, 0, 0},
		{ 0,0,1,0 },
		{ 0,0,0,0 },
		{ 0,0,1,0 }
	};
	vector<vector<int>> arrays2{
		{0, 10, 7},
		{ INT_MAX,0,-5},
		{ INT_MAX,INT_MAX,0 }
	};
	Graph<int> g1(gt1);
	Graph<int>g2(gt2);
	Graph<int>g3(gt3);
	init2(g1, gt1);
	auto r1 = g1.primMST(gt1);
	auto  r2 = g1.krukalMST(gt1);
	cout << "最小生成树prim" << endl;
	PrintEdge(r1);
	cout << "最小生成树krukal" << endl;
	PrintEdge(r2);

	Init3(g2, gt2);
	cout << "dijkstra的距离：" << endl;
	auto res = g2.dijkstra((gt2.nodes[0]));
	
	auto arrs = g2.createArrayByGraph(gt2);
	//g3.Floyd(gt2, arrays2);//允许负值 dan不允许负值的回路
	std::vector<std::vector<int>> matrix = RandomMatrix(5);
	cout << "随机矩阵" << endl;
	ContainerPrintTwoDimension(matrix);
	g3.transformArraysDirected(gt3, matrix);//有权重
	cout << endl;
	g3.Floyd(gt3, matrix);
	cout << "最短路径" << endl << endl;
	ContainerPrintTwoDimension(g3.path);
	g3.PrintPath(2, 4);
}