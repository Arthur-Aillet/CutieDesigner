#pragma once

#include "DecimalData.hpp"
#include "MathOperationNodeModel.hpp"

#include <QtCore/QObject>

class MaxNode : public MathOperationNodeModel {
  public:
  MaxNode(QQmlEngine *engine) : MathOperationNodeModel(engine) {}
  virtual ~MaxNode() {}

  public:
  QString caption() const override { return "max"; }

  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  QString name() const override { return "Max"; }

  private:
  void compute() override {
    auto n1 = _inputNumbers[0].lock();
    auto n2 = _inputNumbers[1].lock();

    if (n1 && n2) {
      _result = std::max(n1->repr<double>(), n2->repr<double>());
      _resultPtr = std::make_shared<DecimalData>(_result);
    } else {
      _resultPtr.reset();
    }

    emit dataUpdated(0);
  }
};
