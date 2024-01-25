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

```JavaScript
for(var idd=0; idd<31; idd++){
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

```JavaScript
function Birthday_get_today() {
    return today;
}
```

After which we can just click submit.


#### Secure OTP (75 points)
It seems a new random 6-digit OTP is generated every minute, and we don't have access to the phone receiving the OTP. When we try brute-forcing we're blocked, so it seems an impossible task.
However, if we click the "Submit" button, sending a bad submit, we'll get the following hints:
- In the console log we get the following message: `[MySecureOTP][DEBUG]: TODO REMOVE THIS: Seed is: 1705355344`, so we have the seed value for the random number generator, so if we can figure out which random number generator is being used, and how it's used to construct the OTP, then we could solve the puzzle.
- If we send if a few bad submits we get an error message in the GUI saying `"Hint: Each digit of the OTP is chosen randomly with randint(0, 9) from left to right."`, since `randint` is a Python function we should try that.

Looking through the source on `secure_otp.js` we can figure out another quick way to get the seed, with the following command in the console:

```JavaScript
console.log($("#" + SecureOTP_oid)[0]._tag.challenge.seed);
```

Now using a Python shell we can run the following command to implement the hints we received:

```Python
seed = 1705355344 # change this to whatever seed value you have
import random
random.seed(seed)
print(''.join(map(str,[random.randint(0, 9) for i in range(6)])))
```

Pasting the result into the OTP box and pressing the "Submit" button completes the challenge.
Make sure to not let the time run out between getting the `seed` value and submitting the answer.


#### Code Breaker (150 points)
The instructions are pretty straightforeward. After opening the problem the Console also has a messaging telling us to use `CodeBreaker_submit(code)` to submit programmatically.
The following command will crack the code:

```JavaScript
async function break_code(){
    var res = "0000000";
    var score = await CodeBreaker_submit(res);
    for(var i = 0; i < 7; i++){
        for (var d = 0; d < 10 + 26*2; d++){
            var v = String(d);
            if (d >= 10) v = String.fromCharCode(d-10+'a'.charCodeAt(0));
            if (d >= 10+26) v = String.fromCharCode(d-10-26+'A'.charCodeAt(0));
            res = res.substring(0, i) + v + res.substring(i+1);
            var val = await CodeBreaker_submit(res);
            console.log(res);
            console.log(val);
            if (val > score){
                score = val;
                break;
            }
        }
    }
    console.log("Complete. Code is:");
    console.log(res);
    return res;
}
```

The code will also submit, so there's nothing else to do!


#### Tiles (250 points)
Here we have a 5x5 sliding tile puzzle which needs to be solved in under 2 minutes, and with less than 350 moves. Very difficult for a human to achieve.
As it turns out, the search space size (`(5*5)!`) makes it difficult for most search algorithms we throw at it.
However I found using some human-style analysis to get the puzzle close to a finished state, then throwing A-star search at it works pretty well.

Start off by grabbing the board state in a list-of-lists format. We can do this with the following snippet of JavaScript in the console:

```JavaScript
console.log(JSON.stringify(Tiles_getGameBoard()));
```

Then use the SlidingTileSolver.ipynb Jupyter Notebook to run the algorithms for solving the problem. A description of how the algorithms work is inside the notebook.

The result will be a comma-separated string of moves, with can be pasted into the input box and clicking the Submit button completes it.


### Networking
#### HTTP Basic (15 points)
The standard tools for analyzing pcaps is Wireshark. We can use the commandline tool `tshark`.
Documentation is [here](https://www.wireshark.org/docs/man-pages/tshark.html).

In particular we'll want to find all HTTP requests with a body, i.e. POST requests, and extract the body and look for the username and password.


```Bash
tshark -r http-auth.cap -Y "http.request.method == POST" -T fields -e text
```

- `-r` is to read the .cap file.
- `-Y` is the filter the packets, in this case to POST requests.
- `-T` is specify the output format, in this case the fields
	- `-e` is to specificly out them as plain text.

Or for a more legible output:

```Bash
tshark -r http-auth.cap -Y "http.request.method == POST" -T fields -e urlencoded-form.key -e urlencoded-form.value | python3.11 -c "import sys;[print('\n'.join(map(': '.join,zip(*[col.split(',') for col in line.split('\t')])))) for line in sys.stdin.read().splitlines()]"
```

From this output we can get the form values, and see the fields `"name"` and `"pass"`, from which we get out answer.
Just past them in and click Submit.


#### WPA2 Deauth
This time we are asked to crack a WPA2 handshake from the wifi using the pcap.
The main tool used to do this is `aircrack-ng`, though it requires a wordlist for its cracking.
A popular choice is the RockYou password list, which can be downloaded [here](https://github.com/brannondorsey/naive-hashcat/releases/download/data/rockyou.txt).
Afterwards just run the command:


```Bash
aircrack-ng -w rockyou.txt de-auth.cap 
```

It should first present the MAC address (BSSID) and the SID (ESSID), before starting the crack, which should take a few minutes before presenting the password.


### Steganography
#### Frequency Analysis (25 points)
We are given a file `flagged-waveform` with no file extension, but looking at the file's binary in a hexdump, we quickly see it's starts with the file signature `RIFF` and `WAVEfmt`, indicating it's a `.wav` file, and indeed we can open it with music player apps.
You can find a good list of file signature [here](https://en.wikipedia.org/wiki/List_of_file_signatures).

```Bash
xxd flagged-waveform | head
```

Listening to it, it sounds like a sequence of sine waves of different frequencies. And indeed if we open it with a waveform viewing tool like Audacity, we see exactly that, along with the length of each frequency section being exactly 1s.
We can extract the sequence of frequency values using a Fourier transform tool, in particular we want some kind of spectrograph. A convenient way to to this is with Python's `scipy` library, so we can control exactly for the spectrogram is created and then we can work with the data extracted. In particular, simple converting it to ASCII gives us the flag.
We can use the code below:

```Python
import scipy.io.wavfile
import scipy.signal
rate, data = scipy.io.wavfile.read('flagged-waveform')
f, t, Sxx = scipy.signal.spectrogram(data, fs=rate, nperseg=rate, noverlap=0)
freqs = Sxx.argmax(axis=0)
message = ''.join(map(chr,freqs))
print(message)
```

Or use the FrequencyAnalysisSolver.ipynb Jupyter Notebook to accomplish the same thing, with a Matplotlib visualization of the spectrogram as well.


### Crypto
#### Skip Cipher (25 points)
From the looks of the text and the title, we can conclude that to decrypt the text we need to start with the first letter (which is the only one capitalized after all), then step some number of letters before taking the next letter and repeat until we cover the entire string, wrapping as needed.
The skip stride length should be coprime to the encrypted text so as to hit each letter once, but we can also check each possible stride.
We can get a wordlist of common English words and check which candidate solution contains the most English words, because that's very likely our solution.

Here's the Python code to solve the problem. We can also use the attached SkipCipherSolver.ipynb Jupyter Notebook as well.

```Python
cipher_text = "Irntfsnie  dp aav sgr  en toeedyleh.easosdkhndnesw a"
n = len(cipher_text)

