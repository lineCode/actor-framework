#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

#include "caf/all.hpp"

#define CAF_SUITE parser
#include "caf/test/unit_test.hpp"
#include "caf/test/unit_test_impl.hpp"

/*
// Google Benchmark Library
#include <benchmark/benchmark.h>

#include <boost/spirit/home/qi.hpp>

#include <boost/fusion/include/std_pair.hpp>
#include <boost/spirit/include/qi_char_class.hpp>
#include <boost/spirit/include/qi_int.hpp>
*/

using std::cout;
using std::endl;
using std::string;

using namespace caf;

/*
constexpr int64_t zero = 0;

CAF_TEST(fixed_ints) {
  int64_t st;
  auto p0 = parser_tester(st, int3_[assign(st)]);
  CAF_CHECK_EQUAL(p0(""), none);
  CAF_CHECK_EQUAL(p0("1"), none);
  CAF_CHECK_EQUAL(p0("12"), none);
  CAF_CHECK_EQUAL(p0("123"), int64_t{123});
  CAF_CHECK_EQUAL(p0("1234"), none);
  CAF_CHECK_EQUAL(p0("12345"), none);
  CAF_CHECK_EQUAL(p0("123456"), none);
  using ints = std::vector<int64_t>;
  ints xs;
  auto p1 = parser_tester(xs, +(int3_[emplace_back(xs)]));
  ints _123{123};
  ints _123456{123, 456};
  CAF_CHECK_EQUAL(p1(""), none);
  CAF_CHECK_EQUAL(p1("1"), none);
  CAF_CHECK_EQUAL(p1("12"), none);
  CAF_CHECK_EQUAL(p1("123"), _123);
  CAF_CHECK_EQUAL(p1("1234"), none);
  CAF_CHECK_EQUAL(p1("12345"), none);
  CAF_CHECK_EQUAL(p1("123456"), _123456);
}

CAF_TEST(integers) {
  int64_t st;
  auto p = parser_tester(st, int_[assign(st)]);
  //single<integer<int64_t>, std::reference_wrapper<int64_t>> sp{std::ref(st)};
  //auto p = parser_tester(st, sp);
  //auto p = parser_tester(st, lift<integer>(st));
  CAF_CHECK_EQUAL(p("0"), zero);
  CAF_CHECK_EQUAL(p("1"), int64_t{1});
  CAF_CHECK_EQUAL(p("10"), int64_t{10});
  CAF_CHECK_EQUAL(p("999"), int64_t{999});
  CAF_CHECK_EQUAL(p("999f"), none);
  CAF_CHECK_EQUAL(p("999s"), none);
  CAF_CHECK_EQUAL(p(" 0"), none);
  CAF_CHECK_EQUAL(p("0 "), none);
  CAF_CHECK_EQUAL(p(" 0 "), none);
}

CAF_TEST(integers_with_spaces) {
  integer_storage st;
  //auto ws = lift<whitespace>(st);
  single<literal<integer_storage, ' '>> ws;
  single<integer<integer_storage>> in;
  auto p1 = parser_tester(st, *ws >> in);
  CAF_CHECK_EQUAL(p1("0"), zero);
  CAF_CHECK_EQUAL(p1("1"), int64_t{1});
  CAF_CHECK_EQUAL(p1("10"), int64_t{10});
  CAF_CHECK_EQUAL(p1("999"), int64_t{999});
  CAF_CHECK_EQUAL(p1(" 0"), zero);
  CAF_CHECK_EQUAL(p1("  1"), int64_t{1});
  CAF_CHECK_EQUAL(p1("   10"), int64_t{10});
  CAF_CHECK_EQUAL(p1("    999"), int64_t{999});
  CAF_CHECK_EQUAL(p1("0 "), none);
  CAF_CHECK_EQUAL(p1("1  "), none);
  CAF_CHECK_EQUAL(p1("10   "), none);
  CAF_CHECK_EQUAL(p1("999    "), none);
  CAF_CHECK_EQUAL(p1("   0"), zero);
  CAF_CHECK_EQUAL(p1("  1 "), none);
  CAF_CHECK_EQUAL(p1(" 10 "), none);
  CAF_CHECK_EQUAL(p1("999 "), none);
  CAF_CHECK_EQUAL(p1("999f"), none);
  CAF_CHECK_EQUAL(p1("999s"), none);
  auto p2 = parser_tester(st, in >> *ws);
  CAF_CHECK_EQUAL(p2("0"), zero);
  CAF_CHECK_EQUAL(p2("1"), int64_t{1});
  CAF_CHECK_EQUAL(p2("10"), int64_t{10});
  CAF_CHECK_EQUAL(p2("999"), int64_t{999});
  CAF_CHECK_EQUAL(p2(" 0"), none);
  CAF_CHECK_EQUAL(p2("  1"), none);
  CAF_CHECK_EQUAL(p2("   10"), none);
  CAF_CHECK_EQUAL(p2("    999"), none);
  CAF_CHECK_EQUAL(p2("0 "), zero);
  CAF_CHECK_EQUAL(p2("1  "), int64_t{1});
  CAF_CHECK_EQUAL(p2("10   "), int64_t{10});
  CAF_CHECK_EQUAL(p2("999    "), int64_t{999});
  CAF_CHECK_EQUAL(p2("   0"), none);
  CAF_CHECK_EQUAL(p2("  1 "), none);
  CAF_CHECK_EQUAL(p2(" 10 "), none);
  CAF_CHECK_EQUAL(p2("999 "), int64_t{999});
  CAF_CHECK_EQUAL(p2("999f"), none);
  CAF_CHECK_EQUAL(p2("999s"), none);
  auto p3 = parser_tester(st, *ws >> in >> *ws);
  CAF_CHECK_EQUAL(p3("0"), zero);
  CAF_CHECK_EQUAL(p3("1"), int64_t{1});
  CAF_CHECK_EQUAL(p3("10"), int64_t{10});
  CAF_CHECK_EQUAL(p3("999"), int64_t{999});
  CAF_CHECK_EQUAL(p3(" 0"), zero);
  CAF_CHECK_EQUAL(p3("  1"), int64_t{1});
  CAF_CHECK_EQUAL(p3("   10"), int64_t{10});
  CAF_CHECK_EQUAL(p3("    999"), int64_t{999});
  CAF_CHECK_EQUAL(p3("0 "), zero);
  CAF_CHECK_EQUAL(p3("1  "), int64_t{1});
  CAF_CHECK_EQUAL(p3("10   "), int64_t{10});
  CAF_CHECK_EQUAL(p3("999    "), int64_t{999});
  CAF_CHECK_EQUAL(p3("   0"), zero);
  CAF_CHECK_EQUAL(p3("  1 "), int64_t{1});
  CAF_CHECK_EQUAL(p3(" 10 "), int64_t{10});
  CAF_CHECK_EQUAL(p3("999 "), int64_t{999});
  CAF_CHECK_EQUAL(p3("999f"), none);
  CAF_CHECK_EQUAL(p3("999s"), none);
  auto p4 = parser_tester(st, +ws >> in);
  CAF_CHECK_EQUAL(p4(""), none);
  CAF_CHECK_EQUAL(p4(" 2"), int64_t{2});
  CAF_CHECK_EQUAL(p4(" 2 3"), none);
  auto p5 = parser_tester(st, *(+ws >> in));
  CAF_CHECK_EQUAL(p5(""), int64_t{0});
  CAF_CHECK_EQUAL(p5(" 2"), int64_t{2});
  CAF_CHECK_EQUAL(p5(" 2 3"), int64_t{3});
  auto p6 = parser_tester(st, in >> *(+ws >> in));
  CAF_CHECK_EQUAL(p6("1"), int64_t{1});
  CAF_CHECK_EQUAL(p6("1 2"), int64_t{2});
  CAF_CHECK_EQUAL(p6("1 2 3"), int64_t{3});
}

CAF_TEST(literals) {
  integer_storage st;
  single<literal<integer_storage, 'a', 'b', 'c'>> abc;
  auto p0 = parser_tester(st, abc);
  CAF_CHECK_EQUAL(p0(""), none);
  CAF_CHECK_EQUAL(p0("a"), none);
  CAF_CHECK_EQUAL(p0("ab"), none);
  CAF_CHECK_EQUAL(p0("abc"), zero);
  CAF_CHECK_EQUAL(p0("cba"), none);
  CAF_CHECK_EQUAL(p0("abcd"), none);
  CAF_CHECK_EQUAL(p0("abcabc"), none);
  auto p1 = parser_tester(st, *abc);
  CAF_CHECK_EQUAL(p1(""), zero);
  CAF_CHECK_EQUAL(p1("a"), none);
  CAF_CHECK_EQUAL(p1("ab"), none);
  CAF_CHECK_EQUAL(p1("abc"), zero);
  CAF_CHECK_EQUAL(p1("cba"), none);
  CAF_CHECK_EQUAL(p1("abcd"), none);
  CAF_CHECK_EQUAL(p1("abcabc"), zero);
  auto p2 = parser_tester(st, +abc);
  CAF_CHECK_EQUAL(p2(""), none);
  CAF_CHECK_EQUAL(p2("a"), none);
  CAF_CHECK_EQUAL(p2("ab"), none);
  CAF_CHECK_EQUAL(p2("abc"), zero);
  CAF_CHECK_EQUAL(p2("cba"), none);
  CAF_CHECK_EQUAL(p2("abcd"), none);
  CAF_CHECK_EQUAL(p2("abcabc"), zero);
  auto p3 = parser_tester(st, abc >> abc);
  CAF_CHECK_EQUAL(p3(""), none);
  CAF_CHECK_EQUAL(p3("a"), none);
  CAF_CHECK_EQUAL(p3("ab"), none);
  CAF_CHECK_EQUAL(p3("abc"), none);
  CAF_CHECK_EQUAL(p3("cba"), none);
  CAF_CHECK_EQUAL(p3("abcd"), none);
  CAF_CHECK_EQUAL(p3("abcabc"), zero);
  CAF_CHECK_EQUAL(p3("abcabcabc"), none);
  auto p4 = parser_tester(st, +(abc >> abc));
  CAF_CHECK_EQUAL(p4(""), none);
  CAF_CHECK_EQUAL(p4("a"), none);
  CAF_CHECK_EQUAL(p4("ab"), none);
  CAF_CHECK_EQUAL(p4("abc"), none);
  CAF_CHECK_EQUAL(p4("cba"), none);
  CAF_CHECK_EQUAL(p4("abcd"), none);
  CAF_CHECK_EQUAL(p4("abcabc"), zero);
  CAF_CHECK_EQUAL(p4("abcabcab"), none);
  CAF_CHECK_EQUAL(p4("abcabcabcabc"), zero);
  auto p5 = parser_tester(st, *(abc >> abc));
  CAF_CHECK_EQUAL(p5(""), zero);
  CAF_CHECK_EQUAL(p5("a"), none);
  CAF_CHECK_EQUAL(p5("ab"), none);
  CAF_CHECK_EQUAL(p5("abc"), none);
  CAF_CHECK_EQUAL(p5("cba"), none);
  CAF_CHECK_EQUAL(p5("abcd"), none);
  CAF_CHECK_EQUAL(p5("abcabc"), zero);
  CAF_CHECK_EQUAL(p5("abcabcab"), none);
  CAF_CHECK_EQUAL(p5("abcabcabcabc"), zero);
}

CAF_TEST(integer_list) {
  integer_storage st;
  single<integer<integer_storage>> num;
  single<literal<integer_storage, ','>> sep;
  auto p = parser_tester(st, num >> *(sep >> num));
  CAF_CHECK_EQUAL(p("0"), zero);
  CAF_CHECK_EQUAL(p("a"), none);
  CAF_CHECK_EQUAL(p("1,2"), int64_t{2});
  CAF_CHECK_EQUAL(p("1,2,3"), int64_t{3});
  CAF_CHECK_EQUAL(p("1,a,3"), none);
  CAF_CHECK_EQUAL(p(",3"), none);
}
*/

