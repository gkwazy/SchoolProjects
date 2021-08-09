package assignment07;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;

public class PathFinder {

	public static void solveMaze(String inputFile, String outputFile) {
		Graph myGraph = new Graph(inputFile);
		String text = "";
		text+=(myGraph.height + " ");
		text+=(myGraph.width );
		for (int i = 0; i < myGraph.height; i++) {
			text += "\n";
			for (int j = 0; j < myGraph.width; j++) {
				text += (myGraph.nodes[i][j].mapValue);
			}
		}
		try {
			System.out.println(text);
			PrintWriter out = new PrintWriter(outputFile);
			out.println(text);
			out.close();

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public static void graftTest(String inputFile) {
		Graph myGraph = new Graph(inputFile);
		System.out.println(myGraph.height);
		System.out.println(myGraph.width);
		for (int i = 0; i < myGraph.height; i++) {
			System.out.println();
			for (int j = 0; j < myGraph.width; j++) {
				System.out.print(myGraph.nodes[i][j].mapValue);
			}
		}
	}

}
