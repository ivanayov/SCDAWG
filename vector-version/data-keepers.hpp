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

const char* vertexesSizeTypeAlloc = "vertexesSizeAlloc";
const char* transitionsSizeTypeAlloc = "vertexesSizeAlloc";

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


/**********************************************************************************/

/*
 * The number of created vertexes.
 */
unsigned int vertexesSize = 3;


int lengths_suffLinks_incLabelEnd_startIndexes_lastIndex[5][500];

int* lengths = lengths_suffLinks_incLabelEnd_startIndexes[0];
int* suffixLinks = lengths_suffLinks_incLabelEnd_startIndexes[1];
int* incomingLabelEndPos = lengths_suffLinks_incLabelEnd_startIndexes[2];
int* startIndexes = lengths_suffLinks_incLabelEnd_startIndexes[3];
int* lastIndex = lengths_suffLinks_incLabelEnd_startIndexes[4];


int firstFreeEdgePos = 0;

int edges_outgoingLabelsStartPos_nexts[3][5000];

int* edges = edges_outgoingLabelsStartPos_nexts[0];
int* outgoingLabelsStartPos = edges_outgoingLabelsStartPos_nexts[1];
int* nextIndexes = edges_outgoingLabelsStartPos_nexts[2];
