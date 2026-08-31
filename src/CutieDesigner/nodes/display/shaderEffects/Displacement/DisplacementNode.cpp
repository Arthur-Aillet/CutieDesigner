#include "DisplacementNode.hpp"
#include "DecimalData.hpp"
#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

using namespace NodeEditor;

DisplacementNode::DisplacementNode(QQmlEngine *engine) : NodeModel(engine) {
  auto comp =
      std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "Displacement");
  _content = std::make_shared<SurfaceData>(std::move(comp),
                                           QVariantMap{{"node", QVariant::fromValue(this)}});
}

QJsonObject DisplacementNode::save() const { return QJsonObject(); }

void DisplacementNode::load(QJsonObject const &json) {}

unsigned int DisplacementNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 4;
  default:
    return 1;
  }
}

NodeDataType DisplacementNode::dataType(PortSide portSide, PortIndex portIndex) const {
  if (portSide == PortSide::In) {
    if (portIndex >= 2)
      return DecimalData().type();
    return SurfaceData().type();
  } else {
    return SurfaceData().type();
  }
}

std::shared_ptr<NodeData> DisplacementNode::outData(PortIndex _portIndex) {
  if (_image.expired() && _map.expired())
    return nullptr;
  return _content;
}

void DisplacementNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (data == nullptr) {
    switch (portIndex) {
    case 0:
      _image.reset();
      emit imageChanged();
      emit dataInvalidated(0);
      return;
    case 1:
      _map.reset();
      emit mapChanged();
      emit dataInvalidated(0);
      return;
    case 2:
      _min = 0.;
      emit minChanged();
      return;
    case 3:
      _max = 3.;
      emit maxChanged();
      return;
    }
  } else {
    switch (portIndex) {
    case 0:
      _image = std::dynamic_pointer_cast<SurfaceData>(data);
      emit imageChanged();
      emit dataUpdated(0);
      return;
    case 1:
      _map = std::dynamic_pointer_cast<SurfaceData>(data);
      emit mapChanged();
      emit dataUpdated(0);
      return;
    case 2:
      _min = data->repr<double>();
      emit minChanged();
      return;
    case 3:
      _max = data->repr<double>();
      emit maxChanged();
      return;
    }
  }
}

QString DisplacementNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return "image";
    case 1:
      return "map";
    case 2:
      return "min";
    case 3:
      return "max";
    }
  default:
    return "out";
  }
}
