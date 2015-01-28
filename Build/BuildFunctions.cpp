
#include "structures.cpp"

vpair update(Vertex s, int[] kp_pair) {
	char c = text[kp_pair[1]];
	Vertex oldr = null_vertex;
	int[2] kp_1_pair = {kp_pair[0], kp_pair.[1]-1};

	while (!check_end_point(s, kp_1_pair, c) {
		Vertex r = new Vertex();
		/* Impicit case */
		if (kp_pair[0] <= kp_pair[1]-1) {
			r = split_edge(s, kp_1_pair);
		}
		/* Expicit case */
		else {
			r = s;
		}
		Vertex rprim = new Vertex();//TODO
		int[2] subword = {kp_pair.[1], INFINITY};
		Edge edg(subword, rprim););
		r.edgeList.addEdge(edg);

		if (oldr != null_vertex){
        	oldr.addSuffix(r);
		}
		oldr = r;
		vpair sk_pair = new vpair();
		Vertex suffix = s.get_suff_link();
		sk_pair = canonize(suffix, kp_1_pair);
	}

        if (oldr != null_vertex){
        	oldr.addSuffix(s);
        }
	return canonize(s, kp_pair);
}

bool check_end_point(Vertex s, int[] kp_pair, char c){
	it (kp_pair[0] <= kp_pair[1]) {
		Edge edg = new Edge();
        edg = s.getEdge(text[kp_pair[0]]);
		return (c == text[edg.subword[0] + kp_pair[1] - kp_pair[0] + 1);
	}
	else {
		return s.edgeList.egdeExists(c);
	}
}

Vertex split_edge(Vertex s, int[] kp_pair){
	Edge edg = new Edge();
	edg = s.getEdge(text[kp_pair[0]]);

	Vertex r = new Vertex();
	r = null_vertex;

	splitEdgeInPos(s, e, oldPair, r);

	return r;
}

vpair canonize(Vertex s, int[] kp_pair){
	if(kp_pair[0] > kp_pair[1]){
		vpair sk_pair(s, kp_pair[0]);
		return sk_pair;
	}
	Edge edg = new Edge();
	edg = s.getEdge(text[kp_pair[0]]);
	int pprim = edg.subword[1];
	int kprim = edg.subword[0];

	int k = 0;
	while(pprim - kprim <= kp_pair[1] - kp_pair[0]){
		k = kp_pair[0] + pprim - kprim + 1;
		s = edg.state_dest;
	}
	if(k < kp_pair[1]){
		Edge resEdg = new Edge();
        resEdg = s.getEdge(text[kp_pair[0]]);//May be a global getEdge() ?????
		s = resEdg.state_src;//TODO !!!!!!!!!!!!!!!! s is always src ????????????????/
	}
	vpair sk_pair(s, k);
	return sk_pair;
}

void splitEdgeInPos(Vertex vsrc, Edge e, int[] oldPair, Vertex r){//TODO
	int firstSubword = {e.subword[0], e.subword[0] + oldPair[1] - oldPair[0]};
	int secondSubword = {e.subword[0] + oldPair[1] - oldPair[0] + 1, e.subword[1]};

	Edge edg1 = new Edge(firstSubword, r);
	Edge edg2 = new Edge(secondSubword , e.state_dest);
	vsrc.edgeList.addEdge(edg1);
	r.edgeList.addEdge(edg2);
	edgeList.removeEdge(e);// TODO !!! ??? !!! from which vertex ????
}

/**************************************************************/

Vertex extension(Vertex s, int[] kp_pair){
    if (kp_pair[0] > kp_pair[1]){
        return s;
    }
    Vertex res = new Vertex();
    res = s.getEdge(text[kp_pair[0]]);
    return res;
}


void redirectEdge(Vertex s, int[] kp_pair, Vertex r){

}

vpair separateNode(Vertex s, int[] kp_pair){
}

