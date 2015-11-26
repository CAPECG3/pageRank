#include <iostream>
#include <unordered_map>
#include <array>
#include <vector>
#include <cmath>
#define NODE_NUM 140000
class PageRank {
public:
	PageRank(std::array<std::unordered_map<int, double>, NODE_NUM> &_matrix, std::unordered_map<int, std::string> &nodeIndex2URL);
	~PageRank(){};
	void start();
private:
	double a = 0.85; //damping factor
	double e=0.0001; //Iteration accuracy
	size_t nodeNumber;
	std::array<std::unordered_map<int, double>, NODE_NUM> &matrix;
	std::unordered_map<int, std::string> &nodeIndex2URL;
	inline double countItAccuracy(const std::vector<double> &v1, const std::vector<double> &v2); 
};
