#pragma once

#include "DecimalData.hpp"

#include <NodeEditor/NodeModel>

class NumberInputNode : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  NumberInputNode(QQmlEngine *engine);
  ~NumberInputNode() override = default;

  bool captionVisible() const override { return false; }
  QString name() const override { return "Number"; }

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
  void embeddedComponentLoaded(std::shared_ptr<QQuickItem> loaded) override;

  public slots:
  void onTextEdited();

  private:
  double _number = 0.0;
  std::shared_ptr<QQuickItem> _portLabel{nullptr};
  std::shared_ptr<DecimalData> _numberData;
};
