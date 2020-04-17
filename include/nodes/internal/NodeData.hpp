#pragma once

#include <QtCore/QString>

#include "Export.hpp"

struct ConstLatin1String : public QLatin1String
{
  constexpr explicit ConstLatin1String(const char* const s) :
      QLatin1String(s, static_cast<int>(std::char_traits<char>::length(s))) {}
};

namespace QtNodes
{

struct NodeDataType
{
  QLatin1String id;
  QLatin1String name;
};

inline bool operator==(const NodeDataType& lhs, const NodeDataType& rhs)
{
  return lhs.id == rhs.id && lhs.name == rhs.name;
}

/// Class represents data transferred between nodes.
/// @param type is used for comparing the types
/// The actual data is stored in subtypes
class NODE_EDITOR_PUBLIC NodeData
{
public:

  virtual ~NodeData() = default;

  virtual bool sameType(NodeData const &nodeData) const
  {
    return (this->type().id == nodeData.type().id);
  }

  /// Type for inner use
  static constexpr NodeDataType Type = NodeDataType{};
  virtual NodeDataType type() const = 0;
};

template <class T> inline T nodedata_cast(NodeData *item)
{
  using Item = typename std::remove_cv<typename std::remove_pointer<T>::type>::type;
  return Item::Type == NodeData::Type
         || (item && Item::Type == item->type()) ? static_cast<T>(item) : 0;
}

template <class T> inline T nodedata_cast(const NodeData *item)
{
  using Item = typename std::remove_cv<typename std::remove_pointer<T>::type>::type;
  return Item::Type == NodeData::Type
         || (item && Item::Type == item->type()) ? static_cast<T>(item) : 0;
}
}
