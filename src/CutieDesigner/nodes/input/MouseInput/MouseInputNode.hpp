#pragma once

#include "CutieWindow.hpp"
#include "Vec2Data.hpp"

#include <NodeEditor/NodeModel>

class MouseInputNode : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  MouseInputNode(QQmlEngine *engine);
  ~MouseInputNode() override {
    if (_window != nullptr) {
      _window->stopRequestRefresh(this);
    }
  };

  bool captionVisible() const override { return true; }
  QString name() const override { return "Mouse"; }

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
  void mouseMoveEvent(QMouseEvent *event);

  private:
  QVector2D _pos = {0.0, 0.0};
  CutieWindow *_window = nullptr;
  std::shared_ptr<Vec2Data> _posData;
};
