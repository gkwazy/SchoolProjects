package assignment07;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.text.Normalizer.Form;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Graph {
	int height;
	int width;
	Node nodes[][];
	Node start;
	Node goal;
	ArrayList<Node> finalPath = new ArrayList<Node>();

	public Graph(String inputFile) {
		File testFile = new File("");
		String currentPath = testFile.getAbsolutePath();
		inputFile = currentPath + inputFile;
		try {
			File myFile = new File(inputFile);
			Scanner myScanner = new Scanner(myFile);
			String[] dimensions = myScanner.nextLine().split(" ");
			height = Integer.parseInt(dimensions[0]);
			width = Integer.parseInt(dimensions[1]);
			nodes = new Node[height][width];

			for (int r = 0; r < height; r++) {
				String nextLine[] = myScanner.nextLine().split("");
				for (int c = 0; c < width; c++) {
					if (nextLine[c].equals("X")) {
						Node tempNode = new Node('X', r, c);
						nodes[r][c] = tempNode;
					} else if (nextLine[c].equals("S")) {
						Node tempNode = new Node('S', r, c);
						start = tempNode;
						nodes[r][c] = tempNode;
					} else if (nextLine[c].equals("G")) {
						Node tempNode = new Node('G', r, c);
						goal = tempNode;
						nodes[r][c] = tempNode;
					} else {
						Node tempNode = new Node(' ', r, c);

						nodes[r][c] = tempNode;
					}
				}

			}
			for (int r = 0; r < height; r++) {
				for (int c = 0; c < width; c++) {
					getNodeNeighbors(nodes[r][c]);
				}
			}
			findPath(start, goal);

		} catch (Exception e) {
			System.out.println(e);
		}
	}

	public void findPath(Node start, Node goal) {
		Queue queue = new LinkedList<Node>();
		start.visited = true;
		queue.add(start);
		
		while (!queue.isEmpty()) {
			Node current = (Node) queue.remove();
			if (current.equals(goal)) {
				Node tempNode = goal;
				while(tempNode.cameFrom != start) {
					finalPath.add(tempNode.cameFrom);
					(tempNode.cameFrom).mapValue = '.';
					tempNode = tempNode.cameFrom;
				}
				return;
			}
			for(Node node: current.neighbors) {
				if (!node.visited) {
					node.visited = true;
					node.cameFrom = current;
					queue.add(node);
				}
			}
		}
	}

	private void getNodeNeighbors(Node node) {

		// checking the North node if open path.
		if (node.row + 1 < height) {
			if (nodes[(node.row) + 1][node.col].mapValue != 'X') {
				node.neighbors.add(nodes[(node.row) + 1][node.col]);
			}
		}
		// checking the South node if open
		if (node.row - 1 >= 0) {
			if (nodes[(node.row) - 1][node.col].mapValue != 'X') {
				node.neighbors.add(nodes[(node.row) - 1][node.col]);
			}
		}
		// checking the East node if open
		if (node.col + 1 < width) {
			if (nodes[node.row][(node.col) + 1].mapValue != 'X') {
				node.neighbors.add(nodes[node.row][(node.col)+1]);
			}
		}
		// checking the West node if open
		if (node.col - 1 >= 0) {
			if (nodes[node.row][(node.col) - 1].mapValue != 'X') {
				node.neighbors.add(nodes[node.row][(node.col)-1]);
			}
		}

	}

}
