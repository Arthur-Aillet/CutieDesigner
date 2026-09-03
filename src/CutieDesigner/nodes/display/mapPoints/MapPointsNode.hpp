#pragma once

#include "SurfaceData.hpp"
#include "qvectornd.h"
#include <NodeEditor/NodeModel>

#include <QGradient>
#include <QVector2D>
#include <QVector>

class MapPointsNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(QList<QVector2D> points READ points NOTIFY pointsChanged)

  MapPointsNode(QQmlEngine *engine);
  ~MapPointsNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "Map points"; }

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override;
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;

  QList<QVector2D> points();

  signals:
  void pointsChanged();

  private:
  QGradient _defaultGradient;
  std::weak_ptr<NodeEditor::NodeData> _points;
  std::shared_ptr<SurfaceData> _content;
};
