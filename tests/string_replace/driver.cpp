#include <crails/utils/string_replace.hpp>

#undef NDEBUG
#include <cassert>

using namespace std;

int main()
{
  // string_view pattern
  assert(Crails::replace_all_occurences("foo bar foo", "foo", "baz") == "baz bar baz");
  assert(Crails::replace_all_occurences("hello", "xyz", "abc") == "hello");
  assert(Crails::replace_all_occurences("", "foo", "bar") == "");
  assert(Crails::replace_all_occurences("foo", "foo", "") == "");
  assert(Crails::replace_all_occurences("aaaa", "aa", "") == "");
  assert(Crails::replace_all_occurences("aaa", "aa", "a") == "aa");
  assert(Crails::replace_all_occurences("cat", "cat", "cats") == "cats");
  assert(Crails::replace_all_occurences("xXxXx", "X", "-") == "x-x-x");
  assert(Crails::replace_all_occurences("hello", "", "X") == "hello");

  // regex pattern
  assert(Crails::replace_all_occurences(string("a1b22c333"), regex("[0-9]+"), "#") == "a#b#c#");
  assert(Crails::replace_all_occurences(string("no digits here"), regex("[0-9]+"), "#") == "no digits here");
  assert(Crails::replace_all_occurences(string("aXbXcXd"), regex("X"), "-") == "a-b-c-d");
  assert(Crails::replace_all_occurences(string("aXXb"), regex("X"), "Y") == "aYYb");
  assert(Crails::replace_all_occurences(string("XbX"), regex("X"), "Y") == "YbY");
  assert(Crails::replace_all_occurences(string(""), regex("X"), "Y") == "");

  // lambda filler
  {
    auto upper = [](const string_view match) -> string
    {
      string result(match);
      for (char& c : result) c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
      return result;
    };
    assert(Crails::replace_all_occurences(string("foo bar baz"), regex("\\w+"), upper) == "FOO BAR BAZ");
  }
  {
    auto expand = [](const string_view) -> string { return "1234"; };
    assert(Crails::replace_all_occurences(string("aXbXc"), regex("X"), expand) == "a1234b1234c");
  }
  {
    auto shrink = [](const string_view) -> string { return "-"; };
    assert(Crails::replace_all_occurences(string("aWORDbWORDc"), regex("WORD"), shrink) == "a-b-c");
  }

  return 0;
}
