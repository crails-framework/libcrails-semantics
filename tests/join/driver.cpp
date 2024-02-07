#include <crails/utils/join.hpp>
#include <vector>
#include <list>
#include <string>
#include <string_view>

#undef NDEBUG
#include <cassert>

using namespace std;  

const vector<string_view> listA{
  "coucou", "petite", "perruche"
};

const list<int> listB{
  12, 42, 914
};

int main()
{
  assert(Crails::join(listA) == "coucou petite perruche");
  assert(Crails::join(listB, '+') == "12+42+914");
  assert(Crails::join(listA.rbegin(), listA.rend()) == "perruche petite coucou");
  return 0;
}
