#pragma once

#include "Vec2Data.hpp"
#include <NodeEditor/NodeModel>

class Vec2InputNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(double x READ x WRITE setX NOTIFY xChanged)
  Q_PROPERTY(double y READ y WRITE setY NOTIFY yChanged)

  Vec2InputNode(QQmlEngine *engine);
  ~Vec2InputNode() override = default;

  bool captionVisible() const override { return false; }
  QString name() const override { return "Vec2"; }

  QJsonObject save() const override;
  void load(QJsonObject const &p) override;

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override {
    return QString();
  }
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  void setInData(std::shared_ptr<NodeEditor::NodeData>, NodeEditor::PortIndex) override {}

  QQmlComponent embeddedComponent(QQmlEngine *engine) override;
  QVariantMap componentInitialProperties() override;

  double x() { return _x; }
  double y() { return _y; }

  void setX(double x);
  void setY(double y);

  signals:
  void xChanged();
  void yChanged();

  private:
  double _x = 0.0;
  double _y = 0.0;
  QVector2D _vec = {0.0, 0.0};
  std::shared_ptr<Vec2Data> _vecData;
};
