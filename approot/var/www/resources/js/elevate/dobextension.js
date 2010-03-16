var ElevateDob = Class.create(Varien.DOB, {
	validate: function()
	{
		var error = false;

		if (this.day.value=='' && this.month.value=='' && this.year.value=='') {
			if (this.required) {
				error = 'This date is a required value.';
			} else {
				this.dob.value = '';
			}
		} else if (this.day.value=='' || this.month.value=='' || this.year.value=='') {
			error = 'Please enter a valid full date.';
		} else {
			var date = new Date();
			if (this.day.value<1 || this.day.value>31) {
				error = 'Please enter a valid day (1-31).';
			} else if (this.month.value<1 || this.month.value>12) {
				error = 'Please enter a valid month (1-12).';
			} else if (this.year.value<1900 || this.year.value>date.getFullYear()) {
				error = 'Please enter a valid year (1900-'+date.getFullYear()+').';
			} else {
				this.dob.value = this.month.value+'/'+this.day.value+'/'+this.year.value;
				var test = new Date(this.dob.value);
				var today = new Date();
				if (isNaN(test) || test > today) {
					error = 'Please enter a valid date.';
				}
			}
		}

		if (error !== false) {
			this.advice.innerHTML = Translator.translate(error);
			this.advice.show();
			return false;
		}

		this.advice.hide();
		return true;
	}
});