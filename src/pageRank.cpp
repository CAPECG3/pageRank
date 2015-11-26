#include "pageRank.h"
PageRank::PageRank(std::array<std::unordered_map<int, double>, NODE_NUM> &_matrix,
                   std::unordered_map<int, std::string> &_nodeIndex2URL):
	matrix(_matrix), nodeIndex2URL(_nodeIndex2URL),
	nodeNumber(_nodeIndex2URL.size()) {
}
void PageRank::start() {
	std::vector<double> r0(nodeNumber);
	std::vector<double> r1(nodeNumber);
	for (size_t i = 0; i < nodeNumber; i++) {
		r0[i] = 1.0 / nodeNumber;
	}
	bool itState = true; //control r0 or r1 needed to iterate
	do {
		//count r1
		for (size_t i = 0; i < nodeNumber; i++) {
			double tmp = 0.0;
			for (auto it = matrix[i].begin(); it != matrix[i].end(); it++) {
				if (itState)	tmp += a * it->second * r0[it->first];
				else	tmp += a * it->second * r1[it->first];
			}
			if (itState)	r1[i] = tmp + (1 - a) * 1.0 / nodeNumber;
			else r0[i] = tmp + (1 - a) * 1.0 / nodeNumber;
		}
		itState = !itState;
	} while (countItAccuracy(r0, r1) > e);

}
double PageRank::countItAccuracy(const std::vector<double> &v1, const std::vector<double> &v2) {
	double max = 0;
	for (size_t i = 0; i < v1.size(); i++) {
		double tmp = std::abs(v1[i] - v2[i]);
		if (max < tmp) {
			max = tmp;
		}
	}
	return max;
}
