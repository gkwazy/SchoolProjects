const http = require('http');
const fs = require('fs');
const WebSocketServer = require('websocket').server;
var rooms = [];


const httpServer = http.createServer(function (req, res) {
    console.log(req.url);
    if (req.url == "/") {
        fs.readFile('./resources/index.html', function (err, data) {
            res.writeHead(200, {
                'Content-Type': 'text/html'
            });
            res.write(data);
            return res.end();
        })
    } else if (req.url == "/index.css") {
        fs.readFile('./resources/index.css', function (err, data) {
            res.writeHead(200, {
                'Content-Type': 'text/css'
            });
            res.write(data);
            return res.end();
        })
    } else if (req.url == "/FrontEnd.js") {
        fs.readFile('./resources/FrontEnd.js', function (err, data) {
            res.writeHead(200, {
                'Content-Type': 'application/javascript'
            });
            res.write(data);
            return res.end();
        })
    } else {
        res.writeHead(404, );
        res.write(data);
        return res.end();
    }
});

const websocket = new WebSocketServer({
    "httpServer": httpServer
})

websocket.on("request", request => {
    console.log("hit")
    var connection = request.accept(null, request.origin);
    connection.on("open", () => console.log("opened"));
    connection.on("close", () => console.log("closed"));
    connection.on("message", function (message) {
        try {
            json = JSON.parse(message.utf8Data)
            rooms.forEach(room => {
                if (room.connections.includes(connection)) {
                    json = JSON.stringify(json)
                    room.connections.forEach(client => {
                        client.send(json)
                    })
                }
            })

        } catch {
            parseMessage = message.utf8Data.split(" ", 2)
            console.log(message.utf8Data)
            json = {
                user: parseMessage[0],
                room: parseMessage[1]
            }
            let found = -1;
            for (let i = 0; i < rooms.length; i++) {
                if (rooms[i].room == json.room) {
                    found = i;
                }
            };

            if (found >= 0) {
                rooms[found].connections.push(connection);

            } else {
                connections = [connection]
                newRoom = {
                    connections: connections,
                    room: json.room
                }
                rooms.push(newRoom)
            }
            json = JSON.stringify(json)
            connection.send(json)
        }
    })
})


httpServer.listen(8080);