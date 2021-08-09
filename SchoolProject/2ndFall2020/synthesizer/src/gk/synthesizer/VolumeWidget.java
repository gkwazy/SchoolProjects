package gk.synthesizer;

import javafx.geometry.Bounds;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class VolumeWidget extends MasterWidget {
    VolumeFilter volumeFilter = new VolumeFilter(1);
    Slider scaleSlider = new Slider();
    TextField scaleTextField = new TextField();
    Circle input;
    Bounds volumeBounds;

    public VolumeWidget(String title, int height, int width, Pane mainPane) {
        super(title, height, width, mainPane);
        super.audioComponent = volumeFilter;
        Pane volumePane = new Pane();
        Label scrollBarLabel = new Label("Scale:");
        //Slider constructor
        scaleSlider.setMin(0);
        scaleSlider.setMax(10);
        scaleSlider.setValue(volumeFilter.getScale());
        scaleSlider.setShowTickLabels(true);
        scaleSlider.setShowTickMarks(true);
        scaleSlider.setMajorTickUnit(2);
        scaleSlider.setMinorTickCount(1);
        scaleSlider.setBlockIncrement(5);
        scaleSlider.setOnMouseReleased(event -> {
            updateFrequencyValue((int)scaleSlider.getValue());
        });

        //Text Field Constructor
        scaleTextField.setMaxWidth(50);
        scaleTextField.setText(Double.toString(volumeFilter.getScale()));
        scaleTextField.textProperty().addListener((observable) -> {
//            if (!Double.isNaN((Integer.parseInt(scaleTextField.getText())))) {
//                // I need to revisit this- the parse will error if NaN
                updateFrequencyValue((Integer.parseInt(scaleTextField.getText())));
//            }else{
//                updateFrequencyValue(0);
//            }

        });

//        input = new Circle(20);
//
//
//        HBox circleBox = new HBox( 20);
//        circleBox.getChildren().addAll(input);

        HBox scaleHBox = new HBox(10);
        scaleHBox.getChildren().addAll(scrollBarLabel, scaleTextField, scaleSlider);

        volumePane.getChildren().addAll(scaleHBox);
        innerPane.setCenter(volumePane);
//        innerPane.setBottom(circleBox);
        mainPane.getChildren().add(innerPane);
    }

    private void updateFrequencyValue(int newValue) {
        if (newValue< 0){
            newValue = 0;
        }
        if(newValue > 1000){
            newValue = 1000;
        }
        this.volumeFilter.setScale(newValue);
        scaleSlider.setValue(volumeFilter.getScale());
        scaleTextField.setText(Double.toString(volumeFilter.getScale()));

    }

}


