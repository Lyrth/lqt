/****************************************************************************
**
** Copyright (C) 1992-2008 Trolltech ASA. All rights reserved.
** Copyright (C) 2002-2005 Roberto Raggi <roberto@kdevelop.org>
**
** This file is part of the Qt Script Generator project on Trolltech Labs.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.  Please review the following information to ensure GNU
** General Public Licensing requirements will be met:
** http://www.trolltech.com/products/qt/opensource.html
**
** If you are unsure which license is appropriate for your use, please
** review the following information:
** http://www.trolltech.com/products/qt/licensing.html or contact the
** sales department at sales@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/


#ifndef LEXER_H
#define LEXER_H

#include "symbol.h"

#include <QtCore/QString>
#include <cstdlib>
#include <cassert>

struct NameSymbol;
class Lexer;
class Control;

typedef void (Lexer::*scan_fun_ptr)();

class Token
{
public:
  int kind;
  std::size_t position;
  std::size_t size;
  char const *text;

  union
  {
    const NameSymbol *symbol;
    std::size_t right_brace;
  } extra;
};

class LocationTable
{
private:
  LocationTable(const LocationTable &source);
  void operator = (const LocationTable &source);

public:
  inline LocationTable(std::size_t size = 1024)
    : lines(0),
      line_count(0),
      current_line(0)
  {
    resize(size);
  }

  inline ~LocationTable()
  {
    std::free(lines);
  }

  inline std::size_t size() const
  { return line_count; }

  void resize(std::size_t size)
  {
    Q_ASSERT(size > 0);
    lines = (std::size_t*) std::realloc(lines, sizeof(std::size_t) * size);
    line_count = size;
  }

  void positionAt(std::size_t offset, int *line, int *column) const
  { positionAt(offset, (int) current_line, line, column); }

  void positionAt(std::size_t offset, int max_line, int *line, int *column) const;

  inline std::size_t &operator[](int index)
  { return lines[index]; }

private:
  std::size_t *lines;
  std::size_t line_count;
  std::size_t current_line;

  friend class Lexer;
};

class TokenStream
{
private:
  TokenStream(const TokenStream &);
  void operator = (const TokenStream &);

public:
  inline TokenStream(std::size_t size = 1024)
     : tokens(0),
       index(0),
       token_count(0)
  {
    resize(size);
  }

  inline ~TokenStream()
  { std::free(tokens); }

  inline std::size_t size() const
  { return token_count; }

  inline std::size_t cursor() const
  { return index; }

  inline void rewind(int i)
  { index = i; }

  void resize(std::size_t size)
  {
    Q_ASSERT(size > 0);
    tokens = (Token*) std::realloc(tokens, sizeof(Token) * size);
    token_count = size;
  }

  inline std::size_t nextToken()
  { return index++; }

  inline int lookAhead(std::size_t i = 0) const
  { return tokens[index + i].kind; }

  inline int kind(std::size_t i) const
  { return tokens[i].kind; }

  inline std::size_t position(std::size_t i) const
  { return tokens[i].position; }

  inline const NameSymbol *symbol(std::size_t i) const
  { return tokens[i].extra.symbol; }

  inline std::size_t matchingBrace(std::size_t i) const
  { return tokens[i].extra.right_brace; }

  inline Token &operator[](int index)
  { return tokens[index]; }

  inline const Token &token(int index) const
  { return tokens[index]; }

private:
  Token *tokens;
  std::size_t index;
  std::size_t token_count;

private:
  friend class Lexer;
};

class LocationManager
{
  LocationManager(LocationManager const &__other);
  void operator = (LocationManager const &__other);

public:
  LocationManager (TokenStream &__token_stream,
          LocationTable &__location_table,
          LocationTable &__line_table):
    token_stream (__token_stream),
    location_table (__location_table),
    line_table (__line_table) {}

  void positionAt(std::size_t offset, int *line, int *column,
                  QString *filename) const;

  void extract_line(int offset, int *line, QString *filename) const;

  TokenStream &token_stream;
  LocationTable &location_table;
  LocationTable &line_table;
};

class TemplateScope;
class Lexer
{
public:
  Lexer(LocationManager &__location, Control *__control);

  ~Lexer();

  void tokenize(const char *contents, std::size_t size);

  LocationManager &_M_location;
  TokenStream &token_stream;
  LocationTable &location_table;
  LocationTable &line_table;
  TemplateScope *template_scope;

private:
  void reportError(const QString& msg);

  void initialize_scan_table();
  void scan_newline();
  void scan_white_spaces();
  void scan_identifier_or_keyword();
  void scan_identifier_or_literal();
  void scan_int_constant();
  void scan_char_constant();
  void scan_string_constant();
  void scan_invalid_input();
  void scan_preprocessor();

  // keywords
  void scanKeyword0();
  void scanKeyword2();
  void scanKeyword3();
  void scanKeyword4();
  void scanKeyword5();
  void scanKeyword6();
  void scanKeyword7();
  void scanKeyword8();
  void scanKeyword9();
  void scanKeyword10();
  void scanKeyword11();
  void scanKeyword12();
  void scanKeyword13();
  void scanKeyword14();
  void scanKeyword16();

  // operators
  void scan_not();
  void scan_remainder();
  void scan_and();
  void scan_left_paren();
  void scan_right_paren();
  void scan_star();
  void scan_plus();
  void scan_comma();
  void scan_minus();
  void scan_dot();
  void scan_divide();
  void scan_colon();
  void scan_semicolon();
  void scan_less();
  void scan_equal();
  void scan_greater();
  void scan_question();
  void scan_left_bracket();
  void scan_right_bracket();
  void scan_xor();
  void scan_left_brace();
  void scan_or();
  void scan_right_brace();
  void scan_tilde();
  void scan_EOF();

  void handle_template_scope(int kind);

private:
  Control *control;
  const unsigned char *cursor;
  const unsigned char *begin_buffer;
  const unsigned char *end_buffer;
  std::size_t index;
  bool parse_template;
  bool parse_template_class;

  static scan_fun_ptr s_scan_table[];
  static scan_fun_ptr s_scan_keyword_table[];
  static bool s_initialized;
};

#endif // LEXER_H

// kate: space-indent on; indent-width 2; replace-tabs on;
