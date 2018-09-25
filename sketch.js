
const NUM_DOTS = 80;
const LINK_THRESHOLD = 200;
const mineCount=99;

var minefield = [];
var mines=[];
var gameOver=false;
function setup() {
  createCanvas(windowWidth, windowHeight);
  for(var i=0;i<30;i++){
    for(var j=0;j<16;j++){
      minefield.push(new square(i,j));
    }
  }
  mines=getRandom(minefield,mineCount);
  for(var i=0;i<mines.length;i++){
    minefield[mines[i]].hasMine=true;
  }
  for (var i=0;i<minefield.length;i++){
    // if(minefield[i].hasMine){
    //   console.log("this has a mine");
    // }else{
    //   console.log("this doesn't have a mine")
    // }
    if(!minefield[i].hasMine){
      minefield[i].getAdjacentSquares();
      minefield[i].number=getMineNumber(minefield[i].adjacentSquares);
      console.log(minefield[i].number);
    }
  }
}
function draw() {
  background(30);
  fill(211,211,211);
  for (var i=0;i<minefield.length;i++){
    minefield[i].display();
    if(gameOver){
      minefield[i].displayGameOver();
    }
  }

}


function mousePressed(){
  if(!gameOver){
    for (var i=0;i<minefield.length;i++){
      if(mouseX>=minefield[i].startingX+minefield[i].xpos*minefield[i].len && mouseX<=minefield[i].startingX+minefield[i].xpos*minefield[i].len+minefield[i].len && mouseY>=minefield[i].startingY+minefield[i].ypos*minefield[i].len && mouseY<=minefield[i].startingY+minefield[i].ypos*minefield[i].len+minefield[i].len){
        if(mouseButton === LEFT){
          if(!minefield[i].hasFlag){
            clicked(i);
            if(minefield[i].hasMine){
              gameOver=true;
            }
          }
        }else{
          minefield[i].hasFlag=!minefield[i].hasFlag;
        }
      }
    }
  }
}


function getRandom(arr, n) {
    var result = new Array(n),
      len = arr.length,
      taken = new Array(len);
    if (n > len){
      throw new RangeError("getRandom: more elements taken than available");
    }
    while (n--) {
      var x = Math.floor(Math.random() * len);
      result[n] = x in taken ? taken[x] : x; //if x index is not already taken, use x
      taken[x] = --len in taken ? taken[len] : len; //record the end to the index. Therefore if x is already taken, use the last of the index
    }
    return result;
}

function getMineNumber(arr) {
  count=0;
  for (var a=0; a<arr.length; a++){
    if(minefield[arr[a]].hasMine){
      count++;
    }
  }
  return count
}

function clicked(index) {
  minefield[index].isPressed=true;
  console.log("entered the next click");
  if(minefield[index].number == 0){
    console.log(index);
    for(var i=0;i<minefield[index].adjacentSquares.length;i++){
      if(!minefield[minefield[index].adjacentSquares[i]].isPressed){
        clicked(minefield[index].adjacentSquares[i]);
      }
    }
  }
}