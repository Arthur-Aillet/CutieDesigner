#include "Dimension/DimensionNode.hpp"
#include "DecimalData.hpp"
#include "DimensionNode.hpp"
#include "NodeDelegateModel.hpp"
#include "SurfaceData.hpp"
#include "Vec2Data.hpp"

DimensionNode::DimensionNode(QQmlEngine *engine) : NodeDelegateModel(engine) {
  auto comp = std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "Dimension");
  _content = std::make_shared<SurfaceData>(std::move(comp),
                                           QVariantMap{{"node", QVariant::fromValue(this)}});
}

unsigned int DimensionNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 4;
  default:
    return 1;
  }
}

NodeDataType DimensionNode::dataType(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    if (portIndex == 0)
      return SurfaceData().type();
    if (portIndex == 1 || portIndex == 2)
      return Vec2Data().type();
    return DecimalData().type();
  default:
    return SurfaceData().type();
  }
}

std::shared_ptr<NodeData> DimensionNode::outData(PortIndex _portIndex) {
  if (_surface.expired())
    return nullptr;
  return _content;
}

void DimensionNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (!data) {
    switch (portIndex) {
    case 0:
      _surface.reset();
      emit dataInvalidated(0);
      emit surfaceChanged();
      return;
    case 1:
      _inPos.reset();
      emit inPosChanged();
      return;
    case 2:
      _inSize.reset();
      emit inSizeChanged();
      return;
    case 3:
      _rotation.reset();
      emit rotationChanged();
      return;
    }
  } else {
    switch (portIndex) {
    case 0:
      _surface = std::dynamic_pointer_cast<SurfaceData>(data);
      emit dataUpdated(0);
      emit surfaceChanged();
      return;
    case 1:
      _inPos = data;
      emit inPosChanged();
      return;
    case 2:
      _inSize = data;
      emit inSizeChanged();
      return;
    case 3:
      _rotation = data;
      emit rotationChanged();
      return;
    }
  }
}

QString DimensionNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return QString("in");
    case 1:
      return QString("pos");
    case 2:
      return QString("size");
    case 3:
      return QString("rotation");
    }
  default:
    return QString("out");
  }
}