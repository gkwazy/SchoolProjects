package gk.synthesizer;

import javafx.geometry.Bounds;
import javafx.geometry.Point2D;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class MasterWidget extends Node {
    String title;
    int width;
    int height;
    AudioComponent audioComponent;
    BorderPane innerPane = new BorderPane();
    boolean beingMoved;
    Circle input;
    Circle output;

    public MasterWidget(String title, int height, int width, Pane mainPane) {
        this.title = title;
        this.width = width;
        this.height = height;
        Label labelTitle = new Label(title);

        innerPane.setStyle("-fx-background-color: white; -fx-border-color:red");
        innerPane.setPrefSize(this.width, this.height);
        innerPane.setMaxSize(this.width, this.height);
        innerPane.setTop(new Label(title));
        HBox circlesPane = new HBox();
        circlesPane.setSpacing(30);

        input = new Circle(20,Color.PURPLE);
        input.setStyle("-fx-background-color: purple");
        circlesPane.getChildren().add(input);

        output = (new Circle(20, Color.ORANGE));
        output.setStyle("-fx-background-color: orange");
        circlesPane.getChildren().add(output);

        innerPane.setBottom(circlesPane);

        innerPane.setOnMouseClicked(event ->{
            beingMoved = true;

        });

        innerPane.setOnMouseDragged(event ->{
            if(beingMoved == true){
                innerPane.setLayoutX(event.getSceneX());
                innerPane.setLayoutY(event.getSceneY());
            }
        });

        innerPane.setOnMouseReleased(event->{
            beingMoved = false;
        });
    }

    public boolean getInputBounds(Point2D point){
        return input.contains(input.sceneToLocal(point));
    }

    public boolean getOutputBounds(Point2D point){
        return output.contains(output.sceneToLocal(point));
    }

    public BorderPane getPane() {
        return innerPane;
    }

    public void setInnerPane(BorderPane innerPane) {
        this.innerPane = innerPane;
    }

   public Point2D getInputPosition(){
       Point2D point = new Point2D(input.getCenterX(), input.getCenterY());
       point = input.localToScene(point);
       return point;
   }

    public Point2D getOutputPosition(){
        Point2D point = new Point2D(output.getCenterX(), output.getCenterY());
        point = output.localToScene(point);
        return point;
    }

}
