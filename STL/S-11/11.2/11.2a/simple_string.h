#ifndef _SIMPLE_STRING_H
#define _SIMPLE_STRING_H

#include <iterator>

/**
 * Forward declarations
 */
class simple_string_iterator;
class simple_string_const_iterator;

/**
 * This simple string class shows the difference between pass-by-value
 * using copy vs. move semantics in C++.  It also shows the "Rule of
 * 5", which supplants the "Rule of 3" with earlier C++ versions
 * https://en.wikipedia.org/wiki/Rule_of_three_(C++_programming).
 */
class simple_string {
public:
  typedef char value_type;
  typedef simple_string_iterator iterator;
  typedef simple_string_const_iterator const_iterator;

  simple_string();

  explicit simple_string(const char *s);

  simple_string(const simple_string &rhs) noexcept;

  simple_string(simple_string &&rhs) noexcept;

  simple_string &operator=(const simple_string &rhs) noexcept;

  simple_string &operator=(simple_string &&rhs) noexcept;

  ~simple_string();

  void swap(simple_string &rhs) noexcept;

  char &operator[](size_t index);

  const char &operator[](size_t index) const;

  bool operator<(const simple_string &rhs) const;

  size_t length() const;

  explicit operator const char *() const;

  // Get an iterator that points to the beginning of the Array.
  iterator begin ();

  // Get a const interator that points to the beginning of the Array.
  const_iterator cbegin () const;

  // Get a const interator that points to the beginning of the Array.
  const_iterator begin () const;

  // Get an iterator that points to the end
  iterator end ();

  // Get a const iterator that points to the end of the list.
  const_iterator end () const;

  // Get a const iterator that points to the end of the list.
  const_iterator cend () const;

private:
  size_t len_;

  char *str_;

  char *strnew(const char *s);
};

std::ostream &
operator<<(std::ostream &os, const simple_string &string);

class simple_string_iterator :
  public std::iterator <std::bidirectional_iterator_tag, simple_string> {
  friend class simple_string;

public:
  /**
   * Dereference operator returns a reference to the item contained at
   * the current position. */
  char& operator* ();

  /**
   * Returns a const reference to the item contained at the current
   * position
   */
  const char& operator* () const;

  /**
   * Preincrement operator
   */
  simple_string_iterator &operator++ ();

  /**
   * Postincrement operator
   */
  const simple_string_iterator operator++ (int);

  /**
   * Predecrement operator
   */
  simple_string_iterator &operator-- ();

  /**
   * Posdecrement operator
   */
  const simple_string_iterator operator-- (int);

  /**
   * Equality operator
   */
  bool operator== (const simple_string_iterator &rhs) const;

  /**
   * Nonequality operator
   */
  bool operator!= (const simple_string_iterator &lhs) const;

private:
  /**
   * Construct an simple_string_iterator at position pos.
   */
  simple_string_iterator (simple_string &simple_string, size_t pos = 0);

  /**
   * the simple_string we are dealing with
   */
  simple_string &simple_string_;

  /**
   * Our current position
   */
  mutable size_t pos_;
};

/**
 * A const_iterator does not guarantee that the current *position*
 * that it points to will not change, it only guarantees that you
 * cannot change the underlying simple_string!
 */
class simple_string_const_iterator :
  public std::iterator <std::bidirectional_iterator_tag, simple_string> {
  friend class simple_string;

public:
  /**
   * Returns a const reference to the item contained at the current
   * position.
   */
  const char& operator* () const;

  /**
   * Preincrement operator
   */
  const simple_string_const_iterator & operator++ () const;

  /**
   * Postincrement operator
   */
  const simple_string_const_iterator operator++ (int) const;

  /**
   * Predecrement operator
   */
  const simple_string_const_iterator &operator-- () const;

  /**
   * Postdecrement operator
   */
  const simple_string_const_iterator operator-- (int) const;

  /**
   * Equality operator
   */
  bool operator== (const simple_string_const_iterator &rhs) const;

  /**
   * Nonequality operator
   */
  bool operator!= (const simple_string_const_iterator &lhs) const;

private:
  /**
   * Construct an iterator at position pos.
   */
  simple_string_const_iterator (const simple_string &simple_string, size_t pos = 0);

  /**
   * the simple_string we are dealing with
   */
  const simple_string &simple_string_;

  /**
   * Our current position
   */
  mutable size_t pos_;
};

#endif /* _SIMPLE_STRING_H */
