package gk.synthesizer;

import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;


@gk.synthesizer.annotations.MasterWidget
public class SineWaveWidget extends MasterWidget {
    SineWave sineWave = new SineWave(440);
    Slider frequencySlider = new Slider();
    TextField frequencyTextField = new TextField();


    public SineWaveWidget(String title, int height, int width, Pane mainPane) {
        super(title,height, width, mainPane);
        super.audioComponent = sineWave;
        @WidgetSize( height = 100, width = 300)
        Pane sineWavePane = new Pane();
        Label scrollBarLabel = new Label("Frequency:");
        //Slider constructor
        frequencySlider.setMin(0);
        frequencySlider.setMax(1000);
        frequencySlider.setValue(sineWave.getFrequency());
        frequencySlider.setShowTickLabels(true);
        frequencySlider.setShowTickMarks(true);
        frequencySlider.setMajorTickUnit(500);
        frequencySlider.setMinorTickCount(10);
        frequencySlider.setBlockIncrement(50);
        frequencySlider.setOnMouseReleased(event -> {
            updateFrequencyValue((int)frequencySlider.getValue());
        });

        //Text Field Constructor
        frequencyTextField.setMaxWidth(50);
        frequencyTextField.setText(Integer.toString(sineWave.getFrequency()));
        frequencyTextField.textProperty().addListener((observable, oldValue, newValue) -> {
            if (!Double.isNaN((Integer.parseInt(frequencyTextField.getText())))) {
                // I need to revisit this- the parse will error if NaN
                updateFrequencyValue((Integer.parseInt(frequencyTextField.getText())));
            }else{
                updateFrequencyValue(0);
            }

        });

        HBox frequencyHBox = new HBox(10);
        frequencyHBox.getChildren().addAll(scrollBarLabel, frequencyTextField, frequencySlider);

        sineWavePane.getChildren().addAll(frequencyHBox);
        innerPane.setCenter(sineWavePane);
        mainPane.getChildren().add(innerPane);
        innerPane.setLayoutY(150);
    }

    private void updateFrequencyValue(int newValue) {
        if (newValue< 0){
            newValue = 0;
        }
        if(newValue > 1000){
            newValue = 1000;
        }
        this.sineWave.setFrequency(newValue);
        frequencySlider.setValue(sineWave.getFrequency());
        frequencyTextField.setText(Integer.toString(sineWave.getFrequency()));
    }

}


