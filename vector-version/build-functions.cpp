
#include "data-keeper-functions.cpp"

using namespace std;

void removeOpenEdge(int indexValue) {
    vector<int>::iterator it;
    it = find (openEdges.begin(), openEdges.end(), indexValue);

    if (it != openEdges.end()){
//        cout << "Remove open edge: " << openEdges[*it] << endl;
        openEdges.erase(it);
    }
}

void addOpenEdge(int indexValue){
    openEdges.push_back(indexValue);
//    cout << "Add open edge: " << indexValue << endl;
}

/*
 * Returns a pair of vertex's number and a int number.
 */
int* canonize(int sVertex, int kp_pair[]){
	int* sk_pair = (int*)malloc(2);
//    cout << "----------------------- Canonize ..." <<endl;

	if(kp_pair[0] > kp_pair[1]){
		sk_pair[0] = sVertex;
		sk_pair[1] = kp_pair[0];
//		cout << "(Res): sk_pair = (" << sk_pair[0] << "," << sk_pair[1] << ")" << endl;
		return sk_pair;
	}

    int edgeIndex = findLabelPosInEdgeList(kp_pair[0]);
    int pprim = edgesLabels[sVertex * alphabetSize + edgeIndex][1];
    int kprim = edgesLabels[sVertex * alphabetSize + edgeIndex][0];
    int sp = edges[sVertex * alphabetSize + edgeIndex];
//    cout << "edgeIndex = " << edgeIndex << ", kprim = " << kprim
//            << ", pprim = " << pprim << ", sp = " << sp << endl;

	int k = kp_pair[0];
	while(pprim - kprim <= kp_pair[1] - k){
//        cout << " in canonize while ..." << endl;
		k = k + pprim - kprim + 1;
		sVertex = sp;
//        cout << "pprim " << pprim << ", kprim " << kprim << ", kp_pair[1] " << kp_pair[1] << ", k " << k << endl;
        if(k <= kp_pair[1]){
            int sindex = findLabelPosInEdgeList(k);
            pprim = edgesLabels[sVertex * alphabetSize + sindex][1];
            kprim = edgesLabels[sVertex * alphabetSize + sindex][0];
            sp = edges[sVertex * alphabetSize + sindex];
        }
	}
	sk_pair[0] = sVertex;
	sk_pair[1] = k;
//    cout << "(Res): sk_pair = (" << sk_pair[0] << "," << sk_pair[1] << ")" << endl;
//    cout << "----------------------- Canonize -----------------------" << endl;
	return sk_pair;
}

bool check_end_point(int sVertex, int kp_pair[], char c){
//    cout << "----------------------- check_end_point:" << endl;
//    cout << "sVertex = " << sVertex << " , kp_pair[0] = " << kp_pair[0] << " , kp_pair[1] = " << kp_pair[1] << " , c = " << c << endl;
	if (kp_pair[0] <= kp_pair[1]) {
        int edgeIndex = findLabelPosInEdgeList(kp_pair[0]);
//        cout << (c == text[edgesLabels[sVertex * alphabetSize + edgeIndex][0] + kp_pair[1] - kp_pair[0] + 1]) << endl;
		return (c == text[edgesLabels[sVertex * alphabetSize + edgeIndex][0] + kp_pair[1] - kp_pair[0] + 1]);
	}
	else {
        bool test = egdeExists(sVertex, c);
//        cout << test << endl;
//        cout << "-----------------------check_end_point-----------------------" << endl;
		return egdeExists(sVertex, c);
	}
}

/*
 * Returns vertex's number.
 */
int extension(int sVertex, int kp_pair[]){
//    cout << "---------------- extension: ..." << endl;
//    cout << "s = " << sVertex << " , kp_pair = (" << kp_pair[0] << "," << kp_pair[1] << ")" << endl;
    if (kp_pair[0] > kp_pair[1]){
        return sVertex;
    }
    int edgeIndex = findLabelPosInEdgeList(kp_pair[0]);
//    cout << "Res: edges[sVertex * alphabetSize + edgeIndex] = " << edges[sVertex * alphabetSize + edgeIndex] << endl;
//    cout << "---------------- extension ------------------" << endl;
    return edges[sVertex * alphabetSize + edgeIndex];
}

void redirectEdge(int sVertex, int kp_pair[], int rVertex){
//    cout << "---------------- redirectEdge: ..." << endl;
//    cout << "s = " << sVertex << " , kp_pair = (" << kp_pair[0] << "," << kp_pair[1] << ")" << " , r = "<< rVertex << endl;
    int edgeIndex = findLabelPosInEdgeList(kp_pair[0]);
    int subword[2] = {edgesLabels[sVertex * alphabetSize + edgeIndex][0],
                        edgesLabels[sVertex * alphabetSize + edgeIndex][0] + kp_pair[1] - kp_pair[0]};

    replaceEdge(sVertex, subword, rVertex);
    removeOpenEdge(sVertex * alphabetSize + edgeIndex);
//    cout << "redirected edge: source: " << sVertex << ", label: " << subword[0] << " , " << subword[1] << " dest: " << rVertex << endl;
//
//    cout << "---------------- redirectEdge ------------------" << endl;
}