#define on_return()                                                            \
  parser_result result;                                                        \
  auto i = first;                                                              \
  auto on_return_cb = [&]

#define start()                                                                \
  ;                                                                            \
  goto s_init;                                                                 \
  s_unexpected_eof:                                                            \
  result.code = ec::unexpected_eof;                                            \
  goto s_return;                                                               \
  s_unexpected_character:                                                      \
  result.code = ec::unexpected_character;                                      \
  s_return:                                                                    \
  on_return_cb();                                                              \
  result.last = i;                                                             \
  return result;                                                               \
  {                                                                            \
    static constexpr bool state_is_terminal = false;

#define state(name)                                                            \
  result.reached_terminal_state = state_is_terminal;                           \
  goto s_unexpected_character;                                                 \
  }                                                                            \
  {                                                                            \
    static constexpr bool state_is_terminal = false;                           \
    s_##name : __attribute__((unused));                                        \
    if (i == last)                                                             \
      goto s_unexpected_eof;                                                   \
    e_##name : __attribute__((unused));

#define term_state(name)                                                       \
  result.reached_terminal_state = state_is_terminal;                           \
  goto s_unexpected_character;                                                 \
  }                                                                            \
  {                                                                            \
    static constexpr bool state_is_terminal = true;                            \
    s_##name : __attribute__((unused));                                        \
    if (i == last)                                                             \
      goto s_fin;                                                              \
    e_##name : __attribute__((unused));

#define fin()                                                                  \
  result.reached_terminal_state = state_is_terminal;                           \
  goto s_unexpected_character;                                                 \
  }                                                                            \
  s_fin:                                                                       \
  result.code = ec::success;                                                   \
  goto s_return;

