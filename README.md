# AIS-Can-You-Hack-It-Solutions
Solutions to the AIS Can You Hack It challenges.

## Solutions
### Client-side Protections
#### Disabled (10 points)
The submit button is disabled.
You can either inspect it in the browser and remove the `disabled` property, or run the following command in the console:

```JavaScript
document.querySelector("button[disabled][ref='submitButton']").disabled = false;
```

After the button is enabled, just click it.

#### Button Clicker (15 points)
The "Click me a lot" button needs to be clicked 1000000 times before the Submit button will be accepted.
However looking at the Network tab in the developer tools we can see the source code for `button_clicker.js`, which shows us the number of clicks is tracked with the variable `ButtonClicker_num_clicks`.
There's also an extra security check if we simply set the value to greater than 1000000 without clicking the button: a local storage boolean `"ButtonClicker_hacking_detected"` which is set to `true` every 100ms with a timer `ButtonClicker_timerId`.

We can bypass both with the following command in the console:

```JavaScript
ButtonClicker_num_clicks = 1000000;
clearInterval(ButtonClicker_timerId);
localStorage.setItem("ButtonClicker_hacking_detected", false);
```

Then just click submit.

#### Weird Input (25 points)
Every time we try to enter the requested string, the input values get changed to all `'a'`s.
We can look at the Network tab in the developer tools and see the source code for `weird_input.js`, which shows us the function `WeirdInput_handle_input` is changing the values.
We could override this function, or more easily override the submit function with the following command in the console:


```JavaScript
function WeirdInput_submit(tag) {
    let input = $(tag.refs.answer);
    input.val(document.querySelector("code").textContent);
    let promise = $.Deferred();
    return promise.resolve();
}
```

After which we can just click submit.

#### Paid Content (50 points)
Clearly we need to flip come variable to say we are a paid user. But where? Looking for a source js file for this challenge turns out it's quite well obfuscated.
However, if we click the submit button we see a POST request is sent, and we can inspect the payload in the Network tab.
We see it contains an `"answer"` key, which contains a string of a JSON. Amongst the keys of this JSON is `"paid"` which is a boolean set to `false`.
So to hack this challenge we can copy the same request, but change the `"paid"` value to `true`.
We can do this by just right-clicking the request in the Network tab and choosing Copy > Copy as fetch.
The `"answer"` field is in the request `"body"` and is url encoded. So look for the subsgtring `"%22paid%22%3Afalse"`, which decodes to `"paid":false` and replace it with `"%22paid%22%3Atrue"`"
Execute the fetch command in the Console tab, then refresh the page to complete the challenge.

### Programming
#### Birthday (15 points)
Clicking the "Submit" button doesn't work, and looking at birthday.js we see there is a `Birthday_submit` function which first checks the `sha256` hashof the current date to the birthday's hash before submitting it. Overriding this to force a submit doesn't work.
But this means we have a `sha256` hash value that will match the birthday string. With 365 possible birthdays per year, this means there are less than 36500 in the last hundred years, so we cna easily brute force a solutions.
We can do this by running the following command in the console:

```
for(var idd=0; idd<31; idd++){
    //console.log(dd);
    for(var imm=0;imm<=12;imm++){
        for(var iyyyy=2024;iyyyy>=1900;iyyyy--){
            var dd = String(idd).padStart(2, '0');
            var mm = String(imm).padStart(2, '0'); //January is 0!
            var yyyy = iyyyy;
            today = `${mm}/${dd}/${yyyy}`;
            
            var result = sha256(today.toString());
        
            if (result === Birthday_date_hash){
                console.log(today);
                birthday = today;
            }
        }
    }
}
```

And we can finish up by overriding the `Birthday_get_today` function to return the value we found:

```
function Birthday_get_today() {
    return today;
}
```

After which we can just click submit.
