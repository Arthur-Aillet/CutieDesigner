#pragma once

#include <NodeEditor/NodeData>
#include <QVector2D>

struct Keypoint {
  Q_GADGET
  QML_VALUE_TYPE(keypoint)
  QML_STRUCTURED_VALUE

  public:
  Q_PROPERTY(QVector2D position MEMBER position)
  Q_PROPERTY(float confidence MEMBER confidence)
  Q_PROPERTY(int idx MEMBER idx)
  QVector2D position;
  float confidence;
  int idx;
};

// Coco skeleton
class PointsData : public NodeEditor::NodeData {
  public:
  using PointCollection = QList<Keypoint>;

  PointsData() {}
  PointsData(const PointCollection &points) {
    registerConvert([&points]() { return points; });
  }

  NodeEditor::NodeDataType type() const override {
    return NodeEditor::NodeDataType("points-0", "Points");
  }
};