#define input(condition, target)                                               \
  if (condition) {                                                             \
    ++i;                                                                       \
    goto s_##target;                                                           \
  }

#define action(condition, target, statement)                                   \
  if (condition) {                                                             \
    statement;                                                                 \
    ++i;                                                                       \
    goto s_##target;                                                           \
  }

#define failure(condition, error_code)                                         \
  if (condition) {                                                             \
    printf("%d\n", __LINE__);                                                  \
    result.code = error_code;                                                  \
    goto s_return;                                                             \
  }

#define epsilon(target) goto e_##target;

enum class ec : uint8_t {
  /// Not-an-error.
  success,
  /// Parser stopped after reaching the end while still expecting input.
  unexpected_eof,
  /// Parser stopped after reading an unexpected character.
  unexpected_character,
  /// Cannot construct a negative caf::duration.
  negative_duration,
  /// Cannot construct a caf::duration with a value exceeding uint32_t.
  duration_overflow,
  /// Too many characters for an atom.
  too_many_characters,
};

std::string to_string(ec x) {
  static constexpr const char* ec_names[] = {
    "success",
    "unexpected_eof",
    "unexpected_character",
    "negative_duration",
    "duration_overflow",
    "too_many_characters",
  };
  return ec_names[static_cast<int>(x)];
}
template <class... Ts>
error make_error(ec code, Ts&&... xs) {
  return {static_cast<uint8_t>(code), atom("parser"),
          make_message(std::forward<Ts>(xs)...)};
}

struct parser_result {
  ec code;
  bool reached_terminal_state;
  const char* last;
  config_value value;
};

