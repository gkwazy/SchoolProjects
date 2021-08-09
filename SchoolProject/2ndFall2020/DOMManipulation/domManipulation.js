function Header(){
    let newDiv = document.createElement('div');
    let newDivText = document.createElement("h1");
    newDivText.innerText = "Hello there";
    newDiv.appendChild(newDivText);
    document.body.appendChild(newDiv);
}

function MyIntro(){

    let firstDiv = document.createElement('div');
    let firstH1 = document.createElement("h1");
    firstH1.innerText = "Well to start my name is Garret W.";
    firstDiv.appendChild(firstH1);
    document.body.appendChild(firstDiv);

    let secondDiv = document.createElement('div');
    let firstP = document.createElement('p');
    secondDiv.appendChild(firstP);
    firstP.innerText =" This page is made mostly for a project, it was made just using the terminal. This is not my perferred method but it help me lear\nHere is a list of things I like to do when I am not learning at school";
    document.body.appendChild(secondDiv);

    let thirdDiv = document.createElement("div");
    let img = document.createElement('img');
    thirdDiv.appendChild(img);
    img.src =  "https://www.zarias.com/wp-content/uploads/2015/12/61-cute-puppies.jpg";
    document.body.appendChild(thirdDiv);
}

Header();
MyIntro();


