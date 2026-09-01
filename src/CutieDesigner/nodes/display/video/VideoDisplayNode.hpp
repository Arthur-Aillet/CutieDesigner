#pragma once

#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

#include <QUrl>
#include <QVideoSink>
#include <QtMultimediaQuick/private/qquickvideooutput_p.h>

#include <QtAVPlayer/qavplayer.h>

#include <optional>

class VideoDisplayNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
  Q_PROPERTY(QString sourceFileName READ sourceFileName NOTIFY sourceChanged)
  Q_PROPERTY(bool looping READ looping WRITE setLooping NOTIFY loopingChanged)
  Q_PROPERTY(double playbackRate READ playbackRate NOTIFY playbackRateChanged)

  VideoDisplayNode(QQmlEngine *engine);
  ~VideoDisplayNode() = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return "Video"; }

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

  QUrl source();
  void setSource(QUrl url);
  QString sourceFileName();
  bool looping();
  void setLooping(bool looping);
  double playbackRate();

  Q_INVOKABLE void newVideoOutput(QQuickVideoOutput *output);
  Q_INVOKABLE void removeVideoOutput(QQuickVideoOutput *output);

  signals:
  void sourceChanged();
  void loopingChanged();
  void playbackRateChanged();

  private:
  std::vector<QQuickVideoOutput *> _sinks;
  QAVPlayer _player;
  bool _looping = true;
  std::optional<QUrl> _sourceUrl = std::nullopt;
  double _playbackRate = 1.0;
  std::shared_ptr<SurfaceData> _content = nullptr;
};
