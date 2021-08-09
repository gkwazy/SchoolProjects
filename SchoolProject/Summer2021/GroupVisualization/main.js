data = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]


//format for events will be { 'id1': int, id2:int action: char}
var events = [
                // { 'id1': 1,'id2':10, action: 'c'},
                // { 'id1': 1,'id2':10, action: 's'},
                // { 'id1': 2,'id2':9, action: 'c'},
                // { 'id1': 2,'id2':9, action: 's'},
                // { 'id1': 3,'id2':8, action: 'c'},
                // { 'id1': 3,'id2':8, action: 's'},
                // { 'id1': 4,'id2':7, action: 'c'},
                // { 'id1': 4,'id2':7, action: 's'},
                // { 'id1': 5,'id2':6, action: 'c'},
                // { 'id1': 5,'id2':6, action: 's'} 
                
            ]


window.onload = async function()
{
    MakeTable();   
}

function MakeTable(){
    d3.select('#canvas')
    .selectAll('rect')
    .data(data)
    .join(
        enter => {
            enter.append('rect')
                .attr('x', d=> d*50)
                .attr('width', 20)
                .attr('height', d=> data[d-1]*50)
                .attr('y', 20)
                .attr('id', d => 'rect' + data[d-1])
                .style('fill', 'blue');
        });
}

function shuffle(){
    for (var i = data.length - 1; i > 0; i--) {
        var j = Math.floor(Math.random() * (i + 1));
        var temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    d3.select('#canvas').selectAll("rect").remove()
    MakeTable()
}

async function bubbleSort(){
    disableAllButton();
    bubbleAlgo(data);
    Sort(); 
}

async function selectSort(){
    disableAllButton();
    selectAlgo(data);
    Sort(); 
}

async function selectAlgo(){
        function swap(arr,xp, yp)
        {
            var temp = arr[xp];
            arr[xp] = arr[yp];
            arr[yp] = temp;
            if ( xp != yp)
                events.push({'id1': data[xp],'id2':data[yp], action: 's'})
        }
    function selectionSort(arr,  n)
        {
            var i, j, min_idx;
            // One by one move boundary of unsorted subarray
            for (i = 0; i < n-1; i++)
            {
                // Find the minimum element in unsorted array
                min_idx = i;
                for (j = i + 1; j < n; j++){
                    events.push({'id1': data[j],'id2':data[min_idx], action: 'c'})
                    if (arr[j] < arr[min_idx])
                        min_idx = j;
                }       
                swap(arr,min_idx, i);
            }
        }
    selectionSort(data,data.length)
}



async function bubbleAlgo(){
    let len = data.length;

    if (data[0] > data[len-1]){
        for (let i = 0; i < len; i++) {
            for (let j = 0; j < len - i; j++) {
                events.push({'id1': data[j],'id2':data[j+1], action: 'c'});
                if (data[j] > data[j + 1]) {
                    let tmp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = tmp;
                    events.push({'id1': data[j],'id2':data[j+1], action: 's'})
                }
            }
        } 
    }  
    else{
        for (let i = 0; i < len; i++) {
            for (let j = 0; j < len - i; j++) {
                events.push({'id1': data[j],'id2':data[j+1], action: 'c'});
                if (data[j] < data[j + 1]) {
                    let tmp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = tmp;
                    events.push({'id1':data[j],'id2':data[j+1], action: 's'})
                }
            }
        }
    }
    return data;
}

async function Sort(){
    console.log(events)
    for(let event of events){
        let elem1 = d3.select('#rect' + event.id1)
        let elem2 = d3.select('#rect' + event.id2)

        switch (event.action){
            case 'c':
                await compairRects(elem1,elem2)
                break;
            case 's':
                await swapRects(elem1,elem2)
                break;
        }
    }
    enableAllButtons();
    console.log("done") 
    events = [];  
}

async function compairRects(elem1,elem2){
    var colorTime = 50;

    transition = await Promise.all(
        [
           elem1.transition().duration(colorTime).style('fill', 'LawnGreen').end(),
           elem2.transition().duration(colorTime).style('fill', 'LawnGreen').end() 
        ]
    )

    transition = await Promise.all(
        [
           elem1.transition().duration(colorTime).style('fill', 'blue').end(),
           elem2.transition().duration(colorTime).style('fill', 'blue').end() 
        ]
    )
}

async function swapRects(elem1, elem2){
    let position1 = getPosition(elem1);
    let position2 = getPosition(elem2);
    var durationTime = 50;
    var colortTime = 25;

    transition = await Promise.all(
        [
           elem1.transition().duration(colortTime).style('fill', 'red').end(),
           elem2.transition().duration(colortTime).style('fill', 'red').end() 
        ]
    )

    transition = await Promise.all(
        [
           elem1.transition().duration(durationTime).attr('x', position2.x).end(),
           elem2.transition().duration(durationTime).attr('x', position1.x).end()
        ]
    )

    transition = await Promise.all(
        [
           elem1.transition().duration(colortTime).style('fill', 'blue').end(),
           elem2.transition().duration(colortTime).style('fill', 'blue').end() 
        ]
    )
}

function getPosition(elem){
    let x = parseFloat(elem.attr('x'));
    let y = parseFloat(elem.attr('y'));
    return {x , y};
}

function enableAllButtons(){
    d3.select('#bubbleStart').attr("disabled", null); 
    d3.select('#shuffle').attr("disabled", null); 
    d3.select('#selectStart').attr("disabled", null); 
}

function disableAllButton(){
    d3.select('#bubbleStart').attr("disabled", true); 
    d3.select('#shuffle').attr("disabled", true);
    d3.select('#selectStart').attr("disabled", true);
    
}