import requests
r = requests.get("https://www.mit.edu/~ecprice/wordlist.10000")
#r = requests.get('https://raw.githubusercontent.com/first20hours/google-10000-english/master/google-10000-english.txt')
wordlist = set(r.text.splitlines())

plain_text = ''
wordcount = 0
solution_stride = 0
for stride in range(n):
    decoded = ''.join(cipher_text[(stride*i)%n] for i in range(n))
    decoded_wordcount = sum(w in wordlist for w in decoded.split(' '))
    if decoded_wordcount > wordcount:
        wordcount = decoded_wordcount
        solution_stride = stride
        plain_text = decoded
print('stride:', solution_stride)
print(plain_text)
```

#### Encoded (75 points)
As the hint says, the data isn't encrypted, but is encoded, several times. We need to recognize the forms of encoding in order to decode the flag.

1. The given string contains only digits and letters a-f, which implies it's byte data encoded in hexadecimal. We can use Python's `bytearray.fromhex` to decode to bytes.
2. The bytes starts with the bytes for PK, the file signature for zip files. We can use Python's `zipfile` library, which indeed shows we have a zip archive containing a file `flag.txt`, which contains our next encoded string.
3. The string contains digits, uppercase and lowercase letters, as well as the `+` and `/` characters, which is the set of characters for base64 encoding. We can use Python's `base64` library to decode to bytes.
4. The bytes starts with the bytes for BZhm the file signature for bzip2 compressed data. We can use Python's `bz2` library to decompress to bytes.
5. The bytes are an ascii string for groups of space-separated strings of 1s and 0s. Clearly these represent bytes. With Python we can split the string by spaces and for each binary string interpret it as binary to integer using `int(c,2)`.
6. Interpreting the byte string as ascii contains only digits and letters a-f, which implies it's byte data encoded in hexadecimal, same as step 1. Using Python's `bytearray.fromhex` again, gives us the flag.

The EncodedSolver.ipynb Jupyter Notebook will perform all the steps, and show the outputs after each step.
