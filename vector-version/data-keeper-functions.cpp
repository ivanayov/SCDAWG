#include "data-keepers.hpp"

using namespace std;

int findLabelPosInEdgeList(int subwordStartPos) {
//    cout << "findLabelPosInEdgeList " << int(text[subwordStartPos]) << endl;
    return int(text[subwordStartPos]) - 97;
}
int findLetterPosInEdgeList(char c) {
//    cout << "findLetterPosInEdgeList " << int(c) << endl;
    return int(c) - 97;
}

int setVertLength(int vertNum, int length){
    vertexes[vertNum] = length;
}

int setSuffLink(int vertNum, int suff){
    suffixLinks[vertNum] = suff;
}

int addEdge(int vertNum, int subword[], int destination){
    int edgePos = findLabelPosInEdgeList(subword[0]);
    edges[vertNum * alphabetSize + edgePos] = destination;
    edgesLabels[vertNum * alphabetSize + edgePos][0] = subword[0];
    edgesLabels[vertNum * alphabetSize + edgePos][1] = subword[1];
}

int removeEdge(int vertNum, int subword[]){
    int edgePos = findLabelPosInEdgeList(subword[0]);
    edges[vertNum * alphabetSize + edgePos] = -1;
    edgesLabels[vertNum * alphabetSize + edgePos][0] = -1;
    edgesLabels[vertNum * alphabetSize + edgePos][1] = -1;
}

int replaceEdge(int vertNum, int subword[], int destination){
    /* oldSubword[0] is equal to subword[0] */
    int edgePos = findLabelPosInEdgeList(subword[0]);
    edges[vertNum * alphabetSize + edgePos] = destination;
    edgesLabels[vertNum * alphabetSize + edgePos][0] = subword[0];
    edgesLabels[vertNum * alphabetSize + edgePos][1] = subword[1];
}

bool egdeExists(int srcVertex, char c){
    int edgePos = findLetterPosInEdgeList(c);
    return edges[srcVertex * alphabetSize + edgePos] != nullVertex;
}
