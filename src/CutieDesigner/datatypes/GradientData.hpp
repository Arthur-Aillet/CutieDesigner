#pragma once

#include <NodeEditor/NodeData>
#include <QtGui/QColor>
#include <qbrush.h>

class GradientData : public NodeEditor::NodeData {
  public:
  GradientData() {}
  GradientData(const QGradient &gradientProp) {
    registerConvert([&gradientProp]() { return gradientProp; });
  }

  NodeEditor::NodeDataType type() const override {
    return NodeEditor::NodeDataType("gradient-01", "Gradient");
  }
};
