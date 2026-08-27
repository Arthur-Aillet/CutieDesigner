#include "GradientInputNode.hpp"
#include "GradientData.hpp"
#include "GradientInputList.hpp"

#include <memory>

using namespace NodeEditor;

GradientInputNode::GradientInputNode(QQmlEngine *engine)
    : NodeModel(engine), _list(std::make_shared<GradientInputList>()),
      _content(std::make_shared<GradientData>(_list->gradient)) {
  QObject::connect(
      _list.get(), &GradientInputList::gradientChanged, this, [this]() { emit dataUpdated(0); },
      Qt::AutoConnection);
}

QJsonObject GradientInputNode::save() const { return {{"stops", _list->save()["stops"]}}; }

void GradientInputNode::load(QJsonObject const &json) { _list->load(json); }

unsigned int GradientInputNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 0;
  default:
    return 1;
  }
}

NodeDataType GradientInputNode::dataType(PortSide _portSide, PortIndex _portIndex) const {
  return GradientData().type();
}

std::shared_ptr<NodeData> GradientInputNode::outData(PortIndex _portIndex) { return _content; }
