#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
int N = 1000;
double x0 = 0.0;
double x1 = 0.0;

int main() {
  std::vector<int> vec1(N+1);
  std::iota(vec1.begin(), vec1.end(), 0);

  std::vector<double> vec2(vec1.size());

  std::transform(vec1.begin(), vec1.end(), vec2.begin(),
                 [N](int i) { return i * M_PI / N; });

  for (auto a : vec1)
    std::cout << a << " ";
  std::cout << std::endl;

  for (auto a : vec2)
    std::cout << a << " ";
  std::cout << std::endl;
}
