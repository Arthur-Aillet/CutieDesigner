#pragma once

#include "SurfaceData.hpp"

#include <NodeEditor/NodeData>
#include <NodeEditor/NodeModel>

class BlurNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(SurfaceData *source READ source NOTIFY sourceChanged)
  Q_PROPERTY(float radius READ radius NOTIFY radiusChanged)

  BlurNode(QQmlEngine *engine);
  ~BlurNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "Blur"; }

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override;
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;

  SurfaceData *source() { return _source.lock().get(); }
  float radius() { return _radius; }

  signals:
  void sourceChanged();
  void radiusChanged();

  private:
  float _radius = 32.0;
  std::weak_ptr<SurfaceData> _source;
  std::shared_ptr<SurfaceData> _content;
};
