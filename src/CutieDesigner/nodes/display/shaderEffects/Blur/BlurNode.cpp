#include "BlurNode.hpp"
#include "DecimalData.hpp"
#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

using namespace NodeEditor;

BlurNode::BlurNode(QQmlEngine *engine) : NodeModel(engine) {
  auto comp = std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "Blur");
  _content = std::make_shared<SurfaceData>(std::move(comp),
                                           QVariantMap{{"node", QVariant::fromValue(this)}});
}

unsigned int BlurNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 2;
  default:
    return 1;
  }
}

NodeDataType BlurNode::dataType(PortSide portSide, PortIndex portIndex) const {
  if (portSide == PortSide::In) {
    if (portIndex >= 1)
      return DecimalData().type();
    return SurfaceData().type();
  } else {
    return SurfaceData().type();
  }
}

std::shared_ptr<NodeData> BlurNode::outData(PortIndex _portIndex) {
  if (_source.expired())
    return nullptr;
  return _content;
}

void BlurNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (data == nullptr) {
    switch (portIndex) {
    case 0:
      _source.reset();
      emit sourceChanged();
      emit dataInvalidated(0);
      return;
    case 1:
      _radius = 32.0;
      emit radiusChanged();
      return;
    }
  } else {
    switch (portIndex) {
    case 0:
      _source = std::dynamic_pointer_cast<SurfaceData>(data);
      emit sourceChanged();
      emit dataUpdated(0);
      return;
    case 1:
      _radius = data->repr<double>();
      emit radiusChanged();
      return;
    }
  }
}

QString BlurNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return "source";
    case 1:
      return "radius";
    }
  default:
    return "out";
  }
}
