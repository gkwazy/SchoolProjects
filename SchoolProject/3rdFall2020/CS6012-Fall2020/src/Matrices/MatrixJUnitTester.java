/*
 * Here is a starting point for your Matrix tester. You will have to fill in the rest with
 * more code to sufficiently test your Matrix class. We will be using our own MatrixTester for grading. 
*/
package assignment01;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class MatrixJUnitTester {

  Matrix threeByTwo, twoByThree, twoByTwoResult, twoByThreeSum, twoByFour,twoByFourResult;
  /* Initialize some matrices we can play with for every test! */

  @Before
  public void setup() {
    threeByTwo = new Matrix(new int[][] { { 1, 2, 3 }, { 2, 5, 6 } });
    twoByThree = new Matrix(new int[][] { { 4, 5 }, { 3, 2 }, { 1, 1 } });
    twoByThreeSum = new Matrix(new int[][] {{8,10},{6,4},{2,2}});
    twoByFour = new Matrix(new int[][] {{5,4},{4,3},{7,6}, {8,9}}); 
    
    // this is the known correct result of multiplying M1 by M2
    twoByTwoResult = new Matrix(new int[][] { { 13, 12}, { 29, 26 } });
    twoByFourResult = new Matrix(new int[][] {{14,33,42},{7,16,21},{3,7,9}});
  }

  @Test
  public void timesWithBalancedDimensions() {
    Matrix matrixProduct = threeByTwo.times(twoByThree);
    Assert.assertTrue(twoByTwoResult.equals(matrixProduct));
    Assert.assertEquals(twoByFourResult, twoByThree.times(threeByTwo));
  }

  @Test
  public void timesWithUnbalancedDimensions() {
	  Assert.assertEquals(null, twoByFour.times(twoByThree));
	  Assert.assertEquals(null, twoByThree.times(twoByFour));
  }

  @Test
  public void twoByTwoToString() {
    String resultString = "13 12 \n29 26 \n";
    String plusString = "8 10 \n6 4 \n2 2 \n";
    Assert.assertEquals(resultString, twoByTwoResult.toString());
    Assert.assertEquals(plusString, (twoByThree.plus(twoByThree)).toString());
  }
  
  @Test
  public void isEqual() {
	  Assert.assertEquals(true, threeByTwo.equals(threeByTwo));
	  Assert.assertEquals(false, threeByTwo.equals(twoByThree));
	  Assert.assertEquals(true, twoByTwoResult.equals(twoByTwoResult));
  }
  
  @Test
  public void Sum() {
    Assert.assertEquals(true, twoByThreeSum.equals(twoByThree.plus(twoByThree)));
    Assert.assertEquals(null, twoByThree.plus(threeByTwo));
    Assert.assertEquals(2, (twoByThree.plus(twoByThree)).numColumns);
    Assert.assertEquals(3, (twoByThree.plus(twoByThree)).numRows);

  }
  
}
