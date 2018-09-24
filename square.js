function square(xpos,ypos){
	this.xpos=xpos;
	this.ypos=ypos;
	this.hasMine=false;
	this.isPressed=false;
	this.number=0;
	this.adjacentSquares=[];

	this.getAdjacentSquares = function(){
		for(a=this.xpos-1;a<=this.xpos+1;a++){
	        for(b=this.ypos-1;b<=this.ypos+1;b++){
	          if(!(a == this.xpos && b== this.ypos)){
	          	if(a*16+b>=0 && a*16+b<=479){
	            	this.adjacentSquares.push(a*16+b)
	            }
	          }
        	}
        }
    }
}
