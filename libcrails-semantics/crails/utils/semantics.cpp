#include "semantics.hpp"
#include <algorithm>

using namespace std;

namespace Crails
{
  bool is_alphanumerical(char c)
  {
    return (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z')
        || (c >= '0' && c <= '9');
  }

  string strip(const string_view str, char character)
  {
    const string chars(1, character);
    const size_t start = str.find_first_not_of(chars);

    if (start == string::npos)
      return string();
    return string(str.substr(start, str.find_last_not_of(chars) - start + 1));
  }

  string trim(const string_view value)
  {
    const char* blank = " \t\r\n";
    const size_t start = value.find_first_not_of(blank);

    if (start == string_view::npos)
      return string();
    return string(value.substr(start, value.find_last_not_of(blank) - start + 1));
  }

  string remove_duplicate_characters(const string& source, char character)
  {
    int length = source.length();

    if (length > 0)
    {
      string str;

      str.reserve(length);
      for (int i = 0 ; i < length - 1 ; ++i)
      {
        if (source[i] != character || source[i] != source[i+1])
          str.push_back(source[i]);
      }
      str.push_back(source[length - 1]);
      return str;
    }
    return source;
  }

  string humanize(const string& tmp)
  {
    string str = strip(tmp);
    string ret;

    for (size_t i = 0 ;  i < str.size() ; ++i)
    {
      if (i == 0 || str[i - 1] == '_' || str[i - 1] == ' ')
      {
        if (str[i] >= 'a' && str[i] <= 'z')
          ret += str[i] - 'a' + 'A';
        else
          ret += str[i];
      }
      else if (str[i] == '_')
      {
        if (i == 0 || str[i - 1] != '_')
          ret += ' ';
      }
      else
        ret += str[i];
    }
    return ret;
  }

  string underscore(const string& tmp)
  {
    string str = strip(tmp);
    string ret;

    for (size_t i = 0 ;  i < str.size() ; ++i)
    {
      if (str[i] >= 'A' && str[i] <= 'Z')
      {
        if (i > 0 && (ret.length() == 0 || (*ret.rbegin()) != '_')) ret += '_';
        ret += str[i] - 'A' + 'a';
      }
      else if (str[i] == ' ')
      {
        if (i == 0 || str[i - 1] != ' ')
          ret += '_';
      }
      else if (str[i] == '-' || str[i] == '\'' || str[i] == '"')
        ret += '_';
      else
        ret += str[i];
    }
    return ret;
  }

  string camelize(const std::string& source, CamelizeOption mode)
  {
    string result;
    bool uppercase_on_next_character = mode == UpperCamelcase;

    for (size_t i = 0 ; i < source.length() ; ++i)
    {
      if (is_alphanumerical(source[i]))
      {
        if (uppercase_on_next_character)
          result += std::toupper(static_cast<unsigned char>(source[i]));
        else
          result += source[i];
        uppercase_on_next_character = false;
      }
      else
        uppercase_on_next_character = true;
    }
    return result;
  }

  string dasherize(const string& source)
  {
    string result;
    bool dash_on_next_character = false;

    for (size_t i = 0 ; i < source.length() ; ++i)
    {
      if (source[i] == ' ' || source[i] == '_' || source[i] == '-' || source[i] == '\'' || source[i] == '"')
        dash_on_next_character = result.length() > 0;
      else if (dash_on_next_character || (source[i] >= 'A' && source[i] <= 'Z'))
      {
        result += '-';
        result += std::tolower(static_cast<unsigned char>(source[i]));
        dash_on_next_character = false;
      }
      else
        result += source[i];
    }
    if (result.length() > 0 && result[0] == '-')
      result.erase(0, 1);
    return result;
  }

  string uppercase(string value)
  {
    transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return toupper(c); });
    return value;
  }

  string lowercase(string value)
  {
    transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return tolower(c); });
    return value;
  }

  string singularize(const string& tmp)
  {
    size_t length = tmp.length();

    if (length > 3)
    {
      string suffix = tmp.substr(length - 3);

      if (suffix == "ies")
        return tmp.substr(0, length - 3) + 'y';
      else if (suffix[1] == 'e' && suffix[2] == 's')
      {
        char   before_es       = suffix[0];
        string two_before_es   = length > 4 ? tmp.substr(length - 4, 2) : string();
        bool   drop_two_chars  = before_es == 's' || before_es == 'x' || before_es == 'z'
                               || two_before_es == "ch" || two_before_es == "sh";

        if (drop_two_chars)
          return tmp.substr(0, length - 2);
        return tmp.substr(0, length - 1);
      }
    }
    if (length > 0)
      return tmp.substr(0, length - 1);
    return tmp;
  }

  string pluralize(const string& tmp)
  {
    if (tmp.length() > 2)
    {
      string suffix = tmp.substr(tmp.length() - 2);

      if (suffix[1] == 's' || suffix[1] == 'x' || suffix[1] == 'z' || suffix == "ch" || suffix == "sh")
        return tmp + "es";
      else if (suffix[1] == 'y')
        return tmp.substr(0, tmp.length() - 1) + "ies";
    }
    return tmp + 's';
  }
}
