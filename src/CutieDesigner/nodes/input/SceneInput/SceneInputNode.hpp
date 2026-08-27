#pragma once

#include "Vec2Data.hpp"

#include <NodeEditor/NodeModel>

class SceneInputNode : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  SceneInputNode(QQmlEngine *engine);
  ~SceneInputNode() override = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return "Scene"; }

  bool labelVisible() const override { return true; }
  QString label() const override { return "Scene dimensions"; }

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
  void posChanged();
  void sizeChanged();

  private:
  QVector2D _pos;
  QVector2D _size;
  QQuickItem *_frame = nullptr;
  std::shared_ptr<Vec2Data> _posData;
  std::shared_ptr<Vec2Data> _sizeData;
};
