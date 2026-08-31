import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import CutieDesigner.Nodes.Display

FlexboxLayout {
    id: noiseControl
    direction: FlexboxLayout.FlexboxDirection.Column
    required property NoiseNode node

    ComboBox {
        model: ["Cloud", "Turbulence", "Marble", "Granite"]

        Component.onCompleted: {
            currentIndex = noiseControl.node.mode;
        }

        onActivated: {
            noiseControl.node.mode = currentIndex;
        }

        onHighlightedIndexChanged: {
            if (highlightedIndex < 0)
                return;
            else
                noiseControl.node.mode = highlightedIndex;
        }
    }
}
