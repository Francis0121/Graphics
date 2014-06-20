webgl.errorHandler = function(error, mode){
	if(!webgl.debug){
		return;
	}
	
	var span, message=error;
	switch (mode) {
	case 1:
		span = $('<span class="info"></span>');
		span.append('<span class="head">[INFO]</span>');
		break;
	case 2:
		span = $('<span class="debug"></span>');
		span.append('<span class="head">[DEBUG]</span>');
		break;
	default:
		span = $('<span class="default"></span>');
		span.append('<span class="head">[DEFAULT]</span>');
	}

	if(error.message != undefined && error.message != ''){
		message = error.message;
	}
	
	span.append(message);
	webgl.error.append(span).append('<br/>');
};
