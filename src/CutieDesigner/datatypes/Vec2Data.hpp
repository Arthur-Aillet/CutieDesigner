#pragma once

#include <NodeEditor/NodeData>

struct Vec2DataType : public NodeEditor::NodeDataType {
  Vec2DataType();
};

class Vec2Data : public NodeEditor::NodeData {
  public:
  Vec2Data() {}
  Vec2Data(const QVector2D &v);

  NodeEditor::NodeDataType type() const override { return Vec2DataType(); }
};
