#pragma once

#include "ui/ObjectType.hpp"
#include <optional>

class BaseSceneStreamReader
{
  public:
	virtual ~BaseSceneStreamReader() = 0;

    virtual std::optional<ObjectType> getType() = 0;
};

inline BaseSceneStreamReader::~BaseSceneStreamReader() = default;
