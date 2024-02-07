#include <crails/utils/split.hpp>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <string_view>

#undef NDEBUG
#include <cassert>

int main()
{
  using namespace std;

  {
    list<string> result = Crails::split<string>("break these words", ' ');
    assert(result.size() == 3);
    assert(*result.begin() == "break");
    assert(*result.rbegin() == "words");
  }

  {
    vector<string_view> result = Crails::split<string_view, vector<string_view>>("1 23 ", ' ');
    assert(result.size() == 2);
    assert(result[0] == "1");
    assert(result[1] == "23");
  }

  {
    list<string_view> result = Crails::split<string_view, list<string_view>>("crails+semantics+++test+strings", '+');
    assert(result.size() == 4);
  }

  {
    vector<string> result = Crails::split<string, vector<string>>("compte  les   repetitions", ' ', true);
    assert(result.size() > 3);
    assert(result[1] == "");
  }

  return 0;
}
