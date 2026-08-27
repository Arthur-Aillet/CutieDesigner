#pragma once

#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

class DitheringNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(SurfaceData *surface READ surface NOTIFY surfaceChanged)
  Q_PROPERTY(int mode READ getMode WRITE setMode NOTIFY modeChanged)
  Q_PROPERTY(int resolution READ resolution NOTIFY resolutionChanged)

  DitheringNode(QQmlEngine *engine);
  ~DitheringNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "Dithering"; }

  QJsonObject save() const override;
  void load(QJsonObject const &p) override;

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override;
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  QQmlComponent embeddedComponent(QQmlEngine *engine) override {
    return QQmlComponent(engine, "CutieDesigner.Nodes.Display", "DitheringControl");
  }

  QVariantMap componentInitialProperties() override {
    return QVariantMap{{"node", QVariant::fromValue(this)}};
  }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;

  SurfaceData *surface() { return _surface.lock().get(); }
  int resolution() { return _resolution; }
  int getMode() { return _mode; }
  void setMode(int mode) {
    if (mode == _mode)
      return;
    _mode = mode;
    emit modeChanged();
  }

  signals:
  void surfaceChanged();
  void modeChanged();
  void resolutionChanged();

  private:
  int _mode = 0;
  int _resolution = 1;
  std::weak_ptr<SurfaceData> _surface;
  std::shared_ptr<SurfaceData> _content;
};
