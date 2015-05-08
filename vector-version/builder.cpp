
#include "build-functions.cpp"

using namespace std;

void buildSCDAWG(int& textSize) {

    for (int i = 0; i < alphabetSize*500000; ++i){
        edges[i] = nullVertex;
        edgesLabels[i][0] = -1;
        edgesLabels[i][1] = -1;
    }
    for (int i = 0; i < 500000; ++i){
        vertexes[i] = 0;
        suffixLinks[i] = nullVertex;
    }

    suffixLinks[root] = 9;
	/*
	 * Create nodes root and bottom
	 */
	for (int j=1; j < textSize; ++j) {
        int edgeIndex = findLabelPosInEdgeList(j);
//        cout << "edgeIndex: " << edgeIndex << endl;
//        cout << "bottom + edgeIndex: " << bottom + edgeIndex << endl;
        if (edges[bottom + edgeIndex] == nullVertex) {
            edges[bottom + edgeIndex] = root;
//            cout << "dest: " << edges[bottom + edgeIndex] << endl;
            edgesLabels[bottom + edgeIndex][0] = -j;
            edgesLabels[bottom + edgeIndex][1] = -j;
//            cout << "Label: " << edgesLabels[bottom + edgeIndex][0] << " , " << edgesLabels[bottom + edgeIndex][1] << endl;
        }
	}

    suffixLinks[root] = bottom;
//    cout << "suffixLinks[root] " << suffixLinks[root] << endl;
    vertexes[bottom] = -1;
//    cout << "vertexes[bottom] " << vertexes[bottom] << endl;
    vertexes[root] = 0;
//    cout << "vertexes[root] " << vertexes[root] << endl;
    vertexes[sink] = 0;
//    cout << "vertexes[sink] " << vertexes[sink] << endl;
	/***********************************/

	int* sk_pair = (int*)malloc(2);
    sk_pair[0] = root;
    sk_pair[1] = 1;
//    cout << "sk_pair " << sk_pair[0] << ", " << sk_pair[1] << endl;
    int i = 0; e = &i;

	do {
		++i;

        /* Not optimal !!! (TODO) */
//        if (text[i] != '$') {
//            for (int j = 0; j < openEdges.size(); ++j){
////                cout << "openEdges[j] " << openEdges[j] << endl;
//                edgesLabels[openEdges[j]][1] = *e;
//            }
//            vertexes[sink] = *e;
//        }

		int ki_pair[2] = {sk_pair[1], i};
//		cout << "Before update:" << endl;
//		cout << "s = " << sk_pair[0] << "ki_pair = (" << ki_pair[0] << "," << ki_pair[1] << ")" << endl;
		sk_pair = update(sk_pair[0], ki_pair);
//		cout << "After update ... " << endl;

	}
	while(text[i] != '$');
}
