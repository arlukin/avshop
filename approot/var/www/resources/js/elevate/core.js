Validation.add('validate-alphaspace', 'Please use letters and spaces only (a-z or A-Z) in this field.', function (v) {
	return Validation.get('IsEmpty').test(v) || /^[a-zA-Z ]+$/.test(v)
 });