
//#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Graph{

public:

	//vector<int>* map;
	vector<int> m_mMap; //'map' may produce conflicts with std::map, especially when using namespace std;
	int row;
	int col;

	Graph (int* pArray, int _row, int _col) : row(_row), col(_col)
	{
		//map = new vector<int>;

		//int len = _row * _col;

		for (int i = 0; i < row * col; i++) {
			m_mMap.push_back(pArray[i]);
		}
	}

	//int size ()
	int size () const
	{
		return row * col;
	}

	//int getYByIndex (int index)
	int getYByIndex (int index) const
	{
		return (int)(index / col);
	}

	//int getXByIndex (int index)
	int getXByIndex (int index) const
	{
		return index - col * getYByIndex(index);
	}

	//int getIndexByXY(int x, int y)
	int getIndexByXY(int x, int y) const
	{
		return col * y + x;
	}

	~Graph ()
	{
		//delete map;
	}
};

//int findMinDist (vector<int>* dist, vector<int>* Q)
int findMinDist (const vector<int>& dist, const vector<int>& Q)
{
	int minIndex = -1;
	int minDist = -1;

	for (int i = 0; i < (int)(dist.size()); i++) {
		if (Q.at(i) != 1) {
			continue;
		}

		int tempDist = dist.at(i);

		if (minDist < 0 || (tempDist >= 0 && tempDist < minDist)) {
			minIndex = i;
			minDist = tempDist;
		}
	}

	return minIndex;
}

//void Dijkstra (Graph* G)
void Dijkstra (const Graph& G)
{
	vector<int> Q; // a list saving nodes' visited/unvisited (0/1) status.
	vector<int> dist; // a list saving the minimum distance to the start position

	// a list saving the previous node's index.
	// e.g. a = [-1, 0, 1, 0] means the previous node of a[2] is a[1]
	vector<int> prev;

	vector<bool> route;

	int unvisitedNum = G.size();

	int startIdx = -1, targetIdx = -1;

	for (int i = 0; i < G.size(); i++) {
		if (G.m_mMap[i] == 2) {
			startIdx = i;
			dist.push_back(0);
		} else {
			if (G.m_mMap[i] == 3) {
				targetIdx = i;
			}

			dist.push_back(-1); // -1 stands for infinite distance
		}

		Q.push_back(1);
		prev.push_back(-1);
		route.push_back(false);
	}

	// calculate nodes' distances to the start position
	while (unvisitedNum > 0) {
		int idx = findMinDist(dist, Q);

		// set the status of node at idx to visited
		Q[idx] = 0;
		unvisitedNum --;

		// if arriving at the target position, stop searching
		if (G.m_mMap[idx] == 3) {
			break;
		}

		vector<pair<int, int> > neighbors;

		// get neighbors
		{
			int y = G.getYByIndex(idx), x = G.getXByIndex(idx);

			neighbors.push_back(pair<int, int>(x, y - 1));
			neighbors.push_back(pair<int, int>(x, y + 1));
			neighbors.push_back(pair<int, int>(x - 1, y));
			neighbors.push_back(pair<int, int>(x + 1, y));
		}

		for (vector<pair<int, int> >::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
			pair<int, int> node = *it;

			if (node.first >= 0 && node.second >= 0 && node.first < G.col && node.second < G.row) {
				int neighborIdx = G.getIndexByXY(node.first, node.second);

				if (G.m_mMap[neighborIdx] != 1) { // check whether the neighbor is a barrier.
					int alt = dist[idx] + 1;

					if (dist[neighborIdx] < 0 || alt < dist[neighborIdx]) {
						dist[neighborIdx] = alt;
						prev[neighborIdx] = idx;
					}
				}
			}
		}
	}

	// reverse iteration to get the route
	int reIter = targetIdx;

	while (reIter != startIdx) {
		route[reIter] = true;

		reIter = prev[reIter];
	}

	route[startIdx] = true;

	for (int k = 0; k < G.size(); k++) {
		int id = G.m_mMap[k];

		if (route[k] == true) {
			if (id == 2) {
				printf("%2s ", "s");
			} else if (id == 3) {
				printf("%2s ", "e");
			} else {
				printf("%2s ", "x");
			}
		} else {
			printf("%2d ", id);
		}

		if ((k + 1) % G.col == 0) {
			printf("\n");
		}
	}
}

int main ()
{
	// 0 road
	// 1 barriers
	// 2 start
	// 3 end
	int pArray[] = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 1, 0,
		0, 0, 0, 0, 1, 0, 1, 0,
		0, 0, 0, 1, 0, 3, 1, 0,
		0, 0, 0, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 2, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	};

	Graph G(pArray, 8, 8);

	Dijkstra(G);

	return 0;
}
