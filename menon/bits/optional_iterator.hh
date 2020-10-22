/// @file   menon/bits/optional_iterator.hh
/// optional_iteratorクラスの定義
/// @author @menonfled
#ifndef MENON_BITS_OPTIONAL_ITERATOR_HH_
#define MENON_BITS_OPTIONAL_ITERATOR_HH_
#pragma once

#include "menon/bits/config.hh"
#include <concepts>
#include <iterator>
#include <optional>
#include <utility>

namespace menon
{
  /// @class  optional_iterator optional_iterator.hh "menon/iterator.hh"
  /// 無効状態を表現可能なイテレータのラッパークラス
  template <std::input_or_output_iterator Iterator>
  class optional_iterator : std::optional<Iterator>
  {
      using iterator_traits = std::iterator_traits<Iterator>;
    public:
      // iterator_traitsのための型定義
      using difference_type   = typename iterator_traits::difference_type;
      using value_type        = typename iterator_traits::value_type;
      using pointer           = typename iterator_traits::pointer;
      using reference         = typename iterator_traits::reference;
      using iterator_category = typename iterator_traits::iterator_category;

      // コンストラクタとデストラクタ
      constexpr optional_iterator() = default;
      constexpr optional_iterator(optional_iterator const&) = default;
      constexpr optional_iterator(optional_iterator&&) = default;
      constexpr optional_iterator(std::nullopt_t nullopt)
        : std::optional<Iterator>(nullopt)
      {
      }
      constexpr optional_iterator(Iterator&& iterator)
        : std::optional<Iterator>(std::forward<Iterator>(iterator))
      {
      }
      template <std::input_or_output_iterator OtherIterator>
        constexpr optional_iterator(OtherIterator&& iterator)
          : std::optional<Iterator>(std::forward<OtherIterator>(iterator))
      {
      }
      template <std::input_or_output_iterator OtherIterator>
        constexpr optional_iterator(optional_iterator<OtherIterator> const& other)
          : std::optional<Iterator>(other)
      {
      }
      ~optional_iterator() noexcept = default;

      // 代入演算子
      optional_iterator& operator=(optional_iterator const&) = default;
      optional_iterator& operator=(optional_iterator&&) = default;
      optional_iterator& operator=(std::nullopt_t nullopt)
      {
        std::optional<Iterator>::operator=(nullopt);
        return *this;
      }
      optional_iterator& operator=(Iterator&& iterator)
      {
        std::optional<Iterator>::operator=(std::forward<Iterator>(iterator));
        return *this;
      }
      template <std::input_or_output_iterator OtherIterator>
        optional_iterator& operator=(OtherIterator&& iterator)
      {
        std::optional<Iterator>::operator=(std::forward<OtherIterator>(iterator));
        return *this;
      }
      template <std::input_or_output_iterator OtherIterator>
        optional_iterator& operator=(optional_iterator<OtherIterator> const& other)
      {
        std::optional<Iterator>::operator=(other);
        return *this;
      }

      // !演算子
      constexpr bool operator!() const
      {
        return !static_cast<bool>(*this);
      }

      // 等価演算子
      constexpr bool operator==(optional_iterator<Iterator> const& other) const
      {
        if (has_value() && other.has_value())
          return value() == other.value();
        return false;
      }
      constexpr bool operator!=(optional_iterator<Iterator> const& other) const
      {
        if (has_value() && other.has_value())
          return value() != other.value();
        return false;
      }

      // 宇宙船演算子
      constexpr auto operator<=>(optional_iterator<Iterator> const& other) const
      {
        return value() <=> other.value();
      }

      // 増分演算子
      optional_iterator<Iterator>& operator++()
      {
        ++value();
        return *this;
      }
      optional_iterator<Iterator> operator++(int)
      {
        return value()++;
      }

      // 間接演算子
      auto operator*() const
      {
        return *value();
      }

      // 矢印演算子
      auto operator->() const
      {
        return value().operator->();
      }

      // 添字演算子
      auto operator[](std::size_t n)
      {
        return value()[n];
      }

      // std::optional<Iterator>への変換関数
      constexpr operator std::optional<Iterator>() const
      {
        return *this;
      }

      /// イテレータの交換
      /// @param[in,out]  other    交換する相手
      /// @return         無し
      void swap(optional_iterator<Iterator>& other) noexcept
      {
        std::optional<Iterator>::swap(other);
      }

