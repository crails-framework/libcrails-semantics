#include "semantics.hpp"

using namespace std;

namespace Crails
{
  bool is_alphanumerical(char c)
  {
    return (c >= 'A' && c <= 'Z')
        || (c >= 'a' && c <= 'z')
        || (c >= '0' && c <= '9');
  }

  string strip(const string& str, char character)
  {
    unsigned short w_begin, w_end;
    bool           got_begin = false;

    if (str.length() == 0) return str;
    for (unsigned short i = 0 ; i < str.length() ; ++i)
    {
      if (str[i] != character)
      {
        if (got_begin == false)
        {
          w_begin   = i;
          got_begin = true;
        }
        w_end = i;
      }
    }
    return str.substr(w_begin, (w_end + 1) - w_begin);
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

    for (unsigned short i = 0 ;  i < str.size() ; ++i)
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

    for (unsigned short i = 0 ;  i < str.size() ; ++i)
    {
      if (str[i] >= 'A' && str[i] <= 'Z')
      {
        if (i > 0) ret += '_';
        ret += str[i] - 'A' + 'a';
      }
      else if (str[i] == ' ')
      {
        if (str[i - 1] != ' ')
          ret += '_';
      }
      else if (str[i] == '-')
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
          result += std::toupper(source[i]);
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
      if (source[i] == ' ')
        dash_on_next_character = result.length() > 0;
      else if (dash_on_next_character || (source[i] >= 'A' && source[i] <= 'Z'))
      {
        result += '-';
        result += std::tolower(source[i]);
        dash_on_next_character = false;
      }
      else
        result += source[i];
    }
    if (result.length() > 0 && result[0] == '-')
      result.erase(0, 1);
    return result;
  }

  string singularize(const string& tmp)
  {
    if (tmp.length() > 3)
    {
      string suffix = tmp.substr(tmp.length() - 3);

      if (suffix == "ies")
        return tmp.substr(0, tmp.length() - 3) + 'y';
      else if (suffix[1] == 'e' && suffix[2] == 's')
      {
        if (suffix[0] == 's')
          return tmp.substr(0, tmp.length() - 2);
        return tmp.substr(0, tmp.length() - 1);
      }
    }
    return tmp.substr(0, tmp.length() - 1);
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
