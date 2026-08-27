#pragma once

#include "TextData.hpp"
#include <NodeEditor/NodeModel>

class TextInputNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

  TextInputNode(QQmlEngine *engine);
  ~TextInputNode() override = default;

  bool captionVisible() const override { return false; }
  QString name() const override { return "Text"; }

  QJsonObject save() const override;
  void load(QJsonObject const &p) override;

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override {
    return "";
  }
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  void setInData(std::shared_ptr<NodeEditor::NodeData>, NodeEditor::PortIndex) override {}

  QQmlComponent embeddedComponent(QQmlEngine *engine) override;
  QVariantMap componentInitialProperties() override;
  QString text();
  void setText(QString text);

  signals:
  void textChanged();

  private:
  QString _text = "";
  std::shared_ptr<TextData> _textData;
};
