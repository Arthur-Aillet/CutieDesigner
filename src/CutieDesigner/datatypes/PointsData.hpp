#pragma once

#include <NodeEditor/NodeData>
#include <QVector2D>
#include <vector>

class PointsData : public NodeEditor::NodeData {
  public:
  PointsData() {}
  PointsData(const QList<QVector2D> &points) {
    registerConvert([&points]() { return points; });
  }

  NodeEditor::NodeDataType type() const override {
    return NodeEditor::NodeDataType("points-0", "Points");
  }
};