/*
 * Returns vertex's number.
 */
int split_edge(int sVertex, int kp_pair[]){
//    cout << "---------------- split_edge: ..." << endl;
    int edgeIndex = findLabelPosInEdgeList(kp_pair[0]);

    int rVertex = vertexesSize;
	++vertexesSize;

    int kprim = edgesLabels[sVertex * alphabetSize + edgeIndex][0];
    int pprim = edgesLabels[sVertex * alphabetSize + edgeIndex][1];
    int sp = edges[sVertex * alphabetSize + edgeIndex];
    removeOpenEdge(sVertex * alphabetSize + edgeIndex);

	int firstSubword[2] = {kprim, kprim + kp_pair[1] - kp_pair[0]};
	int secondSubword[2] = {kprim + kp_pair[1] - kp_pair[0] + 1, pprim};

    edgesLabels[sVertex * alphabetSize + edgeIndex][0] = firstSubword[0];
    edgesLabels[sVertex * alphabetSize + edgeIndex][1] = firstSubword[1];
    edges[sVertex * alphabetSize + edgeIndex] = rVertex;
//    cout << "(split) redirected edge: source: " << sVertex << ", label: " << firstSubword[0] << " , " << firstSubword[1] << " dest: " << rVertex << endl;

    int edgeIndex2 = findLabelPosInEdgeList(secondSubword[0]);
    edgesLabels[rVertex * alphabetSize + edgeIndex2][0] = secondSubword[0];
    edgesLabels[rVertex * alphabetSize + edgeIndex2][1] = secondSubword[1];
    edges[rVertex * alphabetSize + edgeIndex2] = sp;
    addOpenEdge(rVertex * alphabetSize + edgeIndex2);
//    cout << "(split) new edge: source: " << rVertex << ", label: " << secondSubword[0] << " , " << secondSubword[1] << " dest: " << sp << endl;

    vertexes[rVertex] = vertexes[sVertex] + (kp_pair[1] - kp_pair[0] + 1);
//    cout << "Res: rVertex = " << rVertex << endl;
//    cout << "---------------- split_edge ------------------" << endl;

    return rVertex;
}

/*
 * Returns a pair of vertex's number and a int number.
 */
int* separateNode(int sVertex, int kp_pair[]){
//    cout << "---------------- separateNode: ..." << endl;
	int* sk_pair_can = (int*)malloc(2);
    sk_pair_can = canonize(sVertex, kp_pair);

    if (sk_pair_can[1] <= kp_pair[1]) {
//        cout << "(Res): sk_pair_can = (" << sk_pair_can[0] << "," << sk_pair_can[1] << ")" << endl;
//        cout << "---------------- separateNode ------------------" << endl;
        return sk_pair_can;
    }
    if (vertexes[sk_pair_can[0]] == vertexes[sVertex] + kp_pair[1] - kp_pair[0] + 1){
//        cout << "(Res): sk_pair_can = (" << sk_pair_can[0] << "," << sk_pair_can[1] << ")" << endl;
//        cout << "---------------- separateNode ------------------" << endl;
        return sk_pair_can;
    }

//    cout << "separate_node not tested case ..." << endl;
    int resVertex = vertexesSize;
	++vertexesSize;
    for (int i = 0; i < alphabetSize; ++i){
        edges[resVertex * alphabetSize + i] = edges[sk_pair_can[0] * alphabetSize + i];
        edgesLabels[resVertex * alphabetSize + i][0] = edgesLabels[sk_pair_can[0] * alphabetSize + i][0];
        edgesLabels[resVertex * alphabetSize + i][1] = edgesLabels[sk_pair_can[0] * alphabetSize + i][1];
    }
    suffixLinks[resVertex] = suffixLinks[sk_pair_can[0]];
    suffixLinks[sk_pair_can[0]] = resVertex;
    vertexes[resVertex] = vertexes[sVertex] + (kp_pair[1] - kp_pair[0] + 1);

	int* sk_pair = (int*)malloc(2);
    sk_pair[0] = sVertex;
    sk_pair[1] = kp_pair[0];
	int* can_pair = (int*)malloc(2);

    do {
        can_pair = canonize(sk_pair[0], kp_pair);
        int edgeIndex = findLabelPosInEdgeList(kp_pair[0]);
        edges[sk_pair[0] * alphabetSize + edgeIndex] = resVertex;
        edgesLabels[sk_pair[0] * alphabetSize + edgeIndex][0] = kp_pair[0];
        edgesLabels[sk_pair[0] * alphabetSize + edgeIndex][1] = kp_pair[1];

        int kp_1_pair[2] = {kp_pair[0], kp_pair[1]-1};
        sk_pair = canonize(suffixLinks[sVertex], kp_1_pair);
        kp_pair[0] = sk_pair[1];
    }
    while(sk_pair_can[0] != can_pair[0] && sk_pair_can[1] != can_pair[1]);

	int* resPair = (int*)malloc(2);
    resPair[0] = resVertex;
    resPair[1] = kp_pair[1] + 1;

//    cout << "(Res): resPair = (" << resPair[0] << "," << resPair[1] << ")" << endl;
//    cout << "---------------- separateNode ------------------" << endl;
    return resPair;
}


