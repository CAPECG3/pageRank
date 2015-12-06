#include <iostream>
#include <unordered_map>
#include <array>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>
#include <fstream>
#define NODE_NUM 140000
class PageRank {
public:
	PageRank(std::array<std::unordered_map<int, double>, NODE_NUM> &_matrix, std::unordered_map<int, std::string> &nodeIndex2URL);
	~PageRank() {};
	void start(std::ofstream &rank);
private:
	double a = 0.85; //damping factor
	std::vector<double> r;
	double e = 0.0001; //Iteration accuracy
	size_t nodeNumber;
	std::array<std::unordered_map<int, double>, NODE_NUM> &matrix;
	std::unordered_map<int, std::string> &nodeIndex2URL;
	inline double countItAccuracy(const std::vector<double> &v1, const std::vector<double> &v2);
	void pageRank();
	void outTenURL(std::ofstream &rank);
	struct cmp {
		bool operator()(std::pair<double, int> a, std::pair<double, int> b) { return  a.first < b.first; }
	};
	std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, cmp> q;
};
