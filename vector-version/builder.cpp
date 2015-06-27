
#include "build-functions.cpp"

using namespace std;

void buildSCDAWG(int& textSize) {

    initialAlocation(transitionsSizeTypeAlloc);
    initialAlocation(vertexesSizeTypeAlloc);
    /*
    for (int i = 0; i < alphabetSize*500000; ++i){
        edges[i] = nullVertex;
        edgesLabels[i][0] = -1;
        edgesLabels[i][1] = -1;
    }
    for (int i = 0; i < 500000; ++i){
        lengths[i] = 0;
        suffixLinks[i] = nullVertex;
    }*/

    suffixLinks[root] = 9;
	/*
	 * Create nodes root and bottom
	 */
	for (int j=1; j < textSize; ++j) {
        int edgeIndex = perfectHashSearch(text[j], bottom);
//        cout << "edgeIndex: " << edgeIndex << endl;
//        cout << "bottom + edgeIndex: " << bottom + edgeIndex << endl;
        if (edges[edgeIndex] == nullVertex) {
            edges[edgeIndex] = root;
//            cout << "dest: " << edges[bottom + edgeIndex] << endl;
            /*** TODO: root is an exeption and has different incoming labels !!!!!!!!!!!!!!!!!!!! ***/
            outgoingLabelsStartPos[edgeIndex] = -j;
            incomingLabelEndPos[root] = -j;
//            cout << "Label: " << edgesLabels[bottom + edgeIndex][0] << " , " << edgesLabels[bottom + edgeIndex][1] << endl;
        }
	}

    suffixLinks[root] = bottom;
//    cout << "suffixLinks[root] " << suffixLinks[root] << endl;
    lengths[bottom] = -1;
//    cout << "lengths[bottom] " << lengths[bottom] << endl;
    lengths[root] = 0;
//    cout << "lengths[root] " << lengths[root] << endl;
    lengths[sink] = 0;
//    cout << "lengths[sink] " << lengths[sink] << endl;
	/***********************************/

	int* sk_pair = (int*)malloc(2);
    sk_pair[0] = root;
    sk_pair[1] = 1;
//    cout << "sk_pair " << sk_pair[0] << ", " << sk_pair[1] << endl;
    int i = 0; e = &i;

	do {
		++i;

		int ki_pair[2] = {sk_pair[1], i};
//		cout << "Before update:" << endl;
//		cout << "s = " << sk_pair[0] << "ki_pair = (" << ki_pair[0] << "," << ki_pair[1] << ")" << endl;
		sk_pair = update(sk_pair[0], ki_pair);
//		cout << "After update ... " << endl;

	}
	while(text[i] != '$');
}
