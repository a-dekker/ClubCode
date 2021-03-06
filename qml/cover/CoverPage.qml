import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground
{
    Column {
        width: parent.width
        spacing: Theme.paddingMedium
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 15
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Ↄlub<b>C</b>ode"
        }
        Image
        {
            source: Qt.resolvedUrl("../../cover.png")
            anchors.horizontalCenter: parent.horizontalCenter
            scale: mainApp.sizeRatio
            layer.effect: ShaderEffect {
                property color color: Theme.primaryColor

                fragmentShader: "
                varying mediump vec2 qt_TexCoord0;
                uniform highp float qt_Opacity;
                uniform lowp sampler2D source;
                uniform highp vec4 color;
                void main() {
                    highp vec4 pixelColor = texture2D(source, qt_TexCoord0);
                    gl_FragColor = vec4(mix(pixelColor.rgb/max(pixelColor.a, 0.00390625), color.rgb/max(color.a, 0.00390625), color.a) * pixelColor.a, pixelColor.a) * qt_Opacity;
                }
                "
            }
            layer.enabled: true
            layer.samplerName: "source"
        }
    }
}
