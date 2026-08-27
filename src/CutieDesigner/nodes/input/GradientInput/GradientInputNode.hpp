#pragma once

#include "GradientData.hpp"
#include "GradientInputList.hpp"

#include <NodeEditor/NodeModel>

class GradientInputNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  Q_PROPERTY(GradientInputList *colorList READ colorList CONSTANT)

  public:
  GradientInputNode(QQmlEngine *engine);
  ~GradientInputNode() = default;

  public:
  bool captionVisible() const override { return false; }
  QString name() const override { return "Gradient"; }

  QJsonObject save() const override;
  void load(QJsonObject const &p) override;

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override {
    return QString();
  };
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  QQmlComponent embeddedComponent(QQmlEngine *engine) override {
    return QQmlComponent(engine, "CutieDesigner.Nodes.Input", "GradientInputControl");
  }

  QVariantMap componentInitialProperties() override {
    return QVariantMap{{"node", QVariant::fromValue(this)}};
  }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override {};

  GradientInputList *colorList() { return _list.get(); }

  private:
  std::shared_ptr<GradientInputList> _list;
  std::shared_ptr<GradientData> _content;
};
