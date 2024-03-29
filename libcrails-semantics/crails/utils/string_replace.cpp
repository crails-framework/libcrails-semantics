#include "string_replace.hpp"

using namespace std;

namespace Crails
{
  string replace_all_occurences(string data, const string_view pattern, const string_view filler)
  {
    size_t pos = 0;

    while ((pos = data.find(pattern, pos)) != string::npos)
    {
      data.replace(pos, pattern.length(), filler.data(), filler.length());
      pos += filler.length();
    }
    return data;
  }

  string replace_all_occurences(const string& data, const regex& pattern, const string_view filler)
  {
    return replace_all_occurences(data, pattern, [filler](const string_view) -> string { return string(filler); });
  }

  string replace_all_occurences(const string& data, const regex& pattern, function<string(const string_view)> filler)
  {
    size_t pos = 0;
    string result;
    auto it = sregex_iterator(data.begin(), data.end(), pattern);

    result.reserve(data.length());
    for (; it != sregex_iterator() ; ++it)
    {
      const smatch      match = *it;
      const string_view match_string(&data[match.position()], match.length());

      result += data.substr(pos, match.position());
      result += filler(match_string);
      pos = match.position() + match.length();
    }
    result += data.substr(pos);
    return result;
  }
}
