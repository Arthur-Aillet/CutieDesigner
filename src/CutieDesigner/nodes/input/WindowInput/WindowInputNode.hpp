#pragma once

#include "CutieWindow.hpp"
#include "Vec2Data.hpp"
#include <NodeEditor/NodeModel>

class WindowInputNode : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  WindowInputNode(QQmlEngine *engine);
  ~WindowInputNode() override = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return "Window"; }

  bool labelVisible() const override { return true; }
  QString label() const override { return "Cutie window dimensions"; }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override;
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  void setInData(std::shared_ptr<NodeEditor::NodeData>, NodeEditor::PortIndex) override {}

  public slots:
  void resizeEvent(QResizeEvent *event);

  private:
  QVector2D _size;
  CutieWindow *_window = nullptr;
  std::shared_ptr<Vec2Data> _sizeData;
};
