#pragma once

#include "PointsData.hpp"
#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

#include <QImageCapture>

#include <memory>

#include "yolos/tasks/pose.hpp"

#include <QImage>
#include <QVector2D>
#include <optional>

class OpenCVWorker : public QObject {
  Q_OBJECT

  public:
  OpenCVWorker();

  public slots:
  void newImage(QImage image);
  void start();
  void stop();

  signals:
  void finished();
  void resultReady(QList<QVector2D> points);

  private:
  QTime _lastCapture;
  std::unique_ptr<yolos::pose::YOLOPoseDetector> _detector;
  std::optional<QImage> _currentImage;
  bool _running;
};

class OpenCVNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  OpenCVNode(QQmlEngine *engine);
  ~OpenCVNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "OpenCV"; }

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

  public slots:
  void cameraStarted();
  void cameraStopped();
  void imageCaptured(int id, const QImage &image);

  private:
  bool _running = false;
  QQuickItem *_cameraHandler;
  QImageCapture *_imageCapture;
  OpenCVWorker *_worker;
  QThread *_thread;

  QList<QVector2D> _points;
  std::weak_ptr<SurfaceData> _surface;
  std::shared_ptr<PointsData> _pointsData;
};
