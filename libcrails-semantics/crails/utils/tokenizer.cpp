#include "tokenizer.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>

using namespace std;

static char get_escaped_character(char c)
{
  switch (c)
  {
    case '\\': return '\\';
    case '"':  return '"';
    case '\'': return '\'';
    case 'n':  return '\n';
    case 't':  return '\t';
    case 'r':  return '\r';
    case ' ':  return ' ';
  }
  return 0;
}

inline static const Crails::TokenizerCategory& tokenize_error_category()
{
  static const Crails::TokenizerCategory instance;
  return instance;
}

namespace Crails
{
  vector<string> unsafe_tokenize(const string_view input) noexcept
  {
    error_code ec;
    return tokenize(input, ec);
  }

  vector<string> tokenize(const string_view input)
  {
    error_code ec;
    vector<string> result = tokenize(input, ec);

    if (ec)
    {
      ostringstream message;

      message << "Crails::tokenizer: " << ec.message() << " in " << quoted(input);
      throw runtime_error(message.str());
    }
    return result;
  }

  vector<string> tokenize(const string_view input, error_code& ec) noexcept
  {
    vector<string> tokens;
    string current;
    char current_quote = 0;

    tokens.reserve(input.length());
    for (size_t i = 0 ; i < input.length() ; ++i)
    {
      char c = input[i];

      // Escaping characters
      if (c == '\\')
      {
        if (i + 1 >= input.length()) [[unlikely]]
        {
          ec = error_code{TokenizerIncompleteError, tokenize_error_category()};
          break ;
        }
        else
        {
          char escaped_character;

          escaped_character = get_escaped_character(input[++i]);
          if (escaped_character == 0) [[unlikely]]
          {
            ec = error_code{TokenizerEscapeError, tokenize_error_category()};
            break ;
          }
          else
          {
            current += escaped_character;
            continue ;
          }
        }
      }

      // Tokenizing
      if (current_quote)
      {
        if (c == current_quote)
        {
          tokens.push_back(current);
          current.clear();
          current_quote = 0;
        }
        else
          current += c;
      }
      else
      {
        if (c == '"' || c == '\'')
          current_quote = c;
        else if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
        {
          if (!current.empty())
          {
            tokens.push_back(current);
            current.clear();
          }
        }
        else
          current += c;
      }
    }
    if (current.length())
      tokens.push_back(current);
    if (current_quote != 0)
      ec = error_code{TokenizerUnclosedError, tokenize_error_category()};
    return tokens;
  }
}
