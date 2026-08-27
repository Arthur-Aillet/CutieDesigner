#pragma once

#include <NodeEditor/NodeData>

struct DecimalDataType : public NodeEditor::NodeDataType {
  DecimalDataType();
};

class DecimalData : public NodeEditor::NodeData {
  public:
  DecimalData() {}
  DecimalData(const double &v);

  NodeEditor::NodeDataType type() const override { return DecimalDataType(); }
};
