#include <iostream>
#include <fstream>
#include <unistd.h>
#include "urlNetwork.h"
#include "pageRank.h"
using namespace std;
int main() {
	std::ifstream urlNode("urlNode.txt");
	std::ifstream urlEdge("urlEdge.txt");
	/*
	std::ifstream urlNode("debug_urlNode");
	std::ifstream urlEdge("debug_urlEdge");
	*/
	UrlNetwork urlNetwork;
	urlNetwork.createMatrix(urlNode, urlEdge);
	PageRank p(urlNetwork.matrix, urlNetwork.nodeIndex2URL);
	p.start();
	sleep(100);
	return 0;
}