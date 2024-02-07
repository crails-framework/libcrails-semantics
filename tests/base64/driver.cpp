#include <crails/utils/base64.hpp>

#undef NDEBUG
#include <cassert>

int main()
{
  using namespace std;
  string placeholder("on va manger des chips, t'entends ?");
  string encoded = Crails::base64_encode(placeholder);
  string decoded = Crails::base64_decode(encoded);

  assert(encoded == "b24gdmEgbWFuZ2VyIGRlcyBjaGlwcywgdCdlbnRlbmRzID8=");
  assert(placeholder == decoded);
  return 0;
}
