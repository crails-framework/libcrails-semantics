#pragma once
#include <string>
#include <vector>
#include <system_error>

namespace Crails
{
  enum TokenizerError
  {
    TokenizerOk = 0,
    TokenizerUnclosedError,
    TokenizerIncompleteError,
    TokenizerEscapeError
  };

  struct TokenizerCategory : public std::error_category
  {
    const char* name() const noexcept override { return "Crails::tokenize"; }
    std::string message(int value) const noexcept override
    {
      switch (static_cast<TokenizerError>(value))
      {
      case TokenizerOk:              return "";
      case TokenizerUnclosedError:   return "unclosed quote";
      case TokenizerIncompleteError: return "incomplete escape sequence";
      case TokenizerEscapeError:     return "unknown escape sequence";
      }
      return "unknown error";
    }
  };

  std::vector<std::string> tokenize(const std::string_view input, std::error_code&) noexcept;
  std::vector<std::string> tokenize(const std::string_view input);
  std::vector<std::string> unsafe_tokenize(const std::string_view input) noexcept;
}
