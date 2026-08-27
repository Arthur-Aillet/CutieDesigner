#pragma once

#include "DecimalData.hpp"

#include <NodeEditor/NodeModel>

class SliderInputNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
  Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
  Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)

  SliderInputNode(QQmlEngine *engine);
  ~SliderInputNode() override = default;

  bool captionVisible() const override { return false; }
  QString name() const override { return "Slider"; }

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

  double value() { return _value; }
  double min() { return _min; }
  double max() { return _max; }

  void setValue(double value);
  void setMin(double min);
  void setMax(double max);

  signals:
  void valueChanged();
  void minChanged();
  void maxChanged();

  private:
  double _value = 0.0;
  double _min = 0.0;
  double _max = 1.0;
  std::shared_ptr<DecimalData> _valueData;
};
