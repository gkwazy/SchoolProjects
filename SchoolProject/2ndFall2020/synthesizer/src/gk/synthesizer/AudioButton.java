package gk.synthesizer;

import javafx.scene.control.Button;
import javafx.scene.layout.Pane;

public class AudioButton {
    String title;
    MasterWidget audioC;
    Button audioButton;


    AudioButton(MasterWidget widget, Pane buttonPane){
        this.title = widget.getClass().getSimpleName();
        this.audioC = widget;
        this.audioButton = new Button();
        audioButton.setText(title);

        audioButton.setOnAction(eh ->{
        });
    }


}
