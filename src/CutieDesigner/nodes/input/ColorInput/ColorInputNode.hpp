#pragma once

#include "ColorData.hpp"
#include <NodeEditor/NodeModel>

class ColorInputNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

  public:
  ColorInputNode(QQmlEngine *engine);
  ~ColorInputNode() = default;

  public:
  bool captionVisible() const override { return false; }
  QString name() const override { return "Color"; }

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override {
    return QString();
  };
  bool portCaptionVisible(NodeEditor::PortSide, NodeEditor::PortIndex) const override {
    return true;
  }

  QQmlComponent embeddedComponent(QQmlEngine *engine) override;
  QVariantMap componentInitialProperties() override;

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;

  QJsonObject save() const override;
  void load(QJsonObject const &) override;

  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override {};

  QColor color() { return _color; }

  void setColor(QColor color) {
    _color = color;
    emit colorChanged();
    emit dataUpdated(0);
  }

  signals:
  void colorChanged();

  private:
  QColor _color = "red";
  std::shared_ptr<ColorData> _content;
};
