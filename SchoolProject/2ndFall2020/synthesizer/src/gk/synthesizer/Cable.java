package gk.synthesizer;

import javafx.scene.layout.Pane;
import javafx.scene.shape.Line;

public class Cable {
    double startPositionX;
    double startPositionY;
    double endPositionX;
    double endPositionY;
    Line line;

    Cable( double startPositionX, double startPositionY, double endPositionX, double endPositionY) {
        this.startPositionX = startPositionX;
        this.startPositionY = startPositionY;
        this.endPositionX = endPositionX;
        this.endPositionY = endPositionY;
        this.line = new Line(startPositionX, startPositionY, endPositionX,endPositionY);
    }
   public void makeCable(){
       this.line = new Line(startPositionX, startPositionY, endPositionX,endPositionY);
    }

};
