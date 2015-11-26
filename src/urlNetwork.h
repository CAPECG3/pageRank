#ifndef _URL_NETWORK_
#define _URL_NETWORK_
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <array>
#include <string>
#define NODE_NUM 140000
class UrlNetwork {
public:
	std::array<std::unordered_map<int, double>, NODE_NUM> matrix;
	std::unordered_map<int, std::string> nodeIndex2URL;
	void createMatrix(std::ifstream &urlNode, std::ifstream &urlEdge) {
		_createMatrix(urlNode, urlEdge);
	}
private:
	std::unordered_map<int, int> linkNumByCol;
	std::unordered_map<std::string, int> node;
	size_t nodeNumber;
private:
	void createNode(std::ifstream &urlNode) {
		int index = 0;
		std::string line;
		while (urlNode >> line) {
			if (node.find(line) == node.end()) {
				node[line] = index;
				nodeIndex2URL[index] = line;
				index++;
			}
		}
		nodeNumber = node.size();
	}
	void createEdge(std::ifstream &urlEdge) {
		std::string row, col;
		int rowIndex, colIndex;
		while (urlEdge >> col >> row) {
			if (node.find(row) == node.end() || node.find(col) == node.end()) {
				continue;
			}
			rowIndex = node[row];
			colIndex = node[col];
			if (matrix[rowIndex].find(colIndex) == matrix[rowIndex].end()) {
				matrix[rowIndex][colIndex] = 1;
			}
			else {
				matrix[rowIndex][colIndex]++;
			}
			if (linkNumByCol.find(colIndex) == linkNumByCol.end()) {
				linkNumByCol[colIndex] = 1;
			}
			else {
				linkNumByCol[colIndex]++;
			}
		}
	}
	void _createMatrix(std::ifstream &urlNode, std::ifstream &urlEdge) {
		createNode(urlNode);
		createEdge(urlEdge);
		for (size_t i = 0; i < nodeNumber; i++) {
			for (auto it = matrix[i].begin(); it != matrix[i].end(); it++) {
				it->second /= linkNumByCol[it->first];
			}
		}
		std::cout << "matrix create done" << std::endl;
		//displayByAdj();
	}
	void displayByAdj() {
		for (size_t i = 0; i < nodeNumber; i++) {
			for (size_t j = 0; j < nodeNumber; j++) {
				if (matrix[i].find(j) == matrix[i].end()) {
					std::cout << 0 << " ";
				}
				else {
					std::cout << matrix[i][j] << " ";
				}
			}
			std::cout << std::endl;
		}
	}
};
#endif