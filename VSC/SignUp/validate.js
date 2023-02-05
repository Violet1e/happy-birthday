function Validator(formSelector) {
    var _this = this;
    var formRules = {};

    function getParent(element, selector) {
        while(element.parentElement) {
            if (element.parentElement.matches(selector)) {
                return element.parentElement;   
            }
            element = element.parentElement;
        }
    }

     
    var validatorRules = {
        required: function(value) {
            return value ? undefined : 'Vui long nhap truong nay';
        },
        email: function(value) {
            var regex = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;
            return regex.test(value) ? undefined : 'Vui long nhap email nay';
        },
        min: function(min) {
            return function(value) {
                return value.length >= min ? undefined : 'Vui long nhap it nhat ${min}';
            }
        },
        // confirmed: function(value) {
        //     return value === getConfirmValue() ? undefined : message || 'Giá trị nhập không chính xác';
        // }
    };

    var ruleName = 'required';

    // Get element in DOM
    var formElement = document.querySelector(formSelector);

    // handle when have element
    if (formElement) {
        var inputs = formElement.querySelectorAll('[name][rules]');
        for (var input of inputs) {

            var rules = input.getAttribute('rules').split('|');
            for (var rule of rules) {
                var ruleInfo;
                var isRuleHasValue = rule.includes(':');
                
                if (isRuleHasValue) {
                    ruleInfo = rule.split(':');
                    rule = ruleInfo[0];
                }

                var ruleFunc = validatorRules[rule];
                if (isRuleHasValue) {
                    ruleFunc = ruleFunc(ruleInfo[1]);
                }

                if (Array.isArray(formRules[input.name])) {
                    formRules[input.name].push(ruleFunc)
                } else {
                    formRules[input.name] = [ruleFunc];
                }
            }

            // Lắng nghe sự kiện 
            input.onblur = handleValidate;
            input.oninput = handleClearError;
        }

        // Hàm thực hiện validate
        function handleValidate(event) {
            var rules = formRules[event.target.name];
            var errorMessage;

            for (var rule of rules) {
                errorMessage =  rule(event.target.value);
                if (errorMessage) break;
            }

            // Nếu có lỗi
            if (errorMessage) {
                var formGroup = getParent(event.target, '.form-group');
                if (formGroup) {
                    formGroup.classList.add('invalid');
                    var formMessage = formGroup.querySelector('.form-message');
                    if (formMessage) {
                        formMessage.innerText = errorMessage;
                    }
                }
            }

            return !errorMessage;
        }

        // Hàm clear message lỗi
        function handleClearError(event) {
            var formGroup = getParent(event.target, '.form-group');
            if (formGroup.classList.contains('invalid')) {
                formGroup.classList.remove('invalid');
                var formMessage = formGroup.querySelector('.form-message');

                if (formMessage) {
                        formMessage.innerText = '';
                }
            }
        }
    }

    //  Xử lý hành vi submit form
    formElement.onsubmit = function(event) {
        event.preventDefault();
        

        var inputs = formElement.querySelectorAll('[name][rules]');
        var isValid = true;

        for (var input of inputs) {

            if (!handleValidate({target: input,})) {
                isValid = false;
            }
        }
        
        // Khi không có lỗi thì submit form
        if (isValid) {        
            if (typeof _this.onSubmit === 'function') {
                _this.onSubmit(formValue);
            } else {
                formElement.submit();
            }
        }
    }
}