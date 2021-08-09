
// let table = document.getElementsByClassName("table");
window.onload = function(){
    tableArray = [];
    colorArray = ["red","orange","yellow","green","blue","purple","purple", "blue","green","yellow","orange","red"]
    colorNum = 0;
    buildTable();
    window.setInterval(function(){
        document.body.style.backgroundColor = colorArray[colorNum];
        colorNum = colorNum + 1;
        console.log(colorNum);
        if (colorNum == colorArray.length){
            colorNum = 0;
        }
    },100)
}

function buildTable(){
    let tableDiv = document.getElementById('table');
    let table = document.createElement("table")
    for(let i = 1; i<=10;i++){
        let tableRow = document.createElement("tr");
        for(let j = 1; j<=10; j++){
            let tableBlock = document.createElement("td")
            tableArray.push(tableBlock)
            tableBlock.setAttribute("clicked", false);
            tableBlock.setAttribute("highlighted",false);
            tableBlock.addEventListener("click", function(){
                tableArray.forEach(element => {
                element.setAttribute("clicked", false);
                });
                tableBlock.setAttribute("clicked", true)
            });
            tableBlock.addEventListener("mouseover", function(){
                console.log("hover");
                tableArray.forEach(element => {
                    element.setAttribute("highlighted", false);
                    tableBlock.setAttribute("highlighted", true);
                    });
            });
            tableBlock.textContent = j*i;
            tableRow.appendChild(tableBlock);
        }
        table.appendChild(tableRow);
    }
    tableDiv.appendChild(table);
}
