window.onload = function(){
    let yellow = document.getElementsByClassName("yellow");// yellow = {yellowEl}
    let red = document.getElementsByClassName("red"); // red = { redEl, blueEl2}

    document.addEventListener("mousemove", function(event){
        let yellow = document.getElementsByClassName("yellow");
        moveToMouse(event.clientX, event.clientY, yellow);
    })

    moveObjects();

    function moveToMouse(x,y,yellow){
        // console.log(yellow)
        yellow[0].setAttribute("cx", x);
        yellow[0].setAttribute("cy", y);
        yellow[0].setAttribute("fill", "black")
        // console.log(x + ", " + y);
    }

    function moveObjects(){
        for(let i = 0; i < red.length; i++){
            speedFactor = .001;
            let yellowX = parseFloat(yellow[0].getAttribute("cx"));
            let yellowY = parseFloat(yellow[0].getAttribute("cy"));

            // console.log(yellowX);
            // console.log(yellowY);

            let originalX = parseFloat(red[i].getAttribute("cx"));
            let originalY = parseFloat(red[i].getAttribute("cy"));

            let xVector = (yellowX - (originalX + Math.floor(Math.random() * (10))))*(speedFactor);
            let yVector = (yellowY - (originalY + Math.floor(Math.random() * (10))))*(speedFactor);

        
            newX =  originalX + xVector * Math.floor(Math.random() * (10));
            newY = originalY + yVector *  Math.floor(Math.random() * (10)); 
            red[i].setAttribute("cx", newX);
            red[i].setAttribute("cy", newY);
        } 
        
        window.requestAnimationFrame(moveObjects);       
    }




}