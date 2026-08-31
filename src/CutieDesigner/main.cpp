#include "CutieWindow.hpp"
#include "DisplacementNode.hpp"
#include "DitheringNode.hpp"
#include "MaxNode.hpp"
#include "MinNode.hpp"
#include "ModNode.hpp"
#include "TimeController.hpp"

#include "ColorInputNode.hpp"
#include "GradientInputNode.hpp"
#include "MouseInputNode.hpp"
#include "NumberInputNode.hpp"
#include "SceneInputNode.hpp"
#include "SliderInputNode.hpp"
#include "TextInputNode.hpp"
#include "TimeInputNode.hpp"
#include "Vec2InputNode.hpp"
#include "WindowInputNode.hpp"

#include "ATypeNode.hpp"
#include "AdditionNode.hpp"
#include "BlendNode.hpp"
#include "CameraNode.hpp"
#include "CombineColorNode.hpp"
#include "CombineVec2Node.hpp"
#include "CosNode.hpp"
#include "DimensionNode.hpp"
#include "DitheringNode.hpp"
#include "DivisionNode.hpp"
#include "FillNode.hpp"
#include "ImageDisplayNode.hpp"
#include "MaskNode.hpp"
#include "MultiplicationNode.hpp"
#include "NoiseNode.hpp"
#include "SinNode.hpp"
#include "SplitColorNode.hpp"
#include "SplitVec2Node.hpp"
#include "StackNode.hpp"
#include "SubtractionNode.hpp"
#include "SurfaceDisplayNode.hpp"
#include "SurfaceLoader.hpp"
#include "TextTyperNode.hpp"
#include "UkrugNode.hpp"
#include "VideoDisplayNode.hpp"

#include "FileManager.hpp"

#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QVariant>
#include <QtQml>
#include <QtWidgets/QApplication>

#include <NodeEditor/DataFlowContext>
#include <NodeEditor/DataFlowGraph>
#include <NodeEditor/NodeModelRegistry>
#include <NodeEditor/StyleCollection>

static NodeEditor::NodeModelRegistry *createRegistery(QQmlEngine &engine) {
  auto reg = new NodeEditor::NodeModelRegistry(&engine);

  // Input
  reg->registerModel<ColorInputNode>("Input");
  reg->registerModel<GradientInputNode>("Input");
  reg->registerModel<MouseInputNode>("Input");
  reg->registerModel<NumberInputNode>("Input");
  reg->registerModel<SceneInputNode>("Input");
  reg->registerModel<TextInputNode>("Input");
  reg->registerModel<WindowInputNode>("Input");
  reg->registerModel<TimeInputNode>("Input");
  reg->registerModel<Vec2InputNode>("Input");
  reg->registerModel<SliderInputNode>("Input");

  reg->registerModel<AdditionNode>("Process");
  reg->registerModel<DivisionNode>("Process");
  reg->registerModel<MultiplicationNode>("Process");
  reg->registerModel<SubtractionNode>("Process");
  reg->registerModel<SinNode>("Process");
  reg->registerModel<CosNode>("Process");
  reg->registerModel<MinNode>("Process");
  reg->registerModel<MaxNode>("Process");
  reg->registerModel<ModNode>("Process");
  reg->registerModel<CombineColorNode>("Process");
  reg->registerModel<SplitColorNode>("Process");
  reg->registerModel<CombineVec2Node>("Process");
  reg->registerModel<SplitVec2Node>("Process");
  reg->registerModel<TextTyperNode>("Process");

  reg->registerModel<DimensionNode>("Display");
  reg->registerModel<SurfaceDisplayNode>("Display");
  reg->registerModel<UkrugNode>("Display");
  reg->registerModel<ATypeNode>("Display");
  reg->registerModel<MaskNode>("Display");
  reg->registerModel<BlendNode>("Display");
  reg->registerModel<DitheringNode>("Display");
  reg->registerModel<DisplacementNode>("Display");
  reg->registerModel<CameraNode>("Display");
  reg->registerModel<FillNode>("Display");
  reg->registerModel<VideoDisplayNode>("Display");
  reg->registerModel<StackNode>("Display");
  reg->registerModel<ImageDisplayNode>("Display");
  reg->registerModel<NoiseNode>("Display");
  return reg;
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QQmlApplicationEngine engine;
  QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);

  engine.rootContext()->setContextProperty("app", &app);

  auto reg = createRegistery(engine);
  const auto graph = new NodeEditor::DataFlowGraph(reg);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  auto context = new NodeEditor::DataFlowContext(graph);
  context->styleCollection()->followApplicationPalette(true);
  engine.rootContext()->setContextProperty("styleCollection",
                                           QVariant::fromValue(context->styleCollection()));

  TimeController::init();

  FileManager fileManager(graph);

  engine.setInitialProperties({{"fileManager", QVariant::fromValue(&fileManager)},
                               {"dataFlowContext", QVariant::fromValue(context)}});
  engine.loadFromModule("CutieDesigner.App", "App");

  QObject &window = *engine.rootObjects().first();
  TimeController::linkCutieWindow(CutieWindow::getCutieWindow(&engine));

  auto source = graph->addNode(SurfaceDisplayNode(&engine).name());
  graph->setNodeData(source, NodeEditor::NodeRole::Position, QPointF(750, 225));
  graph->setNodeData(source, NodeEditor::NodeRole::Flags,
                     NodeEditor::NodeFlags({NodeEditor::NodeFlag::Locked}).toInt());
  auto display = graph->model<SurfaceDisplayNode>(source);

  engine.rootContext()->setContextProperty("cameraHandler",
                                           window.property("cameraHandler").value<QQuickItem *>());

  auto loader = window.property("objectLoader").value<SurfaceLoader *>();
  QObject::connect(display, SIGNAL(contentChanged(SurfaceData *)), loader,
                   SLOT(setSurfaceData(SurfaceData *)));

  int status = app.exec();

  // Delete first surface loader to unload the visual tree
  // before the node tree to prevent missing properties
  delete loader;
  return status;
}
