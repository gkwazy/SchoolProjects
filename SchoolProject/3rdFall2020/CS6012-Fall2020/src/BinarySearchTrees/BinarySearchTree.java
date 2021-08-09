package assignment05;

import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collection;
import java.util.NoSuchElementException;

public class BinarySearchTree<T extends Comparable<? super T>> implements SortedSet<T> {
	private Node rootNode;
	int size;

	public BinarySearchTree() {
		rootNode = null;
		size = 0;
	}

	private class Node {
		T data;
		Node left = null;
		Node right = null;
	}

	// Driver method
	// Generates a .dot file representing this tree.
	// Use each node's hashCode to uniquely identify it
	public void writeDot(String filename) {
		try {
			PrintWriter output = new PrintWriter(new FileWriter(filename));
			output.println("graph g {");
			if (rootNode != null)
				output.println(rootNode.hashCode() + "[label=\"" + rootNode.data + "\"]");
			writeDotRecursive(rootNode, output);
			output.println("}");
			output.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	// Recursively traverse the tree, outputting each node to the .dot file
	private void writeDotRecursive(Node n, PrintWriter output) throws Exception {
		if (n == null)
			return;
		if (n.left != null) {
			output.println(n.left.hashCode() + "[label=\"" + n.left.data + "\"]");
			output.println(n.hashCode() + " -- " + n.left.hashCode());
		}
		if (n.right != null) {
			output.println(n.right.hashCode() + "[label=\"" + n.right.data + "\"]");
			output.println(n.hashCode() + " -- " + n.right.hashCode());
		}

		writeDotRecursive(n.left, output);
		writeDotRecursive(n.right, output);
	}

	private Node findLocationAdd(Node parent, Node newItem) {
		int compared = parent.data.compareTo(newItem.data);
		if (compared > 0) {
			if (parent.left == null) {
				return parent;
			} else {
				return findLocationAdd(parent.left, newItem);
			}
		} else {
			if (parent.right == null) {
				return parent;
			} else {
				return findLocationAdd(parent.right, newItem);
			}
		}
	}

	private Node findLocationContains(Node parent, Node newItem) {
		int compared = parent.data.compareTo(newItem.data);
		if (compared == 0) {
			return parent;
		}
		if (compared > 0) {
			if (parent.left == null) {
				return parent;
			} else {
				return findLocationContains(parent.left, newItem);
			}
		} else {
			if (parent.right == null) {
				return parent;
			} else {
				return findLocationContains(parent.right, newItem);
			}
		}
	}

	private Node findLocationDeleteParent(Node parent, T wanted) {
		Node tempNode = parent;
		if (tempNode.left != null) {
			if (wanted.compareTo(tempNode.left.data) == 0) {
				return tempNode;
			}
		}
		if (tempNode.right != null) {
			if (wanted.compareTo(tempNode.right.data) == 0) {
				return tempNode;
			}
		}
		if (wanted.compareTo(tempNode.data) < 0) {
			return findLocationDeleteParent(tempNode.left, wanted);
		}
		if (wanted.compareTo(tempNode.data) > 0) {
			return findLocationDeleteParent(tempNode.right, wanted);
		}
		return null;
	}

	private void addToArrayList(ArrayList<T> list, Node node) {
		if (node == null) {
			return;
		}
		addToArrayList(list, node.left);
		list.add(node.data);
		addToArrayList(list, node.right);
	}

	@Override
	public boolean add(T item) {
		try {
			if (item == null) {
				throw new NullPointerException("values passed of null");
			}
			Node tempNode = new Node();
			tempNode.data = item;
			if (rootNode == null) {
				rootNode = tempNode;
				size++;
				return true;
			} else {
				Node neededNode = findLocationAdd(rootNode, tempNode);
				if (neededNode.data.compareTo(tempNode.data) > 0) {
					neededNode.left = tempNode;
					size++;
					return true;
				} else
					neededNode.right = tempNode;
				size++;
				return true;
			}

		} catch (NullPointerException e) {
			System.out.println(e);
			throw e;
		}
	}

	@Override
	public boolean addAll(Collection<? extends T> items) {
		try {
			for (T info : items) {
				if (info == null) {
					throw new NullPointerException("values passed of null");
				}
				add(info);
			}
			return true;
		} catch (NullPointerException e) {
			System.out.println(e);
			throw e;
		}
	}

	@Override
	public void clear() {
		rootNode = null;
		size = 0;

	}

	@Override
	public boolean contains(T item) {
		try {
			if (item == null) {
				throw new NullPointerException("values passed of null");
			}
			if (rootNode == null) {
				return false;
			} else {
				Node tempNode = new Node();
				tempNode.data = item;
				tempNode = findLocationContains(rootNode, tempNode);
				if (tempNode.data.compareTo(item)==0) {
					return true;
				} else {
					return false;
				}
			}
		} catch (NullPointerException e) {
			System.out.println(e);
			throw e;
		}
	}

	@Override
	public boolean containsAll(Collection<? extends T> items) {
		try {
			boolean isThere = true;
			for (T info : items) {
				if (info == null) {
					throw new NullPointerException("values passed of null");
				}
				if (!contains(info)) {
					isThere = false;
				}
			}
			return isThere;
		} catch (NullPointerException e) {
			System.out.println(e);
			throw e;
		}
	}

	@Override
	public T first() throws NoSuchElementException {
		try {
			if (rootNode == null) {
				throw new NoSuchElementException("No elements");
			}
			Node tempNode = new Node();
			tempNode = rootNode;
			while (tempNode.left != null) {
				tempNode = tempNode.left;
			}
			return tempNode.data;

		} catch (NoSuchElementException e) {
			throw e;
		}
	}

	@Override
	public boolean isEmpty() {
		if (rootNode != null) {
			return false;
		}
		return true;
	}

	@Override
	public T last() throws NoSuchElementException {
		try {
			if (rootNode == null) {
				throw new NoSuchElementException("No elements");
			}
			Node tempNode = new Node();
			tempNode = rootNode;
			while (tempNode.right != null) {
				tempNode = tempNode.right;
			}
			return tempNode.data;

		} catch (NoSuchElementException e) {
			throw e;
		}
	}

	@Override
	public boolean remove(T item) {
		Node wantedNode;
		Node parentNode;
		boolean isLeftOfParent = false;
//root node is deleted;
		if (rootNode.data == item) {
			Node subParentNode = rootNode;
			Node smallNode = rootNode.right;
			while (smallNode.left != null) {
				subParentNode = smallNode;
				smallNode = smallNode.left;
			}
			subParentNode.left = null;
			rootNode.data = smallNode.data;
			size--;
		}
		parentNode = findLocationDeleteParent(rootNode, item);
		if (parentNode == null) {
			return false;
		}

		if (item.compareTo(parentNode.left.data) == 0) {
			wantedNode = parentNode.left;
			isLeftOfParent = true;
		} else {
			wantedNode = parentNode.right;
		}
//first case, wanted node is a leaf node. 		
		if (wantedNode.left == null && wantedNode.right == null) {
			if (isLeftOfParent) {
				parentNode.left = null;
			} else {
				parentNode.right = null;
			}
			size--;
		}

// third case, wanted node has two child
		else if (wantedNode.left != null && wantedNode.right != null) {
			Node subParentNode = wantedNode;
			Node smallNode = wantedNode.right;
			while (smallNode.left != null) {
				subParentNode = smallNode;
				smallNode = smallNode.left;
			}
			T temp = smallNode.data;
			remove(smallNode.data);
			wantedNode.data = temp;
			
		}
//second case, wanted node has one child;
		else {
			if (isLeftOfParent) {
				parentNode.left = parentNode.left.left;
			} else {
				if(parentNode.right.left!=null)
				parentNode.right = parentNode.right.left;
				parentNode.right = parentNode.right.right;
			}
			size--;
		}
		return true;
	}

	@Override
	public boolean removeAll(Collection<? extends T> items) {
		try {
			for (T info : items) {
				remove(info);
			}
			return true;
		} catch (Exception e) {

			return false;
		}
		
	}

	@Override
	public int size() {
		return size;
	}

	@Override
	public ArrayList<T> toArrayList() {
		ArrayList tempArray = new ArrayList<T>();
		addToArrayList(tempArray, rootNode);
		return tempArray;
	}

}