parser_result parse_integer(const char* first, const char* last) {
  // Utility functions.
  auto hexval = [](char c) -> int64_t {
    return c >= '0' && c <= '9' ?
             c - '0' :
             (c >= 'A' && c <= 'F' ? c - 'A' : c - 'a') + 10;
  };
  auto bin_digit = [](char c) {
    return c == '0' || c == '1';
  };
  auto oct_digit = [](char c) {
    return c >= '0' && c <= '7';
  };
  auto dec_digit = [](char c) {
    return c >= '0' && c <= '9';
  };
  auto hex_digit = [](char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
           || (c >= 'A' && c <= 'F');
  };
  // Local state.
  int64_t x;
  on_return() {
    result.value = x;
  }
  start() {
    // nop
  }
  state(init) {
    input(*i == '-', start_neg)
    action(*i == '0', pos_zero, x = 0)
    action(dec_digit(*i), pos_dec, x = *i - '0')
  }
  term_state(pos_zero) {
    input(*i == 'b' || *i == 'B', start_pos_bin)
    input(*i == 'x' || *i == 'X', start_pos_hex)
    action(oct_digit(*i), pos_oct, x = *i - '0')
  }
  state(start_neg) {
    action(*i == '0', neg_zero, x = 0)
    action(dec_digit(*i), neg_dec, x = -(*i - '0'))
  }
  term_state(neg_zero) {
    input(*i == 'b' || *i == 'B', start_neg_bin)
    input(*i == 'x' || *i == 'X', start_neg_hex)
    action(oct_digit(*i), neg_oct, x = -(*i - '0'))
  }
  state(start_pos_bin) {
    epsilon(pos_bin)
  }
  term_state(pos_bin) {
    action(bin_digit(*i), pos_bin, x = (x * 2) + (*i - '0'))
  }
  term_state(pos_oct) {
    action(oct_digit(*i), pos_oct, x = (x * 8) + (*i - '0'))
  }
  term_state(pos_dec) {
    action(dec_digit(*i), pos_dec, x = (x * 10) + (*i - '0'))
  }
  state(start_pos_hex) {
    epsilon(pos_hex)
  }
  term_state(pos_hex) {
    action(hex_digit(*i), pos_hex, x = (x * 16) + hexval(*i))
  }
  state(start_neg_bin) {
    epsilon(neg_bin)
  }
  term_state(neg_bin) {
    action(bin_digit(*i), neg_bin, x = (x * 2) - (*i - '0'))
  }
  term_state(neg_oct) {
    action(oct_digit(*i), neg_oct, x = (x * 8) - (*i - '0'))
  }
  term_state(neg_dec) {
    action(dec_digit(*i), neg_dec, x = (x * 10) - (*i - '0'))
  }
  state(start_neg_hex) {
    epsilon(neg_hex)
  }
  term_state(neg_hex) {
    action(hex_digit(*i), neg_hex, x = (x * 16) - (hexval(*i)))
  }
  fin();
}

parser_result parse_integer(const std::string& str) {
  return parse_integer(str.c_str(), str.c_str() + str.size());
}

template <class T>
struct opt_visit {
  optional<T> operator()(T x) const {
    return x;
  }
  template <class U>
  optional<T> operator()(U) const {
    return none;
  }
};

parser_result parse_integer_or_duration(const char* first, const char* last) {
  // Call integer parser first.
  auto tmp = parse_integer(first, last);
  // Expect the parser to stop at the suffix, otherwise return original result.
  if (tmp.code != ec::unexpected_character
      || !holds_alternative<int64_t>(tmp.value))
    return tmp;
  // Pick up where the integer parser stopped.
  first = tmp.last;
  time_unit x;
  on_return() {
    // Bound and sanity checking.
    auto y = get<int64_t>(tmp.value);
    if (result.code != ec::success) {
      // No valid suffix after the integer -> just return the integer.
      result.value = y;
    } else {
      switch (x) {
        default:
          result.value = timespan{y};
          break;
        case time_unit::microseconds:
          result.value = timespan{y * 1000};
          break;
        case time_unit::milliseconds:
          result.value = timespan{y * 1000000};
          break;
        case time_unit::seconds:
          result.value = timespan{y * 1000000000};
          break;
        case time_unit::minutes:
          result.value = timespan{y * 60000000000};
          break;
      }
    }
  }
  start() {
    // nop
  }
  state(init) {
    input(*i == 'u', have_u)
    input(*i == 'n', have_n)
    input(*i == 'm', have_m)
    action(*i == 's', done, x = time_unit::seconds)
  }
  state(have_u) {
    action(*i == 's', done, x = time_unit::microseconds)
  }
  state(have_n) {
    action(*i == 's', done, x = time_unit::nanoseconds)
  }
  state(have_m) {
    input(*i == 'i', have_mi)
    action(*i == 's', done, x = time_unit::milliseconds)
  }
  state(have_mi) {
    action(*i == 'n', done, x = time_unit::minutes)
  }
  term_state(done) {
    // nop
  }
  fin();
}

parser_result parse_double(const char* first, const char* last) {
  // We cannot assume [first, last) is null-terminated and from_chars is a
  // C++17 feature.
  std::string tmp{first, last};
  auto i = tmp.c_str();
  char* e;
  parser_result result;
  // TODO: use from_chars after switching to C++17
  result.value = strtod(i, &e);
  result.last = first + std::distance(i, const_cast<const char*>(e));
  if (i == e) {
    result.reached_terminal_state = false;
    result.code = ec::unexpected_character;
  } else{
    result.reached_terminal_state = true;
    result.code = (*e == '\0') ? ec::success : ec::unexpected_character;
  }
  return result;
}

parser_result parse_atom(const char* first, const char* last) {
  size_t pos = 0;
  char buf[11];
  memset(buf, 0, sizeof(buf));
  auto legal = [](char c) {
    return isalnum(c) || c == '_' || c == ' ';
  };
  on_return() {
    if (result.code == ec::success)
      result.value = atom(buf);
  }
  start() {
    // nop
  }
  state(init) {
    input(*i == '\'', read_chars)
  }
  state(read_chars) {
    input(*i == '\'', done)
    failure(pos >= sizeof(buf) - 1, ec::too_many_characters)
    action(legal(*i), read_chars, buf[pos++] = *i)
  }
  term_state(done) {
    // nop
  }
  fin();
}

