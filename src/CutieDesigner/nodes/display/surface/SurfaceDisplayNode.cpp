#include "SurfaceDisplayNode.hpp"
#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

#include <QtWidgets/QLabel>

#include <memory>

using namespace NodeEditor;

SurfaceDisplayNode::SurfaceDisplayNode(QQmlEngine *engine) : NodeModel(engine), _content() {}

unsigned int SurfaceDisplayNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 1;
  default:
    return 0;
  }
}

NodeDataType SurfaceDisplayNode::dataType(PortSide, PortIndex) const {
  return SurfaceData().type();
}

std::shared_ptr<NodeData> SurfaceDisplayNode::outData(PortIndex) { return nullptr; }

void SurfaceDisplayNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (data == nullptr) {
    _content.reset();
    emit contentChanged(nullptr);
  } else {
    _content = std::dynamic_pointer_cast<SurfaceData>(data);
    emit contentChanged(_content.lock().get());
  }
}