/*
 * Returns a pair of vertex's number and a int number.
 */
int* update(int sVertex, int kp_pair[]) {
//    cout << "----------------------- Update:" << endl;
	int* sk_pair = (int*)malloc(2);
    sk_pair[0] = sVertex;
    sk_pair[1] = kp_pair[0];
    if (text[kp_pair[1]] == '$'){
//        cout << "End of text in update!" << endl;
        return sk_pair;
    }

	char c = text[kp_pair[1]];
	int oldr = nullVertex;
	int kp_1_pair[2] = {kp_pair[0], kp_pair[1]-1};

//    cout << "c = " << c << " , oldr = " << oldr << " , kp_1_pair = (" << kp_1_pair[0] << "," << kp_1_pair[1] << ")" << endl;
    int sp = nullVertex;
	int rVertex = nullVertex;

	while (!check_end_point(sVertex, kp_1_pair, c)) {
//        cout << "In while ..." << endl;

//        cout << "kp_pair[0] <= kp_pair[1]-1 : " << kp_pair[0] << " , " << kp_pair[1]-1 << endl;
		/* Impicit case */
		if (kp_pair[0] <= kp_pair[1]-1) {
//            cout << "Case kp_pair[0] <= kp_pair[1]-1" << endl;
            if (sp != nullVertex && sp == extension(sk_pair[0], kp_1_pair)){
                redirectEdge(sk_pair[0], kp_1_pair, rVertex);

                int s_suff_link = suffixLinks[sk_pair[0]];
                sk_pair = canonize(s_suff_link, kp_1_pair);
                sVertex = sk_pair[0];
                kp_1_pair[0] = sk_pair[1];
                kp_pair[0] = kp_1_pair[0];
//                cout << "kp_1_pair = (" << kp_1_pair[0] << "," << kp_1_pair[1] << ")" << endl;
                continue;
            }
            else{
                sp = extension(sk_pair[0], kp_1_pair);
                rVertex = split_edge(sk_pair[0], kp_1_pair);
            }
		}
		/* Expicit case */
		else {
//            cout << "Case else:" << endl;
			rVertex = sk_pair[0];
		}
//		cout << "rVertex = " << rVertex << endl;
//        cout << "Create edge: ..." << endl;
        int edgeIndex = findLabelPosInEdgeList(kp_pair[1]);
//        cout << "edgeIndex = " << edgeIndex << endl;
//        cout << "rVertex + edgeIndex = " << rVertex * alphabetSize + edgeIndex << endl;
        edges[rVertex * alphabetSize + edgeIndex] = sink;
        edgesLabels[rVertex * alphabetSize + edgeIndex][0] = kp_pair[1];
        edgesLabels[rVertex * alphabetSize + edgeIndex][1] = text_size;

//        cout << "new edge: label: " << edgesLabels[rVertex * alphabetSize + edgeIndex][0] << " , "
//        << edgesLabels[rVertex * alphabetSize + edgeIndex][1] << " dest: " << edges[rVertex * alphabetSize + edgeIndex] << endl;
        addOpenEdge(rVertex * alphabetSize + edgeIndex);

        if (oldr != nullVertex){
            suffixLinks[oldr] = rVertex;
//            cout << "suffixLinks[oldr] = " << suffixLinks[oldr] << endl;
        }
        oldr = rVertex;

        int s_suff_link = suffixLinks[sk_pair[0]];
        sk_pair = canonize(s_suff_link, kp_1_pair);
        sVertex = sk_pair[0];
        kp_1_pair[0] = sk_pair[1];
//        cout << "sk_pair = (" << sk_pair[0] << " , " << sk_pair[1] << ")" << endl;
//        cout << "------------------------------------ End of While ------------------------------------" << endl;
    }
    if (oldr != nullVertex){
        suffixLinks[oldr] = sk_pair[0];
    }
    return separateNode(sk_pair[0], kp_pair);
}

