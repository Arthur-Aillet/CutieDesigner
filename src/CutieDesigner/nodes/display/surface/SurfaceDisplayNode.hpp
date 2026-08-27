#pragma once

#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

class SurfaceDisplayNode : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  SurfaceDisplayNode(QQmlEngine *engine);
  Q_PROPERTY(SurfaceData *content READ getContent NOTIFY contentChanged)

  ~SurfaceDisplayNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return QStringLiteral("Result"); }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;

  SurfaceData *getContent() { return _content.lock().get(); }

  signals:
  void contentChanged(SurfaceData *);

  private:
  std::weak_ptr<SurfaceData> _content;
};
