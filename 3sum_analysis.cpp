#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include<random>
#include<chrono>
#include <cmath>
#include<fstream>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        set <vector<int>> found;

        for (int i = 0; i < n; ++i){
            for(int j = i + 1; j < n; ++j){
                for(int k = j + 1; k < n; ++k){
                    int a = nums[i], b = nums[j], c = nums[k];
                    if(a + b + c == 0){
                        vector<int> triplet = {a, b, c};
                        sort(triplet.begin(), triplet.end());
                        found.insert(triplet);

                    } 
                }
            }

        }
        return vector<vector<int>>(found.begin(), found.end());
    }
};
vector<int> generateInput(int n){
	vector<int> nums;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(-100, 100);

	for(int i = 0; i < n - 3; i++){
		nums.push_back(dis(gen));
	}

	int a = dis(gen);
	int b = dis(gen);
	nums.push_back(-a);
	nums.push_back(-b);
	nums.push_back(a + b);

	shuffle(nums.begin(), nums.end(), gen);
	return nums;
}

int main(){
	vector<int> sizes = {100, 200, 400, 800, 1600, 3200, 6400, 8000};
	ofstream out("runtime_data.csv");
	out << "ntime_ms, log2_n, log2_time\n";

	for(int n: sizes){
		cout << "Generating input for n = " << n <<"...\n";
		vector<int> nums = generateInput(n);

		Solution sol;
		auto start = chrono::high_resolution_clock::now();
		vector<vector<int>> result = sol.threeSum(nums);
		auto end = chrono::high_resolution_clock::now();

		double time_ms = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0;
		cout << "n = " << n <<", time = " << time_ms << " ms\n";

		out << n << "," << time_ms << "," << log2(n) << "," << log2(time_ms) << "\n";
		out.flush();
		if(time_ms > 15000){
			cout << "Runtime too long for n = " << n << ", stopping test early.\n";
			break;
		}
	}
	out.close();
	cout << "Runtime analysis complete.\n";
	return 0;
}
