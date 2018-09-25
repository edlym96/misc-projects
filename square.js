function square(xpos,ypos){
	this.len=20
	this.xpos=xpos;
	this.ypos=ypos;
	this.hasMine=false;
	this.isPressed=false;
	this.number=0;
	this.adjacentSquares=[];
	this.hasFlag=false

	this.display = function(){
		if(this.isPressed){
			if(!this.hasMine){
				fill(169,169,169);
				rect(this.xpos*this.len,this.ypos*this.len,this.len,this.len);
				fill(0, 102, 153);
				textSize(14);
				text(this.number, this.xpos*this.len+this.len/3, this.ypos*this.len+2*this.len/3);
			}else{
				fill(237,41,57);
				rect(this.xpos*this.len,this.ypos*this.len,this.len,this.len);
				fill(50,50,50);
				ellipse(this.xpos*this.len+this.len/2,this.ypos*this.len+this.len/2, this.len/2,this.len/2)
			}
		}else{
			fill(211,211,211);
			rect(this.xpos*this.len,this.ypos*this.len,this.len,this.len);
			if(this.hasFlag){
				textSize(14);
				fill(237,41,57)
				text("!", this.xpos*this.len+this.len/3, this.ypos*this.len+2*this.len/3);
			}
		}
	}

	this.getAdjacentSquares = function(){
		var xstart;
		var xend;
		var ystart;
		var yend;

		if(this.xpos==0){
			xstart=this.xpos;
			xend=this.xpos+1;
		}else if(this.xpos==29){
			xstart=this.xpos-1;
			xend=this.xpos;
		}else{
			xstart=this.xpos-1;
			xend=this.xpos+1;
		}

		if(this.ypos==0){
			ystart=this.ypos;
			yend=this.ypos+1;
		}else if(this.ypos==15){
			ystart=this.ypos-1;
			yend=this.ypos;
		}else{
			ystart=this.ypos-1;
			yend=this.ypos+1;
		}
		for(a=xstart;a<=xend;a++){
	        for(b=ystart;b<=yend;b++){
	          if(!(a == this.xpos && b== this.ypos)){
	            this.adjacentSquares.push(a*16+b);
	          }
        	}
        }
    }
}