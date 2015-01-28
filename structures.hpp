
struct vpair {
	vertex first_el;
	int second_el;

	void vpair(vertex el1, int el2) {
		this.first_el = el1;
		this.second_el = el2;
	}

	void operator=(vpair vp) {
		this.first_el = vp.first_el;
		this.second_el = vp.second_el;
	}
};

template <typename edgeType, typename charType>
class Vertex {

    public:
        EdgeList<edgeType, charType> edgeList(alphabetSize);

        Vertex(int vstart, int vend) {
            this.state_start = vstart;
            this.state_end = vend;
            this.edgeList.elist.fillWilth(empty_edge); //TODO
        }

        ~Vertex(){}

        void operator=(Vertex v) {
            this.state_start = v.state_start;
            this.state_end = v.state_end;
            this.edgeList = v.edgeList;
        }

        void operator==(Vertex v) {
            if (this.state_end == v.get_state_end() && this.edgeList() == v.edgeList()){
                return true;
            }
            return false;
        }

        void operator!=(Vertex v) {
            if (this.state_end != v.get_state_end() || this.edgeList() == v.edgeList()){
                return true;
            }
            return false;
        }

        void addSuffix(Vertex suff){
            this.suffLink = suff;
        }

        int get_state_start() {
            return this.state_start;
        }

        int get_state_end() {
            return this.state_end;
        }

        int get_suff_link() {
            return this.suffLink;
        }

        void removeEdge(Edge e){
            this.edgeList.removeEdge(e);
        }

        void addEdge(Edge e){
            this.edgeList.addEdge(e);
        }

        bool egdeExists(charType c){
            int index = getIndexByLetter(c);
            return this.edgeList.elist[index] != empty_edge;
        }

        Edge getEdge(charType letter){
            int index = getIndexByLetter(letter);
            return this.edgeList.elist[index];
        }

    private:
        int state_start;
        int state_end;
        Vertex suffLink;
};

template <typename edgeType, typename charType>
class Edge {

    public:
        Edge(int[] subword, Vertex dest, bool infinite = false;){
            this.state_dest = dest;

            this.subword[0] = subword[0];
            this.subword[1] = subword[1];

            this.infinite = infinite;
        }
        ~Edge(){}

        void operator=(Edge e) {
            this.state_dest = e.state_dest;
            this.subword[0] = e.subword[0];
            this.subword[1] = e.subword[1];
        }

        void operator==(Edge e) {
            if (this.state_end == e.get_state_end() && this.subword[0] == e.subword[0] && this.subword[1] == e.subword[1]){
                return true;
            }
            return false;
        }

        void operator!=(Edge e) {
            if (this.state_end != e.get_state_end() || this.subword[0] != e.subword[0] || this.subword[1] != e.subword[1]){
                return true;
            }
            return false;
        }

        Vertex state_dest;
        int[2] subword;
        bool infinite;
};

template <typename edgeType, typename charType>
class EdgeList {
    public:
        EdgeList(int alphabetSize){
            this.elist.resize(alphabetSize);//TODO
        }

        ~EdgeList(){}

        void removeEdge(edgeType edge){
            int index = getIndexByLetter(edge.subword[0]);
            this.elist[index] = empty_edge;
            delete edge;
        }

        void addEdge(edgeType edge){
            int index = getIndexByLetter(edge.subword[0]);
            this.elist[index] = edge;
        }

        vector<edgeType> elist;//сортиран по азбуката списък с ребра
};

int getIndexByLetter(letter){
    return (int) letter;
}

int alphabetSize = 0;
int INFINITY = 10000000;

Vertex bottom(-1, -1);
Vertex root(0, 0);

vector<char> text;

