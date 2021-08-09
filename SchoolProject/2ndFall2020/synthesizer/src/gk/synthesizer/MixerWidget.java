package gk.synthesizer;

import javafx.scene.layout.Pane;

public class MixerWidget extends MasterWidget{

    Mixer mixer = new Mixer();

    public MixerWidget(String title, int height, int width, Pane mainPane) {
        super(title, height, width, mainPane);
        super.audioComponent = mixer;
        Pane mixerPane = new Pane();
       innerPane.getChildren().add(mixerPane);
       mainPane.getChildren().add(innerPane);
       innerPane.setLayoutY(300);
    }
}
