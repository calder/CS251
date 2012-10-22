#include <stdbool.h>
#include "Util/CharUtil.h"


/*
                       +---------------------+
                       | ASCII (char) Values |
                       +---------------------+

           0    1    2     3    4    5    6     7    8    9
        +----+----+----++----+----+----+----++----+----+----+
     30 |    |    |    ||  ! |  " |  # |  $ ||  % |  & |  ' |
     40 |  ( |  ) |  * ||  + |  , |  - |  . ||  / |  0 |  1 |
     50 |  2 |  3 |  4 ||  5 |  6 |  7 |  8 ||  9 |  : |  ; |
        +----+----+----++----+----+----+----++----+----+----+
     60 |  < |  = |  > ||  ? |  @ |  A |  B ||  C |  D |  E |
     70 |  F |  G |  H ||  I |  J |  K |  L ||  M |  N |  O |
     80 |  P |  Q |  R ||  S |  T |  U |  V ||  W |  X |  Y |
     90 |  Z |  [ |  \ ||  ] |  ^ |  _ |  ` ||  a |  b |  c |
        +----+----+----++----+----+----+----++----+----+----+
    100 |  d |  e |  f ||  g |  h |  i |  j ||  k |  l |  m |
    110 |  n |  o |  p ||  q |  r |  s |  t ||  u |  v |  w |
    120 |  x |  y |  z ||  { |  | |  } |  ~ ||    |    |    |
        +----+----+----++----+----+----+----++----+----+----+

                      +-----------------------+
                      | Whitespace Characters |
                      +-----------------------+
                               9 - Tab 
                              10 - Newline
                              32 - Space

*/


bool is_digit (char c)
{
    return ('0' <= c) && (c <= '9');
}


bool is_finalizer (char c)
{
    return is_whitespace(c) || is_paren(c) || (c == ';') || (c == 0);
}


bool is_letter (char c)
{
    return ((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122));
}


bool is_paren (char c)
{
    return (c == '(') || (c == ')') || (c == '[') || (c == ']');
}


bool is_symbol_start (char c)
{
    return (c == '!') || (c == '$') || (c == '%') || (c == '&') ||
           (c == '*') || (c == '/') || (c == ':') || (c == '<') ||
           (c == '=') || (c == '>') || (c == '?') || (c == '~') ||
           (c == '_') || (c == '^') || (c == '-') || is_letter(c);
}


bool is_symbol_body (char c)
{
    return is_symbol_start(c) || is_digit(c) ||
           (c == '.') || (c == '+') || (c == '-');
}


bool is_whitespace (char c)
{
    return (c == '\t') || (c == '\n') || (c == ' ');
}