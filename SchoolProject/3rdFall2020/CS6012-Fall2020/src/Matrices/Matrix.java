package assignment01;

import org.junit.platform.launcher.listeners.SummaryGeneratingListener;

public class Matrix {
	int numRows;
	int numColumns;
	int data[][];

	// Constructor with data for new matrix (automatically determines dimensions)
	public Matrix(int data[][]) {
		numRows = data.length; // d.length is the number of 1D arrays in the 2D array
		if (numRows == 0) {
			numColumns = 0;
		} else {
			numColumns = data[0].length; // d[0] is the first 1D array
		}
		this.data = new int[numRows][numColumns]; // create a new matrix to hold the data
		// copy the data over
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numColumns; j++) {
				this.data[i][j] = data[i][j];
			}
		}
	}

	@Override // instruct the compiler that we do indeed intend for this method to override
				// the superclass' (Object) version
	public boolean equals(Object other) {
		if (!(other instanceof Matrix)) { // make sure the Object we're comparing to is a Matrix
			return false;
		}
		Matrix matrix = (Matrix) other; // if the above was not true, we know it's safe to treat 'o' as a Matrix

		if (numColumns != matrix.numColumns) {
			return false;
		}
		if (numRows != matrix.numRows) {
			return false;
		}
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numColumns; j++) {
				if (data[i][j] != matrix.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	@Override // instruct the compiler that we do indeed intend for this method to override
				// the superclass' (Object) version
	public String toString() {

		String matrixString = null;
		if (numRows > 0 || numColumns > 0) {
			matrixString = "";
			for (int i = 0; i < numRows; i++) {
				for (int j = 0; j < numColumns; j++) {
					matrixString += data[i][j] + " ";
				}
				matrixString += "\n";
			}
		}

		return matrixString; // placeholder
	}

	public Matrix times(Matrix matrix) {
		
		if (numColumns != matrix.numRows) {
			return null;
		}else {
			Matrix newMatrix = new Matrix(new int[numRows][matrix.numColumns]);
			
			for(int i = 0; i < newMatrix.numRows; i++) {
				for(int j = 0; j < newMatrix.numColumns; j++) {
					int sum = 0;
					for(int k = 0; k < numColumns; k++) {
						sum += data[i][k] * matrix.data[k][j];
					}
					newMatrix.data[i][j] = sum;
					
					//j level
				}
				//i level
			}
			return newMatrix;
		}
	}

	public Matrix plus(Matrix matrix) {

		if (numRows != matrix.numRows || numColumns != matrix.numColumns) {
			return null;
		} else {
			Matrix newMatrix = new Matrix(new int[numRows][numColumns]);
			for (int i = 0; i < numRows; i++) {
				for (int j = 0; j < numColumns; j++) {
					newMatrix.data[i][j] = data[i][j] + matrix.data[i][j];
				}
			}
			return newMatrix;
		}
	}
}
