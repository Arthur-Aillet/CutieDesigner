#pragma once

#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

#include <QQmlComponent>
#include <QVector2D>
#include <QtCore/QObject>

class DimensionNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(SurfaceData *surface READ getSurface NOTIFY surfaceChanged)
  Q_PROPERTY(QVector2D inPos READ inPos NOTIFY inPosChanged)
  Q_PROPERTY(QVector2D inSize READ inSize NOTIFY inSizeChanged)
  Q_PROPERTY(double rotation READ rotation NOTIFY rotationChanged)

  DimensionNode(QQmlEngine *engine);
  ~DimensionNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "Dimension"; }

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

  SurfaceData *getSurface() { return _surface.lock().get(); }
  QVector2D inPos() {
    if (_inPos.expired())
      return QVector2D(0, 0);
    return _inPos.lock()->repr<QVector2D>();
  }
  QVector2D inSize() {
    if (_inSize.expired())
      return QVector2D(200, 200);
    return _inSize.lock()->repr<QVector2D>();
  }
  double rotation() {
    if (_rotation.expired())
      return 0;
    return _rotation.lock()->repr<double>();
  }

  signals:
  void surfaceChanged();
  void inPosChanged();
  void inSizeChanged();
  void rotationChanged();

  private:
  std::weak_ptr<SurfaceData> _surface;
  std::weak_ptr<NodeEditor::NodeData> _inPos;
  std::weak_ptr<NodeEditor::NodeData> _inSize;
  std::weak_ptr<NodeEditor::NodeData> _rotation;
  std::shared_ptr<SurfaceData> _content;
};
