#pragma once

#include "ColorModes.hpp"
#include "DecimalData.hpp"

#include <NodeEditor/NodeModel>

using namespace CutieDesigner;

class SplitColorNode : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  SplitColorNode(QQmlEngine *engine);
  ~SplitColorNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "Split Color"; }

  QJsonObject save() const override;
  void load(QJsonObject const &) override;

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override;
  bool portCaptionVisible(NodeEditor::PortSide, NodeEditor::PortIndex) const override {
    return true;
  }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;

  QQmlComponent embeddedComponent(QQmlEngine *engine) override;

  public slots:
  void currentModeChanged();
  void embeddedComponentLoaded(std::shared_ptr<QQuickItem> instance) override;

  private:
  std::weak_ptr<NodeEditor::NodeData> _color;
  std::weak_ptr<QQuickItem> _embedded;
  ColorMode _mode = ColorMode::RGBA;
  std::array<double, 5> _outValues;
  std::array<std::shared_ptr<DecimalData>, 5> _outData;
};
