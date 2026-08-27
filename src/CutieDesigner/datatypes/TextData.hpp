#pragma once

#include <NodeEditor/NodeData>

class TextData : public NodeEditor::NodeData {
  public:
  TextData() {}
  TextData(const QString &text) {
    registerConvert([&text]() { return text; });
  }

  NodeEditor::NodeDataType type() const override {
    return NodeEditor::NodeDataType("text", "Text");
  }
};
