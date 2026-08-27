#include "WindowInputNode.hpp"

using namespace NodeEditor;

WindowInputNode::WindowInputNode(QQmlEngine *engine)
    : NodeModel(engine), _sizeData(std::make_shared<Vec2Data>(_size)) {
  _window = CutieWindow::getCutieWindow(engine);
  if (_window == nullptr)
    return;

  _size = QVector2D(_window->width(), _window->height());

  QObject::connect(_window, SIGNAL(resizeEventForward(QResizeEvent *)), this,
                   SLOT(resizeEvent(QResizeEvent *)));
}

unsigned int WindowInputNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::Out:
    return 1;
  default:
    return 0;
  }
}

QString WindowInputNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  return "size";
}

NodeDataType WindowInputNode::dataType(PortSide _portSide, PortIndex _portIndex) const {
  return Vec2Data().type();
}

std::shared_ptr<NodeData> WindowInputNode::outData(PortIndex portIndex) { return _sizeData; }

void WindowInputNode::resizeEvent(QResizeEvent *_event) {
  auto frame = qvariant_cast<QQuickItem *>(_window->property("sceneContent"));

  if (QVector2D(frame->width(), frame->height()) != _size) {
    _size = QVector2D(frame->width(), frame->height());
    emit dataUpdated(0);
  }
}
