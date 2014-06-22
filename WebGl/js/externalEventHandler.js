/**
 * External Event 
 */
webgl.externalEvent = function(){

	$('body').bind('mouseup', function(){
		if(webgl.attribute.dragging){
			webgl.attribute.dragging = false;
			webgl.errorHandler('Mouse point canvas out', 2);
		}
	});
	
	$('button#mix').bind('click', function(){
		webgl.makeRandTexIndex();
	});
	
	$('select#intrinsic').bind('change', function(){
		webgl.attribute.intrinsic = $(this).val();
	});
	
	$('select#texture').bind('change', function(){
		texture.initTexture();
	});
	
	$('button#speedUp1').bind('click', function(){
		webgl.attribute.fSpeed1 += 0.001;
		$('input#floatingSpeed1').val(webgl.attribute.fSpeed1);
	});
	
	$('button#speedDown1').bind('click', function(){
		webgl.attribute.fSpeed1 -= 0.001;
		$('input#floatingSpeed1').val(webgl.attribute.fSpeed1);
	});
	
	$('button#speedUp2').bind('click', function(){
		webgl.attribute.fSpeed2 += 0.001;
		$('input#floatingSpeed2').val(webgl.attribute.fSpeed2);
	});
	
	$('button#speedDown2').bind('click', function(){
		webgl.attribute.fSpeed2 -= 0.001;
		$('input#floatingSpeed2').val(webgl.attribute.fSpeed2);
	});
	
	$('button#motionRateUp').bind('click', function(){
		webgl.attribute.motionRate += 0.001;
		$('input#motionRate').val(webgl.attribute.motionRate);
	});
	
	$('button#motionRateDown').bind('click', function(){
		webgl.attribute.motionRate -= 0.001;
		$('input#motionRate').val(webgl.attribute.motionRate);
	});
};
