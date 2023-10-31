#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

#define size 50

typedef struct graph {
	int n;	//노드의 값
	int adj_mat[size][size];
}graph;

int visited[size];

//그래프 생성
void init(graph* g) {
	int r, c; 
	g->n = 0;
	for (r = 0; r < size; r++) {
		for (c = 0; c < size; c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

//그래프 정점 생성 함수
void insert_vertex(graph* g, int v){
	if ((g->n) + 1 > size) {
		fprintf(stderr, "overflow");
		return;
	}
	g->n++;
}

//그래프 간선 생성 함수
void insert_edge(graph* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "graph index error");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//DFS 탐색 및 출력
int dfs_mat(graph* g, int start, int want, int count) {
	int w;
	count++;
	visited[start] = True;
	printf("%d ->", start);

	if (start == want) {
		printf("\n");
		printf("탐색 완료 : %d\n", start);
	}

	for (w = 0; w < g->n; w++) {
		if (g->adj_mat[start][w] && !visited[w]) {
			count = dfs_mat(g, w, want, count);
		}
	}
	return count;
}

void bfs_mat(graph* g, int v) {
	int w;
	QueueType q;

	queue_init(&q);
	visited[v] = TRUE;
	printf("visit %d->", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = 0; w < g->n; w++)
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = TRUE;
				printf("visited %d->", w);
				enqueue(&q, w);
			}
	}

int main() {

	//그래프 설정
	graph* g;
	g = (graph*)malloc(sizeof(graph));
	init(g);
	for (int i = 0; i < 12; i++) {
		insert_vertex(g, i);
	}

	insert_edge(g, 0, 5);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 6);
	insert_edge(g, 0, 9);

	insert_edge(g, 5, 3);
	insert_edge(g, 5, 4);
	insert_edge(g, 5, 1);

	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	
	insert_edge(g, 6, 4);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 8);

	insert_edge(g, 9, 8);

	insert_edge(g, 4, 1);
	insert_edge(g, 4, 7);

	insert_edge(g, 7, 1);
	insert_edge(g, 7, 10);

	insert_edge(g, 8, 10);

	printf("-----------------------------\n");
	printf("1   : 깊이 우선 탐색(DFS)    |\n");
	printf("2   : 너비 우선 탐색(BFS)    |\n");
	printf("3   : 종료                   |\n");
	printf("-----------------------------\n");

	while (1) {

		int num = 0;
		printf("메뉴 입력 : ");
		scanf_s("%d", &num);

		if (num == 1) {
			int start, want, count=0;
			printf("시작 번호와 탐색할 값 입력 : ");
			scanf_s("%d %d", &start, &want);
			count = dfs_mat(g, start, want, count);
			printf("방문한 노드 수 : %d\n", count);
			break;
		}

		else if (num == 2) {
			int start, want, count = 0;
			printf("시작 번호와 탐색할 값 입력 : ");
			scanf_s("%d %d", &start, &want);
			count = bfs_mat(g, start, want, count);
			printf("방문한 노드 수 : %d\n", count);
			break;
		}

		else if(num == 3)
		{
			printf("종료\n");
			break;
		}
	}

	return 0;
}