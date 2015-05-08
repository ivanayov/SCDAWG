//#include "tests.cpp" //TODO
#include "builder.cpp"

using namespace std;

#include <fcntl.h>
#include <sys/stat.h>

#ifdef WIN32
#include <io.h>

int open_sequential_read(const char* const filename)
{
	int fd = open(filename, O_RDONLY | O_BINARY | O_SEQUENTIAL);
	return fd;
}

//int open_sequential_write(const char* const filename)
//{
//	int fd = open(filename, O_WRITE | O_BINARY | O_SEQUENTIAL);
//	return fd;
//}
#else
#include <unistd.h>

int open_sequential_read(const char* const filename)
{
	int fd = open(filename, O_RDONLY);
	posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL | POSIX_FADV_WILLNEED);
	return fd;
}

//int open_sequential_write(const char* const filename)
//{
//	int fd = open(filename, O_WRITE);
//	posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL | POSIX_FADV_WILLNEED);
//	return fd;
//}
#endif

char* read_input(const char* const filename, int& textSize)
{
	int input_fd = open_sequential_read(filename);

	struct stat input_file_stats;
	fstat(input_fd, &input_file_stats);
	int size = input_file_stats.st_size;

	char* result = (char*)malloc(size + 2);
	result[0] = '/';

	read(input_fd, &result[1], size-1);
	close(input_fd);
	result[size] = '$';
	textSize = size + 1;
	return result;
}

//void write_output(const char* const filename, int data[], int dataSize)
//{
//	int input_fd = open_sequential_read(filename);
//
//	struct stat input_file_stats;
//	fstat(input_fd, &input_file_stats);
//	int size = input_file_stats.st_size;
//
//	char* result = (char*)malloc(size + 2);
//	result[0] = '/';
//
//	read(input_fd, &result[1], size-1);
//	close(input_fd);
//	result[size] = '$';
//	textSize = size + 1;
//	return result;
//}

void printGraphInfo(){
    cout << "Number of nodes = " << vertexesSize - 1 << endl;

    cout << "Number of edges = ";
    int edgesNumber = 0;

    for (unsigned int i = 0; i < vertexesSize; ++i){
        for (int j = 0; j < alphabetSize; ++ j){
            if (edges[i * alphabetSize + j] != nullVertex && edgesLabels[i * alphabetSize + j][0] > 0 && edgesLabels[i * alphabetSize + j][1] > 0) {
                  edgesNumber++;
            }
        }
    }
    cout << edgesNumber << endl;
}

void printToGraphviz(){

    cout << "digraph G {\nrankdir=LR;\n";
    for (unsigned int i = 0; i < vertexesSize; ++i){
        cout << i << " -> " << suffixLinks[i] << " [color=\"#9ACEEB\"];\n";
        for (int j = 0; j < alphabetSize; ++ j){
            if (edges[i * alphabetSize + j] != nullVertex){
                cout << i << " -> " << edges[i * alphabetSize + j]  <<  " [label = \"";
                if (edgesLabels[i * alphabetSize + j][0] > 0 && edgesLabels[i * alphabetSize + j][1] > 0) {
                    for (int k = edgesLabels[i * alphabetSize + j][0]; k <= edgesLabels[i * alphabetSize + j][1] > 0; ++k){
                        cout << text[k];
                    }
                }
                else {
                       cout << edgesLabels[i * alphabetSize + j][0]
                        << ":" << edgesLabels[i * alphabetSize + j][1];
                }
                cout  << "\"];" << "\n";
            }
        }
    }
    cout << "} \n";

//    for (unsigned int i = 0; i < vertexesSize; ++i){
//        cout << "vertex: " << i << " / "
//            << "suffix: " << suffixLinks[i] << " / "
//            << "length: " << vertexes[i] << endl;
//
//            for (int j = 0; j < alphabetSize; ++ j){
//                if (edges[i * alphabetSize + j] != nullVertex){
//                    cout << "label: " << edgesLabels[i * alphabetSize + j][0] << ":" << edgesLabels[i * alphabetSize + j][1]
//                            << " / " << "destination: " << edges[i * alphabetSize + j] << endl;
//                }
//            }
//    }
}

int main(int argc, char* argv[])
{
	const char* input_filename = argv[1];
	int textSize = 0;
	text = read_input(input_filename, textSize);
	textSize -= 1;
	text_size = textSize - 1;
	int i = 0;

	/*
     * Debug:
     */
//	while (text[i] != '$'){
//        cout << text[i];
//        ++i;
//    }
//    cout << text[textSize];
//    cout << endl;
    /*************************/


    buildSCDAWG(textSize);

//    printToGraphviz();
    printGraphInfo();


//    free(text);

//    searchToken();//TODO: Build the system so thai it would be used after without building again.

	return 0;
}