using res_t = std::tuple<config_value, ec, ptrdiff_t>;

using parse_function = parser_result (*)(const char*, const char*);

std::function<res_t (const std::string& x)> make_parser(parse_function f) {
  return [f](const std::string& x) {
    auto y = f(x.c_str(), x.c_str() + x.size());
    //auto val = holds_alternative<T>(y.value) ? get<T>(y.value) : T{};
    return res_t{y.value, y.code, std::distance(x.c_str(), y.last)};
  };
}

res_t res(int x, ec y, ptrdiff_t z) {
  return {config_value{static_cast<int64_t>(x)}, y, z};
}

template <class T>
res_t res(T x, ec y, ptrdiff_t z) {
  return {config_value{x}, y, z};
}

CAF_TEST(integers) {
  auto parse = make_parser(parse_integer);
  CAF_CHECK_EQUAL(parse("0"), res(0, ec::success, 1));
  CAF_CHECK_EQUAL(parse("1"), res(1, ec::success, 1));
  CAF_CHECK_EQUAL(parse("00"), res(0, ec::success, 2));
  CAF_CHECK_EQUAL(parse("10"), res(10, ec::success, 2));
  CAF_CHECK_EQUAL(parse("101"), res(101, ec::success, 3));
  CAF_CHECK_EQUAL(parse("0101"), res(65, ec::success, 4));
  CAF_CHECK_EQUAL(parse("0b101"), res(5, ec::success, 5));
  CAF_CHECK_EQUAL(parse("0B101"), res(5, ec::success, 5));
  CAF_CHECK_EQUAL(parse("0x101"), res(257, ec::success, 5));
  CAF_CHECK_EQUAL(parse("0X101"), res(257, ec::success, 5));
  CAF_CHECK_EQUAL(parse("-0"), res(0, ec::success, 2));
  CAF_CHECK_EQUAL(parse("-1"), res(-1, ec::success, 2));
  CAF_CHECK_EQUAL(parse("-00"), res(0, ec::success, 3));
  CAF_CHECK_EQUAL(parse("-10"), res(-10, ec::success, 3));
  CAF_CHECK_EQUAL(parse("-101"), res(-101, ec::success, 4));
  CAF_CHECK_EQUAL(parse("-0101"), res(-65, ec::success, 5));
  CAF_CHECK_EQUAL(parse("-0b101"), res(-5, ec::success, 6));
  CAF_CHECK_EQUAL(parse("-0B101"), res(-5, ec::success, 6));
  CAF_CHECK_EQUAL(parse("-0x101"), res(-257, ec::success, 6));
  CAF_CHECK_EQUAL(parse("-0X101"), res(-257, ec::success, 6));
  CAF_CHECK_EQUAL(parse("0s"), res(0, ec::unexpected_character, 1));
  CAF_CHECK_EQUAL(parse("0b"), res(0, ec::unexpected_eof, 2));
  CAF_CHECK_EQUAL(parse("0B"), res(0, ec::unexpected_eof, 2));
  CAF_CHECK_EQUAL(parse("0x"), res(0, ec::unexpected_eof, 2));
  CAF_CHECK_EQUAL(parse("0X"), res(0, ec::unexpected_eof, 2));
}

constexpr timespan operator"" _min(unsigned long long x) {
  return timespan{x * 60000000000};
}

constexpr timespan operator"" _s(unsigned long long x) {
  return timespan{x * 1000000000};
}
constexpr timespan operator"" _ms(unsigned long long x) {
  return timespan{x * 1000000};
}

constexpr timespan operator"" _us(unsigned long long x) {
  return timespan{x * 1000};
}

constexpr timespan operator"" _ns(unsigned long long x) {
  return timespan{x};
}

CAF_TEST(timespans) {
  auto parse = make_parser(parse_integer_or_duration);
  CAF_CHECK_EQUAL(parse("0"), res(0, ec::success, 1));
  CAF_CHECK_EQUAL(parse("10"), res(10, ec::success, 2));
  CAF_CHECK_EQUAL(parse("-10"), res(-10, ec::success, 3));
  CAF_CHECK_EQUAL(parse("0min"), res(0_min, ec::success, 4));
  CAF_CHECK_EQUAL(parse("0ss"), res(0, ec::unexpected_character, 2));
  CAF_CHECK_EQUAL(parse("0s"), res(0_s, ec::success, 2));
  CAF_CHECK_EQUAL(parse("0ms"), res(0_ms, ec::success, 3));
  CAF_CHECK_EQUAL(parse("0us"), res(0_us, ec::success, 3));
  CAF_CHECK_EQUAL(parse("0ns"), res(0_ns, ec::success, 3));
  CAF_CHECK_EQUAL(parse("1337min"), res(1337_min, ec::success, 7));
  CAF_CHECK_EQUAL(parse("1337s"), res(1337_s, ec::success, 5));
  CAF_CHECK_EQUAL(parse("1337ms"), res(1337_ms, ec::success, 6));
  CAF_CHECK_EQUAL(parse("1337us"), res(1337_us, ec::success, 6));
  CAF_CHECK_EQUAL(parse("1337ns"), res(1337_ns, ec::success, 6));
  CAF_CHECK_EQUAL(parse("-1min"), res(-1_min, ec::success, 5));
  CAF_CHECK_EQUAL(parse("-1s"), res(-1_s, ec::success, 3));
  CAF_CHECK_EQUAL(parse("-1ms"), res(-1_ms, ec::success, 4));
  CAF_CHECK_EQUAL(parse("-1us"), res(-1_us, ec::success, 4));
  CAF_CHECK_EQUAL(parse("-1ns"), res(-1_ns, ec::success, 4));
  /*
  CAF_CHECK_EQUAL(parse("42949672960min"), res(0, ec::duration_overflow, 14));
  CAF_CHECK_EQUAL(parse("42949672960s"), res(0, ec::duration_overflow, 12));
  CAF_CHECK_EQUAL(parse("42949672960ms"), res(0, ec::duration_overflow, 13));
  CAF_CHECK_EQUAL(parse("42949672960us"), res(0, ec::duration_overflow, 13));
  CAF_CHECK_EQUAL(parse("42949672960ns"), res(0, ec::duration_overflow, 13));
  */
}

