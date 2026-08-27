#pragma once

#include "DecimalData.hpp"

#include <NodeEditor/NodeModel>

#include <memory>

class TimeInputNode : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  TimeInputNode(QQmlEngine *engine);
  ~TimeInputNode() override = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return "Time"; }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;

  QString portCaption(NodeEditor::PortSide _portSide,
                      NodeEditor::PortIndex portIndex) const override;
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  void setInData(std::shared_ptr<NodeEditor::NodeData>, NodeEditor::PortIndex) override {}

  protected:
  std::array<double, 5> _outContent;
  std::array<std::shared_ptr<DecimalData>, 5> _outData;
};
