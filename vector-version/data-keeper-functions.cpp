#include "data-keepers.hpp"

using namespace std;

/*
 * A function to make a serach for outgoing edge from vertex with symbol.
 * If there is no such edge, -1 is returned.
 */
int perfectHashSearch(char symbol, int vertex){
    int vertexStartPos = startIndexes[vertex];
    int edgeIndex = vertexStartPos;
    while (edgeIndex != -1){
        if (text[outgoingLabelsStartPos[edgeIndex]] == symbol){
            return edgeIndex;
        }
        edgeIndex = nextIndexes[vertexStartPos];
    }
    return edgeIndex;
}
/*
int findLabelPosInEdgeList(int subwordStartPos, int edge) {
//    cout << "findLabelPosInEdgeList " << int(text[subwordStartPos]) << endl;
    return int(text[subwordStartPos]) - 97;
}
int findLetterPosInEdgeList(char c, int edge) {
//    cout << "findLetterPosInEdgeList " << int(c) << endl;
    return int(c) - 97;
}
*/

bool vertexesReallocTest(){

}

bool vertexesReallocTest(){

}

void testAndReallocateMemory(const char* sizeType){
/***
     more_numbers = (int*) realloc (numbers, count * sizeof(int));
     numbers = more_numbers;
     memset (pointerTolastIndexFromPrev, -1, newSize - prevSize);
     */
}

void initialAlocation(const char* sizeType){
/***
     more_numbers = (int*) realloc (numbers, count * sizeof(int));
     numbers = more_numbers;
     memset (pointerTolastIndexFromPrev, -1, newSize - prevSize);
     */
}

int setVertLength(int vertNum, int length){
    lengths[vertNum] = length;
}

int setSuffLink(int vertNum, int suff){
    suffixLinks[vertNum] = suff;
}

int addEdge(int vertNum, int subword[], int destination){
    if (lastIndex[vertNum] == -1){
        startIndexes[vertNum] = firstFreeEdgePos;
        lastIndex[vertNum] = startIndexes[vertNum];
        edges[firstFreeEdgePos] = destination;
        outgoingLabelsStartPos[firstFreeEdgePos] = subword[0];
        incomingLabelEndPos[vertNum] = subword[1];
        nextIndexes[firstFreeEdgePos] = -1;
        ++firstFreeEdgePos;
    }
    else {
        edges[firstFreeEdgePos] = destination;
        outgoingLabelsStartPos[firstFreeEdgePos] = subword[0];
        incomingLabelEndPos[vertNum] = subword[1];
        nextIndexes[lastIndex[vertNum]] = firstFreeEdgePos;
        nextIndexes[firstFreeEdgePos] = -1;
        lastIndex[vertNum] = firstFreeEdgePos;
        ++firstFreeEdgePos;
    }
}

int removeEdge(int vertNum, int subword[]){
    int edgePos = perfectHashSearch(text[subword[0]], vertNum);
    if (edgePos != -1){
        edges[edgePos] = -1;
        outgoingLabelsStartPos[edgePos] = -1;
    }
}

int replaceEdge(int vertNum, int subword[], int destination){
    /* oldSubword[0] is equal to subword[0] */
    int edgePos = perfectHashSearch(text[subword[0]], vertNum);
    if (edgePos != -1){
        edges[edgePos] = destination;
        outgoingLabelsStartPos[edgePos] = subword[0];
        incomingLabelEndPos[vertNum] = subword[1];
    }
}

bool egdeExists(int srcVertex, char c){
    int edgePos = perfectHashSearch(c, srcVertex);
    return edgePos != -1;
}
