#include <crails/utils/tokenizer.hpp>

#undef NDEBUG
#include <cassert>

using namespace std;

int main()
{
  assert((Crails::tokenize("hello world") == vector<string>{"hello", "world"}));
  assert((Crails::tokenize("  hello   world  ") == vector<string>{"hello", "world"}));
  assert((Crails::tokenize("a\tb\nc\rd") == vector<string>{"a", "b", "c", "d"}));
  assert(Crails::tokenize("").empty());
  assert(Crails::tokenize("     ").empty());

  // quotes
  assert((Crails::tokenize("hello \"big world\"") == vector<string>{"hello", "big world"}));
  assert((Crails::tokenize("'hello world'") == vector<string>{"hello world"}));
  assert((Crails::tokenize("\"\"") == vector<string>{""}));
  assert((Crails::tokenize("a\"b c\"d") == vector<string>{"ab c", "d"}));

  // escaping characters
  assert((Crails::tokenize("hello\\ world") == vector<string>{"hello world"}));
  assert((Crails::tokenize("say \\\"hi\\\"") == vector<string>{"say", "\"hi\""}));
  assert((Crails::tokenize("a\\\\b") == vector<string>{"a\\b"}));
  assert((Crails::tokenize("a\\nb") == vector<string>{"a\nb"}));
  assert((Crails::tokenize("a\\tb") == vector<string>{"a\tb"}));

  // properly fails on invalid input
  {
    bool threw = false;
    try { Crails::tokenize("say \"oops"); }
    catch (const runtime_error&) { threw = true; }
    assert(threw);
  }
  {
    bool threw = false;
    try { Crails::tokenize("trailing\\"); }
    catch (const runtime_error&) { threw = true; }
    assert(threw);
  }
  {
    bool threw = false;
    try { Crails::tokenize("bad\\qescape"); }
    catch (const runtime_error&) { threw = true; }
    assert(threw);
  }

  // unsafe variant doesn't throw on invalid input
  {
    auto tokens = Crails::unsafe_tokenize("say \"oops");
    assert((tokens == vector<string>{"say", "oops"}));
  }

  return 0;
}
