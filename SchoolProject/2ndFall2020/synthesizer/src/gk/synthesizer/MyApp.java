package gk.synthesizer;

import javafx.geometry.Bounds;
import javafx.geometry.Point2D;
import org.reflections.Reflections;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import java.util.ArrayList;
import java.util.EventListener;

public class MyApp extends Application {
    boolean makingCable = false;
    boolean movingPanel = false;
    int cableStartWidget =0;

    public static void main(String[] args) {
        launch(args);
    }
    @Override
    public void start(Stage primaryStage) throws Exception {

        ArrayList<MasterWidget> widgetList = new ArrayList();
        ArrayList<AudioButton> buttonArrayList = new ArrayList();
        ArrayList<Cable> cableList = new ArrayList();
        Clip mainClip = AudioSystem.getClip();
        AudioFormat format16 = new AudioFormat(44100, 16, 1, true, false);
        BorderPane borderPane = new BorderPane();
        Pane mainPane = new Pane();

        Scene scene = new Scene(borderPane, 800, 800);
        StackPane bottomPane = new StackPane();
        Button playBtn = new Button();

        Pane buttonPane = new Pane();

        MixerWidget mixerWidget = new MixerWidget("Speaker", 100, 100, mainPane);
        widgetList.add(mixerWidget);

        Button volumeBtn = new Button("Volume");
        volumeBtn.setOnAction(event->{
            VolumeWidget volumeWidget = new VolumeWidget("Volume",100,300, mainPane);
            widgetList.add(volumeWidget);
        });

        Button sineWaveBtn = new Button("SineWave");
        sineWaveBtn.setOnAction(event->{
            SineWaveWidget sineWaveWidget = new SineWaveWidget("Sine Wave", 100, 300, mainPane);
            widgetList.add(sineWaveWidget);
        });

        //Failed cant get the reflections to find my annotated lines so the for loop has nothing to loop through.
        //switched to plan B.
//        Reflections reflections = new Reflections("gk.synthesizer");
//        var test =reflections.getTypesAnnotatedWith(gk.synthesizer.annotations.MasterWidget.class);
//        for(var t: reflections.getTypesAnnotatedWith(gk.synthesizer.annotations.MasterWidget.class)){
//            Button button = new Button(t.getSimpleName());
//            button.setOnAction(actionEvent ->{
//               try{
//                    widgetList.add(new SineWaveWidget( "Sine Wave", 100, 300, mainPane));
//               }catch(Exception e){
//                   e.printStackTrace();
//                }
//            });
//            buttonPane.getChildren().add(button);
//        }
        mainPane.setOnMouseClicked(event->{
            Point2D point = new Point2D(event.getX(), event.getY());
            for(int i = 0; i< widgetList.size(); i++){
                if (widgetList.get(i).getOutputBounds(point)){
                    if (!makingCable){
                        makingCable = true;
                        cableStartWidget = i;
                    }
                    continue;
                }
                if(widgetList.get(i).getInputBounds(point)){
                    if(makingCable){
                        Point2D test1 = widgetList.get(i).getInputPosition();
                        double test1x = test1.getX();
                        double test1y = test1.getY();
                        Point2D test2 = widgetList.get(cableStartWidget).getOutputPosition();
                        double test2x = test2.getX();
                        double test2y = test2.getY();
                        for(Cable c : cableList) {
                        mainPane.getChildren().remove(c.line);
                        }
                        makingCable = false;
                        cableList.add(new Cable(test1x,test1y,test2x, test2y));

                        widgetList.get(i).audioComponent.connectInput(widgetList.get(cableStartWidget).audioComponent);

                        for(Cable c : cableList){
                            mainPane.getChildren().add(c.line);
                        }

                    }
                }
            }
        });

        buttonPane.getChildren().addAll(volumeBtn,sineWaveBtn);
        sineWaveBtn.setTranslateY(50);
        borderPane.setRight(buttonPane);
        primaryStage.setTitle("Synthesizer");

        borderPane.setBottom(bottomPane);
        borderPane.setCenter(mainPane);
        borderPane.setRight(buttonPane);
        borderPane.setStyle("-fx-background-color: blue");
        buttonPane.setStyle("-fx-background-color: green");

        bottomPane.getChildren().add(playBtn);
        bottomPane.setStyle("-fx-background-color: yellow");

        playBtn.setText("Play Button");

        playBtn.setOnAction(eh ->{

            AudioClip clip = mixerWidget.mixer.getClip();
            try {
                if (mainClip.isOpen()){
                    mainClip.close();
                }
                mainClip.open(format16, clip.getData(), 0, clip.getData().length); //reads data from my byte array to play it
                mainClip.start(); //plays it
                mainClip.loop(2); //plays it 2 more times if desired, so 3 seconds total

            }catch (LineUnavailableException e) {
                e.printStackTrace();
            }

            });

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