      // std::optional<Iterator>からの継承
      using std::optional<Iterator>::emplace;
      using std::optional<Iterator>::has_value;
      using std::optional<Iterator>::value;
      using std::optional<Iterator>::value_or;
      using std::optional<Iterator>::reset;
      using std::optional<Iterator>::operator bool;
  };

  // 等価演算子
  template <std::input_or_output_iterator Iterator>
  inline auto operator==(optional_iterator<Iterator> const& lhs, Iterator rhs)
  {
    return lhs.value() == rhs;
  }
  template <std::input_or_output_iterator Iterator>
  inline auto operator==(Iterator lhs, optional_iterator<Iterator> const& rhs)
  {
    return lhs == rhs.value();
  }
  template <std::input_or_output_iterator Iterator>
  inline auto operator!=(optional_iterator<Iterator> const& lhs, Iterator rhs)
  {
    return lhs.value() != rhs;
  }
  template <std::input_or_output_iterator Iterator>
  inline auto operator!=(Iterator lhs, optional_iterator<Iterator> const& rhs)
  {
    return lhs != rhs.value();
  }

  template <std::input_or_output_iterator Iterator>
  inline auto operator==(optional_iterator<Iterator> const& lhs, std::nullopt_t)
  {
    return !lhs.has_value();
  }
  template <std::input_or_output_iterator Iterator>
  inline auto operator==(std::nullopt_t, optional_iterator<Iterator> const& rhs)
  {
    return !rhs.has_value();
  }
  template <std::input_or_output_iterator Iterator>
  inline auto operator!=(optional_iterator<Iterator> const& lhs, std::nullopt_t)
  {
    return lhs.has_value();
  }
  template <std::input_or_output_iterator Iterator>
  inline auto operator!=(std::nullopt_t, optional_iterator<Iterator> const& rhs)
  {
    return rhs.has_value();
  }

  // 関係演算子
  template <std::random_access_iterator Iterator>
  inline auto operator<(optional_iterator<Iterator> const& lhs, Iterator rhs)
  {
    return lhs.value() < rhs;
  }
  template <std::random_access_iterator Iterator>
  inline auto operator<(Iterator lhs, optional_iterator<Iterator> const& rhs)
  {
    return lhs < rhs.value();
  }
  template <std::random_access_iterator Iterator>
  inline auto operator>(optional_iterator<Iterator> const& lhs, Iterator rhs)
  {
    return rhs < lhs;
  }
  template <std::random_access_iterator Iterator>
  inline auto operator>(Iterator lhs, optional_iterator<Iterator> const& rhs)
  {
    return rhs < lhs;
  }
  template <std::random_access_iterator Iterator>
  inline auto operator<=(optional_iterator<Iterator> const& lhs, Iterator rhs)
  {
    return !(lhs > rhs);
  }
  template <std::random_access_iterator Iterator>
  inline auto operator<=(Iterator lhs, optional_iterator<Iterator> const& rhs)
  {
    return !(lhs > rhs);
  }
  template <std::random_access_iterator Iterator>
  inline auto operator>=(optional_iterator<Iterator> const& lhs, Iterator rhs)
  {
    return !(lhs < rhs);
  }
  template <std::random_access_iterator Iterator>
  inline auto operator>=(Iterator lhs, optional_iterator<Iterator> const& rhs)
  {
    return !(lhs < rhs);
  }

  // 減分演算子
  template <std::bidirectional_iterator Iterator>
  inline optional_iterator<Iterator>& operator--(optional_iterator<Iterator>& oi)
  {
    --oi.value();
    return oi;
  }
  template <std::bidirectional_iterator Iterator>
  inline optional_iterator<Iterator> operator--(optional_iterator<Iterator>& oi, int)
  {
    return oi.value()--;
  }

  template <std::random_access_iterator Iterator, std::integral Size>
  inline optional_iterator<Iterator> operator+(optional_iterator<Iterator> const& oi, Size n)
  {
    return oi.value() + n;
  }
  template <std::random_access_iterator Iterator, std::integral Size>
  inline optional_iterator<Iterator> operator+(Size n, optional_iterator<Iterator> const& oi)
  {
    return n + oi.value();
  }
  template <std::random_access_iterator Iterator>
  inline auto operator-(optional_iterator<Iterator> const& lhs, optional_iterator<Iterator> const& rhs)
  {
    return lhs.value() - rhs.value();
  }
}

#endif  // !MENON_BITS_OPTIONAL_ITERATOR_HH_
