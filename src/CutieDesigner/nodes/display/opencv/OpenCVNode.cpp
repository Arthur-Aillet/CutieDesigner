#include "OpenCVNode.hpp"
#include "CutieWindow.hpp"
#include "PointsData.hpp"
#include "SurfaceData.hpp"
#include "qdebug.h"
#include "qimagecapture.h"

#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QQmlContext>
#include <QQmlEngine>

#include <memory>
#include <optional>

using namespace NodeEditor;

OpenCVWorker::OpenCVWorker()
    : _detector(
          std::make_unique<yolos::pose::YOLOPoseDetector>("./model/yolo26n-pose.onnx", "", false)),
      _running(false) {}

void OpenCVWorker::start() {
  _running = true;
  while (_running) {
    if (!_currentImage.has_value()) {
      QThread::msleep(20);
      continue;
    }
    QImage conv = _currentImage->convertedTo(QImage::Format_BGR888);
    cv::Mat frame(conv.height(), conv.width(), CV_8UC3, (cv::Scalar *)conv.scanLine(0));
    auto poses = _detector->detect(frame);

    QList<QVector2D> _points = {};

    for (auto &pose : poses) {
      for (auto &point : pose.keypoints) {
        if (point.confidence > 0.25) {
          _points.push_back(QVector2D(point.x, point.y));
        }
      }
    }
    _currentImage = std::nullopt_t({});
    emit resultReady(_points);
  }
  emit finished();
}

void OpenCVWorker::stop() { _running = false; }
void OpenCVWorker::newImage(QImage image) { _currentImage = image; }

void OpenCVNode::imageCaptured(int id, const QImage &image) {
  if (!_running || image.isNull()) {
    return;
  }
  _worker->newImage(image);
  _imageCapture->capture();
}

OpenCVNode::OpenCVNode(QQmlEngine *engine)
    : NodeModel(engine), _points(), _pointsData(std::make_shared<PointsData>(_points)) {
  CutieWindow *window = CutieWindow::getCutieWindow(engine);

  if (!window)
    return;

  _cameraHandler = engine->rootContext()->contextProperty("cameraHandler").value<QQuickItem *>();
  auto captureSession = _cameraHandler->property("captureSession").value<QMediaCaptureSession *>();
  _imageCapture = captureSession->imageCapture();

  connect(_imageCapture, SIGNAL(imageCaptured(int, const QImage &)), this,
          SLOT(imageCaptured(int, const QImage &)));
  connect(_cameraHandler, SIGNAL(cameraStarted()), this, SLOT(cameraStarted()));
  connect(_cameraHandler, SIGNAL(cameraStopped()), this, SLOT(cameraStopped()));
  if (_cameraHandler->property("capturing").toBool()) {
    _imageCapture->capture();
    _running = true;
  }
}

void OpenCVNode::cameraStarted() {
  _running = true;
  _worker = new OpenCVWorker();
  _thread = new QThread;

  _worker->moveToThread(_thread);
  connect(_thread, SIGNAL(started()), _worker, SLOT(start()));
  connect(_worker, SIGNAL(finished()), _thread, SLOT(quit()));
  connect(_worker, SIGNAL(finished()), _worker, SLOT(deleteLater()));
  connect(_thread, SIGNAL(finished()), _thread, SLOT(deleteLater()));
  connect(_worker, &OpenCVWorker::resultReady, [this](QList<QVector2D> points) {
    _points = points;
    emit dataUpdated(0);
  });
  _thread->start();

  _imageCapture->capture();
}

void OpenCVNode::cameraStopped() {
  _running = false;
  _worker->stop();
}

unsigned int OpenCVNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 1;
  default:
    return 1;
  };
}

NodeDataType OpenCVNode::dataType(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    default:
      return SurfaceData().type();
    }
  default:
    return PointsData().type();
  }
}

std::shared_ptr<NodeData> OpenCVNode::outData(PortIndex _portIndex) { return _pointsData; }

void OpenCVNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (!data) {
    _surface.reset();
    emit dataInvalidated(0);
  } else {
    _surface = std::dynamic_pointer_cast<SurfaceData>(data);
    emit dataUpdated(0);
  }
}

QString OpenCVNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
    default:
      return "in";
    }
  default:
    return "points";
  }
}
