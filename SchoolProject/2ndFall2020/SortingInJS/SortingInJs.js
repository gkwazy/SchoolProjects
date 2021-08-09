/*Question 1: Test your sorting function with an array of ints, floating point numbers, 
strings, or a mix. What happens for each case?

The sorting worked mostly for all of them. the mixed was through off 
when it compaired a string and a number. For compairing strings it
word just based off the ASCII table. 

*/

let ints = [5,34,65,23,1,4,234,6,4];
let floats = [5.5,6.3,7,3.4,78.2,34.2];
let words = ["mary", "john", "phill", "albert", "Albert", "Phill"];
let mix = [5,4.3,"mary",30, "apple", 6.7];
let fullName = ["John Smith", "John Doe", "Jane Smith", "Jonny Apply", "Iron Giant"]

MySort(ints,compairInt);
MySort(floats,compairInt);
MySort(words,compairInt);
MySort(mix,compairInt);
MySort(fullName, compairNames);


console.log(ints);
console.log(floats);
console.log(words);
console.log(mix);
console.log(fullName);



function compairNames(a,b){
    a = a.toLowerCase();
    b = b.toLowerCase();

    a = a.split(" ");
    b= b.split(" ");


    if (a[1] == b[1]) {
        return a[0] < b[0];
    }else{
        return a[1]<b[1];
    }

}

function compairInt(a,b){
    isSmaller = a < b;
    return(isSmaller);
}



function MySort(a, compair){
    let tempArray = Array.from(a); 
    for(let i = 0; i < a.length; i++){
       smallest = FindMinLocation(tempArray, compair);

       a[i] = tempArray[smallest];
       tempArray.splice(smallest,1);
    }

    function FindMinLocation(b, compair){
        let minLocation = 0;
        for( let i = 1; i < b.length; i++ ){
            if (compair(b[i],b[minLocation])){
                minLocation = i;
            }
        }
        return minLocation;
    }
}

