#include <numeric>
#include <iostream>
#include <map>

static std::map<char, int> vals = {
    {'a', 2 }, {'b', 3  }, {'c', 5 }, {'d', 7 }, {'e', 11}, {'f', 13}, {'g', 17}, {'h', 19}
  , {'i', 23}, {'j', 29 }, {'k', 31}, {'l', 37}, {'m', 41}, {'n', 43}, {'o', 47}, {'p', 53}
  , {'q', 59}, {'r', 61 }, {'s', 67}, {'t', 71}, {'u', 73}, {'v', 79}, {'w', 83}, {'x', 89}
  , {'y', 97}, {'z', 101}
};

static std::map<char, bool> is_eq = {
    {'a', false}, {'b', false}, {'c', false}, {'d', false}, {'e', false}, {'f', false}, {'g', false}, {'h', false}
  , {'i', false}, {'j', false}, {'k', false}, {'l', false}, {'m', false}, {'n', false}, {'o', false}, {'p', false}
  , {'q', false}, {'r', false}, {'s', false}, {'t', false}, {'u', false}, {'v', false}, {'w', false}, {'x', false}
  , {'y', false}, {'z', false}
};

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int convert(std::string const& str) {
  return std::accumulate(str.begin(), str.end(), 1, [](int const result, char const c) {
    return result * vals[c];
  });
}

std::string display(int val) {
  if (val == 1) return "1";

  std::string result;

  for (auto const& pair : vals) {
    if (!is_eq[pair.first]) while (!(val % pair.second)) {
      result.append(&pair.first);
      val /= pair.second;
    }
  }

  return result;
}

int main() {
  // Read number of equations.
  int n; std::cin >> n;

  // For each equation...
  for (int i = 0; i < n; ++i) {
    // Read in eq letter.
    char letter; std::cin >> letter;

    // Mark letter as eq.
    vals[letter] = 1, is_eq[letter] = true;

    // Read and assign expression to eq.
    std::string expr; std::cin >> expr;
    for (char c : expr) vals[letter] *= vals[c];
  }

  while (true) {
    // Read in values.
    std::string a, b; std::cin >> a >> b;

    // Convert values from string to integer.
    int avals = convert(a), bvals = convert(b);

    // Find greatest common divisor.
    int gcd = ::gcd(avals, bvals);

    // Reduce values.
    avals /= gcd, bvals /= gcd;

    // Display results.
    std::cout << display(avals) << ' ' << display(bvals) << '\n';
  }
}
