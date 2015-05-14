#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <iomanip>
#include <locale>
#include <iostream>
#include <algorithm>

using namespace std;

char* text;

const int alphabetSize = 30;
int *e;

vector<int> openEdges;
int text_size = 0;

const int bottom = 0, sink = 1, root = 2, nullVertex = -1;

/*
 * At pos equal to vertex's number keeps the length of a vertex.
 */
int vertexes[500000];

/*
 * The number of created vertexes.
 */
unsigned int vertexesSize = 3;

/*
 * At pos equal to vertex's number keeps the suffix link of a vertex.
 */
int suffixLinks[500000];

/*
 * At (vertexNum * alphabetSize) starts the list of outgoing edges of a vertex.
 * The list ends at (vertexNum + alphabetSize - 1).
 * The array keeps only destination vertexes.
 */
int edges[alphabetSize*500000];

/*
 * At (vertexNum * alphabetSize) starts the list of outgoing edges of a vertex.
 * The list ends at (vertexNum + alphabetSize - 1).
 * The array keeps edges' labels as StartPos and EndPos values of the label,
 * where StartPos and EndPos are the beggining and the end of the label in the input text.
 */
int edgesLabels[alphabetSize*500000][2];



