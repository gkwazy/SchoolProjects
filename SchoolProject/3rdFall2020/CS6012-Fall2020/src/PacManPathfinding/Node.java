package assignment07;

import java.util.ArrayList;

public class Node {
	char mapValue = 'Q';
	Node cameFrom;
	int row = 0;
	int col = 0;
	boolean visited;
	ArrayList<Node> neighbors = new ArrayList<Node>();
	
	public Node(char value, int height, int width) {
		this.mapValue = value;
		this.row = height;
		this.col = width;
		this.cameFrom = null;
		visited = false;
		
		
	}
}
