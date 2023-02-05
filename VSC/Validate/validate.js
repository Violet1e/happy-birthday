function Validator(options) {

    function getParent(element, selector) {
        while(element.parentElement) {
            if (element.parentElement.matches(selector)) {
                return element.parentElement;   
            }
            element = element.parentElement;
        }
    }

    var selectorRules = {};

    // Function validate
    function validate(inputElement, rule) {
        // var errorElement = getParent(inputElement, '.form-group');   
        var errorElement = getParent(inputElement, options.formGroupSelector).querySelector('.form-message');
        var errorMessage;

        // Get rules of selector
        var rules = selectorRules[rule.selector];

        // Repeat rule and test
        for (var i = 0; i < rules.length; ++i) {
            switch (inputElement.type) {
                case 'radio':
                case 'checkbox':

                break;
                default:
                    errorMessage = rules[i](inputElement.value);
            }
            if (errorMessage) break;
        }
        if (errorMessage) {
            errorElement.innerText = errorMessage;
            getParent(inputElement, options.formGroupSelector).classList.add('invalid')  
        }else {
            errorElement.innerText = '';
            getParent(inputElement, options.formGroupSelector).classList.remove('invalid')  
        }

        return !errorMessage;
    }

    // Get element
    var formElement = document.querySelector(options.form);
    if (formElement) {
        
        // When submit form
        formElement.onsubmit = function(e) {
            e.preventDefault();

            var isFormValid = true;

            // Reapet rule and validate
            options.rules.forEach(function(rule) {
            var inputElement = formElement.querySelector(rule.selector);
            var isValid = validate(inputElement, rule);
            if (!isValid) {
                isFormValid = false;
            }
        });
        
        if (isFormValid) {
            // Case submit with javascipt
            if (typeof options.onSubmit === 'function') {            
                var enableInputs = formElement.querySelectorAll('[name]');
                var formValues = Array.from(enableInputs).reduce(function(values, input) {
                    values[input.name] = input.value
                    return values;
                }, {});              
                options.onSubmit(formValues);   
            } 
            
            // Case submit with default
            else {
                formElement.submit();
            }
        }

        }

        //  Repeat rule and handle
        options.rules.forEach(function(rule) {

            // Save rules
            if (Array.isArray(selectorRules[rule.selector])) {
                selectorRules[rule.selector].push(rule.test);
            } else { 
                selectorRules[rule.selector] = [rule.test];
            }


            var inputElement = formElement.querySelector(rule.selector);
            var errorElement = getParent(inputElement, options.formGroupSelector).querySelector('.form-message')
            if (inputElement) {
                // Blur input
                inputElement.onblur = function() {
                    validate(inputElement, rule);
                }

                // when input
                inputElement.oninput = function() {
                    errorElement.innerText = '';
                    getParent(inputElement, options.formGroupSelector).classList.remove('invalid')  
                }
            }
        })
    }
}

Validator.isRequired = function(selector, message) { 
    return {
        selector: selector,
        test: function(value) {
            return value.trim() ? undefined : message || 'Vui lòng nhập trường này';
        }
    }
}

Validator.isEmail = function(selector, message) {
    return {
        selector: selector,
        test: function(value) {
            var regex = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;
            return regex.test(value) ? undefined : message || 'Vui lòng nhập email';
        }
    }
}

Validator.minLength = function(selector, min, message) {
    return {
        selector: selector,
        test: function(value) {
            return value.length >= min ? undefined : message || 'Mật khẩu quá yếu';
        }
    }
}

Validator.isConfirmed = function(selector, getConfirmValue, message) {
    return {
        selector: selector,
        test: function(value) {
            return value === getConfirmValue() ? undefined : message || 'Giá trị nhập không chính xác'; 
        }
    }
}