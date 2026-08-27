#pragma once

#include <NodeEditor/NodeData>

#include <QtGui/QColor>
#include <qbrush.h>

struct ColorDataType : public NodeEditor::NodeDataType {
  ColorDataType() : NodeEditor::NodeDataType("col", "Color", {"col", "gradient-01"}) {}
};

class ColorData : public NodeEditor::NodeData {

  public:
  ColorData() {}
  ColorData(const QColor &color) {
    registerConvert([&color]() { return color; });
    registerConvert([&color]() {
      QGradient g;
      g.setColorAt(0, color);
      return g;
    });
  }

  NodeEditor::NodeDataType type() const override { return ColorDataType(); }
};
