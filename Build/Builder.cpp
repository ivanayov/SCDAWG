
#include "BuildFunctions.cpp"

void buildSCDAWG(vector<char> word) {

	/*
	 * Create nodes root and bottom
	 */
	for (int j=0; j < text.size(); ++j) {
		int[2] subword = {-j, -j};
		newEdge = new edge(bottom, subword, root); //TODO: Do we really need epsillon transitions here????
		edges.push_back(newEdge);
	}

	suffLink sfl(root, bottom);
	suff.push_back(sfl);

	/***********************************/

    	vpair sk_pair(root, 1); //TODO: Must be (root, 0) and i = -1;
    	int i = 0;

	do {
		++i;
		int[2] ki_pair = {sk_pair.second_el, i};
		sk_pair = update(sk_pair.state_startfirst_el, ki_pair);
	}
	while(word[i] != $);
}
