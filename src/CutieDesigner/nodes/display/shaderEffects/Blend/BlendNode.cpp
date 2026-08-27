#include "BlendNode.hpp"
#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

using namespace NodeEditor;

BlendNode::BlendNode(QQmlEngine *engine) : NodeModel(engine) {
  auto comp = std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "Blend");
  _content = std::make_shared<SurfaceData>(std::move(comp),
                                           QVariantMap{{"node", QVariant::fromValue(this)}});
}

QJsonObject BlendNode::save() const { return QJsonObject({{"mode", _mode}}); }

void BlendNode::load(QJsonObject const &json) {
  QJsonValue value = json["mode"];

  if (!value.isUndefined()) {
    _mode = value.toInt();
  }
}

unsigned int BlendNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 2;
  default:
    return 1;
  }
}

NodeDataType BlendNode::dataType(PortSide _portSide, PortIndex _portIndex) const {
  return SurfaceData().type();
}

std::shared_ptr<NodeData> BlendNode::outData(PortIndex _portIndex) {
  if (_a.expired() && _b.expired())
    return nullptr;
  return _content;
}

void BlendNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (data == nullptr) {
    if (portIndex == 0) {
      _a.reset();
      emit aChanged();
    } else {
      _b.reset();
      emit bChanged();
    }
    emit dataInvalidated(0);
  } else {
    if (portIndex == 0) {
      _a = std::dynamic_pointer_cast<SurfaceData>(data);
      emit aChanged();
    } else {
      _b = std::dynamic_pointer_cast<SurfaceData>(data);
      emit bChanged();
    }
    emit dataUpdated(0);
  }
}

QString BlendNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return QString("a");
    default:
      return QString("b");
    }
  default:
    return QString("out");
  }
}
