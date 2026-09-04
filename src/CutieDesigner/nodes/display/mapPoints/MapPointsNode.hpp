#pragma once

#include "PointsData.hpp"
#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

#include <QGradient>
#include <QVector2D>
#include <QVector>

class MapPointsNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(SurfaceData *surface READ getSurface NOTIFY surfaceChanged)
  Q_PROPERTY(QList<Keypoint> points READ points NOTIFY pointsChanged)

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

  PointsData::PointCollection points();
  SurfaceData *getSurface() { return _surface.lock().get(); }

  signals:
  void pointsChanged();
  void surfaceChanged();

  private:
  QGradient _defaultGradient;
  std::weak_ptr<NodeEditor::NodeData> _points;
  std::weak_ptr<SurfaceData> _surface;
  std::shared_ptr<SurfaceData> _content;
};
