#pragma once

#include "SurfaceData.hpp"
#include "qtmetamacros.h"

#include <NodeEditor/NodeModel>

class NoiseNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(double time READ time NOTIFY timeChanged)
  Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged)

  NoiseNode(QQmlEngine *engine);
  ~NoiseNode() = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return "Noise"; }

  QJsonObject save() const override;
  void load(QJsonObject const &p) override;

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

  QQmlComponent embeddedComponent(QQmlEngine *engine) override;
  QVariantMap componentInitialProperties() override;

  double time() { return _time; }
  int mode() { return _mode; }
  void setMode(int mode) {
    if (_mode == mode)
      return;
    _mode = mode;
    emit modeChanged();
  }

  signals:
  void timeChanged();
  void modeChanged();

  private:
  int _mode = 0;
  double _time = 1.0;
  std::shared_ptr<SurfaceData> _content = nullptr;
};
