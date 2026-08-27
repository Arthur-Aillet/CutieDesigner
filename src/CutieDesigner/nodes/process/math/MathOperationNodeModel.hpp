#pragma once

#include <NodeEditor/NodeModel>

class DecimalData;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MathOperationNodeModel : public NodeEditor::NodeModel {
  Q_OBJECT

  public:
  MathOperationNodeModel(QQmlEngine *engine)
      : NodeEditor::NodeModel(engine), _inputNumbers(nbInputs()) {}
  ~MathOperationNodeModel() = default;

  public:
  virtual unsigned int nbInputs() const { return 2; };
  unsigned int nPorts(NodeEditor::PortSide portSide) const override;

  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  virtual bool portCaptionVisible(NodeEditor::PortSide, NodeEditor::PortIndex) const override {
    return true;
  }
  virtual QString portCaption(NodeEditor::PortSide portSide,
                              NodeEditor::PortIndex portIndex) const override {
    if (portSide == NodeEditor::PortSide::Out)
      return "out";
    if (nbInputs() == 1)
      return "in";
    return QString((char)('a' + portIndex));
  }

  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;

  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;

  protected:
  virtual void compute() = 0;

  protected:
  std::vector<std::weak_ptr<NodeEditor::NodeData>> _inputNumbers;

  double _result;
  std::shared_ptr<DecimalData> _resultPtr;
};
