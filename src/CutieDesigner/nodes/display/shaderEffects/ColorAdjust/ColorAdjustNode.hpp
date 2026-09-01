#pragma once

#include "SurfaceData.hpp"

#include <NodeEditor/NodeData>
#include <NodeEditor/NodeModel>

#include <QColor>

class ColorAdjustNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(SurfaceData *source READ source NOTIFY sourceChanged)
  Q_PROPERTY(float saturation READ saturation NOTIFY saturationChanged)
  Q_PROPERTY(float brightness READ brightness NOTIFY brightnessChanged)
  Q_PROPERTY(float contrast READ contrast NOTIFY contrastChanged)

  ColorAdjustNode(QQmlEngine *engine);
  ~ColorAdjustNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "Color Adjust"; }

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
  float brightness() { return _brightness; }
  float contrast() { return _contrast; }
  float saturation() { return _saturation; }

  signals:
  void sourceChanged();
  void brightnessChanged();
  void contrastChanged();
  void saturationChanged();

  private:
  float _brightness = 0.0;
  float _contrast = 1.0;
  float _saturation = 1.0;
  std::weak_ptr<SurfaceData> _source;
  std::shared_ptr<SurfaceData> _content;
};
