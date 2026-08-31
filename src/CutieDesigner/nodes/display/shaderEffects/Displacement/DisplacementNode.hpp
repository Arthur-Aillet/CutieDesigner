#pragma once

#include "SurfaceData.hpp"

#include <NodeEditor/NodeData>
#include <NodeEditor/NodeModel>

#include <QColor>

class DisplacementNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(SurfaceData *image READ image NOTIFY imageChanged)
  Q_PROPERTY(SurfaceData *map READ map NOTIFY mapChanged)
  Q_PROPERTY(float min READ min NOTIFY minChanged)
  Q_PROPERTY(float max READ max NOTIFY maxChanged)

  DisplacementNode(QQmlEngine *engine);
  ~DisplacementNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "Displacement"; }

  QJsonObject save() const override;
  void load(QJsonObject const &p) override;

  QQmlComponent embeddedComponent(QQmlEngine *engine) override {
    return QQmlComponent(engine, "CutieDesigner.Nodes.Display", "DisplacementControl");
  }

  QVariantMap componentInitialProperties() override {
    return QVariantMap{{"node", QVariant::fromValue(this)}};
  }

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

  SurfaceData *image() { return _image.lock().get(); }
  SurfaceData *map() { return _map.lock().get(); }
  float min() { return _min; }
  float max() { return _max; }

  signals:
  void imageChanged();
  void mapChanged();
  void minChanged();
  void maxChanged();

  private:
  float _min = 0.0;
  float _max = 3.0;
  std::weak_ptr<SurfaceData> _image;
  std::weak_ptr<SurfaceData> _map;
  std::shared_ptr<SurfaceData> _content;
};