CAF_TEST(doubles) {
  auto parse = make_parser(parse_double);
  CAF_CHECK_EQUAL(parse("0"), res(0.0, ec::success, 1));
  CAF_CHECK_EQUAL(parse("1.2"), res(1.2, ec::success, 3));
}

CAF_TEST(atoms) {
  auto parse = make_parser(parse_atom);
  CAF_CHECK_EQUAL(parse("''"), res(atom(""), ec::success, 2));
  CAF_CHECK_EQUAL(parse("'abc'"), res(atom("abc"), ec::success, 5));
  CAF_CHECK_EQUAL(parse("'0123456789'"), res(atom("0123456789"), ec::success, 12));
  CAF_CHECK_EQUAL(parse("'01234567891'"), res(0, ec::too_many_characters, 11));
  CAF_CHECK_EQUAL(parse("'012345678912'"), res(0, ec::too_many_characters, 11));
  CAF_CHECK_EQUAL(parse("'a#'"), res(0, ec::unexpected_character, 2));
  CAF_CHECK_EQUAL(parse("'A B'"), res(atom("A B"), ec::success, 5));
}

/*
struct unit_v {
  static constexpr unit_t value = unit;
};

struct parser_tag {};

template <class T>
struct is_parser : std::is_base_of<parser_tag, T> {};

template <class Impl, class Token = unit_v>
class single : public parser_tag {
public:
  using token = Token;

  using impl = Impl;

  using value_type = typename impl::value_type;

  constexpr single() {
    // nop
  }

  template <class Consumer, class Iterator, class Sentinel>
  std::pair<Iterator, ec> parse(Consumer& consumer, value_type& x,
                                Iterator first, Sentinel last) {
    auto res = impl::run(x, first, last);
    if (res.second == ec::none)
      consumer.value(Token::value, std::move(x));
    return res;
  }

  template <class Consumer, class Iterator>
  std::pair<Iterator, ec> parse(Consumer& consumer, Iterator first,
                                Iterator last) {
    value_type x;
    return parse(consumer, x, first, last);
  }

  template <class NewToken>
  constexpr single<Impl, NewToken> operator[](NewToken) const {
    return {};
  }
};

template <class Parser, class Token = unit_v>
class one_or_more : public parser_tag {
public:
  using token = Token;

  using value_token = typename Parser::token;

  using value_type = typename Parser::value_type;

  constexpr one_or_more() {
    // nop
  }

  constexpr one_or_more(Parser x) : p_(std::move(x)) {
    // nop
  }

  template <class Consumer, class Iterator, class Sentinel>
  std::pair<Iterator, ec> parse(Consumer& consumer, value_type& x,
                                Iterator first, Sentinel last) {
    if (first == last)
      return {first, ec::unexpected_eof};
    consumer.begin_sequence(token::value);
    auto res = p_.parse(consumer, x, first, last);
    if (res.second != ec::none) {
      return res;
    }
    decltype(res) last_res;
    // try again until p_ stops
    do {
      x = 0; // TODO: make generic
      last_res = res;
      res = p_.parse(consumer, x, res.first, last);
    } while (res.second != ec::none);
    consumer.end_sequence(token::value);
    return last_res;
  }

  template <class Consumer, class Iterator, class Sentinel>
  std::pair<Iterator, ec> parse(Consumer& consumer, Iterator first,
                                Sentinel last) {
    value_type x;
    return parse(consumer, x, first, last);
  }

  template <class NewToken>
  constexpr one_or_more<Parser, NewToken> operator[](NewToken) const {
    return {p_};
  }

private:
  Parser p_;
};

template <class Parser, class Token = unit_v>
class zero_or_more : public parser_tag {
public:
  using token = Token;

  constexpr zero_or_more() {
    // nop
  }

  constexpr zero_or_more(Parser p) : p_(std::move(p)) {
    // nop
  }

  using value_token = typename Parser::token;

  using value_type = typename Parser::value_type;

  template <class Consumer, class Iterator, class Sentinel>
  std::pair<Iterator, ec> parse(Consumer& consumer, value_type& x,
                                Iterator first, Sentinel last) {
    consumer.begin_sequence(token::value);
    auto res = std::make_pair(first, ec::none);
    decltype(res) last_res;
    do {
      x = 0; // TODO: make generic
      last_res = res;
      res = p_.parse(consumer, x, res.first, last);
    } while (res.second != ec::none);
    consumer.end_sequence(token::value);
    return last_res;
  }

  template <class Consumer, class Iterator, class Sentinel>
  std::pair<Iterator, ec> parse(Consumer& consumer, Iterator first,
                                Sentinel last) {
    value_type x;
    return parse(consumer, x, first, last);
  }

  template <class NewToken>
  constexpr zero_or_more<Parser, NewToken> operator[](NewToken) const {
    return {p_};
  }

private:
  Parser p_;
};

template <class Parser0, class Parser1, class Token = unit_v>
class sequence : public parser_tag {
public:
  using token = Token;

  constexpr sequence() {
    // nop
  }

  constexpr sequence(Parser0 p0, Parser1 p1)
      : p0_(std::move(p0)),
        p1_(std::move(p1)) {
    // nop
  }

  template <class Consumer, class Iterator, class Sentinel>
  std::pair<Iterator, ec> parse(Consumer& consumer, Iterator first,
                                Sentinel last) {
    auto r0 = p0_.parse(consumer, first, last);
    if (r0.second != ec::none)
      return r0;
    return p1_.parse(consumer, r0.first, last);
  }

private:
  Parser0 p0_;
  Parser1 p1_;
};

template <class Token = unit_v>
class literal : public parser_tag {
public:
  constexpr literal(const char* cstr) : cstr_(cstr) {
    // nop
  }

  constexpr literal(const literal& other) : cstr_(other.cstr_) {
    // nop
  }

  template <class Consumer, class Iterator, class Sentinel>
  std::pair<Iterator, ec> parse(Consumer& consumer, Iterator first,
                                Sentinel last) const {
    auto p = std::mismatch(first, last, cstr_);
    if (*p.second == '\0') {
      consumer.constant(Token::value, cstr_);
      return {p.first, ec::none};
    }
    return {p.first, ec::unexpected_character};
  }

private:
  const char* cstr_;
};

template <class Parser0, class Parser1,
          class E = detail::enable_if_t<is_parser<Parser0>::value
                                        && is_parser<Parser1>::value>>
constexpr sequence<Parser0, Parser1> operator>>(Parser0 x, Parser1 y) {
  return {std::move(x), std::move(y)};
}

template <class Parser, class E = detail::enable_if_tt<is_parser<Parser>>>
constexpr one_or_more<Parser> operator+(Parser x) {
  return {std::move(x)};
}

template <class Parser, class E = detail::enable_if_tt<is_parser<Parser>>>
constexpr zero_or_more<Parser> operator*(Parser x) {
  return {std::move(x)};
}

literal<> lit(const char* cstr) {
  return {cstr};
}

template <class Token>
literal<Token> lit(const char* cstr, Token) {
  return {cstr};
}

//static constexpr auto int64 = single<integer<int64_t>>{};

template <class Parser, class Consumer, class Iterator, class Sentinel>
bool parse(Parser p, Consumer& consumer, Iterator first, Sentinel last) {
  auto res = p.parse(consumer, first, last);
  return res.first == last && res.second == ec::none;
}

template <char...>
struct fast_lit_parser;

template <>
struct fast_lit_parser<> {
  static constexpr long scan(const char*) {
    return 0;
  }
};

template <char C0>
struct fast_lit_parser<C0> {
  static long scan(const char* ptr) {
    return *ptr - C0;
  }
};

template <char C0, char C1>
struct fast_lit_parser<C0, C1> {
  static constexpr int16_t val = C0 | (C1 << 1);
  static long scan(const int16_t* ptr) {
    return *ptr - val;
  }
  static long scan(const char* ptr) {
    return scan(reinterpret_cast<const int16_t*>(ptr));
  }
};

template <char C0, char C1, char C2>
struct fast_lit_parser<C0, C1, C2> {
  static constexpr int32_t val = C0 | (C1 << 1) | (C2 << 2);
  static long scan(const char* ptr) {
    return (ptr[0] | (ptr[1] << 1) | (ptr[2] << 2)) - val;
  }
};

template <char C0, char C1, char C2, char C3>
struct fast_lit_parser<C0, C1, C2, C3> {
  static constexpr int32_t val = C0 | (C1 << 1) | (C2 << 2) | (C3 << 3);
  static long scan(const int32_t* ptr) {
    return *ptr - val;
  }
  static long scan(const char* ptr) {
    return scan(reinterpret_cast<const int32_t*>(ptr));
  }
};

template <char C0, char C1, char C2, char C3, char C4>
struct fast_lit_parser<C0, C1, C2, C3, C4> {
  static constexpr long val = C0 | (C1 << 1) | (C2 << 2) | (C3 << 3) | (C4 << 4);
  static long scan(const char* ptr) {
    return (ptr[0] | (ptr[1] << 1) | (ptr[2] << 2) | (ptr[3] << 3) | (ptr[4] << 4)) - val;
  }
};

template <char C0, char C1, char C2, char C3, char C4, char C5>
struct fast_lit_parser<C0, C1, C2, C3, C4, C5> {
  static constexpr long val = C0 | (C1 << 1) | (C2 << 2) | (C3 << 3) | (C4 << 4) | (C5 << 5);
  static long scan(const char* ptr) {
    return (ptr[0] | (ptr[1] << 1) | (ptr[2] << 2) | (ptr[3] << 3) | (ptr[4] << 4) | (ptr[5] << 5)) - val;
  }
};

template <char C0, char C1, char C2, char C3, char C4, char C5, char C6>
struct fast_lit_parser<C0, C1, C2, C3, C4, C5, C6> {
  static constexpr long val = C0 | (C1 << 1) | (C2 << 2) | (C3 << 3) | (C4 << 4) | (C5 << 5) | (C6 << 6);
  static long scan(const char* ptr) {
    return (ptr[0] | (ptr[1] << 1) | (ptr[2] << 2) | (ptr[3] << 3) | (ptr[4] << 4) | (ptr[5] << 5) | (ptr[6] << 6)) - val;
  }
};

template <char C0, char C1, char C2, char C3, char C4, char C5, char C6, char C7, char... Cs>
struct fast_lit_parser<C0, C1, C2, C3, C4, C5, C6, C7, Cs...> {
  static constexpr long val = C0 | (C1 << 1) | (C2 << 2) | (C3 << 3)
                              | (C4 << 4) | (C5 << 5) | (C6 << 6) | (C7 << 7);
  static bool scan(const long* ptr) {
    return *ptr - val
           | fast_lit_parser<Cs...>::scan(
               reinterpret_cast<const char*>(ptr + 1));
  }
  static long scan(const char* ptr) {
    return scan(reinterpret_cast<const long*>(ptr));
  }
};

template <class T>
struct lit_parser {
  template <class Iterator, class Sentinel>
  static bool parse(Iterator i, Sentinel s) {
    return std::equal(i, s, T::get());
  }
};

#define CAF_STRING_CONSTANT(x) \
  ([] { struct tmp { static constexpr decltype(x) get() { return x; } }; return tmp{}; })()

template <class StringConstant>
lit_parser<StringConstant> make_lit_parser(StringConstant) {
  return {};
}

constexpr const char long_test_string[] = "this is a long string for testing";

void BM_strcmp(benchmark::State& state) {
  auto s1 = long_test_string;
  auto s2 = long_test_string;
  for (auto _ : state) {
    benchmark::DoNotOptimize(strcmp(s1, s2));
  }
}

void BM_lit_parser(benchmark::State& state) {
  auto p = make_lit_parser(CAF_STRING_CONSTANT("foo"));
  for (auto _ : state) {
    benchmark::DoNotOptimize(p.parse(std::begin(long_test_string), std::end(long_test_string)));
  }
}

BENCHMARK(BM_strcmp);
BENCHMARK(BM_lit_parser);

BENCHMARK_MAIN();

namespace {

constexpr const char single_long[] = "8943632";

using std::begin;
using std::end;

void BM_strtol(benchmark::State& state) {
  for (auto _ : state) {
    char* p;
    benchmark::DoNotOptimize(strtol(begin(single_long), &p, 10));
  }
}

void BM_caf_parse_single_long(benchmark::State& state) {
  auto f = [](const char* first, const char* last) {
    struct int_reader {
      long& n;
      inline void value(unit_t, long x) {
        n = x;
      }
    };
    long n;
    int_reader reader{n};
    single<integer<long>> p;
    p.parse(reader, first, last);
    return n;
  };
  for (auto _ : state)
    benchmark::DoNotOptimize(f(begin(single_long), end(single_long)));
}

void BM_spirit_parse_single_long(benchmark::State& state) {
  auto f = [](char const* first, char const* last) {
    namespace qi = boost::spirit::qi;
    long n;
    qi::parse(first, last, qi::long_, n);
    return n;
  };
  for (auto _ : state) {
    benchmark::DoNotOptimize(f(begin(single_long), end(single_long)));
  }
}
constexpr const char two_longs[] = "8943632 and -90823211";

template <class T>
struct wrap_v {
  static constexpr T value = T{};
};

void BM_caf_parse_two_longs(benchmark::State& state) {
  using i0 = std::integral_constant<long, 0>;
  using i1 = std::integral_constant<long, 1>;
  auto f = [](const char* first, const char* last) {
    struct reader {
      long& a;
      long& b;
      inline void value(std::integral_constant<long, 0>, long x) {
        a = x;
      }
      inline void constant(unit_t, const char*) {
        // nop
      }
      inline void value(std::integral_constant<long, 1>, long x) {
        b = x;
      }
    };
    long a;
    long b;
    reader reader{a, b};
    single<integer<long>> lval;
    auto p = lval[wrap_v<i0>{}] >> lit(" and ") >> lval[wrap_v<i1>{}];
    p.parse(reader, first, last);
    return a + b;
  };
  for (auto _ : state)
    benchmark::DoNotOptimize(f(begin(two_longs), end(two_longs)));
}

void BM_spirit_parse_two_longs(benchmark::State& state) {
  auto f = [](char const* first, char const* last) {
    namespace qi = boost::spirit::qi;
    long a;
    long b;
    auto set_a = [&](long x) { a = x; };
    auto set_b = [&](long x) { b = x; };
    qi::parse(first, last, qi::long_[set_a] >> " and " >> qi::long_[set_b]);
    return a + b;
  };
  for (auto _ : state)
    benchmark::DoNotOptimize(f(begin(two_longs), end(two_longs)));
}

} // namespace <anonymous>

BENCHMARK(BM_strtol);
BENCHMARK(BM_caf_parse_single_long);
BENCHMARK(BM_spirit_parse_single_long);
BENCHMARK(BM_caf_parse_two_longs);
BENCHMARK(BM_spirit_parse_two_longs);

BENCHMARK_MAIN();
*/
