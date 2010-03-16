// Global vars
//++++++++++++++++++++++++++++++++++++++++//
var inputDefaults = {};
// Global methods
//++++++++++++++++++++++++++++++++++++++++//
// TOGGLE DESCRIPTION TABS
function toggleDescTabs(event){
	event.stop();
	var element = Event.element(event);
	var parent 	= element.up('form');
	if(parent.down('.desc_long')){
		parent.down('.desc').toggle();
		parent.down('.desc_long').toggle();
	}
	if(parent.down('.tabs .btn_selected')){
		parent.down('.tabs .btn_selected').removeClassName('btn_selected');
		element.addClassName('btn_selected');
	}else{
		element.update('Less info');
	}
}
// TOGGLE STORE TABS
function toggleStoreTabs(event){
	event.stop();
	var element = Event.element(event);
	var	parent	= element.up();
	var toOpen	= parent.next('.stores');
	var toClose	= parent.adjacent('.open_element').first();
	if(toOpen && !(toClose && toClose.identify() == toOpen.identify())){toggleStoreContent(toOpen, toClose)}
}
// TOGGLE STORE INFO
function toggleStoreInfo(event){
	event.stop();
	var element = Event.element(event);
	var toOpen	= $$('.'+element.identify()).first();
	var toClose	= $$('.open_element').first();
	if(toOpen && !(toClose && toClose.identify() == toOpen.identify())){toggleStoreContent(toOpen, toClose)}
}
// CLOSE STORE INFO
function closeStoreInfo(event){
	event.stop();
	var element = Event.element(event);
	var toClose = $$('.open_element').first();
	var toOpen	= $$('.open_tab').first().next('.stores');
	if(toOpen && !(toClose && toClose.identify() == toOpen.identify())){toggleStoreContent(toOpen, toClose)}
}
// TOGGLE STORE CONTENT
function toggleStoreContent(toOpen, toClose){
	if(toClose){
		toClose.hide().removeClassName('open_element')
			.previous('.tab').removeClassName('open_tab');
	}
	if(toOpen){
		Effect.BlindDown(toOpen.identify(),{duration: 0.5});
		toOpen.addClassName('open_element')
			.previous('.tab').addClassName('open_tab');
	}
}
// Window load actions
//++++++++++++++++++++++++++++++++++++++++//
Event.observe(window, 'load', function(){

	// DEFAULT INPUT BLUR
	$$('.blur').each(function(element){
		inputDefaults[element.offsetLeft+element.offsetTop] = element.value;
		Event.observe(element, 'blur', function(event){
		var element = Event.element(event);
		if(!element.value) {
			var value = inputDefaults[element.offsetLeft+element.offsetTop];
 			element.value = value;
		}
     	});
     });
	// DEFAULT INPUT FOCUS
	$$('.focus').each(function(element){
		inputDefaults[element.offsetLeft+element.offsetTop] = element.value;
		Event.observe(element, 'focus', function(event){
			var element = Event.element(event);
			var value = inputDefaults[element.offsetLeft+element.offsetTop];
			if(element.value == value){element.value = ''}
		});
	});
	// COLECTION ROLLOVERS
	$$('div.collection').each(function(element){
		Event.observe(element, 'mouseover', function(event){element.down('.fader').removeClassName('invisible')});
	});
	$$('div.collection').each(function(element){
		Event.observe(element, 'mouseout', function(event){element.down('.fader').addClassName('invisible')});
	});
	// COLECTION VERTICAL TEXT
	$$('div.collection div.inner_text span.heading').each(function(element){
		var height 			= element.getHeight();
		var thumbHeight 	= element.up('.collection').getHeight();
		var marginTop		= (thumbHeight-height)/2;
		element.setStyle({marginTop: marginTop+'px'});
	});
	// TOGGLE PRODUCT DETAIL TABS
	$$('.btn_detail').each(function(element){Event.observe(element, 'click', toggleDescTabs)});
	$$('.btn_product').each(function(element){Event.observe(element, 'click', toggleDescTabs)});
	$$('.more_info').each(function(element){Event.observe(element, 'click', toggleDescTabs)});
 	// STORE LOCATOR
	$$('.main_switch').each(function(element){Event.observe(element, 'click', toggleStoreTabs)});
	$$('.open_more').each(function(element){Event.observe(element, 'click', toggleStoreInfo)});
	$$('.btn_close_window_text').each(function(element){Event.observe(element, 'click', closeStoreInfo)});
	// GIFTFINDER
	$$('#gift_finder_form select').each(function(element){Event.observe(element, 'change', function(event){window.location.href=Event.element(event).value})});
	$$('#gift_finder_form').each(function(element){
		Event.observe(element, 'submit', function(event){
			event.stop();
			var form 	= Event.element(event);
			var sep 	= (window.location.href.match(/\?/)) ? '&' : '?';
			window.location.href = window.location.href+sep+'show_products=1';
		});
	});
 });
