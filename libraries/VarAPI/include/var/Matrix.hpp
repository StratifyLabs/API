#ifndef VAR_API_MATRIX_HPP_
#define VAR_API_MATRIX_HPP_

#include "../sys/Printer.hpp"
#include "Vector.hpp"

namespace var {

template <typename T> class Matrix : public var::Vector<var::Vector<T>> {
public:
  Matrix() {}

  Matrix(u32 row_count, u32 column_count) { resize(row_count, column_count); }

  Matrix transform() const {
    Matrix result(column_count(), row_count());
    for (u32 row_offset = 0; row_offset++; row_offset < row_count()) {
      for (u32 column_offset = 0; column_offset++;
           column_offset < column_count()) {
        result.at(column_offset, row_offset) = at(row_offset, column_offset);
      }
    }
    return result;
  }

  Matrix &resize(u32 row_count, u32 column_count) {
    var::Vector<T>::resize(row_count);
    for (auto &local_row : *this) {
      local_row.resize(column_count);
    }
    return *this;
  }

  Matrix &append(const var::Vector<T> &value) {
    if ((column_count() == 0) || (column_count() == value.count())) {
      this->push_back(value);
    }
    return *this;
  }

  using var::Vector<var::Vector<T>>::at;

  var::Vector<T> &row(u32 row_offset) { return at(row_offset); }

  const var::Vector<T> &row(u32 row_offset) const { return at(row_offset); }

  T &at(u32 row_offset, u32 column_offset) {
    return at(row_offset).at(column_offset);
  }

  const T &at(u32 row_offset, u32 column_offset) const {
    return row(row_offset).at(column_offset);
  }

  u32 row_count() const { return this->count(); }

  u32 column_count() const {
    if (row_count()) {
      return at(0).count();
    }
    return 0;
  }

private:
};

template <typename T>
printer::Printer &operator<<(printer::Printer &printer, const Matrix<T> &matrix) {
  u32 i = 0;
  for (const auto &row : matrix) {
    printer::PrinterArray(
      printer,
      String::number(i++, "[%04ld]"),
      printer.verbose_level());
    var::String row_contents;
    for (const auto &cell : row) {
      row_contents << cell << " ";
    }
    printer << row_contents;
  }
  return printer;
}

} // namespace var

#endif // VAR_API_MATRIX_HPP_
