var chatSocket;
var userName;
window.onload = function () {
    console.log("working");
    let url = "ws://" + location.host +"/chat";
    let form = document.getElementById("myForm");
    let connectedToChat = false;
    var room;
    var messageButton;
    chatSocket = new WebSocket(url);
    console.log(url);

    form.addEventListener('submit', function (e) {
        e.preventDefault();
        console.log("submit")
        userName = document.getElementById("userNameInput").value;
        room = document.getElementById("roomInput").value;
        chatSocket.send("join " + room);
        chatSocket.onerror = function (response) {
            let myDiv = document.getElementById("mainDiv");
            myDiv.innerHTML = "error";};
        form = document.getElementById("messageForm");
    });


    chatSocket.onmessage = function (response) {
        console.log(response);
        console.log("connected?")
        console.log(connectedToChat);
        if (connectedToChat == false) {
            console.log("ops")
            connectedToChat = true;
            buildChatRoom(room);
        } else {
            addToChatString(response);
        }
    }
}

function buildChatRoom(room) {
    document.body.innerHTML = '<div class="jumbotron jumbotron-fluid">' +
        '<div class="container text-center">' +
        '<h13 class="display-4">Welcome to the room: ' + room + '</h3>' +
        '</div>' +
        '</div>' +
        '<div id="newMainDiv" class="container-fluid">' +
        '</div>';


    let newDiv = document.createElement('div');

    let newDivString = "";
    // '<div class="card mx-auto myCards">' +
    //     '<div class="card" style="width: w-75;">' +
    //     '<div class="card-body">' +
    //     '<h6 class="card-subtitle mb-1 text-muted">Card subtitle</h6>' +
    //     '<p class="card-text">Some quick example text to build on the card title and make up the bulk of the cards content.</p>' +
    //     '</div>' +
    //     '</div>';

    let inputDivString = '<div id="inputDiv" class="container-fluid"> ' +
        '<div id="inputCard" class="card" style="width: width: w-75;">' +
        '<div class="card-body">' +
        '<div>' +
        '<form id=messageForm>' +
        '<div class="form-group">' +
        '<input type="text" class="form-control" id="roomInput" placeholder="Enter Message">' +
        '</div>' +
        '<button type="submit" id = "messageButton" class="btn btn-primary float-right">Submit</button>' +
        '</form>' +
        ' </div>' +
        '</div>' +
        '</div>' +
        '</div>';

    let inputDiv = document.createElement("div");
    let myDiv = document.getElementById("newMainDiv");
    newDiv.innerHTML = newDivString;
    myDiv.appendChild(newDiv);
    inputDiv.innerHTML = inputDivString;
    document.body.appendChild(inputDiv);
    messageButton = document.getElementById("messageButton");

    messageForm.addEventListener('submit', function (e) {
        e.preventDefault();
        let inputMessage = document.getElementById("roomInput").value;
        chatSocket.send( userName + " " + inputMessage);
        document.getElementById("roomInput").value = "";
    })
}

function addToChatString(response) {
    console.log("parseing")
    // console.log(response.data);
    var parseReponse = JSON.parse(response.data);
    // var parseReponse = (response.data).split(" ", 2);

    let newDiv = document.createElement('div');
    let newDivString = '<div class="card mx-auto myCards">' +
        '<div class="card" style="width: w-75;">' +
        '<div class="card-body">' +
        '<h6 class="card-subtitle mb-1 text-muted">' + parseReponse.user + '</h6>' +
        '<p class="card-text">' + parseReponse.message + '</p>' +
        '</div>' +
        '</div>';
    let myDiv = document.getElementById("newMainDiv");
    newDiv.innerHTML = newDivString;
    myDiv.appendChild(newDiv);
}