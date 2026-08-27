#include "StackNode.hpp"
#include "SurfaceData.hpp"

#include <QVariant>
#include <QtWidgets/QLabel>

#include <memory>

using namespace NodeEditor;

int SurfaceList::rowCount(const QModelIndex &parent) const {
  int i = 0;
  for (auto &currentSurface : _surfaces) {
    if (!currentSurface.expired())
      i++;
  }
  return i;
}

int SurfaceList::portsCount() const { return _surfaces.size(); }

QVariant SurfaceList::data(const QModelIndex &index, int role) const {
  int i = 0;
  for (auto &currentSurface : _surfaces) {
    if (!currentSurface.expired()) {
      if (i == index.row())
        return QVariant::fromValue(currentSurface.lock().get());
      i++;
    }
  }
  return QVariant::fromValue(nullptr);
}

void SurfaceList::setPort(std::shared_ptr<SurfaceData> surface, int portIndex) {
  int count = 0;

  for (int i = 0; i != portIndex + 1; i++) {
    if (!_surfaces[i].expired())
      count++;
  }

  if (surface == nullptr) {
    beginRemoveRows({}, count - 1, count - 1);
    _surfaces[portIndex].reset();
    endRemoveRows();
  } else if (_surfaces[portIndex].expired()) {
    beginInsertRows({}, count, count);
    _surfaces[portIndex] = surface;
    endInsertRows();
  } else {
    _surfaces[portIndex] = surface;
    emit dataChanged(QAbstractItemModel::createIndex(count - 1, 0),
                     QAbstractItemModel::createIndex(count - 1, 0));
  }
}

void SurfaceList::addEmptyPort() { _surfaces.push_back({}); }

void SurfaceList::removeLastPort() {
  if (portsCount() <= 1)
    return;

  if (!_surfaces[portsCount() - 1].expired()) {
    beginRemoveRows(QModelIndex(), rowCount(), rowCount());
    _surfaces.pop_back();
    endRemoveRows();
  } else {
    _surfaces.pop_back();
  }
  return;
}

StackNode::StackNode(QQmlEngine *engine) : NodeModel(engine) {
  auto comp = std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "Stack");
  _content = std::make_shared<SurfaceData>(std::move(comp),
                                           QVariantMap{{"node", QVariant::fromValue(this)}});
}

void StackNode::addEmptyPort() {
  emit portsAboutToBeInserted(PortSide::In, _surfaceList.portsCount(), _surfaceList.portsCount());
  _surfaceList.addEmptyPort();
  emit portsInserted(PortSide::In);
}

QJsonObject StackNode::save() const { return {{"portsCount", _surfaceList.portsCount()}}; }
void StackNode::load(QJsonObject const &json) {
  auto value = json["portsCount"];

  if (!value.isUndefined()) {
    for (int i = 0; i != _surfaceList.portsCount(); i++) {
      _surfaceList.removeLastPort();
    }
    for (int i = 0; i != value.toInt(); i++) {
      _surfaceList.addEmptyPort();
    }
  }
}

void StackNode::removeLastPort() {
  if (_surfaceList.portsCount() <= 1)
    return;

  emit portsAboutToBeDeleted(PortSide::In, _surfaceList.portsCount() - 1,
                             _surfaceList.portsCount() - 1);
  _surfaceList.removeLastPort();
  emit portsDeleted(PortSide::In);
}

unsigned int StackNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return _surfaceList.portsCount();
  default:
    return 1;
  }
}

NodeDataType StackNode::dataType(PortSide _portSide, PortIndex _portIndex) const {
  return SurfaceData().type();
}

std::shared_ptr<NodeData> StackNode::outData(PortIndex _portIndex) { return _content; }

void StackNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (!data) {
    _surfaceList.setPort(nullptr, portIndex);
    emit dataUpdated(0);
  } else {
    auto surface = std::dynamic_pointer_cast<SurfaceData>(data);
    _surfaceList.setPort(surface, portIndex);
    emit dataUpdated(0);
  }
}

QString StackNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    return QString::number(portIndex);
  default:
    return QString("out");
  }
}
