#pragma once

#include "ColorData.hpp"
#include "ColorModes.hpp"

#include <NodeEditor/NodeModel>

#include <array>

using namespace CutieDesigner;

class CombineColorNode : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  CombineColorNode(QQmlEngine *engine);
  ~CombineColorNode() = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return "Combine Color"; }

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
  std::array<std::weak_ptr<NodeEditor::NodeData>, 5> _input;
  std::weak_ptr<QQuickItem> _embedded;
  QColor _color = "black";
  ColorMode _mode = ColorMode::RGBA;
  std::shared_ptr<ColorData> _outColorPtr;
};
