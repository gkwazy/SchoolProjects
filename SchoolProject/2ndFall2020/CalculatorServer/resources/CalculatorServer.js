window.onload = function(){
//     let submitBtn = document.getElementById("submitBtn"
    let url = "ws://localhost:8080";


    var serverOne = new XMLHttpRequest();
    serverOne.onreadystatechange = function(response) {
        if (this.readyState == 4 && this.status == 200) {
            console.log(response)
            document.getElementById("totalHTTP").textContent = "TheHTTP is: " + response.currentTarget.response;
        }
    };
    var form = document.getElementById("myForm");
    form.addEventListener('submit', function(e){
        e.preventDefault();
        let x = document.getElementById("xValue").value;
        let y = document.getElementById("yValue").value;
        let filename = "/calculate?x=" + x + "&y=" +y;
    serverOne.open("GET", filename, true);
    serverOne.send();
    });
    

    var mySocket = new WebSocket(url);

    // MakeCaculator(arrayOfButtons)
    var form = document.getElementById("myForm");
    form.addEventListener('submit', function(e){
        e.preventDefault();
        let x = document.getElementById("xValue").value;
        let y = document.getElementById("yValue").value;
        mySocket.send(x + " " + y);
        mySocket.onmessage =function (response){
        // console.log(response);
        document.getElementById("total").textContent = "The total is: " + response.data;
            
        }
    });
    // mySocket.onopen = function(response){
    //     mySocket.send("1 2")
    // }
    mySocket.onmessage =function (response){
        console.log(response);
    }
}







// function MakeCaculator(arrayOfButtons){
//     let container = document.getElementById("calculator");
//     for(let j = 0; j < 4; j++){
//         let smallRow = document.createElement("div");
//         smallRow.setAttribute("class", "row-sm");
//         for(let i = 1; i < 5; i++){
//             let button = document.createElement("button");
//             button.setAttribute("type", "button");
//             button.setAttribute("class", "btn btn-secondary btn-lg");
//             button.textContent = i+(j*4);
//             smallRow.appendChild(button);
//         } 
//         container.appendChild(smallRow);
//     }
      
    // }
// }