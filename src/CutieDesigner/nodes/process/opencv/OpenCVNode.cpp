#include "OpenCVNode.hpp"
#include "SurfaceData.hpp"

#include <opencv2/core.hpp>

using namespace NodeEditor;

OpenCVNode::OpenCVNode(QQmlEngine *engine) : NodeModel(engine) {}

unsigned int OpenCVNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 1;
  default:
    return 0;
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
    return SurfaceData().type();
  }
}

std::shared_ptr<NodeData> OpenCVNode::outData(PortIndex _portIndex) { return nullptr; }

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
    return "out";
  }
}
