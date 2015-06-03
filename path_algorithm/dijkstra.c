/*
 *dijkstra算法，从一个点到其余所有点的最短路径，图为非负权值图，有向无向都行。
 */
#include <stdio.h>

#define NVERTEX 7
#define M 0x7ffffff

typedef int Vertex; 	//顶点
typedef struct path{ 	//路径向量
	int len; 				//路径中顶点的个数
	Vertex path[NVERTEX]; 	//路径中顶点的值
} path;
int min[NVERTEX]; 		//最小值
/*g为图的表示形式，s为起点，p为返回路径。
 */
void dijkstra(const int g[NVERTEX][NVERTEX], const Vertex s, path p[NVERTEX]){

	min[s] = 0;
	for(int i = 0; i < NVERTEX; i++){
		for(int j = 0; j < NVERTEX; j++){
			if(g[(i+s) % NVERTEX][j] < M && min[(i+s) % NVERTEX] + g[(i+s) % NVERTEX][j] < min[j]){
				min[j] = min[(i+s) % NVERTEX] + g[(i+s) % NVERTEX][j]; //更新最小值
				
				//设置路径，包括从起点到该点的路径，路径的终点不包括该点
				int k;
				for(k = 0; k < p[(i+s) % NVERTEX].len; k++){
					p[j].path[k] = p[(i+s) % NVERTEX].path[k];
				}
				p[j].path[k] = (i+s) % NVERTEX;
				p[j].len = k + 1;
			}
		}
	}
}

//test dijkstra
int main(int argc, char const *argv[])
{
	//init graph
	int g[NVERTEX][NVERTEX] = {
		{0, 1, 5, M, M, M, M},
		{M, 0, 2, 3, 7, M, M},
		{M, M, 0, 4, M, 6, M},
		{M, M, M, 0, 2, 4, M},
		{M, M, M, M, 0, M, 1},
		{M, M, M, M, M, 0, 2},
		{M, M, M, M, 1, 2, 0}
	};
	printf("M=%d\n", M);
	//init min
	for(int i = 0; i < NVERTEX; i++)	
		min[i] = M;

	//init path
	path p[NVERTEX];
	for(int i = 0; i < NVERTEX; i++){
		p[i].len = 0;
	}

	Vertex s = 0;
	dijkstra(g, s, p);
	printf("start:%d shortest path as following:\n", s);
	for(int i = 0; i < NVERTEX; i++){
		printf("end: %d distanc: %d path: ", i, min[i]);
		for(int j = 0; j < p[i].len; j++){
			printf("%d->", p[i].path[j]);
		}
		printf("%d.\n", i);
	}

	return 0;
}