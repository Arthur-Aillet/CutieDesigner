#pragma once

#include "Vec2Data.hpp"
#include <NodeEditor/NodeModel>

#include <memory>

class CombineVec2Node : public NodeEditor::NodeModel {
  public:
  CombineVec2Node(QQmlEngine *engine);
  ~CombineVec2Node() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return QStringLiteral("Combine Vec2"); }

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
  QVector2D _vec = QVector2D(0.0, 0.0);
  std::shared_ptr<Vec2Data> _vecData;
};
