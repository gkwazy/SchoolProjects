document.writeln("hello world");
console.log("hello world");
// the difference is where the elements are being printed to. The writeln is being printed in the
// HTML and the console.log is in the console where is it not involed in the HTML diretcly.

const cats = {};
const dogs = {};

var funStuff = ["hello there", "bold one", "the force is strin with with one", true, 19, 2.3, cats]; 
console.log(funStuff);
funStuff[1]= "vader hater"
funStuff.push(dogs)
console.log(funStuff);

/* question 2:
for the reason that the print lines in the console is the same. the dom is first changed then the console
is printed. so at times the consoles command will go through last. so when both line 10 and 13 and printed the 
array as already been updated and you cant see the old array any more.  
*/

function addThisUp(a,b){
    return a + b; 
}

let myFunction = function (a, b) {
    return a + b;       
};


/*Question 3 
for most of the tiem i perfer to write it like c++. this is mostly because you most
different languages you can write it like that and then I dont have to changes habits

The differents in the ways they are made is how you can call them. you cant hoist
literal functions 
*/