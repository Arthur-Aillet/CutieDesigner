#pragma once

#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

class CameraNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(QQuickItem *cameraHandler MEMBER _cameraHandler CONSTANT)

  CameraNode(QQmlEngine *engine);
  ~CameraNode() = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return "Camera"; }

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
  void initPipeline();

  private:
  std::shared_ptr<SurfaceData> _content = nullptr;
  QQmlEngine *_engine;
  QQuickItem *_cameraHandler;
};
