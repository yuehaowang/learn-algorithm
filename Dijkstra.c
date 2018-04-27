#include <stdio.h>

struct graph {
	int* map;
	int width;
	int height;
};

struct node {
	int x;
	int y;
};

struct node getCoord(int index, int w)
{
	int x = index % w;

	struct node n = {x, index / w};

	return n;
}

int getIndex(struct node n, int w)
{
	return n.y * w + n.x;
}

int abs(int a)
{
	return (a >= 0) ? a : -a;
}

void output(struct graph gra, int* path)
{
	int len = gra.width * gra.height;

	for (int a = 0; a < len; a++) {
		if (path[a] != 1) {
			printf("%s", (gra.map[a] == 0) ? "o" : "x");
		} else {
			printf("%s", "@");
		}

		if ((a + 1) % gra.width == 0) {
			printf("\n");
		}
	}
}

void getNeighbors(struct node* l, struct node currNode)
{
	struct node up = {currNode.x, currNode.y - 1};
	struct node down = {currNode.x, currNode.y + 1};
	struct node left = {currNode.x - 1, currNode.y};
	struct node right = {currNode.x + 1, currNode.y};

	l[0] = up;
	l[1] = down;
	l[2] = left;
	l[3] = right;
}

void Dijkstra(struct graph gra, const int start, const int end)
{
	const int w = gra.width;
	const int len = w * gra.height;

	int dist[len];

	int path[len];

	int unvisited[len];
	int unvisitedLen = len;

	int curr = start; // the current node

	for (int i = 0; i < len; i++) {
		dist[i] = -1;
		unvisited[i] = 1;
		path[i] = 0;
	}

	dist[start] = 0;

	struct node endP = getCoord(end, w);

	while (unvisitedLen > 0) {
		path[curr] = 1;

		if (curr == end) { // if reaching the destination
			break;
		}

		unvisited[curr] = 0;
		unvisitedLen--;

		// get neighbors

		struct node neighbors[4];
		getNeighbors(neighbors, getCoord(curr, w));

		// find the neighbor with the least distance

		int minSteps = -1;
		int nearest = curr;

		for (int i = 0; i < 4; i++) {
			struct node n = neighbors[i];

			if (n.x >= 0 && n.x < w && n.y >= 0 && n.y < gra.height) {
				int ni = getIndex(n, w);

				if (gra.map[ni] == 0 && unvisited[ni] != 0) {
					int steps = abs(n.x - endP.x) + abs(n.y - endP.y) + dist[curr];

					// to check if the node is surrounded by more than 3 walls.
					// i.e. the situation like:
					//  o x x
					//  o o x
					//  o x x

					{
						struct node around[4];
						getNeighbors(around, n);

						int aroundWallNum = 0;

						for (int j = 0; j < 4; j++) {
							struct node a = around[j];

							if (a.x >= 0 && a.x < w && a.y >= 0 && a.y < gra.height) {
								int ai = getIndex(a, w);

								if (gra.map[ai] != 0) {
									aroundWallNum++;
								}
							}
						}

						if (aroundWallNum >= 3) {
							steps = -1;
						}
					}

					// compare the distance

					if (steps > 0 && (minSteps < 0 || steps < minSteps)) {
						minSteps = steps;
						nearest = ni;
					}

					dist[ni] = steps;
				}
			}
		}

		curr = nearest;
	}

	output(gra, path); // output the result
}

int main()
{
	int map[] = {
		0, 0, 0, 1, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 1, 1, 0, 1,
		0, 0, 0, 1, 0, 0, 1, 0,
		0, 0, 0, 1, 0, 1, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 0,
		0, 0, 0, 1, 0, 0, 0, 0
	};

	struct graph gra = {map, 8, 8};
	struct node start = {6, 0};
	struct node end = {6, 5};

	Dijkstra(gra, getIndex(start, 8), getIndex(end, 8));

	return 0;
}
