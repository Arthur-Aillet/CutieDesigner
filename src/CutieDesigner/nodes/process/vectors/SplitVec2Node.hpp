#pragma once

#include "DecimalData.hpp"

#include <NodeEditor/NodeModel>

#include <memory>

class SplitVec2Node : public NodeEditor::NodeModel {
  public:
  SplitVec2Node(QQmlEngine *engine);
  ~SplitVec2Node() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return QStringLiteral("Split Vec2"); }

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

  private:
  double _x = 0.0;
  double _y = 0.0;
  std::shared_ptr<DecimalData> _xData;
  std::shared_ptr<DecimalData> _yData;
};
