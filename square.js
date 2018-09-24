function square(xpos,ypos){
	this.len=20
	this.xpos=xpos;
	this.ypos=ypos;
	this.hasMine=false;
	this.isPressed=false;
	this.number=0;
	this.adjacentSquares=[];

	this.display = function(){
		if(this.isPressed){
			fill(169,169,169);
			rect(this.xpos*this.len,this.ypos*this.len,this.len,this.len);
		}else{
			fill(211,211,211);
			rect(this.xpos*this.len,this.ypos*this.len,this.len,this.len);
		}
	}

	this.getAdjacentSquares = function(){
		var xstart;
		var xend;
		var ystart;
		var yend;

		if(this.xpos==0){
			xstart=this.xpos;
		}else if(this.xpos==29){
			xend=this.xpos;
		}else{
			xstart=this.xpos-1;
			xend=this.xpos+1;
		}

		if(this.ypos==0){
			ystart=this.ypos;
		}else if(this.ypos==15){
			yend=this.ypos;
		}else{
			ystart=this.ypos-1;
			yend=this.ypos+1;
		}

		for(a=xstart;a<=xend;a++){
	        for(b=ystart;b<=yend;b++){
	          if(!(a == this.xpos && b== this.ypos)){
	            this.adjacentSquares.push(a*16+b)
	          }
        	}
        }
    }
}