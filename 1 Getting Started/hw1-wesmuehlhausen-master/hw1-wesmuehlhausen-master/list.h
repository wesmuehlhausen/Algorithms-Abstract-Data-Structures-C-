// ----------------------------------------------------------------------
// FILE: list.h
// NAME: S. Bowers
// DATE: August, 2020
// DESC: Basic list interface for adding elements (at the end of the
//       list or by index), getting an element stored in the list (by
//       index), setting an element already stored in the list,
//       removing an element from the list, and obtaining the size of
//       (number of elements stored in) the list.
// ----------------------------------------------------------------------

#ifndef LIST_H
#define LIST_H

template <typename T>
class List
{
public:
  /* adds the given item to th end of the list */
  virtual void add(const T& item) = 0;

  /* adds item to the list at given index (0 <= index <= size) */
  /* returns true if index is valid, and false otherwise */
  /* if index is 0 to size-1, all items shifted over one index */
  /* if index is the list size, item added to the end of the list */
  virtual bool add(size_t index, const T& item) = 0;

  /* sets return_item to item at given index */
  /* returns true if index is valid, and false otherwise */
  virtual bool get(size_t index, T& return_item) const = 0;

  /* replaces item at given index to new_item */
  /* returns true if index is valid, and false otherwise */
  virtual bool set(size_t index, const T& new_item) = 0;

  /* removes item at given index, reducing the list size by one */
  /* returns true if index is valid, and false otherwise */
  virtual bool remove(size_t index) = 0;

  /* returns the number of items in the list */
  virtual size_t size() const = 0;

};

#endif
