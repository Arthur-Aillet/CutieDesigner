#include "FileManager.hpp"

#include <NodeEditor/DataFlowGraph>

#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

FileManager::FileManager(NodeEditor::DataFlowGraph *model, QObject *parent)
    : QObject(parent), _model(model) {}

bool FileManager::graphEmpty() {
  for (auto &nodeId : _model->allNodeIds()) {
    if (!_model->nodeData(nodeId, NodeEditor::NodeRole::Flags)
             .value<NodeEditor::NodeFlags>()
             .testFlag(NodeEditor::NodeFlag::Locked)) {
      return false;
    }
  }
  return true;
}

static void removeStartNode(QJsonObject &json) {
  auto nodes = json["nodes"];
  QJsonArray keptNodes;
  for (const auto &node : nodes.toArray()) {
    if (!node.toObject()["flags"].toVariant().value<NodeEditor::NodeFlags>().testFlag(
            NodeEditor::NodeFlag::Locked)) {
      keptNodes.append(node);
    }
  }
  json["nodes"] = keptNodes;
}

QString FileManager::saveGraph(QUrl path) {
  QFile file(path.toLocalFile());

  if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
    return "Couldn't open given file.";
  }
  file.resize(0);
  QJsonObject jsonModel = _model->save();
  removeStartNode(jsonModel);
  QJsonDocument jsonDoc(jsonModel);
  QByteArray str = jsonDoc.toJson(QJsonDocument::Indented);
  file.write(str);
  return "";
}

QString FileManager::loadGraph(QUrl path, bool overwrite) {
  QFile file(path.toLocalFile());

  if (!file.exists()) {
    return "Given file doesn't exist.";
  }
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return "Couldn't open given file.";
  }
  QByteArray content = file.readAll();
  QJsonParseError parseError;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(content, &parseError);
  if (jsonDoc.isNull()) {
    return "Failed to load: " + parseError.errorString();
  }

  if (overwrite) {
    for (auto &nodeId : _model->allNodeIds()) {
      if (!_model->nodeData(nodeId, NodeEditor::NodeRole::Flags)
               .value<NodeEditor::NodeFlags>()
               .testFlag(NodeEditor::NodeFlag::Locked)) {
        _model->deleteNode(nodeId);
      }
    }
  }

  _model->load(jsonDoc.object());
  return "";
}