/*
 * N.B. (-3, -3) is defined to be NULL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
Vertex null_vertex(-3, -3);

int[2] empty_subword = {-1, -1};
Edge empty_edge(empty_subword, null_vertex);


//_______________________________________________________

struct sextLink {
	int[2] state1_x;
	char simbol_a;
	int[2] state2_y;
};

struct revSuffLink {
	int[2] state1_x;
	char simbol_a;
	int[2] state2_ax;
};

//struct vertex {
//	int state_start;
//	int state_end;
//    edge[30]		edges;
//
//	void vertex(int vstart, int vend) {
//		this.state_start = vstart;
//		this.state_end = vend;
//	}
//
//	void operator=(vertex v) {
//		this.state_start = v.state_start;
//		this.state_end = v.state_end;
//		this.edges = v.edges;
//	}
//
//	void operator==(vertex v) {
//		if (this.state_start == v.state_start && this.state_end == v.state_end){
//            return true;
//		}
//        return false;
//	}
//
//	void operator!=(vertex v) {
//		if (this.state_start != v.state_start && this.state_end != v.state_end){
//            return true;
//		}
//        return false;
//	}
//
//    void removeEdge(edge e){ //?????????????????/
//
//    }
//
//    void addEdge(edge e){
//        e.state_src.edge[text[e.subword[0]]] = e.subword[0]; //TODO find the pos where to put that letter!!!! (Perfect hash.)
//    }
//
//    edge getKEdge(int k, vertex v){
//        return v.edges[v.edges.[((int)text[k])];
//    }
//};

//template <typename charType>
//class suffLink {
//
//    public:
//        Vertex state1_ax;
//        Vertex state2_x;
//
//        void suffLink(Vertex vstart, Vertex vend){
//            this.state1_ax = vstart;
//            this.state2_x = vend;
//        }
//};
//
//<typename linkType>
//class SuffixLinks {
//
//    public:
//        SuffixLinks(int alphabetSize){
//            this.sufLinksList(alphabetSize);//TODO
//        }
//
//        ~SuffixLinks(){}
//
//        Vertex getSuffix(Vertex v){//TODO
//            linkType suff =  this.sufLinksList[v.get_state_end()]; //The state end is unique!!!!
//            return suff.state2_x;
//        }
//
//        void addSuffix(linkType suff){
//            sufLinksList[suff.state1_ax.get_state_end()] = suff;
//        }
//
//        vector<linkType> sufLinksList;
//}

/*
Edge empty_edge(null_vertex, empty_subword, null_vertex);

template <typename edgeType, typename charType>
class Edge {

    public:
        Edge(Vertex src, int[] subword, Vertex dest, bool infinite = false;){
            this.state_src = src;
            this.state_dest = dest;

            this.subword[0] = subword[0];
            this.subword[1] = subword[1];

            this.infinite = infinite;
        }
        ~Edge(){}

        void operator=(Edge e) {
            this.state_src = e.state_src;
            this.state_dest = e.state_dest;
            this.subword[0] = e.subword[0];
            this.subword[1] = e.subword[1];
        }

        void operator==(Edge e) {
            if (this.state_start == e.get_state_start() && this.state_end == e.get_state_end()
                    && this.subword[0] == e.subword[0] && this.subword[1] == e.subword[1]){
                return true;
            }
            return false;
        }

        void operator!=(Edge e) {
            if (this.state_start != e.get_state_start() || this.state_end != e.get_state_end()
                    || this.subword[0] != e.subword[0] || this.subword[1] != e.subword[1]){
                return true;
            }
            return false;
        }

        Vertex state_src;
        Vertex state_dest;
        int[2] subword;
        bool infinite;
};

template <typename edgeType, typename charType>
class EdgeList {
    public:
        EdgeList(int alphabetSize){
            this.elist.resize(alphabetSize);//TODO
        }

        ~EdgeList(){}

        void removeEdge(edgeType edge){
            this.elist[edge.subword[0]] = empty_edge;//TODO
            delete edge;
        }

        void addEdge(edgeType edge){
            this.elist[edge.subword[0]] = edge;
        }

        bool egdeExists(charType c, Vertex v){
            int index = getIndexByLetter(c);
            return this.elist[index] != empty_edge;
        }

        edgeType findByVertex(Vertex v){
        }

        vector<edgeType> elist;//сортиран по азбуката списък от списъци, сортирани по source vertex's end
        int size;
};
*/






